#pragma once

#include <string>


/**
 *
 * @param filename_in назва/шлях файлу вводу.
 * @param filename_out назва/шлях файлу виводу.
 * @example
 * PolynomialSolver("polynomials_in.txt", "polynomials_out.txt");
 * // Виведе розв‘язані рівняння у форматі:
 * // [Polynomial] = 0;
 * //   Roots in regular form: [roots]
 * //   Roots in trigonometric form: [roots]
 * //   Roots in exponential form: [roots]
 */
void PolynomialSolver(const std::string& filename_in, const std::string& filename_out);

