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
#include <decimal/decimal>

#include "metric_data_types.h"

using namespace std;

#define DEFAULT_DECIMAL_PRECISSION 2

struct MetricValueTypeUnion {
    int i_value;
    // decimal::decimal32 d_value;
    double d_value;
    bool b_value;
    // const char *t_value;
    string s_value;
};

class MetricValueTypeBuilder {
public:
    MetricValueTypeBuilder() : value_({0}) {}

    MetricValueTypeBuilder& set_integer_value(int value) {
        value_.i_value = value;
        decimal_precission_ = DEFAULT_DECIMAL_PRECISSION;
        return *this;
    }

    // MetricValueTypeBuilder& setd_value(decimal::decimal32 value) {
    MetricValueTypeBuilder& set_decimal_value(double value) {
        value_.d_value = value;
        return *this;
    }

    MetricValueTypeBuilder& set_decimal_precission(int value) {
        decimal_precission_ = value;
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

    MetricValueTypeBuilder& extract_value_from_str(string value) {
        //TODO: extract_value_from_str
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
        } else if (data_type_ == MetricDataTypes::DECIMAL) {
            stringstream ss;
            ss << fixed << setprecision(decimal_precission_) << value_.d_value;
            sprintf(output, "%s", ss.str().c_str());
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
