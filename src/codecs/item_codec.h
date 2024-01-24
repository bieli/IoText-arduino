#ifndef ITEM_CODEC_H
#define ITEM_CODEC_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <optional>

#include "../types/item.h"
#include "metric_data_item_codec.h"
//#include "metric_data_item_codec.h"


class ItemCodec {
public:
    static Item decode2(std::string& value){
        Item item = Item();
        item.name = value;
        return item;
    }

    static Item decode(
        std::string item,
        char split_kind_char = '|',
        char split_data_item_char = '='
    ) {
        std::vector<std::string> tokens;
        std::istringstream stream(item);
        std::string token;

        while (std::getline(stream, token, split_kind_char)) {
           tokens.push_back(token);
        }

        // for (const auto& token : tokens) {
        //  std::cout << "[ DEBUG ] ItemCodec::decode - Token: " << token << std::endl;
        //}

        std::string kind = tokens[0];
        std::string name_and_value_tmp = tokens[1];
        //std::cout << "[ DEBUG ] ItemCodec::decode - kind: " << kind << std::endl;
        //std::cout << "[ DEBUG ] ItemCodec::decode - name_and_value_tmp: " << name_and_value_tmp << std::endl;

        std::vector<std::string> tokens2;
        std::istringstream stream2(name_and_value_tmp);
        std::string token2;

        while (std::getline(stream2, token2, split_data_item_char)) {
           tokens2.push_back(token2);
        }

        //for (const auto& token22 : tokens2) {
        //  std::cout << "[ DEBUG ] ItemCodec::decode - Token22: " << token22 << std::endl;
        //}
        Item it = Item();

        std::string name = tokens2[0];
        std::string value = "";
        if (tokens2.size() > 1) {
            value = tokens2[1];
        }

        it.kind = from_str_convert_to_item_types(kind);
        it.name = name;
        if (it.kind == ItemTypes::METRIC_ITEM && value != "") {
            it.metric = MetricDataItemCodec::decode(value);
        }

        return it;
    }

    static std::string encode(
        Item item,
        std::string split_kind_char = "|",
        std::string split_data_item_char = "="
    ) {
        std::string result = (char) static_cast<int>(item.kind) + split_kind_char + item.name;

        if (item.metric.has_value()) {
            result += split_data_item_char + MetricDataItemCodec::encode(item.metric.value());
        }
        return result;
    }
};

#endif // ITEM_CODEC_H
