cmake_minimum_required(VERSION 3.25)
project(Kursatch3)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED CONFIG)

add_subdirectory(src)
