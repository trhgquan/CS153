#include"MD5.h"

int main() {
    const char* s[] = {{""}, {"fit.hcmus"}};

    for (int i = 0; i < (sizeof(s) / sizeof(s[0])); ++i) {
        MD5 m(s[i], strlen(s[i]));
        unsigned char* digest = m.digest();

        printf("Message: %s (length: %d)\n", s[i], strlen(s[i]));
        printf("Digest: ");
        
        for (int i = 0; i < 16; ++i) {
            printf("%02x", digest[i]);
        }
        printf("\n");

        free(digest);
    }
    
    return 0;
}