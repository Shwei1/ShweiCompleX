#include <iostream>
#include "PolynomialEquation.hpp"

int main(){
    PolynomialEquation cubic1(0, 1, -6, 11, -6);
    auto roots = cubic1.solve_cubic();
    std::cout << roots[0] << ' ' << roots[1] << ' ' << roots[2] << std::endl;

    PolynomialEquation cubic2(0, 1, 0, -7, 6);
    auto roots2 = cubic2.solve_cubic();
    std::cout << roots2[0] << ' ' << roots2[1] << ' ' << roots2[2] << std::endl;

    PolynomialEquation cubic3(0, 1, 0, -1, 1);
    auto roots3 = cubic3.solve_cubic();
    std::cout << roots3[0] << ' ' << roots3[1] << ' ' << roots3[2] << std::endl;

}
