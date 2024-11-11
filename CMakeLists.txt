cmake_minimum_required(VERSION 3.26)
project(ShweiCompleX)

set(CMAKE_CXX_STANDARD 17)

add_executable(ShweiCompleX
#        main.cpp
#        src/Complex.cpp
        src/Complex.hpp
        src/PolynomialEquation.hpp
        src/main.cpp
        src/PolynomialGenerator.cpp
        src/PolynomialGenerator.hpp
        src/PolynomialEquation.cpp
        src/PolynomialSolver.cpp
        src/PolynomialSolver.hpp
        src/CirculantMatrix.cpp)
