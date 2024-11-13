#include "Matrix.hpp"

int main(){

    Matrix A(10, 10);
    A.Rand(10, 10);
    std::cout << A << std::endl;
    auto [L,U,P] = A.LUPFactorization();
    std::cout << L << std::endl;
    std::cout << U << std::endl;
    std::cout << P << std::endl;

    
    auto [Q, R, Cp] = A.QRCPFactorization();
    std::cout << Q << std::endl;
    std::cout << R << std::endl;
    std::cout << Cp << std::endl;

    return 0;
}