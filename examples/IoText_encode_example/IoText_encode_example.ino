// Demostrates how build one record with the IoText data protocol library
// Author: Marcin Bielak

#include "IoText.h"

IoText iot_ext;

using namespace std;

string EXPECTED_MSG = "t|2900267526042,d|devie_id_x3,m|val=t:txt,m|metric_boolean1=b:1,m|metric_integer9=i:3333";

void setup() {
    Serial.begin(115200);

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

    string output = IoTextCodec::encode(items);

    Serial.print("CREATED MSG: ");
    Serial.println(output.c_str());
    Serial.print("EXPECTED   : ");
    Serial.println(EXPECTED_MSG.c_str());

    assertv(
      EXPECTED_MSG.c_str(),
      output.c_str(),
      "Failed IoTexp protocol encoding process!"
    );
}

void loop() {
}
