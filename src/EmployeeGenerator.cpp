#include "EmployeeGenerator.h"

using namespace std;

EmployeeGenerator::EmployeeGenerator() : gen(rd()) {}

string EmployeeGenerator::MakeFemalePatronymic(string patronymic){
    size_t pos = patronymic.find_last_of('v');
    if (pos != string::npos && pos > 0) {
        patronymic.resize(pos + 1);
    }
    patronymic += "na";
    return patronymic;
}
string EmployeeGenerator::GenerateGender(){
    uniform_int_distribution<> gender_dist(0,1);
    bool is_male = gender_dist(gen) == 0;
    if(is_male){
        return "Male";
    }
    return "Female";
}

string EmployeeGenerator::GenerateBirthday(){
    uniform_int_distribution<>year_dist(1950,2025);
    uniform_int_distribution<>month_dist(1,12);
    Date date;
    date.year = year_dist(gen);
    date.month = month_dist(gen);
    int day_in_month = date.GetDaysInMonth();
    uniform_int_distribution<>day_dist(1,day_in_month);
    date.day = day_dist(gen);
    string month_str = (date.month < 10) ? "0" + to_string(date.month) : to_string(date.month);
    string day_str = (date.day < 10) ? "0" + to_string(date.day) : to_string(date.day);
    return to_string(date.year) + "-" + month_str + "-" + day_str;
}


EmployeeInfo EmployeeGenerator::GenerateEmployee(){
    EmployeeInfo employee;
    employee.gender_ = GenerateGender();
    uniform_int_distribution<> distance_patronymic(0,malePatronymics.size() - 1);
    uniform_int_distribution<> distance_last_name(0,maleSurnames.size() - 1);
    if(employee.gender_ == "Male"){
        uniform_int_distribution<> distance_first_name(0,maleNames.size() - 1);
        employee.last_name_ = maleSurnames[distance_last_name(gen)];
        employee.first_name_ = maleNames[distance_first_name(gen)];
        employee.patronymic_ = malePatronymics[distance_patronymic(gen)];
    }
    else{
        uniform_int_distribution<> distance_first_name(0,femaleNames.size() - 1);
        employee.first_name_ = femaleNames[distance_first_name(gen)];
        employee.last_name_ = maleSurnames[distance_last_name(gen)] + 'a';
        employee.patronymic_ = MakeFemalePatronymic(malePatronymics[distance_patronymic(gen)]);
    }
    employee.birthday_str_ = GenerateBirthday();
    return employee;
}

vector<EmployeeInfo> EmployeeGenerator::GenerateEmployees(int count){
    vector<EmployeeInfo> employees;
    employees.reserve(count + 100);
    for(int i = 0; i < count; i++){
        auto emp = GenerateEmployee();
        employees.push_back(emp);
    }
    for(int i = 0; i < 100; i++){
        auto emp = GenerateMaleWithF();
        employees.push_back(emp);
    }
    return employees;
}

EmployeeInfo EmployeeGenerator::GenerateMaleWithF(){
    EmployeeInfo employee;
    uniform_int_distribution<> distance_last_name(0,male_f_last_names.size() - 1);
    uniform_int_distribution<> distance_first_name(0,maleNames.size() - 1);
    uniform_int_distribution<> distance_patronymic(0,malePatronymics.size() - 1);
    employee.last_name_ = male_f_last_names[distance_last_name(gen)];
    employee.first_name_ = maleNames[distance_first_name(gen)];
    employee.patronymic_ = malePatronymics[distance_patronymic(gen)];
    employee.birthday_str_ = GenerateBirthday();
    return employee;
}
