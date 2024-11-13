#include "Matrix.hpp"

int main(){

    Matrix A(2, 2);
    A.Rand(2, 2);
    std::cout << A << std::endl;

    Matrix B(2, 2);
    B.Rand(2, 2);
    std::cout << B << std::endl;

    Matrix C = A + B;
    std::cout << C << std::endl;

    Matrix D = A - B;
    std::cout << D << std::endl;

    Matrix E = A * B;
    std::cout << E << std::endl;

    Matrix F = A * 2;
    std::cout << F << std::endl;

    Matrix G = A / 2;
    std::cout << G << std::endl;

    return 0;
}