cmake_minimum_required(VERSION 3.10)
project (4russians
         LANGUAGES CXX Fortran)
add_library(matrix matrix.h matrix.cpp)
add_library(preprocess preprocess.h preprocess.cpp)
add_library(matmul_fortran matmul_fortran.h matmul_fortran.f90)
add_executable (main main.cpp)
target_link_libraries(preprocess matrix)
target_link_libraries(main matrix preprocess matmul_fortran)

