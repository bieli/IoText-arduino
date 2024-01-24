#ifndef METRIC_DATA_ITEM_CODEC_H
#define METRIC_DATA_ITEM_CODEC_H

#include <string.h>

#include "../types/metric_data_item.h"
#include "../types/metric_data_types.h"


class MetricDataItemCodec {
public:
    static MetricDataItem decode(std::string data_type_and_value, char data_type_and_value_char = ':') {
        //std::cout << "[ DEBUG ] MetricDataItemCodec::decode - data_type_and_value INPUT: " << data_type_and_value << std::endl;

        if (data_type_and_value.size() == 0) {
            MetricDataItem mdi = MetricDataItem();
            return mdi;
        }

        std::vector<std::string> tokens;
        std::istringstream stream(data_type_and_value);
        std::string token;

        while (std::getline(stream, token, data_type_and_value_char)) {
            tokens.push_back(token);
        }

        //for (const auto& token : tokens) {
        //    std::cout << "[ DEBUG ] MetricDataItemCodec::decode - data_type token: " << token << std::endl;
        //}

        std::string data_type = tokens[0];
        std::string value = tokens[1];

        //std::cout << "[ DEBUG ] MetricDataItemCodec::decode - data_type: " << data_type << std::endl;
        //std::cout << "[ DEBUG ] MetricDataItemCodec::decode - value: " << value << std::endl;

        MetricDataTypes mdt = from_str_convert_to_metric_item_types(data_type.c_str());

        return MetricDataItem(mdt, value);
    }

    static std::string encode(const MetricDataItem& mdi, const std::string& data_type_and_value_char = ":") {
        return from_metric_item_types_to_str(mdi.data_type) 
                + data_type_and_value_char 
                + convert_from_metric_value_type_to_str(mdi.value);
    }
};


#endif // METRIC_DATA_ITEM_CODEC_H