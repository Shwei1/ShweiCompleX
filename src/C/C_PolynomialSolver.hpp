#include "C_PolynomialEquation.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <chrono>

/**
 * @brief Функція, що зручно завертає вирішення поліномів типу C_PolynomialEquation для вводу їх з файлу та
 *        виведення їх в інший.
 * @note Ця функція відповідально підчищає виділену на рівняння пам‘ять, тому витоків пам‘яті за її використання не буде.
 * @param filename_in — назва файлу вводу. Формат вводу показано нижче:
 * @example //polynomials_in.txt:
 * a x^4 + b x^3 + c x^2 + d x + e = 0
 * a x^4 + -b x^3 + -c x^3 + d x + e = 0
 * ...
 * @param filename_out — назва файлу виводу.
 * @example
 * PolynomialSolver("polynomials_in.txt", "polynomials_out.txt");
 * // Виведе розв‘язані рівняння у форматі:
 * // [Polynomial] = 0;
 * //   Roots in regular form: [roots]
 * //   Roots in trigonometric form: [roots]
 * //   Roots in exponential form: [roots]
 */
void C_PolynomialSolver(const std::string& filename_in, const std::string& filename_out);