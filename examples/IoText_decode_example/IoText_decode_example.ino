// Demostrates how decode one record with the IoText data protocol library
// Author: Marcin Bielak

#include <sstream>
#include <string>
#include <cassert>

#include "IoText.h"

IoText iot_ext;

string EXPECTED_MSG = "t|2900267526042,d|devie_id_x3,m|val=t:txt,m|metric_boolean1=b:1,m|metric_integer9=i:3333";

void setup() {
  Serial.begin(115200);

  String device_name = "DEVICE_NAME";

  string encoded_payload = iot_ext.encode_test();
  cout << "Encoded payload: " << endl << encoded_payload << endl;
  string payload = encoded_payload;

  cout << "---------" << endl;

  vector<Item> decoded_items = IoTextCodec::decode(payload);

  cout << endl << "Decoded items:" << endl;

  stringstream concatenated_test_msg;

  for (Item item : decoded_items) {
      cout << endl << "type: " << "item.kind" << " " << "│" << " name: " << item.name << endl;
      concatenated_test_msg << "item.kind" << "|" << item.name;
      if (item.metric.has_value()) {
          MetricDataItem mdi = item.metric.value();
          cout << "        ╘═══ metric -> type: " << ItemTypeTool::from_metric_item_types_to_str(mdi.get_metric_data_type());
          cout << ", value: " << mdi.get_value_as_str() << endl;
          concatenated_test_msg << "=" << ItemTypeTool::from_metric_item_types_to_str(mdi.get_metric_data_type());
          concatenated_test_msg << ":" << mdi.get_value_as_str();
      } else {
          concatenated_test_msg << ",";
      }
  }

  assertv(
    EXPECTED_MSG.c_str(),
    concatenated_test_msg.str().c_str(),
    "Failed IoTexp protocol decoding process!"
  );

  Serial.println("TEST FINISHED WITH SUCCESS!");
}

void loop() {
}