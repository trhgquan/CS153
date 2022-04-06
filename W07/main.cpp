/**
 * @file main.cpp
 * @author Lê Hoàng Trọng Tín (19120682), Lê Mai Nguyên Thảo (19120661), Trần Hoàng Quân (19120338)
 * @brief Bài tập tuần 07 - Cài đặt thuật toán Rabin-Miller.
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 */
#include<iostream>
#include<vector>
#define longint uint64_t 

/**
 * @brief PowerMod (x^b mod n)
 * 
 * @param x longint (uint64_t)
 * @param b longint (uint64_t)
 * @param n longint (uint64_t)
 * @return longint 
 */
longint powmod(longint x, longint b, longint n) {
    std::vector<int> bb;
    while (b > 0) {
        bb.push_back(b % 2);
        b >>= 1;
    }

    longint z = 1;
    x = x % n;
    for (int i = bb.size() - 1; i >= 0; --i) {
        z = (z * z) % n;
        if (bb[i] == 1) {
            z = (z * x) % n;
        }
    }

    return z;
}

/**
 * @brief Rabin-Miller test for an integer p with base a
 * 
 * @param p number to do primarity check
 * @param a base
 * @return true if p is a prime, false otherwise.
 */
bool MillerRabinTest(longint p, longint a) {
    longint m = p - 1;
    
    int k = 0;

    while (!(m & 1)) {
        m >>= 1; ++k;
    }

    longint b = powmod(a, m, p);
    
    if ((b % p) == 1) {
        return true;
    }

    for (int i = 0; i < k; ++i) {
        if ((b % p) == p - 1) {
            return true;
        }
        b = powmod(b, 2, p);
    }

    return false;
}

int main() {
    longint a; std::cout << "Nhap co so a = "; std::cin >> a;
    longint p; std::cout << "Nhap so nguyen p = "; std::cin >> p;

    if (MillerRabinTest(p, a)) {
        std::cout << p << " la so nguyen to co so " << a << '\n';
    }
    else {
        std::cout << p << " la hop so\n";
    }

    return 0;
}