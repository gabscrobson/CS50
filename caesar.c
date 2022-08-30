#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string caesar(string p, int key);

int verify_key(string key, int n);

int main(int argc, string argv[])  {

    // VERIFIES IF IT HAS AN INPUT
    if (argc < 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // k is the key | p is the plaintext | c is the ciphertext
    int k = verify_key(argv[1], argc);
    if (k == -1) {
        return 1;
    }

    string p = get_string("plaintext:  ");

    string c = caesar(p, k);

    printf("ciphertext: %s\n", c);

}

int verify_key(string key, int n) {

    int leng = strlen(key);

    // VERIFIES IF IT HAS MORE THAN 1 INPUT
    if (n > 2) {
        printf("Usage: ./caesar key\n");
        return -1;
    }

    // VERIFIES IF IT IS DECIMAL
    else {
        for (int i = 0; i < leng; i++) {
            if (key[i] < 48 || key[i] > 57) {
                printf("Usage: ./caesar key\n");
                return -1;
            }
        }
    }

    // CONVERT STRING TO INT
    int result = atoi(key);

    // VERIFIES IF IT IS A NON-NEGATIVE
    if (key[1] < 0) {
        printf("Usage: ./caesar key\n");
        return -1;
    }

    return result;
}

string caesar(string p, int key) {

    int UPPER[26] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};
    int LOWER[26] = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};

    int leng = strlen(p);
    string c = p;

    for(int i = 0; i < leng; i++) {

        if (p[i] > 64 && p[i] < 91) {
            c[i] = UPPER[(((p[i] - 65) + key)%26)];
        }

        else if (p[i] > 96 && p[i] < 123) {
            c[i] = LOWER[(((p[i] - 97) + key)%26)];
        }
    }

    return c;
}