cmake_minimum_required(VERSION 3.14)
project(Lab4)

set(CMAKE_CXX_STANDARD 17)

# --- Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Lab4
        main.cpp
        src/lab4.cpp
        src/lab4.h
)

target_link_libraries(Lab4 ${OpenCV_LIBS})
