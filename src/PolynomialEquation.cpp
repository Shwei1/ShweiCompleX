#include "PolynomialEquation.hpp"
#include "Complex.hpp"
#include <cmath>

PolynomialEquation::PolynomialEquation(ComplexType a, ComplexType b, ComplexType c, ComplexType d, ComplexType e)
        : coefficients_{a, b, c, d, e} {}

PolynomialEquation::PolynomialEquation(ComplexType a, ComplexType b, ComplexType c, ComplexType d)
            : coefficients_{0, a, b, c, d} {}

PolynomialEquation::PolynomialEquation(ComplexType a, ComplexType b, ComplexType c)
            : coefficients_{0, 0, a, b, c} {}

PolynomialEquation::PolynomialEquation(ComplexType a, ComplexType b)
            : coefficients_{0, 0, 0, a, b} {}

PolynomialEquation::PolynomialEquation(ComplexType e)
            : coefficients_{e, 0, 0, 0, 0} {}

std::vector<PolynomialEquation::ComplexType> PolynomialEquation::solve() const {
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

std::vector<PolynomialEquation::ComplexType> PolynomialEquation::solve_linear() const {
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

std::vector<PolynomialEquation::ComplexType> PolynomialEquation::solve_quadratic() const {
        ComplexType a = coefficients_[2];
        ComplexType b = coefficients_[3];
        ComplexType c = coefficients_[4];

        ComplexType discriminant = b * b - 4.0 * a * c;
        std::vector<ComplexType> roots;

        roots.push_back((-b + ComplexType::sqrt(discriminant)) / (2.0 * a));
        roots.push_back((-b - ComplexType::sqrt(discriminant)) / (2.0 * a));

        return roots;
    }

std::vector<PolynomialEquation::ComplexType> PolynomialEquation::solve_cubic() const {
    std::vector<ComplexType> roots;

    ComplexType a = coefficients_[1];  // Cubic term
    ComplexType b = coefficients_[2];  // Quadratic term
    ComplexType c = coefficients_[3];  // Linear term
    ComplexType d = coefficients_[4];  // Constant term

    ComplexType p = (3 * a * c - b * b) / (3 * a * a);
    ComplexType q = (2 * b * b * b - 9 * a * b * c + 27 * a * a * d)/(27 * a * a * a);

    ComplexType discriminant = (q * q) / 4 + (p * p * p) / 27;

    ComplexType discriminant_root = ComplexType::sqrt(discriminant);


    if (discriminant.get_real() > 0) {

        ComplexType u = std::cbrt((-q.get_real()) / 2 + discriminant_root.get_real());
        ComplexType v = std::cbrt((-q.get_real()) / 2 - discriminant_root.get_real());

        ComplexType x1 = u + v;

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

std::vector<PolynomialEquation::ComplexType> PolynomialEquation::solve_quartic() const {
    ComplexType a = coefficients_[0];
    ComplexType b = coefficients_[1];
    ComplexType c = coefficients_[2];
    ComplexType d = coefficients_[3];
    ComplexType e = coefficients_[4];

    std::vector<ComplexType> roots;

    ComplexType qa = a;
    ComplexType qb = b;

    a = b/qa;
    b = c/qa;
    c = d/qa;
    d = e/qa;

    ComplexType a0 = 0.25 * a;
    ComplexType a02 = a0 * a0;

    ComplexType p = 3 * a02 - 0.5 * b;
    ComplexType q = a * a02 - b * a0 + 0.5 * c;
    ComplexType r = 3 * a02*a02 - b*a02 + c*a0 - d;

    PolynomialEquation cubic_resolvent(1, p, r, p*r - 0.5*q*q);

    auto resolvent_roots = cubic_resolvent.solve_cubic();

    ComplexType z = resolvent_roots[0];

    for (const auto& root : resolvent_roots) {
        if (root.get_imag() == 0 && root.get_real() > z.get_real()) {
            z = root;
        }
    }

    ComplexType alpha = std::sqrt(2*p.get_real() + 2*z.get_real());

    ComplexType beta;
    if (alpha == ComplexType(0, 0)){
        beta = z*z + r;
    }
    else {
        beta = -q / alpha;
    }

    PolynomialEquation quadratic1(1, alpha, z + beta);
    PolynomialEquation quadratic2(1, -alpha, z - beta);

    auto roots1 = quadratic1.solve_quadratic();
    auto roots2 = quadratic2.solve_quadratic();

    roots.insert(roots.end(), roots1.begin(), roots1.end());
    roots.insert(roots.end(), roots2.begin(), roots2.end());

    ComplexType shift = -qb / (4 * qa);
    for (auto& root : roots) {
        root = root + shift;
    }

    return roots;
}

int PolynomialEquation::get_equation_type() const{
        if (coefficients_[0] != 0)
            return 4;
        else if (coefficients_[1] != 0)
            return 3;
        else if (coefficients_[2] != 0)
            return 2;
        else
            return 1;
    }

