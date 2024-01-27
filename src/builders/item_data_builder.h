
#ifndef IOT_EXT_ITEM_DATA_BUILDER_H
#define IOT_EXT_ITEM_DATA_BUILDER_H

#include <string>
#include <optional>
#include <vector>

#include "../types/metric_data_types.h"
#include "metric_data_item.h"


// TODO: this is only prototype - NEED TO BE IMPL.
class IoTextItemDataBuilder {
public:
    IoTextItemDataBuilder(int timestamp, std::string device_name) :
        timestamp_(timestamp), device_name_(device_name) {};

    void add_measure(std::string metric_name, MetricValueType value) {
        // metrics.push_back(MetricDataItem( ... ))
    }
private:
    int timestamp_;
    std::string device_name_;
    std::vector<MetricDataItem> metrics_;
}

#endif // IOT_EXT_ITEM_DATA_BUILDER_H
