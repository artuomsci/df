cmake_minimum_required(VERSION 3.5)

project(TEST_DF LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC *.h *.cpp)

add_executable(TEST_DF ${SRC})

target_link_libraries(TEST_DF DF)
