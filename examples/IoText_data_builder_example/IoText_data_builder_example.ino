// Demostrates how build one record with the IoText data protocol library
// Author: Marcin Bielak

#include "IoText.h"
#include "builders/item_data_builder.h"

using namespace std;


void setup()
{
    IoTextItemDataBuilder builder = IoTextItemDataBuilder(3900237526042, "DEV_NAME_002");
        // TODO: resolve issue with DECIMAL format and library on ESP32 with decimal library
        // builder.add_measure(
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
}

void loop()
{
}
