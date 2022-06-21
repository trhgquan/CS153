#include"AES.h"

int main() {
    const char* keyInput = "Thats my Kung Fu";

    AES engine(keyInput);

    unsigned char* key = engine.key();
    for (int i = 0; i < TOTAL_SIZE; ++i) {
        if (!(i % INPUT_SIZE)) {
            printf("\nK%02d: ", i / INPUT_SIZE);
        }
        printf("%02x ", key[i]);
    }

    return 0;
}