#include "Date.h"
#include <iostream>

int main() {
    try {
        // Default constructor
        Date date1;
        std::cout << "Default Date: ";
        date1.printNumeric();
        std::cout << std::endl;

        // Parameterized constructor
        Date date2(12, 25, 2021);
        std::cout << "Custom Date: ";
        date2.printLong();
        std::cout << std::endl;

        // Test input validation
        try {
            Date invalidDate(2, 30, 2021);
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid Date Exception: " << e.what() << std::endl;
        }

        // Test increment and decrement operators
        Date date3(2, 28, 2020);
        std::cout << "Original Date: ";
        date3.printNumeric();
        std::cout << std::endl;

        ++date3;
        std::cout << "After Increment: ";
        date3.printNumeric();
        std::cout << std::endl;

        --date3;
        std::cout << "After Decrement: ";
        date3.printNumeric();
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}