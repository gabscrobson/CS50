// Copies a BMP file
// Comments with :G were done by me instead of CS50 :G

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 4;
    }

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Absolute value :G
    int biHeight = abs(bi.biHeight);

    // Allocate memory for image matrix SEGFAULT :G
    /*RGBTRIPLE ** image = (RGBTRIPLE **)malloc(biHeight * sizeof(RGBTRIPLE));
    for(int i = 0; i < biHeight; i++) {
        image[i] = malloc(bi.biWidth * sizeof(RGBTRIPLE));
    }*/

    // Image matrix without malloc :G
    RGBTRIPLE image[biHeight][bi.biWidth];

    // Iterate over infile's scanlines
    for (int i = 0; i < biHeight; i++)
    {
        // Iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // Temporary storage
            RGBTRIPLE triple;

            // Read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // Store the image in a matrix :G
            image[i][j] = triple;

        }

        // Skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

    }

    // Iterate backwards in rows :G
    for(int i = biHeight; i >= 0; i--) {
        for(int j = 0; j < bi.biWidth; j++) {

            // Write RGB image to outfile :G
            fwrite(&image[i][j], sizeof(RGBTRIPLE), 1, outptr);

        }

        // Then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Success
    return 0;
}
