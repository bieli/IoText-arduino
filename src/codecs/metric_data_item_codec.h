#ifndef METRIC_DATA_ITEM_CODEC_H
#define METRIC_DATA_ITEM_CODEC_H

#include <string.h>

#include "../types/metric_data_item.h"
#include "../types/metric_data_types.h"
#include "../types/helpers.h"

using namespace std;
// using namespace item_type_ns;

class MetricDataItemCodec {
public:
    static MetricDataItem decode(string data_type_and_value, char data_type_and_value_char = ':') {
        //cout << "[ DEBUG ] MetricDataItemCodec::decode - data_type_and_value INPUT: " << data_type_and_value << endl;

        if (data_type_and_value.size() == 0) {
            MetricDataItem mdi = MetricDataItem();
            return mdi;
        }

        vector<string> tokens;
        istringstream stream(data_type_and_value);
        string token;

        while (getline(stream, token, data_type_and_value_char)) {
            tokens.push_back(token);
        }

        //for (const auto& token : tokens) {
        //    cout << "[ DEBUG ] MetricDataItemCodec::decode - data_type token: " << token << endl;
        //}

        string data_type = tokens[0];
        string value = tokens[1];

        //cout << "[ DEBUG ] MetricDataItemCodec::decode - data_type: " << data_type << endl;
        //cout << "[ DEBUG ] MetricDataItemCodec::decode - value: " << value << endl;

        MetricDataTypes mdt = ItemTypeTool::from_str_convert_to_metric_data_types(data_type.c_str());

        return MetricDataItem(
            mdt,
            MetricValueTypeBuilder()
                .extract_value_from_str(mdt, value)
        );
    }

    static string encode(const MetricDataItem& mdi, const string& data_type_and_value_char = ":") {
        return ItemTypeTool::from_metric_item_types_to_str(mdi.get_metric_data_type()) 
                + data_type_and_value_char 
                + mdi.get_value_as_str();
    }
};


#endif // METRIC_DATA_ITEM_CODEC_H