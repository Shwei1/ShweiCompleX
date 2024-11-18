#include <iostream>
//#include "PolynomialGenerator.hpp"
//#include "PolynomialSolver.hpp"
//#include "CirculantMatrix.hpp"
//#include "GenerateCirculantMatrix.hpp"
// C
#include "C_PolynomialEquation.h"
#include <cstdio>

int main(){
//    PolynomialGenerator::initialise();
//    PolynomialGenerator::generate_polynomials("../polynomials.txt", 100);

//    PolynomialSolver("/Users/shwei/CLionProjects/ShweiCompleX/polynomials.txt", "../polynomials_my_out.txt");

//GenerateCirculantMatrix("../my_matrix.txt");
//
//CirculantMatrix cm("../my_matrix.txt");
//
//cm.solve_and_output("../shweicomplex_matrix_solutions.txt");

double coefs[5] = {1.0, -6.0, 11.0, 6.0, 0.0};
C_PolynomialEquation* cpolynom = PolynomialEquation_create(coefs, 5);

int degree = cpolynom->get_equation_type(cpolynom);
printf("Degree: %d\n", degree);

std::cout << degree << std::endl;

int root_count = 0;
c_double_complex* roots = cpolynom->solve(cpolynom, &root_count);

if (roots) {
    std::cout << "Roots:" << std::endl;
    for (int i = 0; i < root_count; i++) {
        std::cout << "Root " << i + 1 << ": "
                  << roots[i].real() << " + " << roots[i].imag() << "i"
                  << std::endl;
    }
    free(roots);
} else {
    free(roots);
    std::cout << "No roots found." << std::endl;
}


PolynomialEquation_destroy(cpolynom);

}
