#include "Date.h"

using namespace std;

Date Date::ParseFromString(const string& birthday_date){
    istringstream ss(birthday_date);
    string token;
    Date date;
    getline(ss,token,'-');
    date.year = stoi(token);
    getline(ss,token,'-');
    date.month = stoi(token);
    getline(ss,token,'-');
    date.day = stoi(token);
    return date;
}

Date Date::GetCurrentDate() const{
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return Date(now->tm_year + 1900,now->tm_mon + 1,now->tm_mday);
}

int Date::CalculateAge() const{
    const auto current_date = GetCurrentDate();
    int age = current_date.year - year;
    if(current_date.month - month < 0){
        age -=1;
    }
    else if(current_date.month == month){
        if(current_date.day < day){
            age -= 1;
        }
    }
    return age;
}

bool Date::IsLeapYear(){
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
        return true;
    }
    return false;
}

int Date::GetDaysInMonth(){
    static const vector<int> days_in_month = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(month == 2 && IsLeapYear()){
        return 29;
    }
    return days_in_month[month];
}