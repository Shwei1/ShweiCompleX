#include "../../include/CirculantMatrix/C_CirculantMatrix.h"
#include <complex.h>
#include <tgmath.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void C_CirculantMatrix_assign_methods(C_CirculantMatrix* self) {
    self->solve = C_CirculantMatrix_solve;
    self->fft = C_CirculantMatrix_fft;
    self->ifft = C_CirculantMatrix_ifft;
    self->row_to_column = C_CirculantMatrix_row_to_column;
}



void C_CirculantMatrix_row_to_column(const c_double_complex* first_row, c_double_complex* first_column, int size) {
    if (size <= 0 || first_row == NULL || first_column == NULL) {
        fprintf(stderr, "Invalid input: The first row is null or the size is invalid.\n");
        return;
    }

    memcpy(first_column, first_row, size * sizeof(c_double_complex));

    for (int i = 1, j = size - 1; i < j; ++i, --j) {
        c_double_complex temp = first_column[i];
        first_column[i] = first_column[j];
        first_column[j] = temp;
    }
}

void C_CirculantMatrix_init(C_CirculantMatrix* self, const char* filename) {
    C_CirculantMatrix_assign_methods(self);

    if (filename) {
        FILE* file = fopen(filename, "r");
        if (!file) {
            fprintf(stderr, "Error: Could not open the file: %s\n", filename);
            return;
        }

        char line[65536]; //64 kb

        if (fgets(line, sizeof(line), file)) {
            char* colon_pos = strchr(line, ':');
            if (!colon_pos) {
                fprintf(stderr, "Error: Invalid format, missing colon in the first row.\n");
                fclose(file);
                return;
            }
            colon_pos++;
            char* token = strtok(colon_pos, " ");
            int index = 0;
            while (token && index < MATRIX_SIZE) {
                self->A[index] = strtod(token, NULL);
                token = strtok(NULL, " ");
                index++;
            }
            if (index != MATRIX_SIZE) {
                fprintf(stderr, "Warning: Expected %d numbers in the first row, got %d.\n", MATRIX_SIZE, index);
            }
        } else {
            fprintf(stderr, "Error: Failed to read the first row for A.\n");
            fclose(file);
            return;
        }

        if (fgets(line, sizeof(line), file)) {
            char* colon_pos = strchr(line, ':');
            if (!colon_pos) {
                fprintf(stderr, "Error: Invalid format, missing colon in the second row.\n");
                fclose(file);
                return;
            }
            colon_pos++;
            char* token = strtok(colon_pos, " ");
            int index = 0;
            while (token && index < MATRIX_SIZE) {
                self->b[index] = strtod(token, NULL);
                token = strtok(NULL, " ");
                index++;
            }
            if (index != MATRIX_SIZE) {
                fprintf(stderr, "Warning: Expected %d numbers in the second row, got %d.\n", MATRIX_SIZE, index);
            }
        } else {
            fprintf(stderr, "Error: Failed to read the second row for b.\n");
            fclose(file);
            return;
        }

        fclose(file);
    }
}


void C_CirculantMatrix_fft(c_double_complex* vec, int size) { //NOLINT

    if (size <= 1) {
        return;
    }

    c_double_complex* even = (c_double_complex*)malloc(size / 2 * sizeof(c_double_complex));
    c_double_complex* odd = (c_double_complex*)malloc(size / 2 * sizeof(c_double_complex));

    if (!even || !odd) {
        fprintf(stderr, "Memory allocation failed in FFT.\n");
        free(even);
        free(odd);
        return;
    }

    for (int i = 0; i < size / 2; ++i) {
        even[i] = vec[i * 2];
        odd[i] = vec[i * 2 + 1];
    }

    C_CirculantMatrix_fft(even, size / 2);
    C_CirculantMatrix_fft(odd, size / 2);


    for (int k = 0; k < size / 2; ++k) {
        double angle = -2 * M_PI * k / size;
        c_double_complex unity_root = cos(angle) + sin(angle) * I;


        c_double_complex t = unity_root * odd[k];
        vec[k] = even[k] + t;
        vec[k + size / 2] = even[k] - t;
    }

    free(even);
    free(odd);
}

void C_CirculantMatrix_ifft(c_double_complex* vec, int size) {

    for (int i = 0; i < size; ++i) {
        vec[i] = conj(vec[i]);
    }

    C_CirculantMatrix_fft(vec, size);

    for (int i = 0; i < size; ++i) {
        vec[i] = conj(vec[i]) / size;
    }
}


void C_CirculantMatrix_solve(C_CirculantMatrix* self, c_double_complex* solution, int size) {
    if (size <= 0 || self == NULL || solution == NULL) {
        fprintf(stderr, "Invalid input to solve.\n");
        return;
    }

    c_double_complex* fft_A = (c_double_complex*)malloc(size * sizeof(c_double_complex));
    if (!fft_A) {
        fprintf(stderr, "Memory allocation failed for fft_A.\n");
        return;
    }
    C_CirculantMatrix_row_to_column(self->A, fft_A, size);
    C_CirculantMatrix_fft(fft_A, size);


    c_double_complex* fft_B = (c_double_complex*)malloc(size * sizeof(c_double_complex));
    if (!fft_B) {
        fprintf(stderr, "Memory allocation failed for fft_B.\n");
        free(fft_A);
        return;
    }
    memcpy(fft_B, self->b, size * sizeof(c_double_complex));
    C_CirculantMatrix_fft(fft_B, size);

    c_double_complex* fft_X = (c_double_complex*)malloc(size * sizeof(c_double_complex));
    if (!fft_X) {
        fprintf(stderr, "Memory allocation failed for fft_X.\n");
        free(fft_A);
        free(fft_B);
        return;
    }
    for (int k = 0; k < size; ++k) {
        if (cabs(fft_A[k]) > 1e-10) {
            fft_X[k] = fft_B[k] / fft_A[k];
        } else {
            fft_X[k] = 0.0 + 0.0 * I;
        }
    }

    C_CirculantMatrix_ifft(fft_X, size);

    memcpy(solution, fft_X, size * sizeof(c_double_complex));

    free(fft_A);
    free(fft_B);
    free(fft_X);
}
