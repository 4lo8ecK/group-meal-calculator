cmake_minimum_required(VERSION 3.26)

project(food_calc VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(food_calc WIN32
	main.cpp
	src/student.cpp

)

target_link_libraries(food_calc PRIVATE ${wxWidgets_LIBRARIES})

target_include_directories(food_calc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)