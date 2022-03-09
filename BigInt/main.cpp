/**
 * @file main.cpp
 * @author Lê Hoàng Trọng Tín (19120682), Lê Mai Nguyên Thảo (19120661), Trần Hoàng Quân (19120338)
 * @brief Thư viện BigInt
 * @version 0.1
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include"BigInt.h"

int main() {
    try {
        BigInt m; std::cout << "Moi thay nhap m = "; std::cin >> m;
        BigInt a; std::cout << "Moi thay nhap a = "; std::cin >> a;
        BigInt b; std::cout << "Moi thay nhap b = "; std::cin >> b;

        std::cout << "(a + b) % m = " << BigInt::modularAddition(a, b, m) << '\n';
        std::cout << "(a * b) % m = " << BigInt::modularMultiplication(a, b, m) << '\n';
        std::cout << "GCD(a, b) = " << BigInt::GCD(a, b) << '\n';
        std::cout << "Bezout identity = " << BigInt::Bezout(a, b) << '\n';
        std::cout << "Inverse of a in m = " << BigInt::inverseModulo(a, m) << '\n';
        std::cout << "Inverse of b in m = " << BigInt::inverseModulo(b, m) << '\n';
    }
    catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}