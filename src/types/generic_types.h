#pragma once
#ifndef GENERIC_TYPES_H
#define GENERIC_TYPES_H

// #################################################################################
// ### Generic types are inspired by: https://github.com/hideakitai/ArxContainer ###
// #################################################################################

#include <stddef.h>
#ifdef ARDUINO
#include <Arduino.h>
#else
#include <string>
#endif

#ifdef INT5
// avoid conflict with interrrupt macro on e.g. Arduino Mega. This
// should not break code that rely on this constant, by keeping the
// value available as a C++-level constant. This first allocates a
// temporary constant, to capture the value before undeffing, and
// then defines the actual INT5 constant. Finally, INT5 is redefined
// as itself to make sure #ifdef INT5 still works.
static constexpr uint8_t INT5_TEMP_VALUE = INT5;
#undef INT5
static constexpr uint8_t INT5 = INT5_TEMP_VALUE;
#define INT5 INT5
#endif

#include <ArxTypeTraits.h>
#include <ArxContainer.h>

namespace arduino {

#if ARX_HAVE_LIBSTDCPLUSPLUS >= 201103L  // Have libstdc++11

    using idx_t = std::vector<size_t>;
    template <typename T>
    using arr_t = std::vector<T>;
    template <typename T, size_t N>
    using fix_arr_t = std::array<T, N>;
    template <typename T, typename U>
    using map_t = std::map<T, U>;
    template <typename T>
    using bin_t = std::vector<
        typename std::enable_if<std::is_same<T, uint8_t>::value || std::is_same<T, char>::value, T>::type,
        std::allocator<T> >;

#else  // Do not have libstdc++11

#ifndef MAX_PACKET_BYTE_SIZE
#define MAX_PACKET_BYTE_SIZE 128
#endif  // MAX_PACKET_BYTE_SIZE
#ifndef MAX_ARRAY_SIZE
#define MAX_ARRAY_SIZE 8
#endif  // MAX_ARRAY_SIZE
#ifndef MAX_MAP_SIZE
#define MAX_MAP_SIZE 8
#endif  // MAX_MAP_SIZE
#ifndef MAX_OBJECT_SIZE
#define MAX_OBJECT_SIZE 32
#endif  // MAX_OBJECT_SIZE

    using idx_t = arx::vector<size_t, MAX_OBJECT_SIZE>;
    template <typename T, size_t N = MAX_ARRAY_SIZE>
    using arr_t = arx::vector<T, N>;
    template <typename T, size_t N>
    using fix_arr_t = arx::array<T, N>;
    template <typename T, typename U, size_t N = MAX_MAP_SIZE>
    using map_t = arx::map<T, U, N>;
    template <typename T, size_t N = MAX_PACKET_BYTE_SIZE>
    using bin_t = arx::
        vector<typename std::enable_if<std::is_same<T, uint8_t>::value || std::is_same<T, char>::value, T>::type, N>;

#endif  // Do not have libstdc++11

#ifdef ARDUINO
    using str_t = String;
#else
    using str_t = std::string;
#ifndef F
    inline const char* F(const char* c) {
        return c;
    }
#endif
#endif

    namespace type {
        class ArraySize {
            size_t sz;

        public:
            explicit ArraySize(const size_t size = 0) : sz(size) {}
            size_t size() const {
                return sz;
            }
            void size(const size_t s) {
                sz = s;
            }
        };
        class MapSize {
            size_t sz;

        public:
            explicit MapSize(const size_t size = 0) : sz(size) {}
            size_t size() const {
                return sz;
            }
            void size(const size_t s) {
                sz = s;
            }
        };
    }  // namespace type

    using arr_size_t = type::ArraySize;
    using map_size_t = type::MapSize;

    namespace object {
        struct nil_t {
            bool is_nil {false};
            nil_t& operator=(const nil_t& rhs) {
                this->is_nil = rhs.is_nil;
                return *this;
            }
            nil_t& operator=(const bool b) {
                this->is_nil = b;
                return *this;
            }
            bool operator()() const {
                return this->is_nil;
            }
            bool operator==(const nil_t& x) {
                return (*this)() == x();
            }
            bool operator!=(const nil_t& x) {
                return !(*this == x);
            }
        };

        class ext {
            bin_t<uint8_t> m_data;

        public:
            ext() : m_data() {}
            ext(int8_t t, const uint8_t* p, uint32_t s) {
                m_data.reserve(static_cast<size_t>(s) + 1);
                m_data.push_back(static_cast<uint8_t>(t));
                m_data.insert(m_data.end(), p, p + s);
            }
            ext(int8_t t, uint32_t s) {
                m_data.resize(static_cast<size_t>(s) + 1);
                m_data[0] = static_cast<char>(t);
            }
            int8_t type() const {
                return static_cast<int8_t>(m_data[0]);
            }
            const uint8_t* data() const {
                return &(m_data[0]) + 1;
            }
            uint8_t* data() {
                return &(m_data[0]) + 1;
            }
            uint32_t size() const {
                return static_cast<uint32_t>(m_data.size()) - 1;
            }
            bool operator==(const ext& x) const {
                return m_data == x.m_data;
            }
            bool operator!=(const ext& x) const {
                return !(*this == x);
            }
        };

        struct timespec {
            int64_t tv_sec;    // seconds
            uint32_t tv_nsec;  // nanoseconds

            bool operator==(const timespec& x) const {
                return (tv_sec == x.tv_sec) && (tv_nsec == x.tv_nsec);
            }
            bool operator!=(const timespec& x) const {
                return !(*this == x);
            }
            bool operator<(const timespec& x) const {
                if (tv_sec < x.tv_sec)
                    return true;
                else if (tv_sec > x.tv_sec)
                    return false;
                else
                    return tv_nsec < x.tv_nsec;
            }
            bool operator>(const timespec& x) const {
                return (*this != x) && (*this < x);
            }
        };

    }  // namespace object

}  // namespace arduino


#endif  // GENERIC_TYPES_H