#ifndef MD5_H
#define MD5_H

#include<iostream>
#include<math.h>
#include<string.h>

class MD5 {
private:
    unsigned char _message[64];
    unsigned int _messageLength;
    unsigned int _bitLength[2];
    unsigned int _A0, _B0, _C0, _D0;
    unsigned int _s[64] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };
    unsigned int _K[64];
    unsigned char _digest[16];

private:
    void _transform();
    void _init(const char*, unsigned int);
    void _final();

public:
    MD5();
    MD5(const char*, unsigned int);
    unsigned char* digest();
    ~MD5();
    
public:
    /**
     * @brief Code xoay number times lan.
     * @source: https://stackoverflow.com/a/38776153/18152787
     * 
     * @param number 
     * @param times 
     * @return unsigned int 
     */
    static unsigned int rotateLeft(unsigned int, unsigned int);

    /**
     * @brief Cong so c vao so nguyen 64 bit luu trong 2 bien 32 bit a va b.
     * 
     * @param a 
     * @param b 
     * @param c 
     */
    static void plusInt(unsigned int&, unsigned int&, unsigned int);
};
#endif