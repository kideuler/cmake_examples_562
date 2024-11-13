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
