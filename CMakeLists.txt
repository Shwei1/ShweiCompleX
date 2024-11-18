cmake_minimum_required(VERSION 3.26)
project(ShweiCompleX LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES_CPP
        src/C_PolynomialSolver.cpp
        src/PolynomialGenerator.cpp
        src/PolynomialEquation.cpp
        src/PolynomialSolver.cpp
        src/CirculantMatrix.cpp
        src/GenerateCirculantMatrix.cpp
        src/main.cpp
)

set(SOURCES_C
        src/C_PolynomialEquation.c
        src/C_PolynomialEquation.h
)

add_executable(ShweiCompleX ${SOURCES_CPP} ${SOURCES_C})

set_source_files_properties(${SOURCES_C} PROPERTIES LANGUAGE C)
