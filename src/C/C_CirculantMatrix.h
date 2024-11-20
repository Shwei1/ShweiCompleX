#ifndef C_CIRCULANT_MATRIX_H
#define C_CIRCULANT_MATRIX_H

#ifdef __cplusplus
#include <complex>
typedef std::complex<double> c_double_complex;
extern "C" {
#else
#include <complex.h>
typedef double complex c_double_complex; // Це костиль, без якого компілятор не розуміє, що таке тип complex double.
#endif

#define MATRIX_SIZE 16384

    /**
     * @brief структура для задання системи лінійних рівнянь циркулюючою матрицею.
     * @note це портування ідентичної програми на C++, яка описана в /src/C++ Proper/CirculantMatrix.hpp
     */
typedef struct C_CirculantMatrix {
    /**
     * @brief Масив коефіцієнтів A_i циркулюючої матриці.
     */
    c_double_complex A[MATRIX_SIZE];
    /**
     * @brief Масив значень кожного рядка циркулюючої матриці.
     */
    c_double_complex b[MATRIX_SIZE];

    /**
     * @brief Вирішує власне СЛР.
     *      Ця функція інкапсулює в собі всю необхідну функціональність програми.
     * @param self — вказівник на обʼєкт матриці типу C_CirculantMatrix.
     * @param solution — вказівник на масив розв‘язків СЛР, у який після виконання програми ці розв‘язки записуються.
     * @param size — розмірність матриці.
     * @note Хоча загалом алгоритм вирішення підтримує будь які матриці розмірності степеня двійки 2^k, за замовчуванням
     *      у передпроцесорі вказаний розмір 2^14 = 16384
     */
    void (*solve)(struct C_CirculantMatrix* self, c_double_complex* solution, int size);

    /**
     * @brief метод для швидкого перетворення Фур‘є вектора за допомогою алгоритма Кулі-Тьюкі (Cooley-Tukey).
     * @param vec — вказівник на сам вектор (масив) значень.
     * @param size — розмірність вектора, за замовчуванням 16384.
     * @note Алгоритм підтримує розмірність будь-якого степеня двійки 2^k.
     */
    void (*fft)(c_double_complex* vec, int size);
    /**
     * @brief метод для оберненого швидкого перетворення Фур‘є тим самим алгоритмом.
     * @param vec — вказівник на вектор.
     * @param size — розмірність вектора.
     * @note ця функція виділяє пам‘ять на купі (!!!), але потім її коректно звільняє, тому витоку пам‘яті не буде.
     */
    void (*ifft)(c_double_complex* vec, int size);
    /**
     * @brief Допоміжний метод для того, аби перевести перший рядок циркулюючої матриці в перший стовпчик,
     *        використовуючи властивості циркулюючої матриці.
     * @param first_row — вказівник на перший рядок.
     * @param first_column — вказівник на масив, у який буде записано перший стовпчик (на основі рядка)
     * @param size — розмірність рядка і стовпчика
     */
    void (*row_to_column)(const c_double_complex* first_row, c_double_complex* first_column, int size);
} C_CirculantMatrix;


/**
 * @brief Ініціалізатор представника структури. Він інкапсулює в собі задання матриці з файлу, а також
 *        «підключає» необхідні функції в поля структури, що є вказівниками на функцію.
 * @param self
 * @param filename
 * @throw помилка, якщо у файлі немає двокрапки, після якої почнеться зчитування коефіцієнтів.
 * @throw помилка, якщо у якомусь рядку недостатньо коефіцієнтів (менше, ніж зазначено)
 */
void C_CirculantMatrix_init(C_CirculantMatrix* self, const char* filename);

/**
 * @brief прототипи власне самих псевдометодів, або просто функцій, цієї структури.
 */

void C_CirculantMatrix_solve(C_CirculantMatrix* self, c_double_complex* solution, int size);
void C_CirculantMatrix_fft(c_double_complex* vec, int size);
void C_CirculantMatrix_ifft(c_double_complex* vec, int size);
void C_CirculantMatrix_output(C_CirculantMatrix* self);
void C_CirculantMatrix_row_to_column(const c_double_complex* first_row, c_double_complex* first_column, int size);

#ifdef __cplusplus
}
#endif

#endif // C_CIRCULANT_MATRIX_H


