#include"AES.h"

AES::AES() {
    // Do nothing
}

AES::~AES() {
    delete[] _keyExpanded;
}

AES::AES(const char* keyInput) {
    _keyExpanded = new unsigned char[INPUT_SIZE];
    
    for (int i = 0; i < INPUT_SIZE; ++i) {
        _keyExpanded[i] = keyInput[i];
    }

    _keyExpansion();
}

unsigned char* AES::key() {
    return _keyExpanded;
}

void AES::_keyExpansionCore(unsigned char* in, unsigned char i) {
    unsigned char temp = in[0];
    for (int i = 0; i < TEMP_SIZE - 1; ++i) {
        in[i] = in[i + 1];
    }

    in[TEMP_SIZE - 1] = temp;

    for (int i = 0; i < TEMP_SIZE; ++i) {
        in[i] = _SBox[in[i]];
    }

    in[0] ^= _C[i];
}

void AES::_keyExpansion() {
    int bytesGenerated = INPUT_SIZE;

    int rconIndex = 1;

    unsigned char tmpCore[TEMP_SIZE];

    while (bytesGenerated < TOTAL_SIZE) {
        for (int i = 0; i < TEMP_SIZE; ++i) {
            tmpCore[i] = _keyExpanded[i + bytesGenerated - TEMP_SIZE];
        }

        if (!(bytesGenerated % INPUT_SIZE)) {
            _keyExpansionCore(tmpCore, rconIndex++);
        }

        for (unsigned char a = 0; a < TEMP_SIZE; ++a) {
            _keyExpanded[bytesGenerated] = _keyExpanded[bytesGenerated - INPUT_SIZE] ^ tmpCore[a];
            ++bytesGenerated;
        }
    }
}