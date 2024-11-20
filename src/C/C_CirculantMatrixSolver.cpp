#include "C_CirculantMatrixSolver.hpp"

void C_solve_and_output(const char* input_filename, const char* output_filename){
    std::ofstream f_out(output_filename);
    if (!f_out){
        throw std::runtime_error("Could not open the file.");
    }
    const int size = MATRIX_SIZE;

    C_CirculantMatrix matrix;

    C_CirculantMatrix_init(&matrix, input_filename);


    c_double_complex solutions[size];

    auto start = std::chrono::high_resolution_clock::now();

    matrix.solve(&matrix, solutions, size);

    auto end = std::chrono::high_resolution_clock::now();

    f_out << "Solutions for the system of linear equations: (";
    for (int i = 0; i < size; ++i) {
        f_out << solutions[i].real() << ", ";
    }
    f_out << ")\n\n";

    std::chrono::duration<double> duration = end - start;
    f_out << "Time consumed solving the system with <complex.h>: " << duration.count() << " seconds" << std::endl;

    f_out << "\nLet's test if the solutions hold for the first row: ";

    double real_result = 0;
    double imag_result = 0;
    for (int i = 0; i < size; ++i) {
        double real_term = matrix.A[i].real() * solutions[i].real() - (matrix.A[i].imag() * solutions[i].imag());
        double imag_term = matrix.A[i].real() * solutions[i].imag() + matrix.A[i].imag() * solutions[i].real();
        real_result += real_term;
        imag_result += imag_term;
    }

    if (fabs(real_result - matrix.b[0].real()) < 1e-10) {
        f_out << "TRUE" << std::endl;
    } else {
        f_out << "FALSE" << std::endl;
    }
    f_out << "Expected result: " << matrix.b[0].real() << std::endl;
    f_out << "Actual result: " << real_result << std::endl;

    f_out.close();
}