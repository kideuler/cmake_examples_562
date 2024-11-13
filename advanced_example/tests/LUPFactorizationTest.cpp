#include "Matrix.hpp"
#include <iostream>
#include <cassert>

void TestLUPFactorization() {
    // Create a test matrix
    int n = 50;
    Matrix A(n, n);
    A.Rand(n, n);

    // Perform LUP factorization
    auto [L, U, P] = A.LUPFactorization();

    // Verify that PA = LU
    Matrix PA = P * A;
    Matrix LU = L * U;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(std::abs(PA(i, j) - LU(i, j)) < 1e-6);
            
        }
    }

    std::cout << "LUP Factorization test passed!" << std::endl;
}

int main() {
    TestLUPFactorization();
    return 0;
}