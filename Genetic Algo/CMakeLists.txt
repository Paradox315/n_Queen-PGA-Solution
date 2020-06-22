cmake_minimum_required(VERSION 3.16)
project(Genetic_Algo)

set(CMAKE_CXX_STANDARD 14)

add_executable(Genetic_Algo main.cpp environment.h state.h ThreadPool.h)