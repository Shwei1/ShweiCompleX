#include <iostream>
//#include "PolynomialGenerator.hpp"
#include "../include/Polynomials/PolynomialSolver.hpp"
//#include "CirculantMatrix.hpp"
//#include "GenerateCirculantMatrix.hpp"
// C
#include "../include/Polynomials/C_PolynomialSolver.hpp"
#include "../include/CirculantMatrix/C_CirculantMatrixSolver.hpp"

int main(){
//    PolynomialGenerator::initialise();
//    PolynomialGenerator::generate_polynomials("../polynomials.txt", 100);

//    PolynomialSolver("../polynomials.txt", "../shweicomplex_polynomials_solutions.txt");

//GenerateCirculantMatrix("../matrix.txt");
//
//CirculantMatrix cm("../matrix.txt");
//
//cm.solve_and_output("../shweicomplex_matrix_solutions.txt");


//    C_PolynomialSolver("../polynomials.txt", "../complexh_polynomials_solutions.txt");


    C_solve_and_output("../matrix.txt", "../complexh_matrix_solutions.txt");

}
