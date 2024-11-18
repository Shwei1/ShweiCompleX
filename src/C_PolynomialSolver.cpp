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

    auto start = std::chrono::high_resolution_clock::now();



    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Time consumed solving the equations with ShweiCompleX: " << duration.count() << " seconds" << std::endl;
    }



    f_in.close();
    f_out.close();
}