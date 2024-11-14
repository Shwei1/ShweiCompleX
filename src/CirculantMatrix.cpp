#include "CirculantMatrix.hpp"
#include <sstream>
#include <chrono>
#include <cmath>
#include <stdexcept>

std::vector<CirculantMatrix::ComplexType> CirculantMatrix::row_to_column(const std::vector<ComplexType>& first_row) {

    if (first_row.empty()) {
        throw std::invalid_argument("The first row vector is empty.");
    }

    std::vector<ComplexType> first_column = first_row;

    std::reverse(first_column.begin() + 1, first_column.end());

    return first_column;
}

CirculantMatrix::CirculantMatrix(const std::vector<ComplexType> &A, const std::vector<ComplexType> &b): A(A), b(b){}

CirculantMatrix::CirculantMatrix(const std::string &filename) {
    std::ifstream f_in(filename);
    if(!f_in){
        throw std::runtime_error("Could not open the file.");
    }

    std::vector<ComplexType> main_row;
    std::vector<ComplexType> free_coefs;

    main_row.reserve(8);
    free_coefs.reserve(8);

    std::string line;
    if (std::getline(f_in, line)){
        size_t pos = line.find(':');

        std::istringstream stream_nums(line.substr(pos + 1));
        int num;

        while(stream_nums >> num){
            main_row.emplace_back(num);
        }
    }

    if(std::getline(f_in, line)){
        size_t pos = line.find(':');

        std::istringstream stream_nums(line.substr(pos + 1));
        int num;

        while(stream_nums >> num){
            free_coefs.emplace_back(num);
        }
    }

    this->A = main_row;
    this->b = free_coefs;
    f_in.close();
}

std::vector<CirculantMatrix::ComplexType> CirculantMatrix::solve() {
    unsigned long n = A.size();


    std::vector<ComplexType> fft_A = row_to_column(A);
    fast_fourier_transform(fft_A);


    std::vector<ComplexType> fft_B = b;
    fast_fourier_transform(fft_B);

    std::vector<ComplexType> fft_X(n);
    for (int k = 0; k < n; ++k) {
        if (fft_A[k] != Complex(0.0)) {
            fft_X[k] = fft_B[k] / fft_A[k];
        } else {
            fft_X[k] = Complex(0.0);
        }
    }

    inverse_fft(fft_X);

    return fft_X;
}

void CirculantMatrix::solve_and_output(const std::string &filename) {
    std::ofstream f_out(filename);

    auto start = std::chrono::high_resolution_clock::now();

    auto solutions = solve();

    auto end = std::chrono::high_resolution_clock::now();

    f_out << "Solutions for the system of linear equations: (";
    for (ComplexType solution: solutions){
        f_out << solution << ", ";
    }
    f_out << ")\n\n";

    std::chrono::duration<double> duration = end - start;
    f_out << "Time consumed solving the system with ShweiCompleX: " << duration.count() << " seconds" << std::endl;

    f_out << "\nLet's test if the solutions hold for the first row: ";

    double real_result = 0;
    double imag_result = 0;
    for (int i = 0; i < solutions.size(); ++i) {
        double real_term = A[i].get_real() * solutions[i].get_real() - (A[i].get_imag() * solutions[i].get_imag());
        double imag_term = A[i].get_real() * solutions[i].get_imag() + A[i].get_imag() * solutions[i].get_real();
        real_result += real_term;
        imag_result += imag_term;
    }

    if (fabs(real_result - b[0].get_real()) < 1e-10) {
        f_out << "TRUE" << std::endl;
    } else {
        f_out << "FALSE" << std::endl;
    }
    f_out << "Expected result: " << b[0].get_real() << std::endl;
    f_out << "Actual result: " << real_result << std::endl;

    f_out.close();

}

void CirculantMatrix::fast_fourier_transform(std::vector<ComplexType> &vec) { //NOLINT
    unsigned long n = vec.size();
    if (n <= 1) return;

    std::vector<ComplexType> even(n / 2);
    std::vector<ComplexType> odd(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        even[i] = vec[i * 2];
        odd[i] = vec[i * 2 + 1];
    }

    fast_fourier_transform(even);
    fast_fourier_transform(odd);

    std::vector<ComplexType> unity_roots(n);
    for (int k = 0; k < n / 2; ++k) {
        double angle = -2 * M_PI * k / n;
        unity_roots[k] = ComplexType(std::cos(angle), std::sin(angle));
    }

    for (int j = 0; j < n / 2; ++j) {
        ComplexType t = unity_roots[j] * odd[j];
        vec[j] = even[j] + t;
        vec[j + n / 2] = even[j] - t;
    }
}

void CirculantMatrix::inverse_fft(std::vector<ComplexType>& vec) {
    unsigned long n = vec.size();

    for (int i = 0; i < n; ++i) {
        vec[i] = vec[i].conjugate();
    }

    fast_fourier_transform(vec);

    for (int i = 0; i < n; ++i) {
        vec[i] = vec[i].conjugate() / n;
    }

//    std::rotate(vec.rbegin(), vec.rbegin() + 1, vec.rend());

}