#include <stdio.h>
#include <cs50.h>
#include <math.h>

int getDigit(long number, int digit);
int sumDigit(int number);

int main(void) {
    long number = get_long("Card number: ");
    int other = sumDigit(getDigit(number, 2)*2) + sumDigit(getDigit(number, 4)*2) + sumDigit(getDigit(number, 6)*2) + sumDigit(getDigit(number, 8)*2) + sumDigit(getDigit(number, 10)*2) + sumDigit(getDigit(number, 12)*2) + sumDigit(getDigit(number, 14)*2) + sumDigit(getDigit(number, 16)*2);
    int another = getDigit(number, 1) + getDigit(number, 3) + getDigit(number, 5) + getDigit(number, 7) + getDigit(number, 9) + getDigit(number, 11) + getDigit(number, 13) + getDigit(number, 15);

    // Applies the luhn algorithm
    int luhn = (other + another)%10;

    // Creates some x digits templates
    long d13 = pow(10, 12);
    long d14 = pow(10, 13);
    long d15 = pow(10, 14);
    long d16 = pow(10, 15);

    // Verifies if it is valid
    if (luhn != 0 || number < d13) {
        printf("INVALID\n");
    }
    else {

        // Verifies de card company
        if (number >= d13 & number < d14) {
            if (getDigit(number, 13) == 4) {
                printf("VISA\n");
            }
            else {
                printf("INVALID\n");
            }
        }

        else if (number >= d14 & number < d15){
            printf("INVALID\n");
        }

        else if (number >= d15 & number < d16) {
            if (getDigit(number, 15) == 3) {
                if (getDigit(number, 14) == 4 || getDigit(number, 14) == 7){
                    printf("AMEX\n");
                }
                else {
                    printf("INVALID\n");
                }
            }
            else {
                printf("INVALID\n");
            }
        }

        else if (number >= d16) {
            if (getDigit(number, 16) == 4) {
                printf("VISA\n");
            }
            else if (getDigit(number, 16) == 5) {
                if (getDigit(number, 15) == 1 || getDigit(number, 15) == 2 || getDigit(number, 15) == 3 || getDigit(number, 15) == 4 || getDigit(number, 15) == 5) {
                    printf("MASTERCARD\n");
                }
                else {
                    printf("INVALID\n");
                }
            }
            else {
                printf("INVALID\n");
            }
        }
    }
}

// Function to get a digit from a number (right to left)
int getDigit(long number, int digit) {
    long a = pow(10, digit);
    long b = pow(10, digit - 1);
    long result = (number % a - number % b)/b;
    return result;
}

// Function to sum two digits of a number
int sumDigit(int number) {
    if (number >= 10){
        int a = number % 10;
        int b = getDigit(number, 2);
        int result = a + b;
        return result;
    }
    else {
        return number;
    }
}