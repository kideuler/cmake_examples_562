#include "Matrix.hpp"
#include <iostream>
#include <cassert>

void TestLUPFactorization_Parallel() {
    // Create a test matrix
    int n = 50;
    Matrix A(n, n);
    A.Rand(n, n);

    // Perform LUP factorization
    auto [L, U, P] = A.LUPFactorization_Parallel();

    // Verify that PA = LU
    Matrix PA = P * A;
    std::cout << PA << std::endl;
    Matrix LU = L * U;
    std::cout << LU << std::endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << PA(i, j) - LU(i, j) << std::endl;
            assert(std::abs(PA(i, j) - LU(i, j)) < 1e-6);
            
        }
    }

    std::cout << "LUP Factorization test passed!" << std::endl;
}

int main() {
    TestLUPFactorization_Parallel();
    return 0;
}