#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <optional>

#include "item_type.h"
#include "metric_data_item.h"


class Item {
public:
    ItemTypes kind;
    std::string name;
    std::optional<MetricDataItem> metric;

    Item() {

    }

    Item(ItemTypes kind, std::string name, std::optional<MetricDataItem> metric = std::nullopt)
        : kind(kind), name(name), metric(metric) {}
};



/*
class Item { 
public:
   std::string name; 
};


class Item {
public:
    ItemTypes kind;
    std::string name;
    std::optional<MetricDataItem> metric;

    Item(
        ItemTypes kind,
        std::string name, 
        std::optional<MetricDataItem> metric = std::nullopt
        )
        : kind(kind), name(name), metric(metric) {}
};
*/
#endif // ITEM_H