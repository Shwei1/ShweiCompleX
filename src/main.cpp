#include <iostream>
#include "PolynomialEquation.hpp"
#include "PolynomialGenerator.hpp"
#include "PolynomialSolver.hpp"
#include "CirculantMatrix.hpp"
#include "GenerateCirculantMatrix.hpp"

int main(){
//    PolynomialGenerator::initialise();
//    PolynomialGenerator::generate_polynomials("../polynomials.txt", 100);

// 10x^4 + -8x^3 + -45x^2 + -28x + -40 = 0
//PolynomialEquation p(10, -8, -45, -28, -40);
//auto roots = p.solve();
//std::cout << roots[0] << ' ' << roots[1] << ' ' << roots[2]  << ' ' << roots[3] << std::endl;

//    PolynomialSolver("/Users/shwei/CLionProjects/ShweiCompleX/polynomials.txt", "../polynomials_my_out.txt");

//std::vector<Complex<double>> main_row;
//std::vector<Complex<double>> free_coefs;

//CirculantMatrix cm("../my_matrix.txt");
//
//cm.solve_and_output("../shweicomplex_matrix_solutions.txt");

GenerateCirculantMatrix("../my_matrix.txt");

CirculantMatrix cm("../my_matrix.txt");

cm.solve_and_output("../shweicomplex_matrix_solutions.txt");

//cm.output();

//CirculantMatrix cm(main_row, free_coefs);

//auto solutions = cm.solve();

//for (Complex<double> value: solutions){
//    std::cout << value << ", ";
//}

//Complex c(1.0);
//
//auto rootsn = c.roots(8);
//
//for (Complex root: rootsn){
//    std::cout << root << std::endl;
//}

}
