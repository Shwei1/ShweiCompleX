#pragma once

#include <string>
#include "STL_PolynomialEquation.hpp"

std::string trigonometric(const STL_PolynomialEquation::ComplexType& z);

std::string exponential(const STL_PolynomialEquation::ComplexType& z);
/**
 *
 * @param filename_in назва/шлях файлу вводу.
 * @param filename_out назва/шлях файлу виводу.
 * @example
 * STL_PolynomialSolver("polynomials_in.txt", "polynomials_out.txt");
 * // Виведе розв‘язані рівняння у форматі:
 * // [Polynomial] = 0;
 * //   Roots in regular form: [roots]
 * //   Roots in trigonometric form: [roots]
 * //   Roots in exponential form: [roots]
 */

void STL_PolynomialSolver(const std::string& filename_in, const std::string& filename_out);