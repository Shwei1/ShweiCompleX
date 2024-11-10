#include <iostream>
#include "PolynomialEquation.hpp"
#include "PolynomialGenerator.hpp"

int main(){
    PolynomialGenerator::initialise();
    PolynomialGenerator::generate_polynomials("../polynomials.txt", 100);
//    PolynomialEquation cubic1(0, 1, -6, 11, -6);5
//    auto roots = cubic1.solve_cubic();
//    std::cout << roots[0] << ' ' << roots[1] << ' ' << roots[2] << std::endl;
//
//    PolynomialEquation cubic2(0, 1, 0, -7, 6);
//    auto roots2 = cubic2.solve_cubic();
//    std::cout << roots2[0] << ' ' << roots2[1] << ' ' << roots2[2] << std::endl;
//
//    PolynomialEquation cubic3(0, 1, 0, -1, 1);
//    auto roots3 = cubic3.solve_cubic();
//    std::cout << roots3[0] << ' ' << roots3[1] << ' ' << roots3[2] << std::endl;
//    PolynomialEquation quadratic1(0, 0, 1, 0, 1);
//    auto roots4 = quadratic1.solve_quadratic();
//    std::cout << roots4[0] << ", " << roots4[1];
    PolynomialEquation quart(1, 0, 0, 0, 1);
    auto rootsquart = quart.solve();
    std::cout << rootsquart[0] << ' ' << rootsquart[1] << ' ' << rootsquart[2] << ' ' << rootsquart[3] << std::endl;
}
