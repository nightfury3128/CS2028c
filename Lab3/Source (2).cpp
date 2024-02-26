#include "MeasurementConverter.h"
#include <sstream> // For std::stringstream
#include <iostream>

// In MeasurementConverter.cpp

MeasurementConverter::MeasurementConverter(int littles, int lots, int heaps) {
    this->littles = littles;
    this->lots = lots;
    this->heaps = heaps;
    normalize(); // Make sure to call normalize if you want to ensure the values are within your desired range
}

// Helper method to ensure littles < 7 and lots < 23, adjusting lots and heaps accordingly
void MeasurementConverter::normalize() {
    lots += littles / 7;
    littles %= 7;
    heaps += lots / 23;
    lots %= 23;
}

// Constructors and other member functions implementation...

// Overloaded operators implementation
MeasurementConverter MeasurementConverter::operator+(const MeasurementConverter& rhs) const {
    // Add the values and create a new object
    MeasurementConverter result(this->littles + rhs.littles, this->lots + rhs.lots, this->heaps + rhs.heaps);
    result.normalize(); // Adjust the values to keep them within bounds
    return result;
}

// Implement -, *, and / similarly, adjusting with normalize()

bool MeasurementConverter::operator==(const MeasurementConverter& rhs) const {
    return this->littles == rhs.littles && this->lots == rhs.lots && this->heaps == rhs.heaps;
}

MeasurementConverter::operator std::string() const {
    std::stringstream ss;
    ss << "Heaps: " << this->heaps << ", Lots: " << this->lots << ", Littles: " << this->littles;
    return ss.str();
}

int main() {
    // Example initialization
    MeasurementConverter obj1(3, 1, 0); // 3 littles, 1 lot, 0 heaps
    MeasurementConverter obj2(5, 2, 1); // 5 littles, 2 lots, 1 heap

    // Example operation
    MeasurementConverter result = obj1 + obj2;
    std::cout << "Result: " << std::string(result) << std::endl;

    // Continue with user input and loop as described in Task 4

    return 0;
}
