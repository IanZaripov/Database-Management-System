#include "DataBaseManager.h"
#include "Employee.h"

using namespace std;


DataBaseManager::DataBaseManager(string tn) : table_name(tn){
    const char* db_url = getenv("DATABASE_URL");
    if(!db_url){
        throw runtime_error("DATABASE_URL environment is not set");
    }
    connection_str = db_url;
    try{
        connection = make_unique<pqxx::connection>(connection_str);
    }catch(const exception& e){
        cerr << "Connection Failed : "<< e.what()<< '\n';
        throw;
    }
}

void DataBaseManager::CreateTable(){
    pqxx::work txn(*connection);     
    string sql_request = "CREATE TABLE IF NOT EXISTS " + table_name + " (";
    for (size_t i = 0; i < table_columns.size(); ++i) {
        sql_request += table_columns[i];
        if (i < table_columns.size() - 1) {
            sql_request += ", ";
        }
    }
    sql_request += ");";
    txn.exec(sql_request);
    txn.commit();
}


pqxx::result DataBaseManager::SortUniqueFullNameAndData(){
    pqxx::work transaction(*connection);
    string sql_request = "SELECT DISTINCT full_name, birthday, gender FROM " + table_name +
                         " ORDER BY full_name, birthday;";
    pqxx::result result = transaction.exec(sql_request);
    transaction.commit();
    return result;
}

pqxx::result DataBaseManager::SelectByCriterion(){
    pqxx::work transaction(*connection);
    string sql_request = "SELECT full_name FROM " + table_name + 
                         " WHERE gender = 'MALE' AND full_name LIKE 'F%'";
    pqxx::result result= transaction.exec(sql_request);
    transaction.commit();
    return result;
}

void DataBaseManager::AddEmployee(const EmployeeInfo& employee) {
    pqxx::work transaction(*connection);
    string full_name = employee.last_name_ + " " + employee.first_name_ + " " + employee.patronymic_;
    string sql_request = "INSERT INTO " + table_name + " (full_name, birthday, gender) VALUES ($1, $2, $3)";
    transaction.exec_params(sql_request, full_name, employee.birthday_str_, employee.gender_);
    transaction.commit();
}

void DataBaseManager::BulkInsertEmployees(const vector<EmployeeInfo>& employees) {
    const size_t BATCH_SIZE = 1000;
    
    for (size_t offset = 0; offset < employees.size(); offset += BATCH_SIZE) {
        pqxx::work txn(*connection);
        
        size_t batch_end = min(offset + BATCH_SIZE, employees.size());
        size_t records_in_batch = batch_end - offset;
        
        string sql = "INSERT INTO " + table_name + 
                    " (full_name, birthday, gender) VALUES ";
        
        vector<string> params;
        params.reserve(records_in_batch * 3);
        
        for (size_t i = 0; i < records_in_batch; i++) {
            const auto& emp = employees[offset + i];
            string full_name = emp.last_name_ + " " + emp.first_name_ + " " + emp.patronymic_;
            sql += "($" + to_string(i*3+1) + ", $" + to_string(i*3+2) + ", $" + to_string(i*3+3) + ")";
            if (i < records_in_batch - 1){
                sql += ", ";
            }
            params.push_back(full_name);
            params.push_back(emp.birthday_str_);
            params.push_back(emp.gender_);
        }
        txn.exec_params(sql, pqxx::prepare::make_dynamic_params(params));
        txn.commit();
    }
}