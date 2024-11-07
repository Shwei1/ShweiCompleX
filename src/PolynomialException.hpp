#pragma once

#include <stdexcept>
#include <string>

/**
 * @brief Стандартне виключення для степеневого рівняння.
 */
class PolynomialException : public std::runtime_error {
public:
    /**
     * @brief Конструктор для полінома.
     * @param message Опис помилки.
     */
    explicit PolynomialException(const std::string& message)
            : std::runtime_error("Polynomial Error: " + message) {}
};