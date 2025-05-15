cmake_minimum_required(VERSION 3.14)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

# --- Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Lab2
        main.cpp
        src/lab2.cpp
        src/lab2.h
)

target_link_libraries(Lab2 ${OpenCV_LIBS})
