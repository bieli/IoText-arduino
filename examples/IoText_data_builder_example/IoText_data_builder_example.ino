// Demostrates how to do something with the IoText data protocol library
// Author: Marcin Bielak

#include "IoText.h"
#include "builders/item_data_builder.h"

using namespace std;

// string MSG_1_EXAMPLE = "t|3900237526042,d|device_name_001,m|val_water_001=i:1234,m|val_water_002=i:15,m|bulb_state=b:1,m|connector_state=b:0,m|temp_01=d:34.4,m|temp_02=d:36.4,m|temp_03=d:10.4,m|pwr=d:12.231,m|current=d:1.429,m|current_battery=d:1.548";


/*
    vector<Item> items;
    Item item1 = Item(ItemTypes::TIMESTAMP_MILIS, "2900267526042");
    items_.push_back(item1);


    Item item2 = Item(ItemTypes::DEVICE_ID, "devie_id_x3");
    items_.push_back(item2);

    MetricDataItem mdi = MetricDataItem(
        MetricDataTypes::TEXT,
        MetricValueTypeBuilder()
            .set_text_value(string("txt"))
    );
    Item item3 = Item(ItemTypes::METRIC_ITEM, "val", mdi);
    items_.push_back(item3);

*/
void setup()
{
    // string item_decoded_str = IoTextCodec.decode(MSG_1_EXAMPLE);
    // printf("decoded_msg: %s\n", item_decoded_str);
    // EXPECTED_MSG = "t|3900237526042,d|DEV_NAME_002,m|battery_level=d:12.07,m|open_door=b:1,m|open_window=b:0,m|counter_01=i:1234";

    IoTextItemDataBuilder builder = IoTextItemDataBuilder(3900237526042, "DEV_NAME_002");
        // .add_measure(
        //     "battery_level",
        //     MetricDataItem(
        //         MetricDataTypes::DECIMAL,
        //         MetricValueTypeBuilder()
        //             .set_decimal_value(12.34)
        //     )
        // )
        builder.add_measure(
            "open_door",
            MetricDataItem(
                MetricDataTypes::BOOL,
                MetricValueTypeBuilder()
                    .set_bool_value(true)
            )
        )
        .add_measure(
            "open_window",
            MetricDataItem(
                MetricDataTypes::BOOL,
                MetricValueTypeBuilder()
                    .set_bool_value(false)
            )
        )
        .add_measure(
            "counter_01",
            MetricDataItem(
                MetricDataTypes::INTEGER,
                MetricValueTypeBuilder()
                    .set_integer_value(1234)
            )
        )
        .add_measure(
            "txt_1",
            MetricDataItem(
                MetricDataTypes::TEXT,
                MetricValueTypeBuilder()
                    .set_text_value(string("txt"))
            )
        );

    string built_msg = builder.build();

    printf("built_msg: %s\n", built_msg);

    // static_assert(built_msg == EXPECTED_MSG);
}

void loop()
{
}
