#include "Employee.h"

using namespace std;


Employee::Employee(const std::string& first_name,const std::string& last_name,const std::string& patronymic,
                   const std::string& birthday_date, const std::string& gender,
                   shared_ptr<DataBaseManager> db_ptr) : db_manager_ptr(db_ptr){
    employee_info.first_name_ = first_name;
    employee_info.last_name_ = last_name;
    employee_info.patronymic_ = patronymic;
    employee_info.birthday_str_ = birthday_date;
    employee_info.birthday_ = Date::ParseFromString(birthday_date);
    employee_info.gender_ = gender;
}

string Employee::GetFullName() const{
    return employee_info.last_name_ + " " + employee_info.first_name_ + " " + employee_info.patronymic_;
}


void Employee::SendEmployeeToDB(){
    db_manager_ptr->AddEmployee(employee_info);
}