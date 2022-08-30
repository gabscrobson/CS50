#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string subs(string plain, string key);

int key_check(string key);

int main(int argc, string argv[]) {

    // CHECK IF IT HAS AN INPUT
    if (argc < 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // CHECK IF IT HAS MORE THAN 1 INPUT
    if (argc > 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // IF KEYCHECK FUNCTION DETECTS AN ERROR, RETURN 1
    if (key_check(argv[1]) == 1) {
        return 1;
    }
    // ELSE KEY = USER ARGV INPUT
    string key = argv[1];

    // GET USER PLAINTEXT INPUT
    string plain = get_string("plaintext:  ");

    string cipher = subs(plain, key);

    // PRINT RESULT
    printf("ciphertext: %s\n", cipher);

}

int key_check(string key) {
    // STRING LENGHT
    int leng = strlen(key);

    // CHECK IF KEY HAVE 26 CHARACTERS
    if (leng < 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


    for (int i = 0; i < leng; i++) {

        // CHECK IF KEY ONLY HAVE ALPHABET CHARACTERS
        if (isalpha(key[i]) == 0) {
            printf("Key must contain only alphabet characters\n");
            return 1;
        }

        // CHECK IF KEY HAVE REPEATED CHARACTER
        for (int i2 = 0; i2 < 26; i2++) {

            if (i != i2) {

                if (key[i] == key[i2]) {
                    printf("Key must have each character exactly one time\n");
                    return 1;
                }
            }
        }
    }

    return 0;
}

string subs(string plain, string key) {
    // GET PLAINTEXT LENGHT
    int leng = strlen(plain);

    // CREATES CIPHER STRING
    string cipher = plain;

    // CREATES AN ARRAY FOR UPPER KEY
    int UPPER[26];
    for (int i2 = 0; i2 < 26; i2++) {
        if (isupper(key[i2]) > 0 ) {
            UPPER[i2] = key[i2];
        }
        else {
            UPPER[i2] = key[i2] - 32;
        }
    }

    // CREATES AN ARRAY FOR LOWER KEY
    int LOWER[26];
    for (int i3 = 0; i3 < 26; i3++) {
        if (islower(key[i3])> 0) {
            LOWER[i3] = key[i3];
        }
        else {
            LOWER[i3] = key[i3] + 32;
        }
    }

    for (int i = 0; i < leng; i++) {
        if (isupper(plain[i]) > 0) {
            cipher[i] = UPPER[plain[i] - 65];
        }
        else if (islower(plain[i]) > 0) {
            cipher[i] = LOWER[plain[i] - 97];
        }
        else {
            cipher[i] = plain[i];
        }
    }

    return cipher;

}