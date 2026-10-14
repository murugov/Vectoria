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
    alignas (32) std::array<T, N * M> data_ {};
    
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

template <typename T, size_t N, size_t K, size_t M>
Matrix <T, N, M> multiply(const Matrix<T, N, K>& A, const Matrix<T, K, M>& B) {
    Matrix<T, N, M> C {};

    for (size_t i = 0; i < N; ++i) {
        for (size_t k = 0; k < K; ++k) {
            T a_ik = A(i, k);
            for (size_t j = 0; j < M; ++j) {
                C(i, j) += a_ik * B(k, j);
            }
        }
    }
    return C;
}

template <typename T, size_t N, size_t M>
double Matrix<T, N, M>::det () const {
    if (N != M) {
        throw std::invalid_argument("Matrix must be square to compute determinant");
    }
    
    double det_val = 1.0;

    switch (N) {
        case 1:
            return this->get(0, 0);

        case 2:
            // NOTE: ad - bc
            return this->get(0, 0) * this->get(1, 1) - this->get(0, 1) * this->get(1, 0);

        case 3: {
            // NOTE: Sarrus's rule
            T term1 = this->get(0, 0) * (this->get(1, 1) * this->get(2, 2) - this->get(1, 2) * this->get(2, 1));
            T term2 = this->get(0, 1) * (this->get(1, 0) * this->get(2, 2) - this->get(1, 2) * this->get(2, 0));
            T term3 = this->get(0, 2) * (this->get(1, 0) * this->get(2, 1) - this->get(1, 1) * this->get(2, 0));
            return term1 - term2 + term3;
        }

        case 4: {
            // NOTE: Efficient expansion along the first row using 3×3 minors
            T m00 = this->get(1, 1) * (this->get(2, 2) * this->get(3, 3) - this->get(2, 3) * this->get(3, 2)) -
                    this->get(1, 2) * (this->get(2, 1) * this->get(3, 3) - this->get(2, 3) * this->get(3, 1)) +
                    this->get(1, 3) * (this->get(2, 1) * this->get(3, 2) - this->get(2, 2) * this->get(3, 1));
            T m01 = this->get(1, 0) * (this->get(2, 2) * this->get(3, 3) - this->get(2, 3) * this->get(3, 2)) -
                    this->get(1, 2) * (this->get(2, 0) * this->get(3, 3) - this->get(2, 3) * this->get(3, 0)) +
                    this->get(1, 3) * (this->get(2, 0) * this->get(3, 2) - this->get(2, 2) * this->get(3, 0));
            T m02 = this->get(1, 0) * (this->get(2, 1) * this->get(3, 3) - this->get(2, 3) * this->get(3, 1)) -
                    this->get(1, 1) * (this->get(2, 0) * this->get(3, 3) - this->get(2, 3) * this->get(3, 0)) +
                    this->get(1, 3) * (this->get(2, 0) * this->get(3, 1) - this->get(2, 1) * this->get(3, 0));
            T m03 = this->get(1, 0) * (this->get(2, 1) * this->get(3, 2) - this->get(2, 2) * this->get(3, 1)) -
                    this->get(1, 1) * (this->get(2, 0) * this->get(3, 2) - this->get(2, 2) * this->get(3, 0)) +
                    this->get(1, 2) * (this->get(2, 0) * this->get(3, 1) - this->get(2, 1) * this->get(3, 0));

            return this->get(0, 0) * m00 - this->get(0, 1) * m01 + this->get(0, 2) * m02 - this->get(0, 3) * m03;
        }

        default:
            break;
    }

    
    for (size_t i = 0; i < N; ++i) {
        size_t pivot = i;
        for (size_t j = i + 1; j < N; ++j) {
            if (std::abs(this(j, i)) > std::abs(this(pivot, i))) pivot = j;
        }

        if (pivot != i) {
            for (std::size_t j = 0; j < N; ++j) {
                std::swap(this->get(i, j), this->get(pivot, j));
            }
            det_val = -det_val;
        }

        if (std::abs(this->get(i, i)) < 1e-9) return 0.0f;

        det_val *= this->get(i, i);

        for (size_t j = i + 1; j < N; ++j) {
            T factor = this->get(j, i) / this->get(i, i);
            for (size_t k = i; k < N; ++k) {
                this->get(j, k) -= factor * this->get(i, k);
            }
        }
    }

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