#ifndef ITEM_TYPE_TOOL_H
#define ITEM_TYPE_TOOL_H

#include "item_type.h"

using namespace std;

class ItemTypeTool {
public:
    static ItemTypes from_str_convert_to_item_types(string item_type_str) {
        ItemTypes item_type;
        if (item_type_str == "t") {
            item_type = ItemTypes::TIMESTAMP_MILIS;
        } else if (item_type_str == "d") {
            item_type = ItemTypes::DEVICE_ID;
        } else if (item_type_str == "m") {
            item_type = ItemTypes::METRIC_ITEM;
        } else if (item_type_str == "h") {
            item_type = ItemTypes::HEALTH_CHECK;
        }
        return item_type;
    }

    static string from_item_types_convert_to_str(ItemTypes item_type) {
        string output;
        switch (item_type) {
            case ItemTypes::TIMESTAMP_MILIS:
                output = "t";
                break;
            case ItemTypes::DEVICE_ID:
                output = "d";
                break;
            case ItemTypes::METRIC_ITEM:
                output = "m";
                break;
            case ItemTypes::HEALTH_CHECK:
                output = "h";
                break;
            default:
                output = " ";
                break;
        }
        return output;
    }

    static string from_metric_item_types_to_str(MetricDataTypes mdi) {
        string output;
        if (mdi == MetricDataTypes::INTEGER) {
            output = "i";
        } else if (mdi == MetricDataTypes::BOOL) {
            output = "b";
        } else if (mdi == MetricDataTypes::DECIMAL) {
            output = "d";
        } else if (mdi == MetricDataTypes::TEXT) {
            output = "t";
        } else if (mdi == MetricDataTypes::NONE) {
            output = " ";
        }
        return output;
    }

    static MetricDataTypes from_str_convert_to_metric_data_types(string metric_data_type_str) {
        MetricDataTypes metric_data_type;
        if (metric_data_type_str == "i") {
            metric_data_type = MetricDataTypes::INTEGER;
        } else if (metric_data_type_str == "b") {
            metric_data_type = MetricDataTypes::BOOL;
        } else if (metric_data_type_str == "d") {
            metric_data_type = MetricDataTypes::DECIMAL;
        } else if (metric_data_type_str == "t") {
            metric_data_type = MetricDataTypes::TEXT;
        } else if (metric_data_type_str == " ") {
            metric_data_type = MetricDataTypes::NONE;
        }
        return metric_data_type;
    }

    static std::string remove_trailing_zeros_from_str_decimal(const std::string &decimal_value) {
        if (decimal_value.find('.') != std::string::npos) {
            std::string result = decimal_value;
            while (!result.empty() && result.back() == '0')
            {
                result.pop_back();
            }
            if (!result.empty() && result.back() == '.')
            {
                result.pop_back();
            }
            return result;
        }
        return decimal_value;
    }
};


#endif // ITEM_TYPE_TOOL_H
