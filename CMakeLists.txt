cmake_minimum_required(VERSION 3.14)
project(Lab9)

set(CMAKE_CXX_STANDARD 17)

# --- Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Lab9
        main.cpp
        src/lab9.cpp
        src/lab9.h
)

target_link_libraries(Lab9 ${OpenCV_LIBS})
