#ifndef C_CIRCULANT_MATRIX_H
#define C_CIRCULANT_MATRIX_H

#ifdef __cplusplus
#include <complex>
typedef std::complex<double> c_double_complex;
extern "C" {
#else
#include <complex.h>
typedef double complex c_double_complex;
#endif

#define MATRIX_SIZE 16384

typedef struct C_CirculantMatrix {
    c_double_complex A[MATRIX_SIZE];
    c_double_complex b[MATRIX_SIZE];

    void (*solve)(struct C_CirculantMatrix* self, c_double_complex* solution, int size);
    void (*fft)(c_double_complex* vec, int size);
    void (*ifft)(c_double_complex* vec, int size);
//    void (*output)(struct C_CirculantMatrix* self);
    void (*row_to_column)(const c_double_complex* first_row, c_double_complex* first_column, int size);  // Added here
} C_CirculantMatrix;



void C_CirculantMatrix_init(C_CirculantMatrix* self, const char* filename);


void C_CirculantMatrix_solve(C_CirculantMatrix* self, c_double_complex* solution, int size);
void C_CirculantMatrix_fft(c_double_complex* vec, int size);
void C_CirculantMatrix_ifft(c_double_complex* vec, int size);
void C_CirculantMatrix_output(C_CirculantMatrix* self);
void C_CirculantMatrix_row_to_column(const c_double_complex* first_row, c_double_complex* first_column, int size);

#ifdef __cplusplus
}
#endif

#endif // C_CIRCULANT_MATRIX_H


