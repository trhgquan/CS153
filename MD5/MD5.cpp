#include"MD5.h"
#define power 0x100000000

MD5::MD5() {
    // Do nothing;
}

MD5::MD5(const char* s, unsigned int stringLength) {
    _init(s, stringLength);
    _final();
}

MD5::~MD5() {
    // Do nothing
}

unsigned char* MD5::digest() {
    unsigned char* digest = (unsigned char*)malloc(16);
    for (int i = 0; i < 16; ++i) {
        digest[i] = _digest[i];
    }
    return digest;
}

unsigned int MD5::rotateLeft(unsigned int number, unsigned int times) {
    return (number << times) | (number >> (8 * sizeof(unsigned int) - times));
}

void MD5::plusInt(unsigned int& a, unsigned int& b, unsigned int c) {
    if (a > 0xffffffff - c) {
        ++b;
    }
    a += c; 
}

void MD5::_init(const char* s, unsigned int stringLength) {
    // Tinh hang so K
    for (int i = 0; i < 64; ++i) {
        // Cong thuc tinh K da co trong slide, cai hex nay la 2^32.
        _K[i] = floor(abs(sin(i + 1)) * power);
    }

    // Message length ban dau bang 0
    _messageLength = 0;

    _bitLength[0] = 0;
    _bitLength[1] = 0;

    // a0, b0, c0, d0
    _A0 = 0x67452301;
    _B0 = 0xEFCDAB89;
    _C0 = 0x98BADCFE;
    _D0 = 0x10325476;

    //  Preprocessing.
    for (unsigned int i = 0; i < stringLength; ++i) {
        _message[_messageLength] = s[i];
        _messageLength++;
        if (_messageLength == 64) {
            // Ket thuc moi block 512 bits, tien hanh transform.
            _transform();
            plusInt(_bitLength[0], _bitLength[1], 512);
            _messageLength = 0;
        }
    }
}

void MD5::_transform() {
    // Chuyen block 512 bits thanh 16 word 32bits.
    unsigned int m[16]; int j = 0;
    
    // Code nay chuyen message tu big endian thanh little endian.
    for (int i = 0; i < 16; ++i) {
        m[i] = _message[j] + (_message[j + 1] << 8) + (_message[j + 2] << 16) + (_message[j + 3] << 24);
        j += 4;
    }

    unsigned int a = _A0;
    unsigned int b = _B0;
    unsigned int c = _C0;
    unsigned int d = _D0;
    
    for (int i = 0; i < 64; ++i) {
        unsigned int f, g;

        // Case 1
        if (i >= 0 && i <= 15) {
            f = (b & c) | ((~b) & d);
            g = i;
        }

        // Case 2
        else if (i >= 16 && i <= 31) {
            f = (d & b) | ((~d) & c);
            g = (5 * i + 1) % 16;
        }
        
        // Case 3
        else if (i >= 32 && i <= 47) {
            f = b ^ c ^ d;
            g = (3 * i + 5) % 16;
        }

        // Case 4
        else if (i >= 48 && i <= 63) {
            f = c ^ (b | (~d));
            g = (7 * i) % 16;
        }

        f = f + a + _K[i] + m[g];

        a = d; d = c; c = b; b += rotateLeft(f, _s[i]);
    }

    _A0 += a;
    _B0 += b;
    _C0 += c;
    _D0 += d;
}

void MD5::_final() {
    // Pad phan con lai cua data.
    unsigned int i = _messageLength;
    
    if (_messageLength < 56) {
        _message[i] = 0x80; ++i;
        for (; i < 56; ++i) {
            _message[i] = 0x00;
        }
    }
    else if (_messageLength >= 56) {
        _message[i] = 0x80; ++i;
        for (; i < 64; ++i) {
            _message[i] = 0x00;
        }
        _transform();
        memset(_message, 0, 56);
    }

    plusInt(_bitLength[0], _bitLength[1], 8 * _messageLength);

    // Pad block cuoi
    for (int i = 0; i < 4; ++i) {
        _message[56 + i] = _bitLength[0] >> (i * 8);
    }
    for (int i = 0; i < 4; ++i) {
        _message[60 + i] = _bitLength[1] >> (i * 8);
    }

    _transform();

    // Chuyen tu little endian ve lai big endian.
    for (int i = 0; i < 4; ++i) {
        _digest[i]      = (_A0 >> (i * 8)) & 0x000000ff;
        _digest[i + 4]  = (_B0 >> (i * 8)) & 0x000000ff;
        _digest[i + 8]  = (_C0 >> (i * 8)) & 0x000000ff;
        _digest[i + 12] = (_D0 >> (i * 8)) & 0x000000ff;
    }
}