#ifndef MILLER_RABIN_H
#define MILLER_RABIN_H

#include<iostream>
#include<vector>
#define longint int64_t

class MillerRabin {
private:
    /**
     * @brief Base to test.
     * 
     */
    std::vector<longint> _testSeed;
private:
    /**
     * @brief Run Miller-Rabin test
     * 
     * @return true if number is Prime in this base.
     * @return false otherwise
     */
    bool _test(longint, longint);
public:
    /**
     * @brief Power mod
     * 
     * @param a 
     * @param b 
     * @param n 
     * @return (a ^ b) % n 
     */
    static longint powmod(longint, longint, longint);
public:
    MillerRabin();
    MillerRabin(const std::vector<longint>&);
    ~MillerRabin();

    /**
     * @brief Run Miller-Rabin test
     * 
     * @return true if number is Prime
     * @return false otherwise
     */
    bool test(longint);
};

#endif