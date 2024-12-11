#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

class Date {
private:
    int month;
    int day;
    int year;

public:
    // Constructors
    Date();
    Date(int m, int d, int y);

    // Setters and Getters
    void setDate(int m, int d, int y);
    int getMonth() const;
    int getDay() const;
    int getYear() const;

    // Utility Functions
    bool isLeapYear(int y) const;
    int daysInMonth(int m, int y) const;

    // Print Functions
    void printNumeric() const;
    void printLong() const;
    void printEuropean() const;

    // Operator Overloads
    Date& operator++();        // Prefix increment
    Date operator++(int);      // Postfix increment
    Date& operator--();        // Prefix decrement
    Date operator--(int);      // Postfix decrement
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
};

#endif