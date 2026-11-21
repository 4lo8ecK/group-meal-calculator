cmake_minimum_required(VERSION 3.16)
project(FoodCalc VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 5.15 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(FoodCalc src/main.cpp
    src/month/student.cpp
    src/month/manager.cpp
    src/month/flwork.cpp)

target_link_libraries(FoodCalc PRIVATE Qt5::Core Qt5::Widgets)

target_include_directories(FoodCalc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)