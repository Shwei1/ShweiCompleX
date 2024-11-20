#include <vector>
#include <string>
#include <fstream>
#include "../Complex.hpp"

/**
 * @brief Клас системи лінійних рівнянь, заданих циркулюючою матрицею, що інкапсулює в собі методи, для її вирішення.
 * @note За умовчуванням ця матриця працює з системою лінійних рівнянь рангу 2^14 = 16384, але можна відредагувати код, аби вона працювала для
 * будь-якої матриці рангу 2^k.
 */

class CirculantMatrix {

public:

/**
 * @note За умовчуванням використовується тип комплексного числа з дійсними компонентами.
 */
    using ComplexType = Complex<double>;

private:
    /**
     * @var A — вектор коефіцієнтів A_i, по суті — перший рядок матриці.
     * @var b — вектор константних членів СЛР.
     */
    std::vector<ComplexType> A;
    std::vector<ComplexType> b;

public:

/**
 * @brief Матрицю можна ініціалізувати за допомогою двох векторів з потрібними значеннями.
 * @param A — вектор коефіцієнтів A_i, по суті — перший рядок матриці.
 * @param b — вектор константних членів СЛР.
 */
    CirculantMatrix(const std::vector<ComplexType>& A, const std::vector<ComplexType>& b);


/**
 * @brief Як варіант для користувацького вводу матриці – можна задати коефіцієнти та константні члени в файлі в певному форматі:
 * @example //my_file.txt:
 * [any text followed by a colon]: A1 A2 ... A16384
 * [any text followed by a colon]: b1 b2 ... b16384
 * @see GenerateCirculantMatrix.cpp
 * @param filename — назва файлу для введення коефіцієнтів.
 */
    CirculantMatrix(const std::string& filename); //NOLINT

/**
 * @brief Метод для, власне, отримання вектору з розв‘язками системи.
 * @note використовує fast_fourier_transform() та inverse_fft()
 * @return вектор розв‘язків СЛР
 */
    std::vector<ComplexType> solve();

/**
 * @brief Метод для виводу розв‘язків у файл.
 * @param filename — назва файлу виводу.
 */
    void solve_and_output(const std::string& filename);

    void output(){ //DEBUG METHOD
        for (ComplexType coef: b){
            std::cout << coef << std::endl;
        }
        std::cout << b.size() << std::endl;
    }

/**
 * @brief статичний метод для того, аби переконфігурувати перший рядок матриці (А) у перший стовпчик,
 *        необхідний для знаходження власних чисел матриці.
 * @param first_row — вектор-рядок, у якому треба перезібрати елементи, аби вийшов вектор-стовпчик у контексті циркулюючої матриці.
 * @return Перший стовпець матриці, переведений з першого рядку
 */
    static std::vector<ComplexType> row_to_column(const std::vector<ComplexType>& first_row);

//    static unsigned long bit_reverse(unsigned long x, unsigned int log2n);

private:

/**
 * @brief Швидке перетворення Фур‘є алгоритмом Кулі-Тьюкі (Cooley-Tukey).
 * @param vec — вектор, який потрібно перенести з часової області в частотну.
 */
    void fast_fourier_transform(std::vector<ComplexType>& vec);

/**
 * @brief Обернене швидке перетворення Фур‘є тим самим алгоритмом Кулі-Тьюкі.
 * @param vec — вектор, який треба перенести назад з частотної області в часову.
 */
    void inverse_fft(std::vector<ComplexType>& vec);

};
