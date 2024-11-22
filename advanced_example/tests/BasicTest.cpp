#include "Matrix.hpp"
#include <iostream>
#include <cassert>
#include "gtest/gtest.h"

TEST(TestMatrixClass, Construct) {
    // Create matrices
    Matrix A(3, 3);
    A.Rand(3, 3);
    Matrix B(3, 3);
    B.Rand(3, 3);
    Matrix C(3, 3);
    C.Eye(3, 3);
}

TEST(TestMatrixClass, Addition) {
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
            EXPECT_EQ(D(i, j),A(i, j) + B(i, j));
        }
    }
}

TEST(TestMatrixClass, Subtract) {
    // Create matrices
    Matrix A(3, 3);
    A.Rand(3, 3);
    Matrix B(3, 3);
    B.Rand(3, 3);
    Matrix C(3, 3);
    C.Eye(3, 3);

    // Test subtraction
    Matrix E = A - B;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(E(i, j),A(i, j) - B(i, j));
        }
    }
}

TEST(TestMatrixClass, Multiply) {
    // Create matrices
    Matrix A(3, 3);
    A.Rand(3, 3);
    Matrix B(3, 3);
    B.Rand(3, 3);
    Matrix C(3, 3);
    C.Eye(3, 3);

    // Test multiplication
    Matrix F = A * B;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            double sum = 0;
            for (int k = 0; k < 3; ++k) {
                sum += A(i, k) * B(k, j);
            }
            EXPECT_EQ(F(i, j), sum);
        }
    }
}

TEST(TestMatrixClass, ScalarMultiplication) {
    // Create matrices
    Matrix A(3, 3);
    A.Rand(3, 3);
    Matrix B(3, 3);
    B.Rand(3, 3);
    Matrix C(3, 3);
    C.Eye(3, 3);

    
    // Test scalar multiplication
    Matrix G = A * 2.0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(G(i, j), A(i, j) * 2.0);
        }
    }
}

TEST(TestMatrixClass, ScalarDivision) {
    // Create matrices
    Matrix A(3, 3);
    A.Rand(3, 3);
    Matrix B(3, 3);
    B.Rand(3, 3);
    Matrix C(3, 3);
    C.Eye(3, 3);


    // Test scalar division
    Matrix H = A / 2.0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(H(i, j), A(i, j) / 2.0);
        }
    }
}

TEST(TestMatrixClass, TestIdentity) {
    // Create matrices
    Matrix A(3, 3);
    A.Rand(3, 3);
    Matrix B(3, 3);
    B.Rand(3, 3);
    Matrix C(3, 3);
    C.Eye(3, 3);

    // Test identity matrix
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) {
                EXPECT_EQ(C(i, j), 1.0);
            } else {
                EXPECT_EQ(C(i, j), 0.0);
            }
        }
    }
}