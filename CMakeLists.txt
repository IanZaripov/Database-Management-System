cmake_minimum_required(VERSION 3.10)
project(EmployeeApp)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск библиотеки libpqxx
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/Employee.cpp
    src/DataBaseManager.cpp
    src/Date.cpp
    src/Logger.cpp
    src/EmployeeGenerator.cpp
)

# Включение директорий
include_directories(src)
include_directories(${LIBPQXX_INCLUDE_DIRS})

# Создание исполняемого файла
add_executable(app ${SOURCES})

# Подключение библиотек
target_link_libraries(app ${LIBPQXX_LIBRARIES})

# Флаги компиляции
target_compile_options(app PRIVATE -Wall -Wextra -O2)