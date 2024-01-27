#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "item_type.h"
#include "metric_data_item.h"
#include "optional.h"

class Item {
public:
    ItemTypes kind;
    string name;
    Optional<MetricDataItem> metric;

    Item() {

    }

    Item(ItemTypes kind, string name, Optional<MetricDataItem> metric = Optional<MetricDataItem>())
        : kind(kind), name(name), metric(metric) {}
};

#endif // ITEM_H