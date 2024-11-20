#pragma once
#include <fstream>
#include "C_CirculantMatrix.h"
#include <chrono>

/**
 * @brief функція, що завертає в собі вирішення системи рівнянь, заданих циркулюючою матрицею.
 * @param input_filename — назва (шлях) файла вводу у форматі:
 * @example //my_matrix.txt:
 * Coefficients for A followed by a colon: A1 A2 ... A16384
 * Coefficients for b followed by a colon: b1 b2 ... b16384
 * @param output_filename — шлях або назва файла для виводу.
 */
void C_solve_and_output(const char* input_filename, const char* output_filename);