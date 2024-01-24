#ifndef IOT_EXT_CODEC_H
#define IOT_EXT_CODEC_H

#include <string>
#include <optional>
#include <vector>

#include "../types/item.h"
#include "item_codec.h"


class IoTextCodec {
public:
    inline static const std::string ITEMS_DIVIDER = ",";

    static std::vector<Item> decode(
        std::string payload, std::string items_divider = ITEMS_DIVIDER) {
        std::vector<Item> items;
        std::vector<std::string> items_lst;
        size_t pos = 0;
        while ((pos = payload.find(items_divider)) != std::string::npos) {
            std::string item_str = payload.substr(0, pos);
            items_lst.push_back(item_str);
            payload.erase(0, pos + items_divider.length());
        }
        items_lst.push_back(payload);

        for (std::string item_str : items_lst) {
            //std::cout << "+++++" << std::endl;
            Item item_obj = ItemCodec::decode(item_str);
            items.push_back(item_obj);
        }
        return items;
    }

    static std::string encode(std::vector<Item> items, std::string items_divider = ITEMS_DIVIDER) {
        std::string encoded_str = "";
        for (Item item : items) {
            // std::cout << "[ DEBUG ] IoTextCodec::encode -> item.name: " << item.name << std::endl;
            std::string item_str = ItemCodec::encode(item);
            encoded_str += item_str + items_divider;
        }
        encoded_str = encoded_str.substr(0, encoded_str.length() - items_divider.length());
        return encoded_str;
    }
};


#endif // IOT_EXT_CODEC_H