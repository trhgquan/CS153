/**
 * @file main.cpp
 * @author Lê Hoàng Trọng Tín (19120682), Lê Mai Nguyên Thảo (19120661), Trần Hoàng Quân (19120338)
 * @brief Bài tập về nhà tuần 3 (tự giác): cài đặt thuật toán Euclide & Euclide mở rộng
 * @version 0.2
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
    }
    catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}