#ifndef ITEM_TYPE_H
#define ITEM_TYPE_H

#include <iostream>
#include <string>
#include <optional>

using namespace std;

enum class ItemTypes : char {
    TIMESTAMP_MILIS = 't',
    DEVICE_ID = 'd',
    METRIC_ITEM = 'm',
    HEALTH_CHECK = 'h'
};

/*
namespace item_type_ns {
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
}
*/
#endif // ITEM_TYPE_H
