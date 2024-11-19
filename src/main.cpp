// C++ HEADERS
//#include "PolynomialGenerator.hpp"
#include "../include/Polynomials/PolynomialSolver.hpp"
#include "../include/Polynomials/STL_PolynomialSolver.hpp"
#include "../include/Polynomials/PolynomialEquation.hpp"
//#include "CirculantMatrix.hpp"
//#include "GenerateCirculantMatrix.hpp"

// C HEADERS
#include "../include/Polynomials/C_PolynomialSolver.hpp"
#include "../include/CirculantMatrix/C_CirculantMatrixSolver.hpp"

int main(){

//    PolynomialGenerator::initialise();
//    PolynomialGenerator::generate_polynomials("../data/polynomials.txt", 100);
//    GenerateCirculantMatrix("../data/matrix.txt");

//    PolynomialSolver("../data/polynomials.txt", "../results/shweicomplex_polynomials_solutions.txt");
    STL_PolynomialSolver("../data/polynomials.txt", "../results/stdcomplex_polynomials_solutions.txt");
//GenerateCirculantMatrix("../matrix.txt");

//CirculantMatrix cm("../matrix.txt");
//
//cm.solve_and_output("../shweicomplex_matrix_solutions.txt");


//    C_PolynomialSolver("../data/polynomials.txt", "../results/complexh_polynomials_solutions.txt");

//Circulant Matrix C:
//    C_solve_and_output("../data/matrix.txt", "../results/complexh_matrix_solutions.txt");

// 19 x^3 + 22 x^2 + 44 x + -26 = 0

//STL_PolynomialEquation stlp(0, 19, 22, 44, -26);
//auto roots = stlp.solve();
//PolynomialEquation p(0, 19, 22, 44, -26);
//auto otherroots = p.solve();
//
//for (auto root: roots){
//    std::cout << root << ' ';
//}

}
