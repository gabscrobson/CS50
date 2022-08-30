#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_sentences(string text);

int count_words(string text);

int count_letters(string text);

int main(void) {
    // HEADER
    // S is the average number of setences per 100 words
    // L is the average number of letters per 100 words
    // Coleman-Liau index is |index = 0.0588 * L - 0.296 * S - 15.8|
    float L, S, index;
    int rounded, words, letters, sentences;
    int grade[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    // GET TEXT INPUT FROM THE USER
    string text = get_string("Text: ");

    // COUNT LETTERS, WORDS, SENTECES WITH RESPECTIVE FUNCTIONS
    letters = count_letters(text);

    words = count_words(text);

    sentences = count_sentences(text);

    // CALCULATE L
    L = (100*letters)/(float)words;

    // CALCULATE S
    S = (100*sentences)/(float)words;

    // CALCULATE INDEX
    index = 0.0588 * L - 0.296 * S - 15.8;

    // ROUNDING INDEX
    rounded = round(index);

    // PRINT RESULT
    if (index < 1) {
        printf("Before Grade 1\n");
    }

    else if (index >= 16) {
        printf("Grade 16+\n");
    }

    else {
        printf("Grade %d\n", grade[rounded]);
    }

}

// WORKING
int count_letters(string text) {

    int letters = 0;
    int leng = strlen(text);

    for (int i = 0; i < leng; i++) {

        // UPPERCASE
        if (text[i] >= 65 &&  text[i] <= 90) {
            letters = letters + 1;
        }

        // LOWERCASE
        else if (text[i] >= 97 && text[i] <= 122) {
            letters = letters + 1;
        }

    }

    return letters;
}

// WORKING
int count_words(string text) {
    int words = 0;
    int leng = strlen(text);

    for (int i = 0; i < leng; i++) {
        if (text[i] == 32) {
            words++;
        }
    }

    words = words + 1;

    return words;
}

// WORKING
int count_sentences(string text) {

    int sentences = 0;
    int leng = strlen(text);

    for (int i = 0; i < leng; i++) {
        if (text[i] == 46 || text[i] == 63 || text[i] == 33) {
            sentences++;
        }
    }


    return sentences;
}