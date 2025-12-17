#pragma once

#include "DataBaseManager.h"
#include "Date.h"
#include <string>
#include <memory>
#include <ctime>

struct EmployeeInfo{
    std::string first_name_;
    std::string last_name_;
    std::string patronymic_;
    std::string birthday_str_;
    std::string gender_;
    Date birthday_;
};

class Employee {
public:
    Employee(const std::string& first_name,const std::string& last_name,const std::string& patronymic,
    const std::string& birthday_data, const std::string& gender,std::shared_ptr<DataBaseManager> db_ptr);
    void SendEmployeeToDB();
    std::string GetFullName() const;
    int CalculateAge() const{ return employee_info.birthday_.CalculateAge();}
private:
    std::shared_ptr<DataBaseManager> db_manager_ptr;
    EmployeeInfo employee_info;
};