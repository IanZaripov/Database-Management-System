#include "Logger.h"

using namespace std;

void Logger::Log(const string& message){
    cout << "[" << GetCurrentTime() << "]" << message << endl;
}

void Logger::StartTimer(const std::string& operation_name){
    current_operation = operation_name;
    start_time = chrono::high_resolution_clock::now();
    Log("Starting " + current_operation);
}

long long Logger::StopTimer(){
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds> (end_time - start_time);
    Log("Completed " + current_operation);
    return duration.count();
}

string Logger::GetCurrentTime(){
    auto now = chrono::system_clock::now();
    auto time_t = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time_t),"%Y-%m-%d %H:%M:%S");
    return ss.str();
}
