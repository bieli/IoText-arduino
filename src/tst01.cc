#include <iostream>
#include <string>

// Define the union
union MyUnion {
    int intValue;
    double doubleValue;
    char charValue;
    // Add more types as needed
};

// Builder class for the union
class UnionBuilder {
public:
    UnionBuilder() : unionValue({0}) {}

    // Setters for different types
    UnionBuilder& setIntValue(int value) {
        unionValue.intValue = value;
        return *this;
    }

    UnionBuilder& setDoubleValue(double value) {
        unionValue.doubleValue = value;
        return *this;
    }

    UnionBuilder& setCharValue(char value) {
        unionValue.charValue = value;
        return *this;
    }

    // Add more setters for additional types as needed

    // Build function to get the union with the set values
    MyUnion build() const {
        return unionValue;
    }

private:
    MyUnion unionValue;
};

class MyClass {
public:
    MyUnion myUnion;

    MyClass() : myUnion(UnionBuilder().setIntValue(42).setDoubleValue(3.14).setCharValue('A').build()) {}
};

int main() {
    // Create an instance of MyClass with values set using the builder
    MyClass myObject;

    // Access the union values
    std::cout << "Int Value: " << myObject.myUnion.intValue << std::endl;
    std::cout << "Double Value: " << myObject.myUnion.doubleValue << std::endl;
    std::cout << "Char Value: " << myObject.myUnion.charValue << std::endl;

    return 0;
}
