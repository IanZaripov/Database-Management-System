#include "DataBaseManager.h"
#include "Employee.h"
#include "EmployeeGenerator.h"
#include "Logger.h"
#include "Date.h"
#include <iostream>
#include <optional>
#include <pqxx/pqxx>
#include <string>

using namespace std;

void PrintEmployeeDirectory(pqxx::result employees,optional<long long> param){
    for(const auto& row : employees){
        string full_name = row[0].as<string>();
        string birthday = row[1].as<string>();
        string gender = row[2].as<string>();
        Date d = Date::ParseFromString(birthday);
        cout << "full name: " << full_name << endl; 
        cout << "birthday: "<< birthday << endl;
        cout << "gender: " << gender << endl;
        cout << "age: " << d.CalculateAge() << endl;
    }
    if(param != nullopt){
        cout << "Time: " << param.value()<< " ms"<< endl;
    }
}

Employee CreateEmployee(const std::string& first_name,const std::string& second_name,
                        const std::string& patronymic,const std::string& birthday_data,
                        const std::string& gender,shared_ptr<DataBaseManager> db_ptr){
    return {first_name,second_name,patronymic,birthday_data,gender,db_ptr};
}

void ProcessMode(shared_ptr<DataBaseManager> db_ptr,char* argv[]){
    int mode = stoi(argv[1]);
    switch (mode)
    {
    case 1: {
        db_ptr->CreateTable();
        break;
    }
    case 2: {
        Employee employee = CreateEmployee(argv[2],argv[3],argv[4],argv[5],argv[6],db_ptr);
        employee.SendEmployeeToDB();
        break;
    }
    case 3:{
        const auto employees = db_ptr->SortUniqueFullNameAndData();
        PrintEmployeeDirectory(employees,nullopt);
        break;
    }
    case 4:{
        EmployeeGenerator emp_gen;
        const auto employees = emp_gen.GenerateEmployees(1000000);
        db_ptr->BulkInsertEmployees(employees);
        break;
    }
    case 5:{
        Logger logger;
        logger.StartTimer("Select male with F in the begining of last_name");
        const auto employees = db_ptr->SelectByCriterion();
        auto time_result = logger.StopTimer();
        PrintEmployeeDirectory(employees,time_result);
        break;
    }
    default:
        break;
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2){
        return 1;
    }
    auto db_ptr = make_shared<DataBaseManager>("employee");
    ProcessMode(db_ptr,argv);
    return 0;
}