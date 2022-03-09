#ifndef BIGINT_H
#define BIGINT_H

#include<iostream>
#include<string>
#include<sstream>
#include<vector>

class BigInt {
private:
    std::string _num;
    bool _negative;
private:
    int _charIntToInt(char) const;
    std::string _reverse(const std::string&) const;
    std::string _removeLeadingZeros(const std::string&) const;
    void _addLeadingZeros(std::string&, int) const;
    void _addTrailingZeros(std::string&, int) const;
    bool _validate(const std::string&);
    bool _isNegative(const std::string&);
    std::string _absolute(const std::string&);
public:
    BigInt();
    BigInt(const std::string&);
    BigInt(const std::string&, bool);
    BigInt(const BigInt&);
    void operator=(const BigInt&);
    ~BigInt();
public:
    bool isNegative() const;
public:
    void setNegative(bool);
    char& operator[](const int);
    bool operator<(const BigInt&) const;
    bool operator<(const std::string&) const;
    bool operator>(const BigInt&) const;
    bool operator>(const std::string&) const;
    bool operator==(const BigInt&) const;
    bool operator==(const std::string&) const;
    bool operator!=(const BigInt&) const;
    bool operator!=(const std::string&) const;
    bool operator<=(const BigInt&) const;
    bool operator<=(const std::string&) const;
    bool operator>=(const BigInt&) const;
    bool operator>=(const std::string&) const;
    BigInt operator+(const BigInt&) const;
    BigInt operator+(const std::string&) const;
    void operator+=(const BigInt&);
    void operator+=(const std::string&);
    BigInt operator-(const BigInt&) const;
    BigInt operator-(const std::string&) const;
    void operator-=(const BigInt&);
    void operator-=(const std::string&);
    BigInt operator*(const BigInt&) const;
    BigInt operator*(const std::string&) const;
    void operator*=(const BigInt&);
    void operator*=(const std::string&);
    BigInt operator/(const BigInt&) const;
    BigInt operator/(const std::string&) const;
    void operator /=(const BigInt&);
    void operator /=(const std::string&);
    BigInt operator%(const BigInt&) const;
    BigInt operator%(const std::string&) const;
    void operator%=(const BigInt&);
public:
    static BigInt max(const BigInt&, const BigInt&);
    static BigInt modularAddition(const BigInt&, const BigInt&, const BigInt&);
    static BigInt modularMultiplication(const BigInt&, const BigInt&, const BigInt&);
    static BigInt GCD(BigInt, BigInt);
    static std::vector<BigInt> Bezout(const BigInt&, const BigInt&);
    static BigInt inverseModulo(const BigInt&, const BigInt&);
public:
    friend std::istream& operator>>(std::istream&, BigInt&);
    friend std::ostream& operator<<(std::ostream&, const BigInt&);
    friend std::ostream& operator<<(std::ostream&, const std::vector<BigInt>&);
};

#endif