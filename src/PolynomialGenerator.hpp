#pragma once

#include <string>
#include <random>

/**
 * @brief клас для генерування многочленів певного вигляду у файл.
 * @note Усі його методи статичні за задумом.
 * @example
 * PolynomialGenerator::initialise();
 * PolynomialGenerator::generate_polynomials("polynomial_equations.txt", 100 );
 * // Генерує 100 рівнянь випадкового степеня з випадковими цілими коефіцієнтами.
 */
class PolynomialGenerator {
private:
    /**
     * @var rd
     * @brief random device для генератора випадкових чисел.
     * @var gen
     * @brief генератор випадкових чисел — «Вихор Мерсенна».
     * @var type_dist; coef_distr
     * @brief інтервал генерування коефіцієнтів та степенів.
     */
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_int_distribution<> type_distr;
    static std::uniform_int_distribution<> coef_distr;

public:
    /**
     * @brief ініціалізує об‘єкт класу, встановлює зазначені вище параметри для генерування випадкових чисел.
     * @note За замовчуванням коефіцієнти — цілі, від -50 до 50.
     */
    static void initialise();

    /**
     * @brief Метод для власне генерації поліномів.
     * @param filename назва/шлях файлу для генерування рівнянь.
     * @param n кількість рівнянь для генерування.
     * @example
     * // за замовчуванням виводить поліном у форматі:
     * a x^4 + b x^3 + c x^2 + d x + e = 0
     * a x^3 + b x^2 + c x + d = 0
     */
    static void generate_polynomials(const std::string& filename, int n);
};
