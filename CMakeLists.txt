cmake_minimum_required(VERSION 3.1)
project(Algorithms)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(include)
file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
foreach(testsourcefile ${SOURCES})
    string(REPLACE ".cpp" "" testname ${testsourcefile})
    add_executable( ${testname} ${testsourcefile})
endforeach(testsourcefile ${SOURCES})
