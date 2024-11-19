#include <iostream>
//#include "PolynomialGenerator.hpp"
#include "PolynomialSolver.hpp"
//#include "CirculantMatrix.hpp"
//#include "GenerateCirculantMatrix.hpp"
// C
#include "C_PolynomialSolver.hpp"
#include "С_CirculantMatrixSolver.hpp"

int main(){
//    PolynomialGenerator::initialise();
//    PolynomialGenerator::generate_polynomials("../polynomials.txt", 100);

//    PolynomialSolver("../polynomials.txt", "../shweicomplex_polynomials_solutions.txt");

//GenerateCirculantMatrix("../my_matrix.txt");
//
//CirculantMatrix cm("../my_matrix.txt");
//
//cm.solve_and_output("../shweicomplex_matrix_solutions.txt");


//    C_PolynomialSolver("../polynomials.txt", "../complexh_polynomials_solutions.txt");


    C_solve_and_output("../my_matrix.txt", "../complexh_matrix_solutions.txt");

}
