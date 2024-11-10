#pragma once

#include <vector>
#include <array>
#include "Complex.hpp"

class PolynomialEquation {
public:
    using ComplexType = Complex<double>;

    PolynomialEquation(ComplexType a, ComplexType b, ComplexType c, ComplexType d, ComplexType e);
    PolynomialEquation(ComplexType a, ComplexType b, ComplexType c, ComplexType d);
    PolynomialEquation(ComplexType a, ComplexType b, ComplexType c);
    PolynomialEquation(ComplexType a, ComplexType b);
    PolynomialEquation(ComplexType e);

    [[nodiscard]] std::vector<ComplexType> solve() const;
    [[nodiscard]] std::vector<ComplexType> solve_linear() const;
    [[nodiscard]] std::vector<ComplexType> solve_quadratic() const;
    [[nodiscard]] std::vector<ComplexType> solve_cubic() const;
    [[nodiscard]] std::vector<ComplexType> solve_quartic() const;

private:
    std::array<ComplexType, 5> coefficients_;
    [[nodiscard]] int get_equation_type() const;
};



