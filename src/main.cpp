#include "../tools/PolynomialGenerator.hpp"
#include "../tools/GenerateCirculantMatrix.hpp"

#include "../src/C++ Proper/PolynomialSolver.hpp"
#include "../src/C++ Proper/CirculantMatrix.hpp"

#include "../src/C++ STL/STL_PolynomialSolver.hpp"
#include "../src/C++ STL/STL_CirculantMatrix.hpp"

// HEADERS FOR C
#include "../src/C/C_PolynomialSolver.hpp"
#include "../src/C/C_CirculantMatrixSolver.hpp"

int main(){

    PolynomialGenerator::initialise();
    PolynomialGenerator::generate_polynomials("../data/polynomials.txt", 1000);
    GenerateCirculantMatrix("../data/matrix.txt");

    PolynomialSolver("../data/polynomials.txt", "../results/shweicomplex_polynomials_solutions.txt");
    STL_PolynomialSolver("../data/polynomials.txt", "../results/stdcomplex_polynomials_solutions.txt");
    C_PolynomialSolver("../data/polynomials.txt", "../results/complexh_polynomials_solutions.txt");

    CirculantMatrix cm("../data/matrix.txt");
    cm.solve_and_output("../results/shweicomplex_matrix_solutions.txt");

    STL_CirculantMatrix stdcm("../data/matrix.txt");
    stdcm.solve_and_output("../results/stdcomplex_matrix_solutions.txt");

    C_solve_and_output("../data/matrix.txt", "../results/complexh_matrix_solutions.txt");

}
