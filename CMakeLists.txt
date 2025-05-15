cmake_minimum_required(VERSION 3.14)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)

# --- Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Lab3
        main.cpp
        src/lab3.cpp
        src/lab3.h
)

target_link_libraries(Lab3 ${OpenCV_LIBS})
