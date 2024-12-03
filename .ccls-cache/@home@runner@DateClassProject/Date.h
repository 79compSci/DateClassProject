#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

class Date {
private:
    int month;   // Stores the month (1-12)
    int day;     // Stores the day (1-31 depending on the month)
    int year;    // Stores the year

    // Helper function to validate the date
    bool isValidDate(int month, int day, int year) {
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > getDaysInMonth(month, year)) return false;
        return true;
    }

    // Helper function to check leap year
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // Helper function to get the number of days in a month
    int getDaysInMonth(int month, int year) {
        if (month == 2) {
            return isLeapYear(year) ? 29 : 28;
        }
        static int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return daysInMonth[month - 1];
    }

public:
    // Constructors
    Date() : month(1), day(1), year(1930) {}

    Date(int m, int d, int y) {
        if (isValidDate(m, d, y)) {
            month = m;
            day = d;
            year = y;
        } else {
            throw std::invalid_argument("Invalid date provided");
        }
    }

    // Set and Get Functions
    void setDate(int m, int d, int y) {
        if (isValidDate(m, d, y)) {
            month = m;
            day = d;
            year = y;
        } else {
            throw std::invalid_argument("Invalid date provided");
        }
    }

    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getYear() const { return year; }

    // Print Functions
    void printFormat1() const {
        std::cout << month << "/" << day << "/" << year << std::endl;
    }

    void printFormat2() const {
        static std::string monthNames[] = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };
        std::cout << monthNames[month - 1] << " " << day << ", " << year << std::endl;
    }

    void printFormat3() const {
        static std::string monthNames[] = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };
        std::cout << day << " " << monthNames[month - 1] << " " << year << std::endl;
    }

    // Overloaded Operators
    Date& operator++() {  // Pre-increment
        ++day;
        if (day > getDaysInMonth(month, year)) {
            day = 1;
            ++month;
            if (month > 12) {
                month = 1;
                ++year;
            }
        }
        return *this;
    }

    Date operator++(int) {  // Post-increment
        Date temp = *this;
        ++(*this);
        return temp;
    }

    Date& operator--() {  // Pre-decrement
        --day;
        if (day < 1) {
            --month;
            if (month < 1) {
                month = 12;
                --year;
            }
            day = getDaysInMonth(month, year);
        }
        return *this;
    }

    Date operator--(int) {  // Post-decrement
        Date temp = *this;
        --(*this);
        return temp;
    }

    int operator-(const Date& other) const {
        auto toDays = [](int m, int d, int y) {
            int days = y * 365 + d;
            for (int i = 1; i < m; ++i) {
                days += (i == 2) ? 28 : (i == 4 || i == 6 || i == 9 || i == 11 ? 30 : 31);
                if (i == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) days++;
            }
            return days;
        };
        return std::abs(toDays(month, day, year) - toDays(other.month, other.day, other.year));
    }

    friend std::ostream& operator<<(std::ostream& out, const Date& date) {
        static std::string monthNames[] = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };
        out << monthNames[date.month - 1] << " " << date.day << ", " << date.year;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Date& date) {
        int m, d, y;
        char sep1, sep2;
        in >> m >> sep1 >> d >> sep2 >> y;
        if (sep1 == '/' && sep2 == '/' && date.isValidDate(m, d, y)) {
            date.setDate(m, d, y);
        } else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
};