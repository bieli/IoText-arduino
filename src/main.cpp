#include <iostream>
#include <variant>
#include <optional>
#include <vector>

#include "types/metric_data_item.h"
#include "types/item_type.h"
#include "types/item.h"
#include "codecs/item_codec.h"
#include "codecs/iot_ext_codec.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wno-volatile"
//<for loop>
#pragma GCC diagnostic pop

using namespace std;


int main() {
    vector<Item> items;
    Item item1 = Item(ItemTypes::TIMESTAMP_MILIS, "2900267526042");
    items.push_back(item1);

    Item item2 = Item(ItemTypes::DEVICE_ID, "devie_id_x3");
    items.push_back(item2);

    MetricDataItem mdi = MetricDataItem(MetricDataTypes::TEXT, "txt");
    Item item3 = Item(ItemTypes::METRIC_ITEM, "val", std::make_optional(mdi));
    items.push_back(item3);

    MetricDataItem mdi2 = MetricDataItem(MetricDataTypes::DECIMAL, "123.456");
    Item item4 = Item(ItemTypes::METRIC_ITEM, "metric_name", std::make_optional(mdi2));
    items.push_back(item4);

    MetricDataItem mdi3 = MetricDataItem(MetricDataTypes::BOOL, "1");
    Item item5 = Item(ItemTypes::METRIC_ITEM, "metric_boolean1", std::make_optional(mdi3));
    items.push_back(item5);

    MetricDataItem mdi4 = MetricDataItem(MetricDataTypes::INTEGER, "1234567890");
    Item item6 = Item(ItemTypes::METRIC_ITEM, "metric_integer9", std::make_optional(mdi4));
    items.push_back(item6);

    string encoded_payload = IoTextCodec::encode(items);
    cout << "Encoded payload: " << endl << encoded_payload << endl;
    string payload = encoded_payload;

    vector<Item> decoded_items = IoTextCodec::decode(payload);

    cout << endl << "Decoded items:" << endl;

    for (Item item : decoded_items) {
        cout << endl << "type: " << item.kind << " " << "│" << " name: " << item.name << endl;
        if (item.metric.has_value()) {
            MetricDataItem mdi = item.metric.value();
            cout << "        ╘═══ metric -> type: " << from_metric_item_types_to_str(mdi.data_type);
            cout << ", value: " << convert_from_metric_value_type_to_str(mdi.value) << endl;
        }
    }

    cout << "---------" << endl;

    return 0;
}
