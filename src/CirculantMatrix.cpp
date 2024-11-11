#include <vector>
#include "Complex.hpp"


class CirculantMatrix {
    using ComplexType = Complex<double>;

public:

    CirculantMatrix() : A(16384), b(16384) {
        std::fill(A.begin(), A.end(), Complex(0.0));
        std::fill(b.begin(), b.end(), Complex(0.0));
    }

    std::vector<ComplexType> solve(const std::vector<ComplexType>& main_row, const std::vector<ComplexType>& vec) {
        unsigned long n = main_row.size();


        std::vector<ComplexType> fft_A = main_row;
        fast_fourier_transform(fft_A);


        std::vector<ComplexType> fft_B = vec;
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

    void fast_fourier_transform(std::vector<ComplexType>& vec){ //NOLINT
        unsigned long n = vec.size();
        if (n<=1) return;
        std::vector<ComplexType> even(n/2);
        std::vector<ComplexType> odd(n/2);
        for (int i = 0; i < n / 2; ++i){
            even[i] = vec[i*2];
            odd[i] = vec[i*2 + 1];
        }

        fast_fourier_transform(even);
        fast_fourier_transform(odd);

        std::vector<ComplexType> unity_roots = ComplexType(1.0).roots(static_cast<int>(n));

        for (int j = 0; j < n/2; ++j){
            ComplexType t = unity_roots[j] * odd[j];
            vec[j] = even[j] + t;
            vec[j + n/2] = even[j] - t;
        }
    }

    void inverse_fft(std::vector<ComplexType>& vec) {
        unsigned long n = vec.size();

        for (int i = 0; i < n; ++i) {
            vec[i] = vec[i].conjugate();
        }

        fast_fourier_transform(vec);

        for (int i = 0; i < n; ++i) {
            vec[i] = vec[i].conjugate() / static_cast<double>(n);
        }
    }

    static void GenerateCirculantMatrix(unsigned long n, const std::string& filename){
        return;
    }

private:
    std::vector<ComplexType> A;
    std::vector<ComplexType> b;
};