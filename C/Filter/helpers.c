
#include "helpers.h"
#include <math.h>
#include <stdio.h>
typedef struct
{
    float red;
    float green;
    float blue;
} colors;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average =
                round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +
                                 0.189 * image[i][j].rgbtBlue);
            sepiaRed = (sepiaRed > 255) ? 255 : sepiaRed;

            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +
                                   0.168 * image[i][j].rgbtBlue);
            sepiaGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;

            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +
                                  0.131 * image[i][j].rgbtBlue);
            sepiaBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // creating a 1px bigger copy

    RGBTRIPLE copy[height + 2][width + 2];

    // filling the copy with black pixels

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            copy[i][j] = (RGBTRIPLE){0, 0, 0};
        }
    }

    // put the image in the copy

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            copy[i][j] = image[i - 1][j - 1];
        }
    }

    // calculations

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            int d = 0;
            colors sum = (colors){0, 0, 0};
            for (int a = i - 1; a < i + 2; a++)
            {
                for (int b = j - 1; b < j + 2; b++)
                {
                    sum.red += (float) copy[a][b].rgbtRed;
                    sum.green += (float) copy[a][b].rgbtGreen;
                    sum.blue += (float) copy[a][b].rgbtBlue;

                    if (a != 0 && a != height + 1 && b != 0 && b != width + 1)
                    {
                        d++;
                    }
                }
            }
            sum.red = round(sum.red / d);
            sum.green = round(sum.green / d);
            sum.blue = round(sum.blue / d);

            image[i - 1][j - 1].rgbtRed = (BYTE) sum.red;
            image[i - 1][j - 1].rgbtGreen = (BYTE) sum.green;
            image[i - 1][j - 1].rgbtBlue = (BYTE) sum.blue;
        }
    }
}
