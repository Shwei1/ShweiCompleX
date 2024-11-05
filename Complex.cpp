#include <iostream>
#include <cmath>
#include <sstream>

template <typename NumberType>
class Complex{
public:
    Complex(NumberType real = NumberType{}, NumberType imag = NumberType{}): realPart_(real), imagPart_(imag){}

    /**
    * @brief Наступні методи повертають складові частини комплексного числа
    * @return Складова у форматі NumberType.
    */

    [[nodiscard]] NumberType getReal() const {return realPart_;}

    [[nodiscard]] NumberType getImag() const {return imagPart_;}

    /**
    * @brief Повертає комплексне число, спряжене даному.
    * @note Дублює метод conjugate().
    * @return Комплексне число з оберненою уявною компонентою.
    */

    [[nodiscard]] Complex operator-() const {
        return {realPart_, -imagPart_};
    }

    [[nodiscard]] Complex operator+() const {
        return {realPart_, imagPart_};
    }

    /**
    * @brief Наступні методи забезпечують арифметичні дії між комплексними числами.
    * @return Результат операції
    */

    [[nodiscard]] Complex operator+ (const Complex& other) const {return {realPart_ + other.realPart_, imagPart_ + other.imagPart_};}

    [[nodiscard]] Complex operator- (const Complex& other) const {return {realPart_ - other.realPart_, imagPart_ - other.imagPart_};}

    [[nodiscard]] Complex operator* (const Complex& other) const {return {realPart_ * other.realPart_ - imagPart_ * other.imagPart_,
                                                                                 realPart_ * other.imagPart_ + imagPart_ * other.realPart_};}

    [[nodiscard]] Complex operator/ (const Complex& other) const {
        if (other == Complex(0, 0))
            throw std::domain_error("Zero division error.");
        return Complex((realPart_ * other.realPart_ + imagPart_ * other.imagPart_)/(other.realPart_ * other.realPart_ + other.imagPart_ * other.imagPart_),
                                                                                 (imagPart_ * other.realPart_ - realPart_ * other.imagPart_)/(other.realPart_ * other.realPart_ + other.imagPart_ * other.imagPart_));}

    [[nodiscard]] Complex<double> operator/ (const NumberType& value) const {
        if (value == 0) {
            throw std::domain_error("Zero division error.");
        }
        return {static_cast<double>(realPart_)/ value, static_cast<double>(imagPart_) / value};
    }

    friend Complex operator+ (const NumberType& value, const Complex& z) {
        return {value + z.realPart_, z.imagPart_};
    }

    friend Complex operator- (const NumberType& value, const Complex& z) {
        return {value - z.realPart_, -z.imagPart_};
    }

    friend Complex operator* (const NumberType& value, Complex& z) {return {value * z.realPart_, value * z.imagPart_};}

    [[nodiscard]] bool operator== (const Complex& other) const {return (realPart_ == other.realPart_ && imagPart_ == other.imagPart_);}

    [[nodiscard]] bool operator!= (const Complex& other) const {return (realPart_ != other.realPart_ || imagPart_ != other.imagPart_);}

    [[nodiscard]] Complex conjugate() const {
        return {realPart_, -imagPart_};
    }

    friend std::ostream& operator<< (std::ostream& os, const Complex& z) {
        os << z.realPart_;
        if (z.imagPart_ >= 0) {
            if (z.imagPart_ == 1){
                os << " + " << "i";
            }
            else
                os << " + " << z.imagPart_ << "i";
        } else {
            if (z.imagPart_ == -1){
                os << " - " << "i";
            }
            else
                os << " - " << -z.imagPart_ << "i";
        }
        return os;
    }

    friend std::istream& operator>> (std::istream& is, Complex& z) {
        NumberType temp_real, temp_imag;
        if (is >> temp_real && is >> temp_imag) {
            z.realPart_ = temp_real;
            z.imagPart_ = temp_imag;
            return is;
        } else {
            is.setstate(std::ios::failbit);
            return is;
        }
    }


private:
    NumberType realPart_;
    NumberType imagPart_;

};

int main(int argc, char** argv) {
    Complex c1(1, -1);
    Complex c2(1, 1);
    Complex sum = c2 + 2;
    sum = 1 + sum;
    Complex res = -c2 / 2;
    Complex diff = 2 - c2;
    std::cout << res;

}