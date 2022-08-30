#include <stdio.h>
#include <cs50.h>

int main(void)
{

    printf("------CS50 Mario-Less------\n");
    // size input
    int s;
    do
    {
        s = get_int("Size: ");
    }
    while (s < 1 || s > 8);


    // Printing
    for (int i2 = 1; i2 <= s; i2++)
    {

        for (int i3 = 0; i3 < s - i2; i3++)
        {
            printf(" ");
        }

        for (int i4 = 0; i4 < i2; i4++)
        {
            printf("#");
        }

        printf("\n");
    }
}
// it worked :)