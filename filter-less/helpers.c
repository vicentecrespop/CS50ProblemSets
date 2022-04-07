#include "helpers.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE *red = &image[i][j].rgbtRed;
            BYTE *blue = &image[i][j].rgbtBlue;
            BYTE *green = &image[i][j].rgbtGreen;
            int average;

            // Calculate the average pixel value
            float average_pixel = (*red + *blue + *green) / 3.0;
            if ((average_pixel - (int) average_pixel) > 0.5)
            {
                average = (int) average_pixel + 1;
            }
            else
            {
                average = (int) average_pixel;
            }

            // Set each color value to the average value
            *red = average;
            *blue = average;
            *green = average;
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
            BYTE *red = &image[i][j].rgbtRed;
            BYTE *blue = &image[i][j].rgbtBlue;
            BYTE *green = &image[i][j].rgbtGreen;


            // Calculate each new color value using the Sephia formula
            float sepiaRed = 0.393 * *red + 0.769 * *green + 0.189 * *blue;
            float sepiaGreen = 0.349 * *red + 0.686 * *green + 0.168 * *blue;
            float sepiaBlue = 0.272 * *red + 0.534 * *green + 0.131 * *blue;

            // Ensure the result is an integer between 0 and 255, inclusive.
            int finalRed = round(sepiaRed);
            if (finalRed > 255)
            {
                finalRed = 255;
            }
            int finalGreen = round(sepiaGreen);
            if (finalGreen > 255)
            {
                finalGreen = 255;
            }
            int finalBlue = round(sepiaBlue);
            if (finalBlue > 255)
            {
                finalBlue = 255;
            }

            // Set each color to Sepia value
            *red = finalRed;
            *green = finalGreen;
            *blue = finalBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < half; j++)
        {
            BYTE *red = &image[i][j].rgbtRed;
            BYTE *green = &image[i][j].rgbtGreen;
            BYTE *blue = &image[i][j].rgbtBlue;
            BYTE *rgb = malloc(3 * sizeof(BYTE));
            rgb[0] = *red;
            rgb[1] = *green;
            rgb[2] = *blue;
            BYTE *oppoRed = &image[i][width - 1 - j].rgbtRed;
            BYTE *oppoGreen = &image[i][width - 1 - j].rgbtGreen;
            BYTE *oppoBlue = &image[i][width - 1 - j].rgbtBlue;
            *red = *oppoRed;
            *green = *oppoGreen;
            *blue = *oppoBlue;
            *oppoRed = rgb[0];
            *oppoGreen = rgb[1];
            *oppoBlue = rgb[2];
            free(rgb);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a variable that will store the new rgb values of the pixels
    RGBTRIPLE new_image[height][width];

    // Go through all the pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE *red = &new_image[i][j].rgbtRed;
            BYTE *green = &new_image[i][j].rgbtGreen;
            BYTE *blue = &new_image[i][j].rgbtBlue;
            int count = 0;
            float averageRed = 0, averageGreen = 0, averageBlue = 0;

            // For every pixel check the pixels around it
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int a = i + x;
                    int b = j + y;

                    // Checks if the pixel is in a row or collum that is inside the image
                    if (!(a < 0 || a > height - 1 || b < 0 || b > width - 1))
                    {
                        averageRed += image[a][b].rgbtRed;
                        averageGreen += image[a][b].rgbtGreen;
                        averageBlue += image[a][b].rgbtBlue;
                        count++;
                    }
                }
            }
            // Rounds to the nearest integer
            *red = round(averageRed / count);
            *green = round(averageGreen / count);
            *blue = round(averageBlue / count);
        }
    }
    // Copies the new rgb values to the original image
    memcpy(image, new_image, sizeof(new_image));
    return;
}

