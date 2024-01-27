// compile:
// g++ -std=c++17 src/main2.cpp -o main2 && ./main

#include <iostream>
#include <string>

class Item {
public:
    Item(const std::string& name, double price) : name_(name), price_(price) {}

    const std::string& getName() const {
        return name_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        os << "Item: " << item.name_ << ", Price: " << item.price_;
        return os;
    }

    void display() const {
        std::cout << "Item: " << name_ << ", Price: " << price_ << std::endl;
    }

private:
    std::string name_;
    double price_;
};

class Builder {
public:
    // Default constructor
    Builder() : item_("DefaultItem", 0.0) {}

    // Default constructor with default values for Item
    // Builder(const std::string& defaultName = "DefaultItem", double defaultPrice = 0.0)
    //    : item_(defaultName, defaultPrice) {}


    Builder& setItem(const std::string& name) {
        item_ = Item(name, 0.0);  // Default price is 0.0
        return *this;
    }

    Builder& setParameter(double price) {
        item_ = Item(item_.getName(), price);
        return *this;
    }

    Item build() const {
        return item_;
    }

private:
    Item item_;
};

int main() {
    Builder builder;
    Item item = builder
                .setItem("ExampleItem")
                .setParameter(123.2)
                .build();

    // item.display();
    
    // Use the overloaded << operator to display the item
    std::cout << item << std::endl;

    return 0;
}
