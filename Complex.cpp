#include <iostream>
#include <cmath>
#include <sstream>

class Complex{
public:
    Complex(double real = 0.0, double imag = 0.0): realPart_(real), imagPart_(imag){}

    [[nodiscard]] double getReal() const {return realPart_;}

    [[nodiscard]] double getImag() const {return imagPart_;}

    [[nodiscard]] Complex operator+ (const Complex& other) const {return {realPart_ + other.realPart_, imagPart_ + other.imagPart_};}

    [[nodiscard]] Complex operator- (const Complex& other) const {return {realPart_ - other.realPart_, imagPart_ - other.imagPart_};}

    [[nodiscard]] Complex operator* (const Complex& other) const {return {realPart_ * other.realPart_ - imagPart_ * other.imagPart_,
                                                                                 realPart_ * other.imagPart_ + imagPart_ * other.realPart_};}

    [[nodiscard]] Complex operator/ (const Complex& other) const {
        if (other == Complex(0, 0))
            throw std::domain_error("Zero division error.");
        return Complex((realPart_ * other.realPart_ + imagPart_ * other.imagPart_)/(other.realPart_ * other.realPart_ + other.imagPart_ * other.imagPart_),
                                                                                 (imagPart_ * other.realPart_ - realPart_ * other.imagPart_)/(other.realPart_ * other.realPart_ + other.imagPart_ * other.imagPart_));}

    [[nodiscard]] bool operator== (const Complex& other) const {return (realPart_ == other.realPart_ && imagPart_ == other.imagPart_);}

    [[nodiscard]] bool operator!= (const Complex& other) const {return (realPart_ != other.realPart_ || imagPart_ != other.imagPart_);}

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
        double tempreal, tempimag;
        if (is >> tempreal && is >> tempimag) {
            z.realPart_ = tempreal;
            z.imagPart_ = tempimag;
            return is;
        } else {
            is.setstate(std::ios::failbit);
            return is;
        }
    }


private:
    double realPart_;
    double imagPart_;

};

int main(int argc, char** argv) {
    Complex c1(1, -1);
    Complex c2(1, 1);
    Complex sum = 2 + c2;
    std::cout << sum;
//    std::cout << c1.getImag() << std::endl;
//    std::cout << c2 + c1 << std::endl;

}