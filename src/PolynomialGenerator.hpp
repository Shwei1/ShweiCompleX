#pragma once

#include <string>
#include <random>

class PolynomialGenerator {
private:
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_int_distribution<> type_distr;
    static std::uniform_int_distribution<> coef_distr;

public:

    static void initialise();

    static void generate_polynomials(const std::string& filename, int n);
};
