cmake_minimum_required(VERSION 3.14)
project(IntegrityService VERSION 1.0)
#set C++ version to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(IntegrityService src/main.cpp src/Hasher.cpp src/Server.cpp src/SHA256.cpp)
