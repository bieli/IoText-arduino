/**
 * IoText data protocol library for Arduino and PlatformIO embedded platforms
 * https://github.com/bieli/IoText-arduino
 *
 * Apache 2.0 License
 * (c) 2023 Marcin Bielak
**/

#include "IoText.h"


IoText::IoText() {
}

IoText::~IoText() {
}

char* IoText::build(unsigned long timestamp, char* device_name) {
    sprintf(buffer, "t|%ld,d|%s", timestamp, device_name);
    return buffer;
}

string IoText::encode_test() {
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

    return IoTextCodec::encode(items);
}
