#include<iostream>
#include<vector>
#define longint uint64_t 

longint powmod(longint x, longint b, longint n) {
    std::vector<int> bb;
    while (b > 0) {
        bb.push_back(b % 2);
        b /= 2;
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

int main() {
    longint x, b, n; std::cin >> x >> b >> n;
    std::cout << powmod(x, b, n) << std::endl;
    return 0;
}