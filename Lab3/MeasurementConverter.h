#ifndef MEASUREMENTCONVERTER_H
#define MEASUREMENTCONVERTER_H
#include <string> // For std::string

class MeasurementConverter {
private:
    int littles;
    int lots;
    int heaps;

    void normalize(); // Helper to adjust littles and lots

public:
    // Constructors
    MeasurementConverter();
    MeasurementConverter(int littles, int lots, int heaps);
    MeasurementConverter(int littles);

    // Getters
    int getLittles() const;
    int getLots() const;
    int getHeaps() const;

    // Setters
    void setLittles(int newLittles);
    void setLots(int newLots);
    void setHeaps(int newHeaps);

    // Operator Overloads
    MeasurementConverter operator+(const MeasurementConverter& rhs) const;
    MeasurementConverter operator-(const MeasurementConverter& rhs) const;
    MeasurementConverter operator*(const MeasurementConverter& rhs) const;
    MeasurementConverter operator/(const MeasurementConverter& rhs) const;
    bool operator==(const MeasurementConverter& rhs) const;
    operator std::string() const; // For converting to string
};

#endif // MEASUREMENTCONVERTER_H
