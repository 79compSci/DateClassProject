#include "Date.h"
#include <iostream>
#include <stdexcept>

// Default constructor
Date::Date() : month(1), day(1), year(1930) {}

// Parameterized constructor
Date::Date(int m, int d, int y) {
    setDate(m, d, y);
}

// Setters and Getters
void Date::setDate(int m, int d, int y) {
    if (m < 1 || m > 12 || d < 1 || d > daysInMonth(m, y) || y < 1)
        throw std::invalid_argument("Invalid date!");
    month = m;
    day = d;
    year = y;
}

int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }
int Date::getYear() const { return year; }

// Utility Functions
bool Date::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(int m, int y) const {
    static const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && isLeapYear(y))
        return 29;
    return days[m - 1];
}

// Print Functions
void Date::printNumeric() const {
    std::cout << month << '/' << day << '/' << year;
}

void Date::printLong() const {
    static const std::string months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    std::cout << months[month - 1] << ' ' << day << ", " << year;
}

void Date::printEuropean() const {
    static const std::string months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    std::cout << day << ' ' << months[month - 1] << ' ' << year;
}

// Operator Overloads
Date& Date::operator++() { // Prefix increment
    day++;
    if (day > daysInMonth(month, year)) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    return *this;
}

Date Date::operator++(int) { // Postfix increment
    Date temp = *this;
    ++(*this);
    return temp;
}

Date& Date::operator--() { // Prefix decrement
    day--;
    if (day < 1) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
        }
        day = daysInMonth(month, year);
    }
    return *this;


Date Date::operator--(int) { // Postfix decrement
    Date temp = *this;
    --(*this);
    return temp;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    static const std::string months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    os << months[date.month - 1] << " " << date.day << ", " << date.year;
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
    int m, d, y;
    char sep1, sep2;
    is >> m >> sep1 >> d >> sep2 >> y;
    if (sep1 != '/' || sep2 != '/' || m < 1 || m > 12 || d < 1 || y < 1)
        is.setstate(std::ios::failbit);
    else
        date.setDate(m, d, y);
    return is;
}