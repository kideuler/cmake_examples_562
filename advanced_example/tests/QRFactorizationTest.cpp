#include "Matrix.hpp"
#include <iostream>
#include <cassert>
#include "gtest/gtest.h"

TEST(TestQRFactorization, QRFactorization) {
    // Create a test matrix
    int n = 30;
    Matrix A(n, n);
    A.Rand(n, n);

    // Perform QRCP factorization
    auto [Q, R] = A.QRFactorization();

    // Verify that A = Q * R
    Matrix QR = Q * R;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(std::abs(A(i, j) - QR(i, j)) < 1e-4);
        }
    }

    std::cout << "QR Factorization test passed!" << std::endl;
}