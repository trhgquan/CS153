#include"MillerRabin.h"

longint MillerRabin::powmod(longint a, longint b, longint n) {
    std::vector<int> base;
    while (b > 0) {
        base.push_back(b % 2); b >>= 1;
    }

    longint z = 1;
    for (int i = base.size() - 1; i >= 0; --i) {
        z = (z * z) % n;
        if (base[i] == 1) {
            z = (z * a) % n;
        }
    }

    return z;
}

bool MillerRabin::_test(longint p, longint a) {
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

bool MillerRabin::test(longint x) {
    for (const auto& num : _testSeed) {
        if (!_test(num, x)) {
            return false;
        }
    }
    return true;
}

MillerRabin::MillerRabin() {
    // Do nothing
}

MillerRabin::~MillerRabin() {
    // Do nothing
}

MillerRabin::MillerRabin(const std::vector<longint>& testSeed) {
    _testSeed = testSeed;
}

