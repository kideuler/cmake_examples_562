#include <iostream>


class Matrix {
    public:
        Matrix(int rows, int cols) : rows(rows), cols(cols) {
            data = new double[rows * cols];
        }

        ~Matrix() {
            delete[] data;
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
        

    private:
        int rows;
        int cols;
        double* data;
};