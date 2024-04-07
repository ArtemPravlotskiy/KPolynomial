//
// Created by pravl on 26.03.2024.
//

#ifndef KPOLYNOMIAL_H
#define KPOLYNOMIAL_H

#include <algorithm>
#include <initializer_list>
#include <ostream>


class Iterator;

class KPolynomial {
public:
    KPolynomial() : coefficients(nullptr), size(0) {}

    KPolynomial(const int* coeffs, const size_t size) : size(size) {
        coefficients = new int[size];
        for (size_t i = 0; i < size; ++i) {
            coefficients[i] = coeffs[i];
        }
    }

    KPolynomial(const std::initializer_list<int>& coeffs) : size(coeffs.size()) {
        coefficients = new int[size];
        size_t i = 0;
        for (const int coeff : coeffs) {
            coefficients[i++] = coeff;
        }
    }

    explicit KPolynomial(const size_t size) : size(size) {
        coefficients = new int[size];
        for (size_t i = 0; i < size; ++i) {
            coefficients[i] = 1;
        }
    }

    ~KPolynomial() {
        delete[] coefficients;
    }

    KPolynomial& operator=(const KPolynomial& other) {
        if (this != &other) {
            delete[] coefficients;
            size = other.size;
            coefficients = new int[size];
            for (size_t i = 0; i < size; ++i) {
                coefficients[i] = other.coefficients[i];
            }
        }
        return *this;
    }

    KPolynomial operator+(const KPolynomial& other) const {
        const size_t maxSize = std::max(size, other.size);
        const auto resultCoeffs = new int[maxSize]();
        for (size_t i = 0; i < maxSize; ++i) {
            const int coeff1 = (i < size) ? coefficients[i] : 0;
            const int coeff2 = (i < other.size) ? other.coefficients[i] : 0;
            resultCoeffs[i] = coeff1 + coeff2;
        }
        return {resultCoeffs, maxSize};
    }

    KPolynomial& operator+=(const KPolynomial& other) {
        *this = *this + other;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const KPolynomial& poly) {
        out << poly.coefficients[0] << " + ";
        for (size_t i = 1; i < poly.size; ++i) {
            if (poly.coefficients[i] != 0) {
                if (poly.coefficients[i] != 1) {
                    out << poly.coefficients[i];
                }
                out << "x^" << i;
                if (i != poly.size - 1) {
                    out << " + ";
                }
            }
        }
        return out;
    }

    [[nodiscard]] size_t Count() const {
        return size;
    }

    [[nodiscard]] int Degree() const {
        return static_cast<int>(size) - 1;
    }

    [[nodiscard]] int GetCoefficient(int i) const {
        return coefficients[i];
    }

    void Clear() {
        delete[] coefficients;
        coefficients = nullptr;
        size = 0;
    }

    KPolynomial operator*(const KPolynomial& other) const {
        size_t resultSize = size + other.size - 1;
        auto resultCoeffs = new int[resultSize]();
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < other.size; ++j) {
                resultCoeffs[i + j] += coefficients[i] * other.coefficients[j];
            }
        }
        return {resultCoeffs, resultSize};
    }

    KPolynomial& operator*=(const KPolynomial& other) {
        *this = *this * other;
        return *this;
    }

    [[nodiscard]] Iterator* createIterator() const;

private:
    int* coefficients;
    size_t size;
};

class Iterator {
public:
    explicit Iterator(const KPolynomial* poly) : polynomial(poly) {}

    void first() {
        index = 0;
    }

    void next() {
        index++;
    }

    [[nodiscard]] bool isDone() const {
        return index == polynomial->Count() + 1;
    }

    [[nodiscard]] int current() const {
        return polynomial->GetCoefficient(index);
    }

    [[nodiscard]] int getIndex() const {
        return index;
    }

private:
    const KPolynomial* polynomial;
    size_t index;
};

inline Iterator *KPolynomial::createIterator() const {
    return new Iterator(this);
}

class Iteratorv2 {
public:
    explicit Iteratorv2 (const KPolynomial &poly) : polynomial(poly), index(0) {}

    void operator++() {
        index++;
    }

    bool operator() () const {
        return index != polynomial.Count() + 1;
    }

    int operator *() const {
        return polynomial.GetCoefficient(index);
    }

    [[nodiscard]] int getIndex() const {
        return index;
    }

private:
    const KPolynomial &polynomial;
    int index;
};

#endif //KPOLYNOMIAL_H
