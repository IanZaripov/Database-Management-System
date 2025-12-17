#pragma once
#include "Employee.h"
#include "Date.h"
#include <vector>
#include <string>
#include <random>

static std::vector<std::string> maleNames = {
    "Alexander", "Aleksey", "Andrey", "Anton", "Artyom", "Boris", "Vadim", 
    "Valentin", "Valery", "Vasily", "Viktor", "Vitaly", "Vladimir", 
    "Vladislav", "Vyacheslav", "Gennady", "Georgy", "Grigory", "Daniil",
    "Denis", "Dmitry", "Evgeny", "Egor", "Ivan", "Igor", "Ilya", "Kirill",
    "Konstantin", "Leonid", "Maxim", "Mikhail", "Nikita", "Nikolay", "Oleg",
    "Pavel", "Peter", "Roman", "Ruslan", "Sergey", "Stanislav", "Stepan",
    "Timur", "Fedor", "Yuri", "Yaroslav"
};

static std::vector<std::string> femaleNames = {
    "Anna", "Alina", "Alisa", "Anastasia", "Elena", "Angelina", "Valentina",
    "Valeria", "Varvara", "Vera", "Veronika", "Victoria", "Galina", "Daria",
    "Diana", "Evgenia", "Ekaterina", "Elena", "Elizaveta", "Irina",
    "Ksenia", "Larisa", "Lydia", "Lyudmila", "Margarita", "Marina", "Maria",
    "Nadezhda", "Natalia", "Nina", "Oksana", "Olga", "Polina", "Svetlana",
    "Sofia", "Tatiana", "Uliana", "Yulia", "Yana"
};

static std::vector<std::string> maleSurnames = {
    "Ivanov", "Petrov", "Sidorov", "Smirnov", "Kuznetsov", "Popov", "Vasiliev",
    "Sokolov", "Mikhailov", "Novikov", "Fedorov", "Morozov", "Volkov", "Alekseev",
    "Lebedev", "Semenov", "Egorov", "Pavlov", "Kozlov", "Stepanov", "Nikolaev",
    "Orlov", "Andreev", "Makarov", "Nikitin", "Zakharov", "Romanov", "Filippov",
    "Gusev", "Titov", "Kuzmin", "Baranov", "Medvedev", "Komarov", "Shcherbakov",
    "Polyakov", "Karpov", "Solovyov", "Vinogradov", "Bogdanov"
};

static std::vector<std::string> malePatronymics = {
    "Alexandrovich", "Alekseevich", "Andreevich", "Antonovich", "Artyomovich",
    "Borisovich", "Vadimovich", "Valentinovich", "Valeryevich", "Vasilyevich",
    "Viktorovich", "Vitalyevich", "Vladimirovich", "Vladislavovich", "Vyacheslavovich",
    "Gennadyevich", "Georgievich", "Grigoryevich", "Daniilovich", "Denisovich",
    "Dmitrievich", "Evgenyevich", "Egorovich", "Ivanovich", "Igorevich", "Talevich",
    "Kirillovich", "Konstantinovich", "Leonidovich", "Maximovich", "Mikhailovich",
    "Nikolaevich", "Olegovich", "Pavlovich", "Petrovich", "Romanovich", "Sergeyevich"
};

static std::vector<std::string> male_f_last_names = {
    "Fisher", "Fletcher", "Foster", "Fox", "Franklin",
    "Fraser", "Freeman", "Fuller", "Fulton", "Fowler",
    "Ford", "Farrell", "Ferguson", "Fields", "Finley",
    "Fitzgerald", "Fleming", "Flores", "Flynn", "Forbes",
    "Fordham", "Foreman", "Forrest", "Foster", "Fowler",
    "Fox", "Frank", "Franklin", "Fraser", "Frederick",
    "Freeman", "French", "Frost", "Fry", "Fulton",
    "Funk", "Furness", "Fyfe", "Fabian", "Faber",
    "Fabrizio", "Fagan", "Fahey", "Fahy", "Fairbanks",
    "Fairchild", "Fairfax", "Fairfield", "Falconer", "Falk",
    "Falkner", "Fallon", "Fane", "Fannin", "Farley",
    "Farmer", "Farnham", "Farnsworth", "Farr", "Farragut",
    "Farran", "Farrell", "Farrington", "Farrow", "Farson",
    "Fast", "Faucett", "Faulkner", "Faunce", "Fawcett",
    "Fawkes", "Faxon", "Fay", "Featherstone", "Fechter",
    "Fedden", "Felix", "Fell", "Fellows", "Fenby",
    "Fenchurch", "Fender", "Fenimore", "Fenn", "Fenton",
    "Fenwick", "Fergus", "Ferguson", "Fern", "Fernandez",
    "Fernley", "Ferrand", "Ferrara", "Ferrari", "Ferrell",
    "Ferris", "Fetherston", "Fettes", "Fiddler", "Field",
    "Fielding", "Fields", "Fiennes", "Fife", "Figgis"
};


class EmployeeGenerator{
public:
    EmployeeGenerator();
    std::vector<EmployeeInfo> GenerateEmployees(int count = 0);
    EmployeeInfo GenerateMaleWithF(); 
    std::string GenerateGender();
    std::string GenerateBirthday();
    std::string MakeFemalePatronymic(std::string patronymic);
    EmployeeInfo GenerateEmployee();
private:
    std::vector<Employee> generated_employee;
    std::random_device rd;
    std::mt19937 gen;
};