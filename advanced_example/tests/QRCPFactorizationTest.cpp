#include "Matrix.hpp"
#include <iostream>
#include <cassert>
#include "gtest/gtest.h"

TEST(TestQRCPFactorization, QRCPFactorization) {
    // Create a test matrix
    int n = 30;
    Matrix A(n, n);
    A.Rand(n, n);

    // Perform QRCP factorization
    auto [Q, R, P] = A.QRCPFactorization();

    // Verify that P * A = Q * R
    Matrix PA = P * A;
    Matrix QR = Q * R;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(std::abs(PA(i, j) - QR(i, j)) < 1e-4);
        }
    }

    std::cout << "QRCP Factorization test passed!" << std::endl;
}