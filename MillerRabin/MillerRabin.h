#ifndef MILLER_RABIN_H
#define MILLER_RABIN_H

#include<iostream>
#include<vector>
#define longint int64_t

class MillerRabin {
private:
    std::vector<longint> _testSeed;
private:
    bool _test(longint, longint);
public:
    static longint powmod(longint, longint, longint);
public:
    MillerRabin();
    MillerRabin(const std::vector<longint>&);
    ~MillerRabin();
    bool test(longint);
};

#endif