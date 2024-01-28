#ifndef METRIC_DATA_ITEM_H
#define METRIC_DATA_ITEM_H

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <string>
#include <variant>
#include <optional>
#include <cstddef>
#include <cstdio>
#include <limits>
#include <sstream>
#include <cstring>

// #ifdef ENABLE_DECIMAL_TYPE
    // #include <decimal/decimal>
// #endif

#include "metric_data_types.h"
#include "helpers.h"

using namespace std;
// using namespace item_type_ns;

#define DEFAULT_DECIMAL_PRECISSION 2

#ifdef ENABLE_DECIMAL_TYPE
    struct decimal_struct {
        uint32_t fraction;
        uint32_t mantissa;
        int precission;
    };
#endif

struct MetricValueTypeUnion {
    int i_value;
#ifdef ENABLE_DECIMAL_TYPE
    // double d_value;
    decimal_struct decimal;
#endif
    bool b_value;
    string s_value;
};

class MetricValueTypeBuilder {
public:
    MetricValueTypeBuilder() {
        value_ = {0};
#ifdef ENABLE_DECIMAL_TYPE
        value_.decimal = decimal_struct {0, 0, 0};
#endif
    }

    MetricValueTypeBuilder& set_integer_value(int value) {
        value_.i_value = value;
        decimal_precission_ = DEFAULT_DECIMAL_PRECISSION;
#ifdef ENABLE_DECIMAL_TYPE
        value_.decimal = decimal_struct {0, 0, 0};
        value_.decimal.precission = decimal_precission_;
#endif
        return *this;
    }

#ifdef ENABLE_DECIMAL_TYPE
    MetricValueTypeBuilder& set_decimal_value(long double value) {
        // value_.d_value = value;

        // #define DECIMAL_MAX_DIGITS 10
        // char str_decimal[DECIMAL_MAX_DIGITS + sizeof(char)];
        // snprintf(str_decimal, "%f", value);

        ostringstream os; 
        os << fixed << setprecision(decimal_precission_) << value;
        string str_decimal = os.str(); 

        // ostringstream os; 
        // os << value; 
        // string str_decimal = os.str(); 

        update_decimal_from_str(str_decimal);

        return *this;
    }

    MetricValueTypeBuilder& set_decimal_value_from_parts(uint32_t fraction, uint32_t mantissa) {
        value_.decimal.fraction = fraction;
        value_.decimal.mantissa = prepare_mantissa_with_precission(mantissa, decimal_precission_);
        return *this;
    }

    MetricValueTypeBuilder& set_decimal_value_as_str(string value) {
        update_decimal_from_str(value);
        return *this;
    }

    void update_decimal_from_str(string str_decimal) {
        size_t pos = str_decimal.find('.');

        string fraction_str = str_decimal.substr(0, pos);
        string mantissa_str = str_decimal.substr(pos + 1, decimal_precission_);

        // cout << "str_decimal: " << str_decimal << endl;
        // cout << "fraction_str: " << fraction_str << endl;
        // cout << "mantissa_str: " << mantissa_str << endl;precission

        value_.decimal.fraction = stol(fraction_str);
        value_.decimal.mantissa = stol(mantissa_str);
    }

    uint32_t prepare_mantissa_with_precission(uint32_t mantissa, int precission) {
        ostringstream os; 
        os << mantissa;
        string str_mantissa = os.str();

        if (precission <= 0) {
            return stol(str_mantissa);
        }

        string str_mantissa_precission = str_mantissa.substr(0, precission);

        // cout << "str_mantissa: " << str_mantissa << endl;
        // cout << "str_mantissa_precission: " << str_mantissa_precission << endl;

        return stol(str_mantissa_precission);
    }
#endif
    MetricValueTypeBuilder& set_decimal_precission(int value) {
        decimal_precission_ = value;
#ifdef ENABLE_DECIMAL_TYPE
        value_.decimal.precission = decimal_precission_;
#endif
        return *this;
    }

    int get_decimal_precission() const {
        return decimal_precission_;
    }

    MetricValueTypeBuilder& set_bool_value(bool value) {
        value_.b_value = value;
        return *this;
    }

    MetricValueTypeBuilder& set_text_value(string value) {
        // value_.t_value = value.c_str();
        value_.s_value = value;
        return *this;
    }

    MetricValueTypeBuilder& extract_value_from_str(MetricDataTypes mdt, string value) {
        // cout << "[ DEBUG ] extract_value_from_str -> mdt: " << ItemTypeTool::from_metric_item_types_to_str(mdt) << ", value: " << value << endl;
        if (mdt == MetricDataTypes::INTEGER) {
            value_.i_value = stoi(value);
        } else if (mdt == MetricDataTypes::BOOL) {
            value_.b_value = strcmp(value.c_str(), "1") == 0 ? true : false;
#ifdef ENABLE_DECIMAL_TYPE
        } else if (mdt == MetricDataTypes::DECIMAL) {
            update_decimal_from_str(value);

            // stringstream ss;
            // ss << fixed << setprecision(decimal_precission_) << atof(value.c_str());
            ///// update_decimal_from_str(ss.str());
            // ss >> value_.d_value;
            // ss << static_cast<double>(value_.d_value);

            // double dbl = atof(value.c_str());
            // stringstream ss1;
            // ss1 << fixed << setprecision(decimal_precission_) << dbl;
            // TODO: set private field: decimal_precission_ in this code block
            // cout << "[ DEBUG ] extract_value_from_str -> input: " << value << ", converted:" << ss1.str().c_str() << endl;
#endif
        } else if (mdt == MetricDataTypes::TEXT) {
            value_.s_value = value;
        }
        return *this;
    }

    MetricValueTypeUnion build() const {
        return value_;
    }

    // TODO: maybe add operator<<?
    //friend ostream& operator<<(ostream& os, const MetricValueTypeUnion& value) {
    //    //os << "MetricValueTypeUnion: i_value: " << value.i_value;
    //    os << " AAAA ";
    //    return os;
    //}

    MetricValueTypeBuilder& display() {
        cout << "value_.i_value: " << value_.i_value << endl;
        return *this;
    }

private:
    MetricValueTypeUnion value_;
    int decimal_precission_;
};


class MetricDataItem {
public:
    MetricDataItem() {
        data_type_ = MetricDataTypes::NONE;
        value_ = MetricValueTypeBuilder().build();
    };

    MetricDataItem(const MetricDataTypes& data_type, const MetricValueTypeBuilder& value) {
        data_type_ = data_type;
        value_ = value.build();
        decimal_precission_ = value.get_decimal_precission();
    }

    const MetricDataTypes& get_metric_data_type() const {
        return data_type_;
    }

    const MetricValueTypeUnion& get_value() const {
        return value_;
    }

    const string get_value_as_str() const {
        char output[MAX_METRIC_DATA_TYPE_TEST__MAX_SIZE + 1];
        if (data_type_ == MetricDataTypes::INTEGER) {
            sprintf(output, "%d", value_.i_value);
        } else if (data_type_ == MetricDataTypes::BOOL) {
            sprintf(output, "%s", value_.b_value == true ? "1" : "0");
#ifdef ENABLE_DECIMAL_TYPE
        } else if (data_type_ == MetricDataTypes::DECIMAL) {
            // stringstream ss;
            // ss << fixed << setprecision(decimal_precission_) << value_.d_value;
            // string tmp_value = ItemTypeTool::remove_trailing_zeros_from_str_decimal(ss.str());
            // sprintf(output, "%s", tmp_value.c_str());

            // #include <sstream>

            // #define SSTR( x ) static_cast< std::ostringstream & >( \
            //         ( std::ostringstream() << std::dec << x ) ).str()

            //         int i = value_.decimal.mantissa;
            //         std::string ssss = SSTR( value_.decimal.mantissa );

            // // TODO: string tmp_value = ItemTypeTool::remove_trailing_zeros_from_str_decimal(ss.str());
            // string tmp_value = ItemTypeTool::remove_trailing_zeros_from_str_decimal(ssss);
            // sprintf(output, "%d.%d", value_.decimal.fraction, tmp_value);

            sprintf(output, "%d.%d", value_.decimal.fraction, value_.decimal.mantissa);
#endif
        } else if (data_type_ == MetricDataTypes::TEXT) {
            sprintf(output, "%s", (char *) value_.s_value.c_str());
        } else if (data_type_ == MetricDataTypes::NONE) {
            sprintf(output, "%s", " ");
        }
        return output;
    }

private:
    MetricDataTypes data_type_;
    MetricValueTypeUnion value_;
    int decimal_precission_;
};

#endif // METRIC_DATA_ITEM_H
