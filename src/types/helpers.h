#ifndef ITEM_TYPE_TOOL_H
#define ITEM_TYPE_TOOL_H

#include "item_type.h"


class ItemTypeTool {
public:
    static ItemTypes from_str_convert_to_item_types(std::string item_type_str) {
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

    static std::string from_metric_item_types_to_str(MetricDataTypes mdi) {
        std::string output;
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

    static MetricDataTypes from_str_convert_to_metric_data_types(std::string metric_data_type_str) {
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
};


std::string operator+(const std::string& str, ItemTypes item_type) {
    return str + static_cast<char>(item_type);
}

std::ostream& operator<<(std::ostream& os, ItemTypes item_type) {
    switch (item_type) {
        case ItemTypes::TIMESTAMP_MILIS:
            os << "t";
            break;
        case ItemTypes::DEVICE_ID:
            os << "d";
            break;
        case ItemTypes::METRIC_ITEM:
            os << "m";
            break;
        case ItemTypes::HEALTH_CHECK:
            os << "h";
            break;
        default:
            os.setstate(std::ios_base::failbit);
            break;
    }
    return os;
}

#endif // ITEM_TYPE_TOOL_H
