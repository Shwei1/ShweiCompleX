#include "C_PolynomialEquation.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <chrono>

void C_PolynomialSolver(const std::string& filename_in, const std::string& filename_out) {
    std::ifstream f_in(filename_in);
    std::ofstream f_out(filename_out);

    if (!(f_out && f_in)) {
        throw std::runtime_error("Could not open the file.");
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::string line;
    while (std::getline(f_in, line)) {
        double coefficients[5] = {0, 0, 0, 0, 0};
        std::stringstream ss(line);
        double coef;
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


        double coefs[5] = {coefficients[0], coefficients[1], coefficients[2], coefficients[3], coefficients[4] };

        C_PolynomialEquation* cpolynom = PolynomialEquation_create(coefs, 5);

        int root_count = 0;
        c_double_complex* roots = cpolynom->solve(cpolynom, &root_count);

        f_out << line << std::endl;
        f_out << "\tRoots in regular form: (";
        for (int i = 0; i < root_count; i++){
            f_out << roots[i].real() << " + " << roots[i].imag() << "i, ";
        }
        f_out << ")\n";
        f_out << "\tRoots in trigonometric form: (";
        for (int i = 0; i < root_count; i++) {
            double r = std::sqrt(roots[i].real() * roots[i].real() + roots[i].imag() * roots[i].imag());
            double theta = std::atan2(roots[i].imag(), roots[i].real());
            f_out << r << " * (cos(" << theta << ") + i*sin(" << theta << ")), ";
        }
        f_out << ")\n";
        f_out << "\tRoots in exponential form: (";
        for (int i = 0; i < root_count; i++) {
            double r = std::sqrt(roots[i].real() * roots[i].real() + roots[i].imag() * roots[i].imag());
            double theta = std::atan2(roots[i].imag(), roots[i].real());
            f_out << r << " * e^(i * " << theta << "), ";
        }
        f_out << ")\n\n";
        free(roots);

        PolynomialEquation_destroy(cpolynom);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    f_out << "Time consumed solving the equations with <complex.h>: " << duration.count() << " seconds" << std::endl;


    f_in.close();
    f_out.close();
}