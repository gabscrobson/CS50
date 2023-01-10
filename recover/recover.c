#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2) {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");

    // Create variables
    BYTE buffer[BLOCK_SIZE];
    int count = 0;
    char outname[8];
    FILE *out;

    // Loop while there is something to read
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE){

        // Search for JPEG header
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef)) {

            if(count != 0) {
                fclose(out);
            }

            // jpg name
            if(count < 10)
                sprintf(outname, "00%d.jpg", count);
            else if(count < 100)
                sprintf(outname, "0%d.jpg", count);
            else
                sprintf(outname, "%d.jpg", count);

            // open file
            out = fopen(outname, "w");

            // write on file
            fwrite(buffer, BLOCK_SIZE, 1, out);

            count++;
        }

        else {
            if(count != 0) {
                // write on file
                fwrite(buffer, BLOCK_SIZE, 1, out);
            }
        }

    }

    fclose(file);
    fclose(out);

    return 0;
}