#pragma once

#include "../src/Complex.hpp"
#include <vector>


void GenerateCirculantMatrix_direct(std::vector<Complex<double>>& main_row_vector, std::vector<Complex<double>>& free_coefs_vector);

void GenerateCirculantMatrix(const std::string& filename);