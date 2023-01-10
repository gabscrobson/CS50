#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if(argc != 3) {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *fpin = fopen(argv[1], "r");
    if(fpin == NULL) {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Read header into an array
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, fpin);

    // Use check_format to ensure WAV format
    // TODO #4
    if(!check_format(header)) {
        fclose(fpin);
        printf("Unsupported file format.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *fpout = fopen(argv[2], "w");
    if(fpout == NULL){
        fclose(fpin);
        printf("Could not create %s", argv[2]);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, fpout);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8

    // Create buffer
    BYTE buffer[block_size];

    // Read and write the last block
    fseek(fpin, -block_size, SEEK_END);
    fread(buffer, block_size, 1, fpin);
    fwrite(buffer, block_size, 1, fpout);

    // Iterate file backwards and writing on outfile
    while(ftell(fpin) > sizeof(WAVHEADER)){
        fseek(fpin, -block_size*2, SEEK_CUR);
        fread(buffer, block_size, 1, fpin);
        fwrite(buffer, block_size, 1, fpout);
    }

    // Close files
    fclose(fpin);
    fclose(fpout);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    char compare[5];
    for(int i = 0; i < 4; i++) {
        compare[i] = header.format[i];
    }
    compare[4] = '\0';

    if(strcmp(compare, "WAVE"))
        return 0;

    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample/8);
}