#include <iostream>
#include <variant>
#include <optional>
#include <vector>

// #define ENABLE_DECIMAL_TYPE

#include "src/types/metric_data_item.h"
#include "src/types/item_type.h"
#include "src/types/item.h"
#include "src/codecs/item_codec.h"
#include "src/codecs/iot_ext_codec.h"

using namespace std;


int main() {
    MetricValueTypeUnion mvtu = MetricValueTypeBuilder()
        .set_integer_value(123)
        .display()
        .build();

    vector<Item> items;
    Item item1 = Item(ItemTypes::TIMESTAMP_MILIS, "2900267526042");
    items.push_back(item1);

    Item item2 = Item(ItemTypes::DEVICE_ID, "devie_id_x3");
    items.push_back(item2);

    MetricDataItem mdi = MetricDataItem(
        MetricDataTypes::TEXT,
        MetricValueTypeBuilder()
            .set_text_value(string("txt"))
    );
    Item item3 = Item(ItemTypes::METRIC_ITEM, "val", mdi);
    items.push_back(item3);

#ifdef ENABLE_DECIMAL_TYPE
    MetricDataItem mdi2 = MetricDataItem(
        MetricDataTypes::DECIMAL,
        MetricValueTypeBuilder()
            .set_decimal_value(1234567890.12345678901234567890)
            .set_decimal_precission(3)
    );
    Item item4 = Item(ItemTypes::METRIC_ITEM, "metric_name", mdi2);
    items.push_back(item4);
#endif

    MetricDataItem mdi3 = MetricDataItem(
        MetricDataTypes::BOOL,
        MetricValueTypeBuilder()
            .set_bool_value(true)
    );
    Item item5 = Item(ItemTypes::METRIC_ITEM, "metric_boolean1", mdi3);
    items.push_back(item5);

    MetricDataItem mdi4 = MetricDataItem(
        MetricDataTypes::INTEGER, 
        MetricValueTypeBuilder()
            .set_integer_value(3333)
    );
    Item item6 = Item(ItemTypes::METRIC_ITEM, "metric_integer9", mdi4);
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
            cout << "        ╘═══ metric -> type: " << from_metric_item_types_to_str(mdi.get_metric_data_type());
            cout << ", value: " << mdi.get_value_as_str() << endl;
        }
    }

    cout << "---------" << endl;

    return 0;
}
