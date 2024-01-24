#ifndef ITEM_TYPE_H
#define ITEM_TYPE_H

#include <iostream>
#include <string>
#include <optional>

//#include "metric_data_item.h"

enum class ItemTypes : char {
    TIMESTAMP_MILIS = 't',
    DEVICE_ID = 'd',
    METRIC_ITEM = 'm',
    HEALTH_CHECK = 'h'
};


ItemTypes from_str_convert_to_item_types(std::string item_type_str) {
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


#endif // ITEM_TYPE_H
