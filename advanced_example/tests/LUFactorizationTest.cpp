#include "Matrix.hpp"
#include <iostream>
#include <cassert>
#include "gtest/gtest.h"

TEST(LUFactorizationTest, LUFactorization) {
    // Create a test matrix
    int n = 30;
    Matrix A(n, n);
    A.Rand(n, n);

    // Perform LUP factorization
    auto [L, U] = A.LUFactorization();

    // Verify that A = LU
    Matrix LU = L * U;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(std::abs(A(i, j) - LU(i, j)) < 1e-6);
            
        }
    }

    std::cout << "LU Factorization test passed!" << std::endl;
}