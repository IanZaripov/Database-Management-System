#pragma once
#include <string>
#include <vector>
#include <sstream>

class Date {
public:
    Date() = default;
    Date(int y, int m, int d) : year(y), month(m), day(d) {}
    static Date ParseFromString(const std::string& birthday_date);
    Date GetCurrentDate() const;
    int CalculateAge() const;
    int GetDaysInMonth();
    bool IsLeapYear();
    int year;
    int month; 
    int day;
};