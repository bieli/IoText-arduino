#ifndef METRIC_DATA_TYPES_H
#define METRIC_DATA_TYPES_H

#include <iostream>
#include <string>

using namespace std;

#define MAX_METRIC_DATA_TYPE_TEST__MAX_SIZE 64

enum class MetricDataTypes : char {
    INTEGER = 'i',
    BOOL = 'b',
    DECIMAL = 'd',
    TEXT = 't',
    NONE = ' '
};

#endif // METRIC_DATA_TYPES_H

