#include "helpers.h"

#include <stdio.h>
#include <math.h>

// Swap variables :G
void swap(RGBTRIPLE *a, RGBTRIPLE *b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            float media = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtRed = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtBlue = media;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < (width/2); j++) {
            swap(&image[i][j], &image[i][width-1-j]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {


            int pixelsinbox = 0;
            float red = 0;
            float green = 0;
            float blue = 0;

            for(int a = i-1; a <= i+1; a++) {
                if(a >= 0 && a < height){
                    for(int b = j-1; b <= j+1; b++) {
                        if(b>=0 && b < width) {
                            pixelsinbox++;
                            red += image[a][b].rgbtRed;
                            green += image[a][b].rgbtGreen;
                            blue += image[a][b].rgbtBlue;
                        }
                    }
                }
            }

            buffer[i][j].rgbtRed = round(red/pixelsinbox);
            buffer[i][j].rgbtGreen = round(green/pixelsinbox);
            buffer[i][j].rgbtBlue = round(blue/pixelsinbox);
        }
    }

    // image = buffer;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            image[i][j].rgbtRed = buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = buffer[i][j].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int GY[3][3] = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
    int GX[3][3] = {{-1, -2, -1},{0, 0, 0},{1, 2, 1}};

    RGBTRIPLE buffer[height][width];

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            float gyred = 0, gygreen = 0, gyblue = 0;
            float gxred = 0, gxgreen = 0, gxblue = 0;
            float red = 0, green = 0, blue = 0;

            for(int a = i-1; a <= i+1; a++) {
                if(a >= 0 && a < height){
                    for(int b = j-1; b <= j+1; b++) {
                        if(b>=0 && b < width) {
                            gyred += GY[a+1-i][b+1-j] * image[a][b].rgbtRed;
                            gygreen += GY[a+1-i][b+1-j] * image[a][b].rgbtGreen;
                            gyblue += GY[a+1-i][b+1-j] * image[a][b].rgbtBlue;

                            gxred += GX[a+1-i][b+1-j] * image[a][b].rgbtRed;
                            gxgreen += GX[a+1-i][b+1-j] * image[a][b].rgbtGreen;
                            gxblue += GX[a+1-i][b+1-j] * image[a][b].rgbtBlue;
                        }
                    }
                }
            }
            red = round(sqrt((gyred * gyred) + (gxred * gxred)));
            if(red > 255)
                red = 255;
            green = round(sqrt((gygreen * gygreen) + (gxgreen * gxgreen)));
            if(green > 255)
                green = 255;
            blue = round(sqrt((gyblue * gyblue) + (gxblue * gxblue)));
            if(blue > 255)
                    blue = 255;
            buffer[i][j].rgbtRed = red;
            buffer[i][j].rgbtGreen = green;
            buffer[i][j].rgbtBlue = blue;

        }
    }

    // image = buffer;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            image[i][j].rgbtRed = buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = buffer[i][j].rgbtBlue;
        }
    }

    return;
}

void swap(RGBTRIPLE *a, RGBTRIPLE *b) {
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}
