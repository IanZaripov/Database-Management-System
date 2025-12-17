#pragma once
#include <pqxx/pqxx>
#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <exception>
#include <vector>

struct EmployeeInfo;

static const std::vector<std::string> table_columns = {
    "full_name VARCHAR(100) NOT NULL",
    "birthday DATE NOT NULL",
    "gender CHAR(10) NOT NULL",
};

class DataBaseManager{
public:
    DataBaseManager(std::string tn);
    void CreateTable();
    pqxx::result SortUniqueFullNameAndData();
    void AddEmployee(const EmployeeInfo& employee);
    pqxx::result SelectByCriterion();
    void BulkInsertEmployees(const std::vector<EmployeeInfo>& employees);
private:
    std::string table_name;
    std::string connection_str;
    std::unique_ptr<pqxx::connection> connection;
};