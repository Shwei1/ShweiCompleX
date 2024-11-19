#pragma once

#include <vector>
#include <array>
#include "../Complex.hpp"

/**
 * @brief Клас для задання та вирішення рівнянь до 4-го степеня.
 */
class PolynomialEquation {
public:
/**
 * @note за замовчуванням усі дії відбуваються з комплексним типом у форматі double.
 */
    using ComplexType = Complex<double>;

/**
 * @brief Ініціалізатори різних видів для різних типів рівнянь.
 * @params від найстаршого коефіцієнта до наймолодшого.
 * @note Загалом задіюється лише перший ініціалізатор, але можливість задавати рівнняння інакше — теж є.
 * @example
 * PolynomialEquation eq(1, 2, 3, 4, 5);
 * // a = 1; b = 2; c = 3; d = 4; e = 5;
 * // a — квартичний член; b — кубічний; c — квадратний; d — лінійний; e — вільний.
 * @example
 * PolynomialEquation eq(1, 2, 3);
 * a = 1; b = 2; c = 3;
 * a — квадратний член; b — лінійний; c — вільний.
 */
    PolynomialEquation(ComplexType a, ComplexType b, ComplexType c, ComplexType d, ComplexType e);
    PolynomialEquation(ComplexType a, ComplexType b, ComplexType c, ComplexType d);
    PolynomialEquation(ComplexType a, ComplexType b, ComplexType c);
    PolynomialEquation(ComplexType a, ComplexType b);
    PolynomialEquation(ComplexType e);


/**
 * @brief метод, що автоматично визначає степінь рівняння та задіює відповідний до степеня метод знаходження коренів.
 * @return вектор коренів певної довжини. NaN якщо коренів немає або якщо їх нескінченність.
 */
    [[nodiscard]] std::vector<ComplexType> solve() const;

/**
 * @brief Метод для вирішення лінійних рівнянь.
 * @return вектор з коренем рівняння.
 * @warning вектор зі значенням NaN, якщо коренів немає або якщо їх нескінченність.
 */
    [[nodiscard]] std::vector<ComplexType> solve_linear() const;

/**
* @brief Метод для вирішення квадратних рівнянь.
* @return вектор з двома коренями рівняння.
*/
    [[nodiscard]] std::vector<ComplexType> solve_quadratic() const;

/**
* @brief Метод для вирішення кубічних рівнянь.
* @return вектор з трьома коренями рівняння.
*/
    [[nodiscard]] std::vector<ComplexType> solve_cubic() const;

/**
* @brief Метод для вирішення рівнянь четвертого степеня.
*      Застосовується метод вирішення рівняння через пониження його порядку та кубічну резольвенту.
* @call solve_cubic() для знаходження найбільшого дійсного кореня резольвенти.
* @see імплементація в PolynomialEquation.cpp
* @return вектор з чотирма коренями рівняння.
*/
    [[nodiscard]] std::vector<ComplexType> solve_quartic() const;


/**
 * @brief Допоміжний метод для визначення степеня рівняння.
 * @see solve()
 * @return степінь рівняння. Якщо степінь нульовий або перший — повертає 1, і solve() задіює свої методи для його вирішення.
 */
    [[nodiscard]] int get_equation_type() const;

private:

    std::array<ComplexType, 5> coefficients_;
};



