cmake_minimum_required(VERSION 3.26)
project(ShweiCompleX LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES_CPP
        src/Polynomials/C_PolynomialSolver.cpp
        tools/PolynomialGenerator.cpp
        src/Polynomials/PolynomialEquation.cpp
        src/Polynomials/PolynomialSolver.cpp
        src/CirculantMatrix/CirculantMatrix.cpp
        tools/GenerateCirculantMatrix.cpp
        src/main.cpp
        include/Polynomials/C_PolynomialSolver.hpp
        include/CirculantMatrix/C_CirculantMatrixSolver.hpp
)

set(SOURCES_C
        src/Polynomials/C_PolynomialEquation.c
        include/Polynomials/C_PolynomialEquation.h
        include/CirculantMatrix/C_CirculantMatrix.h
        src/CirculantMatrix/C_CirculantMatrix.c
)

add_executable(ShweiCompleX ${SOURCES_CPP} ${SOURCES_C})

set_source_files_properties(${SOURCES_C} PROPERTIES LANGUAGE C)
