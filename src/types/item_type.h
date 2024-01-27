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

#endif // ITEM_TYPE_H
