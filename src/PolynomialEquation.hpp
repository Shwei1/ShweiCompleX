#pragma once

#include "PolynomialException.hpp"
#include "Complex.hpp"
#include <vector>
#include <variant>
#include <cmath>
#include <array>

class PolynomialEquation {
public:
    using ComplexType = Complex<double>;

    PolynomialEquation(ComplexType a, ComplexType b, ComplexType c, ComplexType d, ComplexType e)
            : coefficients_{a, b, c, d, e} {}

    PolynomialEquation(ComplexType a, ComplexType b, ComplexType c, ComplexType d)
            : coefficients_{0, a, b, c, d} {}

    PolynomialEquation(ComplexType a, ComplexType b, ComplexType c)
            : coefficients_{0, 0, a, b, c} {}

    PolynomialEquation(ComplexType a, ComplexType b)
            : coefficients_{0, 0, 0, a, b} {}

    PolynomialEquation(ComplexType e)
            : coefficients_{e, 0, 0, 0, 0} {}


    [[nodiscard]]std::vector<ComplexType> solve_quadratic() const {
        ComplexType a = coefficients_[2];
        ComplexType b = coefficients_[1];
        ComplexType c = coefficients_[0];

        ComplexType discriminant = b * b - 4.0 * a * c;
        std::vector<ComplexType> roots;

        roots.push_back((-b + ComplexType::sqrt(discriminant)) / (2.0 * a));
        roots.push_back((-b - ComplexType::sqrt(discriminant)) / (2.0 * a));

        return roots;
    }

    [[nodiscard]] std::vector<ComplexType> solve_cubic() const {
        std::vector<ComplexType> roots;

        ComplexType a = coefficients_[1];  // Cubic term
        ComplexType b = coefficients_[2];  // Quadratic term
        ComplexType c = coefficients_[3];  // Linear term
        ComplexType d = coefficients_[4];  // Constant term

        ComplexType p = (3 * a * c - b * b) / (3 * a * a);
        ComplexType q = (2 * b * b * b - 9 * a * b * c + 27 * a * a * d)/(27 * a * a * a);

        std::cout << "The value of p: " << p << std::endl;
        std::cout << "The value of q: " << q << std::endl;

        ComplexType discriminant = (q * q) / 4 + (p * p * p) / 27;

        std::cout << "The value of the discriminant: " << discriminant << std::endl;

        ComplexType discriminant_root = ComplexType::sqrt(discriminant);

        std::cout << "The value of the discriminant root: " << discriminant_root << std::endl;

        if (discriminant.get_real() > 0) {
            std::cout << "You have called the case for d>0." << std::endl;
            ComplexType u = std::cbrt((-q.get_real()) / 2 + discriminant_root.get_real());
            ComplexType v = std::cbrt((-q.get_real()) / 2 - discriminant_root.get_real());

            std::cout << "The value of u: " << u << std::endl;
            std::cout << "The value of v: " << v << std::endl;

            ComplexType omega1 = Complex(1.0).roots(3)[1];
            ComplexType omega2 = Complex(1.0).roots(3)[2];

            ComplexType x1 = u + v;

            std::cout << "The value of u+v: " << x1 << std::endl;

            ComplexType x2 = -(u + v) / 2 + ComplexType(0, std::sqrt(3.0) / 2) * (u - v);
            ComplexType x3 = -(u + v) / 2 - ComplexType(0, std::sqrt(3.0) / 2) * (u - v);

            roots.push_back(x1);
            roots.push_back(x2);
            roots.push_back(x3);
        }
        else if (discriminant.get_real() == 0){
            ComplexType u = ComplexType::cbrt(q/2);
            ComplexType x1 = 2 * u;
            ComplexType x2 = -u;
            ComplexType x3 = x2;

            roots.push_back(x1);
            roots.push_back(x2);
            roots.push_back(x3);
        }
        else {

            double r = 2.0 * std::sqrt(-p.get_real() / 3.0);
            double theta = std::acos(3.0 * q.get_real() / (2.0 * p.get_real()) * std::sqrt(-3.0 / p.get_real()));

            ComplexType x1 = r * std::cos(theta / 3.0);
            ComplexType x2 = r * std::cos((theta + 2.0 * M_PI) / 3.0);
            ComplexType x3 = r * std::cos((theta + 4.0 * M_PI) / 3.0);

            roots.push_back(x1);
            roots.push_back(x2);
            roots.push_back(x3);
        }


        ComplexType shift = -b / (3.0 * a);

        for (auto& root : roots) {
            root = root + shift;
        }
        return roots;
    }

private:
    std::array<ComplexType, 5> coefficients_;

    int get_equation_type() const{
        if (coefficients_[4] != 0)
            return 4;
        else if (coefficients_[3] != 0)
            return 3;
        else if (coefficients_[2] != 0)
            return 2;
        else if (coefficients_[1] != 0)
            return 1;
        else
            return 0;
    }
};



