#include "../../include/Polynomials/PolynomialEquation.hpp"
#include "../../include/Polynomials/PolynomialSolver.hpp"
#include <fstream>
#include <iostream>
#include <chrono>

void PolynomialSolver(const std::string& filename_in, const std::string& filename_out) {
    std::ifstream f_in(filename_in);
    std::ofstream f_out(filename_out);

    if (!(f_out && f_in)) {
        throw std::runtime_error("Could not open the file.");
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::string line;
    while (std::getline(f_in, line)) {
        int coefficients[5] = {0, 0, 0, 0, 0};
        std::stringstream ss(line);
        int coef;
        std::string power;
        std::string token;
// -25 x^3 + 16 x^2 + -13 x + -18 = 0

        while(ss >> coef >> power >> token){
            if (power == "x^4"){
                coefficients[0] = coef;
            }
            else if (power == "x^3"){
                coefficients[1] = coef;
            }
            else if (power == "x^2"){
                coefficients[2] = coef;
            }
            else if (power == "x"){
                coefficients[3] = coef;
            }
            else {
                coefficients[4] = coef;
            }
        }


        PolynomialEquation polynomial(coefficients[0], coefficients[1], coefficients[2], coefficients[3], coefficients[4]);
        auto roots = polynomial.solve();
        f_out << line << std::endl;
        f_out << "\tRoots in regular form: (";
        for (PolynomialEquation::ComplexType root : roots){
            f_out << root << ", ";
        }
        f_out << ")\n";
        f_out << "\tRoots in trigonometric form: (";
        for (PolynomialEquation::ComplexType root : roots){
            f_out << root.trigonometric() << ", ";
        }
        f_out << ")\n";
        f_out << "\tRoots in exponential form: (";
        for (PolynomialEquation::ComplexType root : roots){
            f_out << root.exponential() << ", ";
        }
        f_out << ")\n\n";

    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    f_out << "Time consumed solving the equations with ShweiCompleX: " << duration.count() << " seconds" << std::endl;


    f_in.close();
    f_out.close();
}