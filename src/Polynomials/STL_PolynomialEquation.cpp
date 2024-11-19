#include "../../include/Polynomials/STL_PolynomialEquation.hpp"
#include <cmath>
#include <iostream>

STL_PolynomialEquation::STL_PolynomialEquation(ComplexType a, ComplexType b, ComplexType c, ComplexType d, ComplexType e)
: coefficients_{a, b, c, d, e} {}

STL_PolynomialEquation::STL_PolynomialEquation(ComplexType a, ComplexType b, ComplexType c, ComplexType d)
: coefficients_{0, a, b, c, d} {}

STL_PolynomialEquation::STL_PolynomialEquation(ComplexType a, ComplexType b, ComplexType c)
: coefficients_{0, 0, a, b, c} {}

STL_PolynomialEquation::STL_PolynomialEquation(ComplexType a, ComplexType b)
: coefficients_{0, 0, 0, a, b} {}

STL_PolynomialEquation::STL_PolynomialEquation(ComplexType e)
: coefficients_{e, 0, 0, 0, 0} {}

std::vector<STL_PolynomialEquation::ComplexType> STL_PolynomialEquation::solve() const {
std::vector<ComplexType> roots;
switch (get_equation_type()) {
case 1:
roots = solve_linear();
break;
case 2:
roots = solve_quadratic();
break;
case 3:
roots = solve_cubic();
break;
default:
roots = solve_quartic();
break;
}
return roots;
}

std::vector<STL_PolynomialEquation::ComplexType> STL_PolynomialEquation::solve_linear() const {
    std::vector<ComplexType> root;
    ComplexType a = coefficients_[3];
    ComplexType b = coefficients_[4];

    if (a == ComplexType(0, 0) && b == ComplexType(0, 0)){
        root.emplace_back(std::nan("Infinite solutions"));
    }
    else if (a == ComplexType(0, 0) && b != ComplexType(0, 0)){
        root.emplace_back(std::nan("No solutions"));
    }
    else {
        ComplexType x = -b / a;
        root.push_back(x);
    }
    return root;
}

std::vector<STL_PolynomialEquation::ComplexType> STL_PolynomialEquation::solve_quadratic() const {
    ComplexType a = coefficients_[2];
    ComplexType b = coefficients_[3];
    ComplexType c = coefficients_[4];

    ComplexType discriminant = b * b - 4.0 * a * c;
    std::vector<ComplexType> roots;

    roots.push_back((-b + std::sqrt(discriminant)) / (2.0 * a));
    roots.push_back((-b - std::sqrt(discriminant)) / (2.0 * a));

    return roots;
}

std::vector<STL_PolynomialEquation::ComplexType> STL_PolynomialEquation::solve_cubic() const {
    std::vector<ComplexType> roots;

    ComplexType a = coefficients_[1];
    ComplexType b = coefficients_[2];
    ComplexType c = coefficients_[3];
    ComplexType d = coefficients_[4];

    ComplexType p = (std::complex<double>(3.0) * a * c - b * b) / (std::complex<double>(3.0) * a * a);
    ComplexType q = (std::complex<double>(2.0) * b * b * b - std::complex<double>(9.0) * a * b * c + std::complex<double>(27.0) * a * a * d) /
                    (std::complex<double>(27.0) * a * a * a);

    ComplexType discriminant = (q * q) / std::complex<double>(4.0) + (p * p * p) / std::complex<double>(27.0);

    ComplexType discriminant_root = std::sqrt(discriminant);

    if (discriminant.real() > 0) {
        ComplexType u = std::cbrt((-q.real())/2 + discriminant_root.real());
        ComplexType v = std::cbrt((-q.real())/2 - discriminant_root.real());

        ComplexType x1 = u + v;

        ComplexType x2 = -(u + v) / std::complex<double>(2.0) + ComplexType(0.0, std::sqrt(3.0) / 2.0) * (u - v);
        ComplexType x3 = -(u + v) / std::complex<double>(2.0) - ComplexType(0.0, std::sqrt(3.0) / 2.0) * (u - v);

        roots.push_back(x1);
        roots.push_back(x2);
        roots.push_back(x3);
    } else if (discriminant.real() == 0) {

        ComplexType u = std::pow(q / std::complex<double>(2.0), std::complex<double>(1.0 / 3.0));

        ComplexType x1 = std::complex<double>(2.0) * u;
        ComplexType x2 = -u;
        ComplexType x3 = x2;

        roots.push_back(x1);
        roots.push_back(x2);
        roots.push_back(x3);
    } else {
        double r = 2.0 * std::sqrt(-p.real() / 3.0);
        double theta = std::acos((3.0 * q.real()) / (2.0 * p.real()) * std::sqrt(-3.0 / p.real()));


        roots.push_back(r * std::complex<double>(std::cos(theta / 3.0), 0.0));
        roots.push_back(r * std::complex<double>(std::cos((theta + 2.0 * M_PI) / 3.0), 0.0));
        roots.push_back(r * std::complex<double>(std::cos((theta + 4.0 * M_PI) / 3.0), 0.0));

    }

    ComplexType shift = -b / (std::complex<double>(3.0) * a);

    for (auto& root : roots) {
        root = root + shift;
    }
    return roots;
}


std::vector<STL_PolynomialEquation::ComplexType> STL_PolynomialEquation::solve_quartic() const {
    ComplexType a = coefficients_[0];
    ComplexType b = coefficients_[1];
    ComplexType c = coefficients_[2];
    ComplexType d = coefficients_[3];
    ComplexType e = coefficients_[4];

    std::vector<ComplexType> roots;

    ComplexType qa = a;
    ComplexType qb = b;

    a = b / qa;
    b = c / qa;
    c = d / qa;
    d = e / qa;

    ComplexType a0 = std::complex<double>(0.25) * a;
    ComplexType a02 = a0 * a0;

    ComplexType p = std::complex<double>(3.0) * a02 - std::complex<double>(0.5) * b;
    ComplexType q = a * a02 - b * a0 + std::complex<double>(0.5) * c;
    ComplexType r = std::complex<double>(3.0) * a02 * a02 - b * a02 + c * a0 - d;

    STL_PolynomialEquation cubic_resolvent(std::complex<double>(1.0),p,r,p * r - std::complex<double>(0.5) * q * q);

    auto resolvent_roots = cubic_resolvent.solve_cubic();

    ComplexType z = resolvent_roots[0];

    for (const auto& root : resolvent_roots) {
        if (root.imag() == 0 && root.real() > z.real()) {
            z = root;
        }
    }

    ComplexType alpha = std::sqrt(std::complex<double>(2.0) * p.real() + std::complex<double>(2.0) * z.real());

    ComplexType beta;
    if (alpha == std::complex<double>(0.0, 0.0)) {
        beta = z * z + r;
    } else {
        beta = -q / alpha;
    }

    STL_PolynomialEquation quadratic1(std::complex<double>(1.0), alpha, z + beta);
    STL_PolynomialEquation quadratic2(std::complex<double>(1.0), -alpha, z - beta);

    auto roots1 = quadratic1.solve_quadratic();
    auto roots2 = quadratic2.solve_quadratic();

    roots.insert(roots.end(), roots1.begin(), roots1.end());
    roots.insert(roots.end(), roots2.begin(), roots2.end());

    ComplexType shift = -qb / (std::complex<double>(4.0) * qa);
    for (auto& root : roots) {
        root = root + shift;
    }

    return roots;
}


int STL_PolynomialEquation::get_equation_type() const{
    if (coefficients_[0] != ComplexType(0))
        return 4;
    else if (coefficients_[1] != ComplexType(0))
        return 3;
    else if (coefficients_[2] != ComplexType(0))
        return 2;
    else
        return 1;
}
