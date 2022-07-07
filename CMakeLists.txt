cmake_minimum_required(VERSION 3.22)
project(Calculator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
        
add_executable(Calculator main.cpp calculator.cpp calculator.h controller.cpp controller.h calculator.ui)
target_link_libraries(Calculator
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )
