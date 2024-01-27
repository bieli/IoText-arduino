#ifndef METRIC_DATA_ITEM_H
#define METRIC_DATA_ITEM_H

#include <iostream>
#include <string>
#include <variant>
#include <optional>

#include "metric_data_types.h"


using MetricValueType = std::variant<std::string, int, double, bool>;

struct MetricDataItem {
    MetricDataTypes data_type;
    MetricValueType value;

    MetricDataItem() {
        
    }

    MetricDataItem(MetricDataTypes data_type, std::string value)
       : data_type(data_type), value(value) {}
};


template <typename... Ts>
std::string variant_to_string(const std::variant<Ts...>& var) {
    std::string result;
    std::visit([&result](const auto& value) {
        if constexpr (std::is_same_v<std::decay_t<decltype(value)>, std::string>) {
            result = value;
        } else {
            result = std::to_string(value);
        }
    }, var);
    return result;
}

std::string convert_from_metric_value_type_to_str(MetricValueType mvt) {
    return variant_to_string(mvt);
}

#endif // METRIC_DATA_ITEM_H
