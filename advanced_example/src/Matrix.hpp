#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>
#include <omp.h>


class Matrix {
    public:
        Matrix() : rows(0), cols(0), data(nullptr) {}

        Matrix(int rows, int cols) : rows(rows), cols(cols) {
            data = new double[rows * cols];
        }

        ~Matrix() {
            delete[] data;
        }

        Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
            data = new double[rows * cols];
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    data[i * cols + j] = other.data[i * cols + j];
                }
            }
        }

        double operator()(int row, int col) const {
            return data[row * cols + col];
        }

        double & operator()(int row, int col) {
            return data[row * cols + col];
        }

        friend std::ostream& operator<< (std::ostream& os, const Matrix& matrix) {
            for (int i = 0; i < matrix.rows; i++) {
                for (int j = 0; j < matrix.cols; j++) {
                    os << matrix.data[i * matrix.cols + j] << " ";
                }
                os << std::endl;
            }
            return os;
        }

        void Rand(int rows, int cols) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    data[i * cols + j] = rand() / double(RAND_MAX);
                }
            }
        }

        void Eye(int rows, int cols) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (i == j) {
                        data[i * cols + j] = 1;
                    } else {
                        data[i * cols + j] = 0;
                    }
                }
            }
        }

        int Rows() const {
            return rows;
        }

        int Cols() const {
            return cols;
        }

        // Operators to be defined in cpp file
        Matrix operator+(const Matrix& other);
        Matrix operator-(const Matrix& other);
        Matrix operator*(const Matrix& other);
        Matrix operator*(double scalar);
        Matrix operator/(double scalar);

        // Advanced example linear algebra
        std::tuple<Matrix, Matrix> LUFactorization();
        std::tuple<Matrix, Matrix, Matrix> LUPFactorization();
        std::tuple<Matrix, Matrix, Matrix> LUPFactorization_Parallel();
        std::tuple<Matrix, Matrix> QRFactorization();
        std::tuple<Matrix, Matrix, Matrix> QRCPFactorization();
        //std::tuple<Matrix, Matrix, Matrix> QRCPFactorization_Parallel();

    private:
        int rows;
        int cols;
        double* data;
};