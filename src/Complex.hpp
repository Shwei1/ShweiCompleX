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
    Complex(NumberType real = NumberType{}, NumberType imag = NumberType{}): realPart_(real), imagPart_(imag){}

    /**
    * @brief Наступні методи повертають складові частини комплексного числа
    * @return Складова у форматі NumberType.
    */

    [[nodiscard]] NumberType get_real() const {return realPart_;}

    [[nodiscard]] NumberType get_imag() const {return imagPart_;}

/**
* @brief Повертає комплексне число, спряжене даному.
* @see Дублює метод conjugate().
* @return Комплексне число з оберненою уявною компонентою.
*/

    [[nodiscard]] Complex operator-() const {
        return {-realPart_, -imagPart_};
    }

    [[nodiscard]] Complex operator+() const {
        return {realPart_, imagPart_};
    }

/**
* @brief Наступні методи забезпечують арифметичні дії між комплексними числами.
* @param other — інше комплексне число.
* @note Усі методи перетворюють компоненти в тип double.
* @throw Помилка при ділення на нуль.
* @return Результат операції
*/

    [[nodiscard]] Complex operator+ (const Complex& other) const {
        return Complex(static_cast<double>(realPart_) + other.realPart_, static_cast<double>(imagPart_) + other.imagPart_);
    }

    [[nodiscard]] Complex operator- (const Complex& other) const {
        return Complex(static_cast<double>(realPart_) - other.realPart_, static_cast<double>(imagPart_) - other.imagPart_);
    }

    [[nodiscard]] Complex operator* (const Complex& other) const {
        return Complex(
                static_cast<double>(realPart_) * other.realPart_ - static_cast<double>(imagPart_) * other.imagPart_,
                static_cast<double>(realPart_) * other.imagPart_ + static_cast<double>(imagPart_) * other.realPart_
        );
    }

    [[nodiscard]] Complex operator/ (const Complex& other) const {
        if (other == Complex(0, 0)) {
            throw std::domain_error("Zero division error.");
        }
        double denominator = static_cast<double>(other.realPart_) * other.realPart_ +
                             static_cast<double>(other.imagPart_) * other.imagPart_;
        return Complex(
                (static_cast<double>(realPart_) * other.realPart_ + static_cast<double>(imagPart_) * other.imagPart_) / denominator,
                (static_cast<double>(imagPart_) * other.realPart_ - static_cast<double>(realPart_) * other.imagPart_) / denominator
        );
    }

/**
 * @brief Наступні методи забезпечують арифметичні дії між комплексним числом та іншим числовим типом даних.
 * @param value — інший числовий тип.
 * @param complex — комплексне число.
 * @note Усі методи перетворюють компоненти в тип double.
 * @throw Помилка при ділення на нуль.
 * @return Результат операції
 */

    friend Complex operator+ (const NumberType& value, const Complex& complex) {
        return Complex(static_cast<double>(value) + complex.realPart_, complex.imagPart_);
    }

    friend Complex operator- (const NumberType& value, const Complex& complex) {
        return Complex(static_cast<double>(value) - complex.realPart_, -complex.imagPart_);
    }

    friend Complex operator* (const NumberType& value, const Complex& complex) {
        return Complex(static_cast<double>(value) * complex.realPart_, static_cast<double>(value) * complex.imagPart_);
    }

    friend Complex operator/ (const NumberType& value, const Complex& complex) {
        if (complex == Complex(0, 0)) {
            throw std::domain_error("Zero division error.");
        }
        double denominator = static_cast<double>(complex.realPart_) * complex.realPart_ +
                             static_cast<double>(complex.imagPart_) * complex.imagPart_;
        return Complex(
                (static_cast<double>(value) * complex.realPart_) / denominator,
                (-static_cast<double>(value) * complex.imagPart_) / denominator
        );
    }

/**
 * @brief Перевантажені булеві оператори для перевірки рівності та не-рівності.
 * @note Оператори більше/менше не потребують перевантаження, адже комплексні числа не впорядковані.
 * @return значення істиності порвівння.
 */


    [[nodiscard]] bool operator== (const Complex& other) const {return (realPart_ == other.realPart_ && imagPart_ == other.imagPart_);}

    [[nodiscard]] bool operator!= (const Complex& other) const {return (realPart_ != other.realPart_ || imagPart_ != other.imagPart_);}

/**
* @brief Наступні методи перевантажують операції доповненного присвоєння для комплексного числа.
* @param other — комплексне число.
* @note Усі методи перетворюють компоненти в тип double.
* @throw domain_error — помилка при діленні на нуль.
* @return Результат операції.
*/

    Complex& operator+=(const Complex& other) {
        realPart_ += other.realPart_;
        imagPart_ += other.imagPart_;
        return *this;
    }

    Complex& operator-=(const Complex& other) {
        realPart_ -= other.realPart_;
        imagPart_ -= other.imagPart_;
        return *this;
    }

    Complex& operator*=(const Complex& other) {
        double tempReal = realPart_ * other.realPart_ - imagPart_ * other.imagPart_;
        imagPart_ = realPart_ * other.imagPart_ + imagPart_ * other.realPart_;
        realPart_ = tempReal;
        return *this;
    }

    Complex& operator/=(const Complex& other) {
        if (other == Complex(0, 0))
            throw std::domain_error("Zero division error.");
        double denominator = other.realPart_ * other.realPart_ + other.imagPart_ * other.imagPart_;
        double tempReal = (realPart_ * other.realPart_ + imagPart_ * other.imagPart_) / denominator;
        imagPart_ = (imagPart_ * other.realPart_ - realPart_ * other.imagPart_) / denominator;
        realPart_ = tempReal;
        return *this;
    }

    /**
* @brief Наступні методи перевантажують операції доповненного присвоєння для довільного дійсного числа.
* @param complex — комплексне число.
* @param value — змінна числового типу.
* @note Усі методи перетворюють компоненти в тип double.
* @throw domain_error — помилка при діленні на нуль.
* @return Результат операції.
*/


    friend Complex& operator+=(Complex& complex, const NumberType& value) {
        complex.realPart_ += value;
        return complex;
    }

    friend Complex& operator-=(Complex& complex, const NumberType& value) {
        complex.realPart_ -= value;
        return complex;
    }

    friend Complex& operator*=(Complex& complex, const NumberType& value) {
        complex.realPart_ = static_cast<double>(complex.realPart_) * value;
        complex.imagPart_ = static_cast<double>(complex.imagPart_) * value;
        return complex;
    }

    friend Complex& operator/=(Complex& complex, const NumberType& value) {
        if (value == 0) {
            throw std::domain_error("Zero division error.");
        }
        complex.realPart_ = static_cast<double>(complex.realPart_) / value;
        complex.imagPart_ = static_cast<double>(complex.imagPart_) / value;
        return complex;
    }

/**
 * @brief Конкретна імплементація спряженого числа.
 * @return спряжене комплексне число.
*/

    [[nodiscard]] Complex conjugate() const {
        return {realPart_, -imagPart_};
    }

/**
 * @brief Пошук модуля комлпексного числа.
 * @return модуль комплексного числа в типі double.
*/

    [[nodiscard]] double magnitude() const {
        return std::sqrt(static_cast<double>(realPart_ * realPart_ + imagPart_ * imagPart_));
    }

/**
 * @brief Пошук аргумента (або фази) комплексного числа
 * @return аргумент в радіанах.
*/

    [[nodiscard]] double phase() const {
        return std::atan2(static_cast<double>(imagPart_), static_cast<double>(realPart_));
    }

/**
 * @brief Піднесення до степеня за формулою де Муавра.
 * @return комплексне число.
*/

    [[nodiscard]] Complex pow(int exponent) const {
        double r = std::pow(magnitude(), exponent);
        double angle = phase() * exponent;
        return {r * std::cos(angle), r * std::sin(angle)};
    }

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

    [[nodiscard]] std::vector<Complex> roots(int n) {
        if (n<=0)
            throw std::invalid_argument("The degree of the root must be a positive integer.");
        double r = std::pow(magnitude(), 1.0 / n);
        double theta = phase() / n;
        std::vector<Complex> result;
        for (int k = 0; k < n; ++k) {
            double angle = theta + 2 * M_PI * k / n;
            if (std::abs(realPart_) < 1e-10) realPart_ = 0;
            if (std::abs(imagPart_) < 1e-10) imagPart_ = 0;
            result.emplace_back(r * std::cos(angle), r * std::sin(angle));
        }
        return result;
    }

/**
 * @brief Наступні методи забезпечують вивід комплексного числа в консоль за допомогою стандартних потоків.
 * @return перевантажений оператор вводу/виводу.
*/

    friend std::ostream& operator<< (std::ostream& os, const Complex& complex) {
        os << complex.realPart_;
        if (complex.imagPart_ >= 0) {
            if (complex.imagPart_ == 1.0){
                os << " + " << "i";
            }
            else
                os << " + " << complex.imagPart_ << "i";
        } else {
            if (complex.imagPart_ == -1.0){
                os << " - " << "i";
            }
            else
                os << " - " << -complex.imagPart_ << "i";
        }
        return os;
    }

    friend std::istream& operator>> (std::istream& is, Complex& complex) {
        NumberType temp_real, temp_imag;
        if (is >> temp_real && is >> temp_imag) {
            complex.realPart_ = temp_real;
            complex.imagPart_ = temp_imag;
            return is;
        } else {
            is.setstate(std::ios::failbit);
            return is;
        }
    }

/**
 * @brief Наступні методи перетворюють комплексне число на строку в тригонометричній або експоненційній формі.
 * @return строка з певним виглядом комплексного числа.
*/

    [[nodiscard]] std::string exponential() const {
        std::ostringstream os;
        os << magnitude() << " * e^(i * " << phase() << ")";
        return os.str();
    }

    [[nodiscard]] std::string trigonometric() const {
        std::ostringstream os;
        os << magnitude() << " * (cos(" << phase() << ") + i * sin(" << phase() << "))";
        return os.str();
    }

/**
* @brief Обчислює основний квадратний корінь з комплексного числа.
* @see roots(2) для загального випадку.
* @return Основний комплексний квадратний корінь.
*/
    static Complex sqrt(const Complex& complex) {
        double r = std::sqrt(complex.magnitude());
        double theta = complex.phase() / 2;
        return Complex(r * std::cos(theta), r * std::sin(theta));
    }

/**
* @brief Обчислює основний кубічний корінь з комплексного числа.
* @see roots(3) для загального випадку.
* @return Основний комплексний кубічний корінь.
*/
    static Complex cbrt(const Complex& complex) {
        double r = std::cbrt(complex.magnitude());
        double theta = complex.phase() / 3;
        return Complex(r * std::cos(theta), r * std::sin(theta));
    }


private:
    NumberType realPart_;
    NumberType imagPart_;

};
