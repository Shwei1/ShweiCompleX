cmake_minimum_required(VERSION 3.26)
project(ShweiCompleX LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES_CPP
        src/C/C_PolynomialSolver.cpp
        tools/PolynomialGenerator.cpp
        "src/C++ Proper/PolynomialEquation.cpp"
        "src/C++ Proper/PolynomialSolver.cpp"
        "src/C++ Proper/CirculantMatrix.cpp"
        tools/GenerateCirculantMatrix.cpp
        src/main.cpp
        src/C/C_PolynomialSolver.hpp
        src/C/C_CirculantMatrixSolver.hpp
        src/C/C_CirculantMatrixSolver.cpp
        "src/C++ STL/STL_PolynomialEquation.hpp"
        "src/C++ STL/STL_PolynomialEquation.cpp"
        "src/C++ STL/STL_PolynomialSolver.hpp"
        "src/C++ STL/STL_PolynomialSolver.cpp"
        "src/C++ STL/STL_CirculantMatrix.hpp"
        "src/C++ STL/STL_CirculantMatrix.cpp"
        src/C/C_CirculantMatrixSolver.cpp
)

set(SOURCES_C
        src/C/C_PolynomialEquation.c
        src/C/C_PolynomialEquation.h
        src/C/C_CirculantMatrix.h
        src/C/C_CirculantMatrix.c
)

add_executable(ShweiCompleX ${SOURCES_CPP} ${SOURCES_C})

set_source_files_properties(${SOURCES_C} PROPERTIES LANGUAGE C)

#target_include_directories(ShweiCompleX PRIVATE include)
