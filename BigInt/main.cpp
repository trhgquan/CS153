#include"BigInt.h"

int main() {
    try {
        BigInt m; std::cout << "m = "; std::cin >> m;
        BigInt a; std::cout << "a = "; std::cin >> a;
        BigInt b; std::cout << "b = "; std::cin >> b;

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