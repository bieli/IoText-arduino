#ifndef OPTIONAL_H
#define OPTIONAL_H

#pragma once

template <typename T>
class Optional {
public:
    Optional() : hasValue_(false) {}
    Optional(T value) : value_(value), hasValue_(true) {}

    bool has_value() const {
        return hasValue_;
    }

    T value_or(T defaultValue) const {
        return hasValue_ ? value_ : defaultValue;
    }

    T value() const {
        return value_;
    }
private:
    T value_;
    bool hasValue_;
};

#endif // OPTIONAL_H