#include "Matrix.hpp"


Matrix Matrix::operator+(const Matrix& other) {

    if (rows != other.Rows() || cols != other.Cols()) {
        throw std::invalid_argument("Matrix dimensions must match");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) {

    if (rows != other.Rows() || cols != other.Cols()) {
        throw std::invalid_argument("Matrix dimensions must match");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) {

    if (cols != other.Rows()) {
        throw std::invalid_argument("Matrix dimensions must match");
    }

    Matrix result(rows, other.Cols());
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.Cols(); j++) {
            double sum = 0;
            for (int k = 0; k < cols; k++) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) {

    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) * scalar;
        }
    }
    return result;
}

Matrix Matrix::operator/(double scalar) {

    if (scalar == 0) {
        throw std::invalid_argument("Division by zero");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) / scalar;
        }
    }
    return result;
}

std::tuple<Matrix, Matrix> Matrix::LUFactorization() {
    if (rows != cols) {
        throw std::invalid_argument("Matrix must be square for LU factorization");
    }

    Matrix L(rows, cols);
    L.Eye(rows, cols);
    Matrix U(rows, cols);

    for (int k = 0; k < cols; ++k) {
        // Compute U(k, i)
        for (int i = k; i < cols; ++i) {
            double sum = 0;
            for (int j = 0; j < k; ++j) {
                sum += L(k, j) * U(j, i);
            }
            U(k, i) = (*this)(k, i) - sum;
        }

        // Compute L(i, k)
        for (int i = k + 1; i < rows; ++i) {
            double sum = 0;
            for (int j = 0; j < k; ++j) {
                sum += L(i, j) * U(j, k);
            }
            L(i, k) = ((*this)(i, k) - sum) / U(k, k);
        }
    }

    return std::make_tuple(L, U);
}

std::tuple<Matrix, Matrix, Matrix> Matrix::LUPFactorization() {
    if (rows != cols) {
        throw std::invalid_argument("Matrix must be square for LUP factorization");
    }

    Matrix L(rows, cols);
    L.Eye(rows, cols);
    Matrix U(rows, cols);
    Matrix A_C(*this);
    Matrix P(rows, cols);
    P.Eye(rows, cols);

    std::vector<int> pivot(rows);
    for (int i = 0; i < rows; ++i) {
        pivot[i] = i;
    }

    for (int k = 0; k < cols; ++k) {
        // Find the pivot row
        int maxIndex = k;
        for (int i = k + 1; i < rows; ++i) {
            if (std::abs(A_C(i, k)) > std::abs(A_C(maxIndex, k))) {
                maxIndex = i;
            }
        }

        // Swap rows in U and P
        if (maxIndex != k) {
            std::swap(pivot[k], pivot[maxIndex]);
            for (int j = 0; j < cols; ++j) {
                std::swap(A_C(k, j), A_C(maxIndex, j));
                std::swap(P(k, j), P(maxIndex, j));
            }
        }
    }

    for (int k = 0; k < cols; ++k) {

        // Compute U(k, i)
        for (int i = k; i < cols; ++i) {
            double sum = 0;
            for (int j = 0; j < k; ++j) {
                sum += L(k, j) * U(j, i);
            }
            U(k, i) = A_C(k, i) - sum;
        }

        // Compute L(i, k)
        for (int i = k + 1; i < rows; ++i) {
            double sum = 0;
            for (int j = 0; j < k; ++j) {
                sum += L(i, j) * U(j, k);
            }
            L(i, k) = (A_C(i, k) - sum) / U(k, k);
        }
    }

    return std::make_tuple(L, U, P);
}

std::tuple<Matrix, Matrix, Matrix> Matrix::LUPFactorization_Parallel() {
    if (rows != cols) {
        throw std::invalid_argument("Matrix must be square for LUP factorization");
    }

    Matrix L(rows, cols);
    L.Eye(rows, cols);
    Matrix U(rows, cols);
    Matrix A_C(*this);
    Matrix P(rows, cols);
    P.Eye(rows, cols);

    std::vector<int> pivot(rows);
    for (int i = 0; i < rows; ++i) {
        pivot[i] = i;
    }
   
    for (int k = 0; k < cols; ++k) {
        // Find the pivot row
        int maxIndex = k;
        for (int i = k + 1; i < rows; ++i) {
            if (std::abs(A_C(i, k)) > std::abs(A_C(maxIndex, k))) {
                maxIndex = i;
            }
        }

        // Swap rows in U and P
        if (maxIndex != k) {
            std::swap(pivot[k], pivot[maxIndex]);
            for (int j = 0; j < cols; ++j) {
                std::swap(A_C(k, j), A_C(maxIndex, j));
                std::swap(P(k, j), P(maxIndex, j));
            }
        }
    }

    #pragma omp parallel shared(L,U,A_C)
    {
    for (int k = 0; k < cols; ++k) {

        // Compute U(k, i)
        #pragma omp for
        for (int i = k; i < cols; ++i) {
            double sum = 0;
            for (int j = 0; j < k; ++j) {
                sum += L(k, j) * U(j, i);
            }
            U(k, i) = A_C(k, i) - sum;
        }

        // Compute L(i, k)
        #pragma omp for
        for (int i = k + 1; i < rows; ++i) {
            double sum = 0;
            for (int j = 0; j < k; ++j) {
                sum += L(i, j) * U(j, k);
            }
            L(i, k) = (A_C(i, k) - sum) / U(k, k);
        }
    }
    }
    

    return std::make_tuple(L, U, P);
}

std::tuple<Matrix, Matrix> Matrix::QRFactorization() {
    if (rows < cols) {
        throw std::invalid_argument("Matrix must have more rows than columns for QR factorization");
    }

    Matrix Q(rows, cols);
    Matrix R(cols, cols);

    for (int k = 0; k < cols; ++k) {
        // Compute the k-th column of Q
        for (int i = 0; i < rows; ++i) {
            Q(i, k) = (*this)(i, k);
        }

        // Orthogonalize against previous columns
        for (int j = 0; j < k; ++j) {
            double dot_product = 0;
            for (int i = 0; i < rows; ++i) {
                dot_product += Q(i, j) * (*this)(i, k);
            }
            R(j, k) = dot_product;
            for (int i = 0; i < rows; ++i) {
                Q(i, k) -= dot_product * Q(i, j);
            }
        }

        // Normalize the k-th column of Q
        double norm = 0;
        for (int i = 0; i < rows; ++i) {
            norm += Q(i, k) * Q(i, k);
        }
        norm = std::sqrt(norm);
        R(k, k) = norm;
        for (int i = 0; i < rows; ++i) {
            Q(i, k) /= norm;
        }
    }

    return std::make_tuple(Q, R);
}

std::tuple<Matrix, Matrix, Matrix> Matrix::QRCPFactorization() {
    if (rows < cols) {
        throw std::invalid_argument("Matrix must have more rows than columns for QRCP factorization");
    }

    Matrix Q(rows, cols);
    Matrix R(cols, cols);
    Matrix A_C(*this);
    Matrix P(cols, cols);
    P.Eye(cols, cols);

    std::vector<int> pivots(cols);
    for (int i = 0; i < cols; ++i) {
        pivots[i] = i;
    }

    for (int k = 0; k < cols; ++k) {
        // Find the column with the largest norm
        int maxIndex = k;
        double maxNorm = 0;
        for (int j = k; j < cols; ++j) {
            double norm = 0;
            for (int i = k; i < rows; ++i) {
                norm += R(i, j) * R(i, j);
            }
            if (norm > maxNorm) {
                maxNorm = norm;
                maxIndex = j;
            }
        }

        // Swap columns in R and P
        if (maxIndex != k) {
            for (int i = 0; i < rows; ++i) {
                std::swap(A_C(i, k), A_C(i, maxIndex));
            }
            for (int i = 0; i < cols; ++i) {
                std::swap(P(k, i), P(maxIndex, i));
            }
            std::swap(pivots[k], pivots[maxIndex]);
        }
    }

    for (int k = 0; k < cols; ++k) {
        // Compute the k-th column of Q
        for (int i = 0; i < rows; ++i) {
            Q(i, k) = A_C(i, k);
        }

        // Orthogonalize against previous columns
        for (int j = 0; j < k; ++j) {
            double dot_product = 0;
            for (int i = 0; i < rows; ++i) {
                dot_product += Q(i, j) * A_C(i, k);
            }
            R(j, k) = dot_product;
            for (int i = 0; i < rows; ++i) {
                Q(i, k) -= dot_product * Q(i, j);
            }
        }

        // Normalize the k-th column of Q
        double norm = 0;
        for (int i = 0; i < rows; ++i) {
            norm += Q(i, k) * Q(i, k);
        }
        norm = std::sqrt(norm);
        R(k, k) = norm;
        for (int i = 0; i < rows; ++i) {
            Q(i, k) /= norm;
        }
    }

    return std::make_tuple(Q, R, P);
}
