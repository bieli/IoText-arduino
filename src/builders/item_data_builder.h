#ifndef IOT_EXT_ITEM_DATA_BUILDER_H
#define IOT_EXT_ITEM_DATA_BUILDER_H

#include <string>
#include <optional>
#include <vector>

#include "../types/metric_data_types.h"
#include "../types/metric_data_item.h"

using namespace std;


class IoTextItemDataBuilder {
public:
    IoTextItemDataBuilder(long long int timestamp, string device_name) {
        timestamp_ = timestamp;
        device_name_ = device_name;
        char buffer[128];

        items_.clear();

        sprintf(buffer, "%d", timestamp_);
        Item timestamp_item = Item(
            ItemTypes::TIMESTAMP_MILIS, 
            buffer
        );
        items_.push_back(timestamp_item);

        Item device_name_item = Item(
            ItemTypes::DEVICE_ID, 
            device_name_
        );
        items_.push_back(device_name_item);
    };

    IoTextItemDataBuilder& add_measure(string metric_name, MetricDataItem metric_data_item) {
        Item item3 = Item(ItemTypes::METRIC_ITEM, metric_name, metric_data_item);
        items_.push_back(item3);
        return *this;
    }

    string build() const {
        return IoTextCodec::encode(items_);
    }
private:
    long long int timestamp_;
    vector<Item> items_;
    string device_name_;
    vector<MetricDataItem> metrics_;
};

#endif // IOT_EXT_ITEM_DATA_BUILDER_H
