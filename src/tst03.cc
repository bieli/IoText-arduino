#include <iostream>
#include <iomanip>
#include <sstream>
#include <decimal/decimal>

// Custom overload for operator<<
std::ostream& operator<<(std::ostream& os, const std::decimal::decimal32& value) {
    // Convert the decimal32 value to a string for streaming
    std::ostringstream ss;
    ss << value;
    
    // Stream the string representation to the output
    os << std::fixed << std::setprecision(2) << ss.str();
    return os;
}

int main() {
    // Create a const std::decimal::decimal32 object from a double value
    const std::decimal::decimal32 decimal32Value(3.14);

    // Use the custom operator<< to stream the decimal32 value
    std::cout << "Formatted decimal32 value: " << decimal32Value << std::endl;

    return 0;
}
