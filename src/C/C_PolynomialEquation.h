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


/**
 * @brief Структура для задання многочлена.
 *        Включає в себе «поле» масиву коефіцієнтів рівняння, а також вказівники як на специфічні
 *        методи для вирішення конкретних типів рівнянь, так і загальний метод solve() для довільного рівняння.
 * @example
 * double coefficients[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
 * C_PolynomialEquation* polynom = PolynomialEquation_create(coefficients, 5);
 * int root_count = 0;
 * c_double_complex roots = polynom->solve(polynom, &root_count);
 * for (int i = 0; i < root_count; ++i){
 *      printf("Root %d: %lf + %lfi /n", i+1, creal(roots[i]), cimag(roots[i])); // На С
 *      std::cout << "Root " << i << ": " << roots[i].real() << " + " << roots[i].imag() << "i/n"; // На С++
 * }
 * free(roots); (!!!)
 * PolynomialEquation_destroy(polynom); (!!!)
 */
typedef struct C_PolynomialEquation {
    /**
     * @brief Масив коефіцієнтів рівняння. Вони задаються від старшого до молодшого зліва направо.
     * @example
     * // коефіцієнти ax^4 + bx^3 + cx^2 + dx + e = 0 задаються масивом {a, b, c, d, e}
     * @note На відміну від імплементації в класах на C++, тут розмір масиву коефіцієнтів сталий і має включати 5 значень
     *       від коефіцієнту при x^4 до вільного члену.
     * @see PolynomialEquation_create()
     */
    double coefficients[5];

    /**
     * @brief допоміжний метод для отримання степеню рівняння, на основі чого виділятиметься пам‘ять під масив коренів
     * @param self — вказівник на сутність поліному C_PolynomialEquation.
     * @return степінь найстаршого коефіцієнта.
     */
    int (*get_equation_type)(struct C_PolynomialEquation* self);

    /**
     * @brief Ключовий метод, що абстрагує користувача від усіх інших
     * @param self — вказівник на поліном.
     * @param root_count — вказівник на змінну з кількістю коренів рівняння.
     *        Це значення створюється поза викликом функції для того, аби знати межі для ітерування по масиву коренів.
     *        Всередині виклику цій змінній присвоюється значення, повернене get_equation_type().
     * @return вказівник на масив коренів рівняння.
     * @note всередині виклику під масив коренів виділяється пам‘ять (!!!), отже необіхдно після виклику функції цю пам‘ять
     *  звільнити, інакше виникне memory leak.
     * @see приклад використання структури зверху.
     * @note Оскільки функція викликає відповідні методи для вирішення конкретного типу рівнянь, то є ризик
     *       помилки сегментації SIGSEGV, проте функція в цьому випадку перевіряє, чи не є вказівник null pointer'ом.
     *       У такому випадку просто виводиться джерело проблемти в консоль.
     */
    c_double_complex* (*solve)(struct C_PolynomialEquation* self, int* root_count);

    /**
     * @brief наступні методи за принципом ідентичні описаним у src/C++ Proper/PolynomialEquation.cpp
     * @param self — вказівник на рівняння.
     * @param roots — вказівник на масив коренів.
     * @see solve() — цей метод самостійно виділяє потрібну кількість пам‘яті під корені і передає вказівник на такий
     *      масив у ці методи.
     * @param root_count
     */
    void (*solve_linear)(struct C_PolynomialEquation* self, c_double_complex* roots, int* root_count);
    void (*solve_quadratic)(struct C_PolynomialEquation* self, c_double_complex* roots, int* root_count);
    void (*solve_cubic)(struct C_PolynomialEquation* self, c_double_complex* roots, int* root_count);
    void (*solve_quartic)(struct C_PolynomialEquation* self, c_double_complex* roots, int* root_count);
} C_PolynomialEquation;

/**
 * @brief Метод для ініціалізації рівняння.
 * @note Цей ініціалізатор виділяє під рівняння пам‘ять на купі, тому
 * @see PolynomialEquation_destroy() для звільнення цієї пам‘яті.
 * @param coeffs — вказівник на масив коефіцієнтів.
 * @param size — розмір масиву коефіцієнтів. У прицнипі є можливість задати рівняння меншим за 5 масивом,
 *        але всередині ініціалізатора все одно інші коефіцієнти заповняться нулями.
 * @return Вказівник на ініціалізований многочлен.
 */
C_PolynomialEquation* PolynomialEquation_create(double* coeffs, int size);

/**
 * @brief деструктор рівнняння. Його задача лише звільняти пам‘ять.
 * @param eq — вказівник на рівняння, яке треба знищити.
 */
void PolynomialEquation_destroy(C_PolynomialEquation* eq);

#ifdef __cplusplus
}
#endif

#endif