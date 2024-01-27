// Demostrates how decode one record with the IoText data protocol library
// Author: Marcin Bielak

#include "IoText.h"

IoText iot_ext;

void setup() {
  Serial.begin(115200);

  String device_name = "DEVICE_NAME";

  string encoded_payload = iot_ext.encode_test();
  cout << "Encoded payload: " << endl << encoded_payload << endl;
  string payload = encoded_payload;

  cout << "---------" << endl;

  vector<Item> decoded_items = IoTextCodec::decode(payload);

  cout << endl << "Decoded items:" << endl;

  for (Item item : decoded_items) {
      cout << endl << "type: " << "item.kind" << " " << "│" << " name: " << item.name << endl;
      if (item.metric.has_value()) {
          MetricDataItem mdi = item.metric.value();
          cout << "        ╘═══ metric -> type: " << ItemTypeTool::from_metric_item_types_to_str(mdi.get_metric_data_type());
          cout << ", value: " << mdi.get_value_as_str() << endl;
      }
  }

  cout << "---------" << endl;

  Serial.print("IoText build string:");
  // Serial.println(output);
}

void loop() {
}