#include"MillerRabin.h"

int main() {
    std::vector<longint> seed = {2, 3, 5, 7, 11};
    MillerRabin engine(seed);

    std::vector<longint> test = {1337, 7331, 2069, 9337};
    for (const auto& num : test) {
        std::cout << "Is " << num << " a prime? " << (engine.test(num) ? "YES" : "NO") << '\n';
    }
}