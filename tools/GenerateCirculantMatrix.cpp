#include "../include/Complex.hpp"
#include <random>
#include <fstream>
#include "../include/CirculantMatrix/GenerateCirculantMatrix.hpp"

void GenerateCirculantMatrix_direct(std::vector<Complex<double>>& main_row_vector, std::vector<Complex<double>>& free_coefs_vector){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-10000, 10000);

    main_row_vector.resize(16384);
    free_coefs_vector.resize(16384);

    for (int i = 0; i < 16384; ++i) {
        main_row_vector[i] = Complex(static_cast<double>(dist(gen)));
        free_coefs_vector[i] = Complex(static_cast<double>(dist(gen)));
    }
}

void GenerateCirculantMatrix(const std::string& filename){ //TODO: make the amount of elements a parameter, check if it is a power of 2.

    //TODO: method to check if param is a power of two.

    std::ofstream f_out(filename);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 101);

    f_out << "The first row of the circulant matrix: ";

    for (int i = 0; i < 16384; ++i){ //TODO: make param
        f_out << dist(gen) << ' ';
    }

    f_out << "\nThe constant vector: ";

    for (int i = 0; i < 16384; ++i){ //TODO: make param
        f_out << dist(gen) << ' ';
    }

    f_out.close();
}


