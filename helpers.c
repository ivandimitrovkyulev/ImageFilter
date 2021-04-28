#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            float average_value = round((image[i][k].rgbtRed + image[i][k].rgbtGreen + image[i][k].rgbtBlue) / 3.0);
            image[i][k].rgbtRed = average_value;
            image[i][k].rgbtGreen = average_value;
            image[i][k].rgbtBlue = average_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int i = 0; i < height; i++)
    {
        int m = width - 1;
        for (int k = 0; k < (width / 2); k++)
        {
            temp = image[i][k];
            image[i][k] = image[i][m];
            image[i][m] = temp;

            m--;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            temp[i][k] = image[i][k];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            float delitel = 0.0;
            int red, green, blue;
            red = green = blue = 0;

            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (i+m < height && k+n < width &&
                    i+m > -1 && k+n > -1)
                    {
                        red += temp[i+m][k+n].rgbtRed;
                        green += temp[i+m][k+n].rgbtGreen;
                        blue += temp[i+m][k+n].rgbtBlue;
                        delitel++;
                    }
                }
            }

            red = round(red / delitel);
            green = round(green / delitel);
            blue = round(blue / delitel);

            image[i][k].rgbtRed = red;
            image[i][k].rgbtGreen = green;
            image[i][k].rgbtBlue = blue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            temp[i][k] = image[i][k];
        }
    }
    int kernelX[3][3], kernelY[3][3];

    kernelX[0][0] = -1; kernelX[0][1] = 0; kernelX[0][2] = 1;
    kernelX[1][0] = -2; kernelX[1][1] = 0; kernelX[1][2] = 2;
    kernelX[2][0] = -1; kernelX[2][1] = 0; kernelX[2][2] = 1;

    kernelY[0][0] = -1; kernelY[0][1] = -2; kernelY[0][2] = -1;
    kernelY[1][0] = 0; kernelY[1][1] = 0; kernelY[1][2] = 0;
    kernelY[2][0] = 1; kernelY[2][1] = 2; kernelY[2][2] = 1;

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            float delitel = 0.0;
            int GXred, GXgreen, GXblue, GYred, GYgreen, GYblue, Gx, Gy;
            Gx = Gy = GXred = GXgreen = GXblue = GYred = GYgreen = GYblue = 0;

            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (i+m < height && k+n < width &&
                    i+m > -1 && k+n > -1)
                    {
                        GXred += temp[i+m][k+n].rgbtRed * kernelX[m+1][n+1];
                        GXgreen += temp[i+m][k+n].rgbtGreen * kernelX[m+1][n+1];
                        GXblue += temp[i+m][k+n].rgbtBlue * kernelX[m+1][n+1];
                        
                        GYred += temp[i+m][k+n].rgbtRed * kernelY[m+1][n+1];
                        GYgreen += temp[i+m][k+n].rgbtGreen * kernelY[m+1][n+1];
                        GYblue += temp[i+m][k+n].rgbtBlue * kernelY[m+1][n+1];
                        
                        delitel++;
                    }
                }
            }
            if (round(sqrt(GXred*GXred + GYred*GYred)) > 255)
                image[i][k].rgbtRed = 255;
            else
                image[i][k].rgbtRed = round(sqrt(GXred*GXred + GYred*GYred));

            if (round(sqrt(GXgreen*GXgreen + GYgreen*GYgreen)) > 255)
                image[i][k].rgbtGreen = 255;
            else
                image[i][k].rgbtGreen = round(sqrt(GXgreen*GXgreen + GYgreen*GYgreen));
                
            if (round(sqrt(GXblue*GXblue + GYblue*GYblue)) > 255)
                image[i][k].rgbtBlue = 255;
            else
                image[i][k].rgbtBlue = round(sqrt(GXblue*GXblue + GYblue*GYblue));
            
        }
    }
    return;
}