#include <complex.h>
#include <tgmath.h>
#include <stdlib.h>
#include <stdio.h>
#include "C_PolynomialEquation.h"

int get_equation_type_impl(struct C_PolynomialEquation* self) {
    for (int i = 0; i < 5; i++) {
        if (self->coefficients[i] != 0.0) {
            return 4-i;
        }
    }
    return 0;
}

double complex* solve(struct C_PolynomialEquation* self, int* root_count) {
    if (!self || !root_count) {
        printf("Invalid arguments: self or root_count is NULL\n");
        return NULL;
    }

    int degree = self->get_equation_type(self);
    if (degree < 1 || degree > 4) {
        printf("Invalid degree: %d\n", degree);
        *root_count = 0;
        return NULL;
    }

    *root_count = degree;

    double complex* roots = (double complex*)malloc(sizeof(double complex) * degree);
    if (!roots) {
        printf("Failed to allocate memory for roots\n");
        *root_count = 0;
        return NULL;
    }

    switch (degree) {
        case 1:
            if (self->solve_linear) {
                self->solve_linear(self, roots, root_count);
            } else {
                printf("solve_linear function pointer is NULL\n");
                free(roots);
                *root_count = 0;
                return NULL;
            }
            break;
        case 2:
            if (self->solve_quadratic) {
                self->solve_quadratic(self, roots, root_count);
            } else {
                printf("solve_quadratic function pointer is NULL\n");
                free(roots);
                *root_count = 0;
                return NULL;
            }
            break;
        case 3:
            if (self->solve_cubic) {
                self->solve_cubic(self, roots, root_count);
            } else {
                printf("solve_cubic function pointer is NULL\n");
                free(roots);
                *root_count = 0;
                return NULL;
            }
            break;
        case 4:
            if (self->solve_quartic) {
                self->solve_quartic(self, roots, root_count);
            } else {
                printf("solve_quartic function pointer is NULL\n");
                free(roots);
                *root_count = 0;
                return NULL;
            }
            break;
        default:
            printf("Unexpected degree: %d\n", degree);
            free(roots);
            *root_count = 0;
            return NULL;
    }

    return roots;
}


void solve_linear_impl(C_PolynomialEquation* self, c_double_complex* roots, int* root_count) {
    if (self->coefficients[3] != 0.0) {
        roots[0] = -self->coefficients[4] / self->coefficients[3];
        *root_count = 1;
    } else {
        *root_count = 0;
    }
}

void solve_quadratic_impl(struct C_PolynomialEquation* self, c_double_complex* roots, int* root_count) {
    c_double_complex a = self->coefficients[2];
    c_double_complex b = self->coefficients[3];
    c_double_complex c = self->coefficients[4];

    if (a == 0.0) {
        *root_count = 0;
        return;
    }

    c_double_complex discriminant = b * b - 4.0 * a * c;

    roots[0] = (-b + sqrt(discriminant)) / (2.0 * a);
    roots[1] = (-b - sqrt(discriminant)) / (2.0 * a);

    *root_count = 2;
}

void solve_cubic_impl(struct C_PolynomialEquation* self, c_double_complex* roots, int* root_count) {
    c_double_complex a = self->coefficients[1]; // Cubic term
    c_double_complex b = self->coefficients[2]; // Quadratic term
    c_double_complex c = self->coefficients[3]; // Linear term
    c_double_complex d = self->coefficients[4]; // Constant term

    printf("Initialised coefficients: %lf %lf %lf %lf\n", creal(a), creal(b), creal(c), creal(d));

    if (a == 0.0) {
        *root_count = 0;
        return;
    }

    c_double_complex p = (3.0 * a * c - b * b) / (3.0 * a * a);
    c_double_complex q = (2.0 * b * b * b - 9.0 * a * b * c + 27.0 * a * a * d) / (27.0 * a * a * a);

    printf("p = %lf\n", creal(p));
    printf("q = %lf\n", creal(q));

    c_double_complex discriminant = (q * q) / 4.0 + (p * p * p) / 27.0;

    printf("discriminant = %lf\n", creal(discriminant));

    c_double_complex discriminant_root = csqrt(discriminant);

    printf("discriminant root = %lf + %lfi\n", creal(discriminant_root), cimag(discriminant_root));

    if (creal(discriminant) > 0) {
        printf("You are dealing with case d>0, specifically d = %lf\n", creal(discriminant));
        c_double_complex u = cpow(-q / 2.0 + discriminant_root, 1.0 / 3.0);
        c_double_complex v = cpow(-q / 2.0 - discriminant_root, 1.0 / 3.0);

        printf("u = %lf\n", creal(u));
        printf("v = %lf\n", creal(v));

        roots[0] = u + v;
        roots[1] = -(u + v) / 2.0 + I * csqrt(3.0) / 2.0 * (u - v);
        roots[2] = -(u + v) / 2.0 - I * csqrt(3.0) / 2.0 * (u - v);
    } else if (creal(discriminant) == 0) {
        printf("You are dealing with case d=0\n, specifically d = %lf", creal(discriminant));
        c_double_complex u = cpow(-q / 2.0, 1.0 / 3.0);

        roots[0] = 2.0 * u;
        roots[1] = -u;
        roots[2] = -u;
    } else {
        printf("You are dealing with case d<0, specifically d = %lf\n", creal(discriminant));

        double r = 2.0 * csqrt(-creal(p) / 3.0);
        printf("r = %lf\n", r);
        double theta = acos(3.0 * creal(q) / (2.0 * creal(p) * csqrt(-3.0 / creal(p))));
        printf("theta = %lf\n", theta);
        roots[0] = r * cos(theta / 3.0);
        roots[1] = r * cos((theta + 2.0 * M_PI) / 3.0);
        roots[2] = r * cos((theta + 4.0 * M_PI) / 3.0);
    }

    c_double_complex shift = -b / (3.0 * a);
    for (int i = 0; i < 3; i++) {
        roots[i] += shift;
    }

    *root_count = 3;
}

void solve_quartic_impl(struct C_PolynomialEquation* self, c_double_complex* roots, int* root_count) {

    c_double_complex qa = self->coefficients[0]; // Quartic term
    c_double_complex qb = self->coefficients[1]; // Cubic term
    c_double_complex qc = self->coefficients[2]; // Quadratic term
    c_double_complex qd = self->coefficients[3]; // Linear term
    c_double_complex qe = self->coefficients[4]; // Constant term

    if (qa == 0.0) {
        *root_count = 0;
        return;
    }

    c_double_complex a = qb / qa;
    c_double_complex b = qc / qa;
    c_double_complex c = qd / qa;
    c_double_complex d = qe / qa;

    c_double_complex a0 = 0.25 * a;
    c_double_complex a02 = a0 * a0;


    c_double_complex p = 3.0 * a02 - 0.5 * b;
    c_double_complex q = a * a02 - b * a0 + 0.5 * c;
    c_double_complex r = 3.0 * a02 * a02 - b * a02 + c * a0 - d;

    printf("p = %.2f + %.2fi\n", creal(p), cimag(p));
    printf("q = %.2f + %.2fi\n", creal(q), cimag(q));
    printf("r = %.2f + %.2fi\n", creal(r), cimag(r));

    double cubic_coeffs[5] = {0.0, 1.0, creal(p), creal(r), creal(p * r - 0.5 * q * q)};
    C_PolynomialEquation* cubic_resolvent = PolynomialEquation_create(cubic_coeffs, 4);

    c_double_complex* resolvent_roots = malloc(3 * sizeof(c_double_complex));
    if (!resolvent_roots) {
        *root_count = 0;
        PolynomialEquation_destroy(cubic_resolvent);
        return;
    }

    int resolvent_root_count = 0;
    cubic_resolvent->solve_cubic(cubic_resolvent, resolvent_roots, &resolvent_root_count);

    c_double_complex z = resolvent_roots[0];
    for (int i = 0; i < resolvent_root_count; i++) {
            printf("Looking at z[%d] = %lf + %lfi\n", i+1, creal(z), cimag(z));
        if (fabs(cimag(resolvent_roots[i])) < 1e-10 && creal(resolvent_roots[i]) > creal(z)) {
            z = resolvent_roots[i];
        }
    }

    printf("z = %.2f + %.2fi\n", creal(z), cimag(z));

    free(resolvent_roots);
    PolynomialEquation_destroy(cubic_resolvent);


    c_double_complex alpha = csqrt(2.0 * p + 2.0 * z);


    c_double_complex beta;
    if (alpha == 0.0) {
        beta = z * z + r;
    } else {
        beta = -q / alpha;
    }

    printf("alpha = %.2f + %.2fi\n", creal(alpha), cimag(alpha));
    printf("beta = %.2f + %.2fi\n", creal(beta), cimag(beta));

    double quadratic1_coeffs[5] = {0.0, 0.0, 1.0, creal(alpha), creal(z + beta)};
    double quadratic2_coeffs[5] = {0.0, 0.0, 1.0, -creal(alpha), creal(z - beta)};

    C_PolynomialEquation* quadratic1 = PolynomialEquation_create(quadratic1_coeffs, 3);
    C_PolynomialEquation* quadratic2 = PolynomialEquation_create(quadratic2_coeffs, 3);

    c_double_complex roots1[2];
    c_double_complex roots2[2];
    int root_count1 = 0, root_count2 = 0;

    quadratic1->solve_quadratic(quadratic1, roots1, &root_count1);
    quadratic2->solve_quadratic(quadratic2, roots2, &root_count2);

    for (int i = 0; i < root_count1; i++) {
        roots[i] = roots1[i];
    }
    for (int i = 0; i < root_count2; i++) {
        roots[root_count1 + i] = roots2[i];
    }
    *root_count = root_count1 + root_count2;

    c_double_complex shift = -qb / (4.0 * qa);
    for (int i = 0; i < *root_count; i++) {
        roots[i] += shift;
    }

    PolynomialEquation_destroy(quadratic1);
    PolynomialEquation_destroy(quadratic2);
}


C_PolynomialEquation* PolynomialEquation_create(double* coeffs, int size) {
    C_PolynomialEquation* eq = malloc(sizeof(C_PolynomialEquation));
    if (!eq) return NULL;

    for (int i = 0; i < 5; i++) {
        eq->coefficients[i] = (i < size) ? coeffs[i] : 0.0;
    }

    eq->get_equation_type = get_equation_type_impl;
    eq->solve_linear = solve_linear_impl;
    eq->solve_quadratic = solve_quadratic_impl;
    eq->solve_cubic = solve_cubic_impl;
    eq->solve_quartic = solve_quartic_impl;
    eq->solve = solve;

    return eq;
}

void PolynomialEquation_destroy(C_PolynomialEquation* eq) {
    free(eq);
}
