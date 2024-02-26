#include <iostream>
#include <iomanip>
using namespace std;

// Product structure
struct Product {
    int id;
    int units;
    double price;
    double sales;
};

// Function prototypes
void calcSales(Product[], int);
void showOrder(Product[], int);
void dualSort(Product[], int);
void showTotals(Product[], int);

// NUM_PRODS is the number of products produced.
const int NUM_PRODS = 9;

int main() {
    // Array of products
    Product products[NUM_PRODS] = {
        {914, 842, 12.95},
        {915, 416, 14.95},
        {916, 127, 18.95},
        {917, 514, 16.95},
        {918, 437, 21.95},
        {919, 269, 31.95},
        {920, 97,  14.95},
        {921, 492, 14.95},
        {922, 212, 16.95}
    };

    // Calculate each product's sales.
    calcSales(products, NUM_PRODS);

    // Sort the products array in descending order by sales.
    dualSort(products, NUM_PRODS);

    // Set the numeric output formatting.
    cout << setprecision(2) << fixed << showpoint;

    // Display the products and sales amounts.
    showOrder(products, NUM_PRODS);

    // Display total units sold and total sales.
    showTotals(products, NUM_PRODS);

    return 0;
}

void calcSales(Product products[], int num) {
    for (int index = 0; index < num; index++)
        products[index].sales = products[index].units * products[index].price;
}

void dualSort(Product products[], int size) {
    int startScan, maxIndex;
    Product tempProduct;
    for (startScan = 0; startScan < (size - 1); startScan++) {
        maxIndex = startScan;
        tempProduct = products[startScan];
        for (int index = startScan + 1; index < size; index++) {
            if (products[index].sales > products[maxIndex].sales) {
                tempProduct = products[index];
                maxIndex = index;
            }
        }
        products[maxIndex] = products[startScan];
        products[startScan] = tempProduct;
    }
}

void showOrder(Product products[], int num) {
    cout << "Product Number\tSales\n";
    cout << "----------------------------------\n";
    for (int index = 0; index < num; index++) {
        cout << products[index].id << "\t\t$";
        cout << setw(8) << products[index].sales << endl;
    }
    cout << endl;
}

void showTotals(Product products[], int num) {
    int totalUnits = 0;
    double totalSales = 0.0;
    for (int index = 0; index < num; index++) {
        totalUnits += products[index].units;
        totalSales += products[index].sales;
    }
    cout << "Total Units Sold: " << totalUnits << endl;
    cout << "Total Sales: $" << totalSales << endl;
}

