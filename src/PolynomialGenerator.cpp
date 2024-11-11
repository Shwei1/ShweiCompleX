#include "PolynomialGenerator.hpp"
#include <fstream>
#include <stdexcept>

std::random_device PolynomialGenerator::rd;
std::mt19937 PolynomialGenerator::gen(PolynomialGenerator::rd());
std::uniform_int_distribution<> PolynomialGenerator::type_distr(1, 4);
std::uniform_int_distribution<> PolynomialGenerator::coef_distr(-50, 50);

void PolynomialGenerator::initialise() {
    gen.seed(rd());
    type_distr = std::uniform_int_distribution<>(1, 4);
    coef_distr = std::uniform_int_distribution<>(-50, 50);
}

void PolynomialGenerator::generate_polynomials(const std::string& filename, int n) {
    std::ofstream f_out(filename);
    if (!f_out) {
        throw std::runtime_error("Could not open the file.");
    }

    for (int i = 0; i < n; ++i) {
        std::string polynomial;
        int degree = type_distr(gen);
        for (int j = degree; j >= 0; --j) {
            int coef = coef_distr(gen);
            std::string str_coef = std::to_string(coef);
            std::string str_power = std::to_string(j);
            if (j != degree) {
                polynomial += "+ ";
            }
            if (j == 1)
                polynomial += str_coef + " x" + ' ';
            else if (j == 0)
                polynomial += str_coef + " = 0";
            else {
                polynomial += str_coef + " x^" + str_power + ' ';
            }
        }
        f_out << polynomial << '\n';
    }
    f_out.close();
}