#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <iostream>
#include <array>
#include <optional>
#include <cassert>

// 74 page in file "opengl.pfd"

namespace Math {

template <typename T, size_t N, size_t M>
class Matrix {
private:
    std::array<T, N * M> data_ {};
    
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Matrix () = default;
    
    Matrix (std::initializer_list<T> list) {
        size_t i = 0;
        for (const T& elem : list) {
            if (i >= N * M) break;
            data_[i++] = elem;
        }
    }
       
    // --- Copy Semantics ---

    Matrix (const Matrix<T, N, M>& other) = default;
    Matrix<T, N, M>& operator = (const Matrix<T, N, M>& other) = default;    

    // --- Move Semantics ---

    Matrix (Matrix<T, N, M>&& other) noexcept = default;
    Matrix<T, N, M>& operator = (Matrix<T, N, M>&& other) noexcept = default;

    // --- Destructor ---

    ~Matrix () = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---

    const T& get (size_t i, size_t j) const { return data_[i * M + j]; }

    // --- Read-Only Access ---
    const T& operator () (size_t i, size_t j) const { return this->get(i, j); }

    // --- Read-Write Access ---
    T& operator () (size_t i, size_t j) { return data_[i * M + j]; }

    // -------------------------------------------------------------------------------
    // --- Setters ---

    void set (size_t i, size_t j, const T& val) { data_[i * M + j] = val; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void print () const;

    Matrix<T, N, M> add (const Matrix<T, N, M>& other) const;
    Matrix<T, N, M> sub (const Matrix<T, N, M>& other) const;
    Matrix<T, N, M> mul (T factor) const;

    double det () const;

    // -------------------------------------------------------------------------------
    // --- Operators Prototypes ---

    std::optional<T> operator [] (const size_t i) const;

    Matrix<T, N, M>  operator + (const Matrix<T, N, M>& other) const;
    Matrix<T, N, M>  operator - (const Matrix<T, N, M>& other) const;
    Matrix<T, N, M>  operator * (T factor) const;
    Matrix<T, N, M>  operator / (T divider) const;
    T                operator ^ (const Matrix<T, N, M>& other) const;

    Matrix<T, N, M>& operator += (const Matrix<T, N, M>& other);
    Matrix<T, N, M>& operator -= (const Matrix<T, N, M>& other);
    Matrix<T, N, M>& operator *= (T factor);
    Matrix<T, N, M>& operator /= (T divider);

    // -------------------------------------------------------------------------------
    // --- Implementation Of Operators ---

    friend std::ostream& operator << (std::ostream& os, const Matrix<T, N, M>& m) {
        os << "(";
        for (size_t i = 0; i < N; ++i) {
            os << "(";
            for (size_t j = 0; j < M; ++j) {
                os << m.data_[i * M + j];
                if (j < M - 1) {
                    os << ", ";
                }
            }
            os << ")";
            if (i < N - 1) {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }
};

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

template <typename T, size_t N, size_t M>
void Matrix<T, N, M>::print () const {
    std::cout << *this << std::endl;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::add (const Matrix<T, N, M>& other) const {
    Matrix<T, N, M> sum {};

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            sum.data_[i * M + j] = this->data_[i * M + j] + other.data_[i * M + j];
        }
    }
    return sum;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::sub (const Matrix<T, N, M>& other) const {
    Matrix<T, N, M> diff {};

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            diff.data_[i * M + j] = this->data_[i * M + j] - other.data_[i * M + j];
        }
    }
    return diff;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::mul (T factor) const {
    Matrix<T, N, M> prod {};

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            prod.data_[i * M + j] = this->data_[i * M + j] * factor;
        }
    }
    return prod;
}

template <typename T, size_t N, size_t M>
double Matrix<T, N, M>::det () const {
    if (N != M) {
        throw std::invalid_argument("Matrix must be square to compute determinant");
    }
    double det_val = 0.0;

    // for (size_t i = 0; i < N; ++i) {
    //     det_val += this->data_[i * M + i] * ;
    // }
    
    return det_val;
}

// -------------------------------------------------------------------------------
// --- Implementation Of Operators ---

template <typename T, size_t N, size_t M>
std::optional<T> Matrix<T, N, M>::operator [] (const size_t i) const {
    if (i >= N * M) {
        return std::nullopt;
    }
    return data_[i];
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator + (const Matrix<T, N, M>& other) const {
    return this->add(other);
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator - (const Matrix<T, N, M>& other) const {
    return this->sub(other);
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator * (T factor) const {
    return this->mul(factor);
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator / (T divider) const {
    return this->mul(static_cast<T>(1) / divider);
}


template <typename T, size_t N, size_t M>
T Matrix<T, N, M>::operator ^ (const Matrix<T, N, M>& other) const {
    return this->det(other);
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator += (const Matrix<T, N, M>& other) {
    for (size_t i = 0; i < N * M; ++i) {
        this->data_[i] += other.data_[i];
    }
    return *this;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator -= (const Matrix<T, N, M>& other) {
    for (size_t i = 0; i < N * M; ++i) {
        this->data_[i] -= other.data_[i];
    }
    return *this;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator *= (T factor) {
    for (size_t i = 0; i < N * M; ++i) {
        this->data_[i] *= factor;
    }
    return *this;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator /= (T divider) {
    for (size_t i = 0; i < N * M; ++i) {
        this->data_[i] /= divider;
    }
    return *this;
}

using Matrix2x2 = Matrix<float, 2, 2>;
using Matrix3x3 = Matrix<float, 3, 3>;
using Matrix4x4 = Matrix<float, 4, 4>;

} // namespace Math

#endif