#include "Matrix.hpp"
#include <iostream>
#include <cassert>

void TestMatrixClass() {
    // Create matrices
    Matrix A(3, 3);
    A.Rand(3, 3);
    Matrix B(3, 3);
    B.Rand(3, 3);
    Matrix C(3, 3);
    C.Eye(3, 3);

    // Test addition
    Matrix D = A + B;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            assert(D(i, j) == A(i, j) + B(i, j));
        }
    }

    // Test subtraction
    Matrix E = A - B;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            assert(E(i, j) == A(i, j) - B(i, j));
        }
    }

    // Test multiplication
    Matrix F = A * B;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            double sum = 0;
            for (int k = 0; k < 3; ++k) {
                sum += A(i, k) * B(k, j);
            }
            assert(F(i, j) == sum);
        }
    }

    // Test scalar multiplication
    Matrix G = A * 2.0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            assert(G(i, j) == A(i, j) * 2.0);
        }
    }

    // Test scalar division
    Matrix H = A / 2.0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            assert(H(i, j) == A(i, j) / 2.0);
        }
    }

    // Test identity matrix
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) {
                assert(C(i, j) == 1.0);
            } else {
                assert(C(i, j) == 0.0);
            }
        }
    }

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    TestMatrixClass();
    return 0;
}