#ifndef METRIC_DATA_TYPES_H
#define METRIC_DATA_TYPES_H

#include <iostream>
#include <string>

enum class MetricDataTypes : char {
    INTEGER = 'i',
    BOOL = 'b',
    DECIMAL = 'd',
    TEXT = 't'
};


MetricDataTypes from_str_convert_to_metric_item_types(std::string metric_data_type_str) {
    MetricDataTypes metric_data_type;
    if (metric_data_type_str == "i") {
        metric_data_type = MetricDataTypes::INTEGER;
    } else if (metric_data_type_str == "b") {
        metric_data_type = MetricDataTypes::BOOL;
    } else if (metric_data_type_str == "d") {
        metric_data_type = MetricDataTypes::DECIMAL;
    } else if (metric_data_type_str == "t") {
        metric_data_type = MetricDataTypes::TEXT;
    }
    return metric_data_type;
}


std::string from_metric_item_types_to_str(MetricDataTypes mdi) {
    std::string output;
    if (mdi == MetricDataTypes::INTEGER) {
        output = "i";
    } else if (mdi == MetricDataTypes::BOOL) {
        output = "b";
    } else if (mdi == MetricDataTypes::DECIMAL) {
        output = "d";
    } else if (mdi == MetricDataTypes::TEXT) {
        output = "t";
    }
    return output;
}


#endif // METRIC_DATA_TYPES_H

