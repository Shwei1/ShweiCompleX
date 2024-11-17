#ifndef POLYNOMIAL_SOLVER_H
#define POLYNOMIAL_SOLVER_H

#ifdef __cplusplus
#include <complex>
typedef std::complex<double> c_double_complex;
extern "C" {
#else
#include <complex.h>
typedef double complex c_double_complex;
#endif



typedef struct C_PolynomialEquation {
    double coefficients[5];

    int (*get_equation_type)(struct C_PolynomialEquation* self);
    c_double_complex* (*solve)(struct C_PolynomialEquation* self, int* root_count);
    void (*solve_linear)(struct C_PolynomialEquation* self, c_double_complex* roots, int* root_count);
    void (*solve_quadratic)(struct C_PolynomialEquation* self, c_double_complex* roots, int* root_count);
    void (*solve_cubic)(struct C_PolynomialEquation* self, c_double_complex* roots, int* root_count);
    void (*solve_quartic)(struct C_PolynomialEquation* self, c_double_complex* roots, int* root_count);
} C_PolynomialEquation;

C_PolynomialEquation* PolynomialEquation_create(double* coeffs, int size);

void PolynomialEquation_destroy(C_PolynomialEquation* eq);

#ifdef __cplusplus
}
#endif

#endif