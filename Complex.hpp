#pragma once

#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>


/**
 * @brief Шаблонний клас для комплексних чисел.
 * @tparam NumberType числовий тип для дійсної та уявної компонент.
 */

template <typename NumberType>
class Complex{
public:
    Complex(NumberType real = NumberType{}, NumberType imag = NumberType{});

    /**
    * @brief Наступні методи повертають складові частини комплексного числа
    * @return Складова у форматі NumberType.
    */

    [[nodiscard]] NumberType get_real() const;

    [[nodiscard]] NumberType get_imag() const;

/**
* @brief Повертає комплексне число, спряжене даному.
* @see Дублює метод conjugate().
* @return Комплексне число з оберненою уявною компонентою.
*/

    [[nodiscard]] Complex operator-() const;

    [[nodiscard]] Complex operator+() const;

/**
* @brief Наступні методи забезпечують арифметичні дії між комплексними числами.
* @param other — інше комплексне число.
* @note Усі методи перетворюють компоненти в тип double.
* @throw Помилка при ділення на нуль.
* @return Результат операції
*/

    [[nodiscard]] Complex operator+ (const Complex& other) const;

    [[nodiscard]] Complex operator- (const Complex& other) const;

    [[nodiscard]] Complex operator* (const Complex& other) const;

    [[nodiscard]] Complex operator/ (const Complex& other) const;

/**
 * @brief Наступні методи забезпечують арифметичні дії між комплексним числом та іншим числовим типом даних.
 * @param value — інший числовий тип.
 * @param complex — комплексне число.
 * @note Усі методи перетворюють компоненти в тип double.
 * @throw Помилка при ділення на нуль.
 * @return Результат операції
 */

    friend Complex operator+ (const NumberType& value, const Complex& complex);

    friend Complex operator- (const NumberType& value, const Complex& complex);

    friend Complex operator* (const NumberType& value, const Complex& complex);

    friend Complex operator/ (const NumberType& value, const Complex& complex);

/**
 * @brief Перевантажені булеві оператори для перевірки рівності та не-рівності.
 * @note Оператори більше/менше не потребують перевантаження, адже комплексні числа не впорядковані.
 * @return значення істиності порвівння.
 */


    [[nodiscard]] bool operator== (const Complex& other) const;

    [[nodiscard]] bool operator!= (const Complex& other) const;

/**
* @brief Наступні методи перевантажують операції доповненного присвоєння для комплексного числа.
* @param other — комплексне число.
* @note Усі методи перетворюють компоненти в тип double.
* @throw domain_error — помилка при діленні на нуль.
* @return Результат операції.
*/

    Complex& operator+=(const Complex& other);

    Complex& operator-=(const Complex& other);

    Complex& operator*=(const Complex& other);

    Complex& operator/=(const Complex& other);

    /**
* @brief Наступні методи перевантажують операції доповненного присвоєння для довільного дійсного числа.
* @param complex — комплексне число.
* @param value — змінна числового типу.
* @note Усі методи перетворюють компоненти в тип double.
* @throw domain_error — помилка при діленні на нуль.
* @return Результат операції.
*/

    friend Complex& operator+=(Complex& complex, const NumberType& value);

    friend Complex& operator-=(Complex& complex, const NumberType& value);

    friend Complex& operator*=(Complex& complex, const NumberType& value);

    friend Complex& operator/=(Complex& complex, const NumberType& value);

/**
 * @brief Конкретна імплементація спряженого числа.
 * @return спряжене комплексне число.
*/

    [[nodiscard]] Complex conjugate() const;

/**
 * @brief Пошук модуля комлпексного числа.
 * @return модуль комплексного числа в типі double.
*/

    [[nodiscard]] double magnitude() const;

/**
 * @brief Пошук аргумента (або фази) комплексного числа
 * @return аргумент в радіанах.
*/

    [[nodiscard]] double phase() const;

/**
 * @brief Піднесення до степеня за формулою де Муавра.
 * @return комплексне число.
*/

    [[nodiscard]] Complex pow(int exponent) const;

/**
 * @brief Взяття множини коренів з комплексного числа за формулою де Муавра.
 * @param n — степінь кореня.
 * @return Вектор коренів комплексного числа.
 * @note n має бути додатним натуральним числом.
 * @throw std::invalid_argument Якщо n менше або рівне нулеві.
 *
 * @example
 * Complex z1(1, 1);
 * auto roots = z1.roots(2);
 * // вектор roots тепер містить корені з (1 + i).
 * @example
 * Complex z2(-1);
 * auto roots = z2.roots(2);
 * std::cout << roots[0];
 * // Виведеться перше значення кореня з -1.
 */

    [[nodiscard]] std::vector<Complex> roots(int n) const;

/**
 * @brief Наступні методи забезпечують вивід комплексного числа в консоль за допомогою стандартних потоків.
 * @return перевантажений оператор вводу/виводу.
*/

    friend std::ostream& operator<< (std::ostream& os, const Complex& complex);

    friend std::istream& operator>> (std::istream& is, Complex& complex);

/**
 * @brief Наступні методи перетворюють комплексне число на строку в тригонометричній або експоненційній формі.
 * @return строка з певним виглядом комплексного числа.
*/

    [[nodiscard]] std::string exponential() const;

    [[nodiscard]] std::string trigonometric() const;

/**
* @brief Обчислює основний квадратний корінь з комплексного числа.
* @see roots(2) для загального випадку.
* @return Основний комплексний квадратний корінь.
*/
    friend Complex sqrt(const Complex& complex);

/**
* @brief Обчислює основний кубічний корінь з комплексного числа.
* @see roots(3) для загального випадку.
* @return Основний комплексний кубічний корінь.
*/
    friend Complex cbrt(const Complex& complex);



private:
    NumberType realPart_;
    NumberType imagPart_;
};
