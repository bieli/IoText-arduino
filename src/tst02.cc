#include <iostream>
#include <string>
#include <vector>

#include "types/optional.h"
#include "codecs/item_codec.h"
#include "codecs/iot_ext_codec.h"


using namespace std;


enum class ItemTypes : char {
    TIMESTAMP_MILIS = 't',
    DEVICE_ID = 'd',
    METRIC_ITEM = 'm',
    HEALTH_CHECK = 'h'
};


ItemTypes from_str_convert_to_item_types(string item_type_str) {
    ItemTypes item_type;
    if (item_type_str == "t") {
        item_type = ItemTypes::TIMESTAMP_MILIS;
    } else if (item_type_str == "d") {
        item_type = ItemTypes::DEVICE_ID;
    } else if (item_type_str == "m") {
        item_type = ItemTypes::METRIC_ITEM;
    } else if (item_type_str == "h") {
        item_type = ItemTypes::HEALTH_CHECK;
    }
    return item_type;
}


string operator+(const string& str, ItemTypes item_type) {
    return str + static_cast<char>(item_type);
}

ostream& operator<<(ostream& os, ItemTypes item_type) {
    switch (item_type) {
        case ItemTypes::TIMESTAMP_MILIS:
            os << "t";
            break;
        case ItemTypes::DEVICE_ID:
            os << "d";
            break;
        case ItemTypes::METRIC_ITEM:
            os << "m";
            break;
        case ItemTypes::HEALTH_CHECK:
            os << "h";
            break;
        default:
            os.setstate(ios_base::failbit);
            break;
    }
    return os;
}





















enum class MetricDataTypes : char {
    INTEGER = 'i',
    BOOL = 'b',
    DECIMAL = 'd',
    TEXT = 't',
    NONE = ' '
};


MetricDataTypes from_str_convert_to_metric_item_types(string metric_data_type_str) {
    MetricDataTypes metric_data_type;
    if (metric_data_type_str == "i") {
        metric_data_type = MetricDataTypes::INTEGER;
    } else if (metric_data_type_str == "b") {
        metric_data_type = MetricDataTypes::BOOL;
    } else if (metric_data_type_str == "d") {
        metric_data_type = MetricDataTypes::DECIMAL;
    } else if (metric_data_type_str == "t") {
        metric_data_type = MetricDataTypes::TEXT;
    } else if (metric_data_type_str == " ") {
        metric_data_type = MetricDataTypes::NONE;
    }
    return metric_data_type;
}


string from_metric_item_types_to_str(MetricDataTypes mdi) {
    string output;
    if (mdi == MetricDataTypes::INTEGER) {
        output = "i";
    } else if (mdi == MetricDataTypes::BOOL) {
        output = "b";
    } else if (mdi == MetricDataTypes::DECIMAL) {
        output = "d";
    } else if (mdi == MetricDataTypes::TEXT) {
        output = "t";
    } else if (mdi == MetricDataTypes::NONE) {
        output = " ";
    }
    return output;
}


union MetricValueTypeUnion {
    int i_value;
    double d_value;
    char c_value;
};

class MetricValueTypeBuilder {
public:
    MetricValueTypeBuilder() : value_({0}) {}

    MetricValueTypeBuilder& seti_value(int value) {
        value_.i_value = value;
        return *this;
    }

    MetricValueTypeBuilder& setd_value(double value) {
        value_.d_value = value;
        return *this;
    }

    MetricValueTypeBuilder& setc_value(char value) {
        value_.c_value = value;
        return *this;
    }

    MetricValueTypeUnion build() const {
        return value_;
    }

    //friend ostream& operator<<(ostream& os, const MetricValueTypeUnion& value) {
    //    //os << "MetricValueTypeUnion: i_value: " << value.i_value;
    //    os << " AAAA ";
    //    return os;
    //}

    MetricValueTypeBuilder& display() {
        cout << "value_.i_value: " << value_.i_value << endl;
        return *this;
    }

private:
    MetricValueTypeUnion value_;
};


class MetricDataItem {
public:
    MetricDataItem() = default;

    MetricDataItem(const MetricDataTypes& data_type, const MetricValueTypeBuilder& value) 
        : data_type_(data_type), value_(MetricValueTypeBuilder().build()) {}

    const MetricDataTypes& get_metric_data_type() const {
        return data_type_;
    }

    const MetricValueTypeUnion& get_value() const {
        return value_;
    }

private:
    MetricDataTypes data_type_;
    MetricValueTypeUnion value_;
};



class Item {
public:
    ItemTypes kind;
    string name;
    Optional<MetricDataItem> metric;

    Item() {

    }

    Item(ItemTypes kind, string name, Optional<MetricDataItem> metric = Optional<MetricDataItem>(MetricDataItem()))
        : kind(kind), name(name), metric(metric) {}
};


int main() {
    MetricValueTypeUnion mvtu = MetricValueTypeBuilder()
        .seti_value(123)
        .display()
        .build();

    MetricValueTypeBuilder mvtb = MetricValueTypeBuilder()
        .seti_value(3333);

    MetricDataItem mdi = MetricDataItem(MetricDataTypes::INTEGER, mvtb);


    vector<Item> items;
    Item item1 = Item(ItemTypes::TIMESTAMP_MILIS, "2900267526042");
    items.push_back(item1);


    Item item2 = Item(ItemTypes::DEVICE_ID, "devie_id_x3");
    items.push_back(item2);
/*
    MetricDataItem mdi = MetricDataItem(
        MetricDataTypes::TEXT,
        MetricValueTypeBuilder()
            .seti_value("txt")
    );
    Item item3 = Item(ItemTypes::METRIC_ITEM, "val", mdi);
    items.push_back(item3);
*/
    MetricDataItem mdi2 = MetricDataItem(
        MetricDataTypes::DECIMAL,
        MetricValueTypeBuilder()
            .seti_value(12.2323)
    );
    Item item4 = Item(ItemTypes::METRIC_ITEM, "metric_name", mdi2);
    items.push_back(item4);

    MetricDataItem mdi3 = MetricDataItem(
        MetricDataTypes::BOOL,
        MetricValueTypeBuilder()
            .seti_value(true)
    );
    Item item5 = Item(ItemTypes::METRIC_ITEM, "metric_boolean1", mdi3);
    items.push_back(item5);

    MetricDataItem mdi4 = MetricDataItem(
        MetricDataTypes::INTEGER, 
        MetricValueTypeBuilder()
            .seti_value(3333)
    );
    Item item6 = Item(ItemTypes::METRIC_ITEM, "metric_integer9", mdi4);
    items.push_back(item6);

    string encoded_payload = IoTextCodec::encode(items);
    cout << "Encoded payload: " << endl << encoded_payload << endl;
    string payload = encoded_payload;

}