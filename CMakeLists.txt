cmake_minimum_required(VERSION 3.7)
project(RegisterAccess)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES test.cpp)
set(HEADERS register_access.hpp test.cpp register_access.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})