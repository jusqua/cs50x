#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Initializing variables
    float buffer;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculating grayscale
            buffer = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0) + 0.5;
            // Apply changes
            image[i][j].rgbtBlue = buffer;
            image[i][j].rgbtGreen = buffer;
            image[i][j].rgbtRed = buffer;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Initializing variables
    RGBTRIPLE aux;
    // Switching places
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            aux = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = aux;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Initializing variables
    RGBTRIPLE temp[height][width];
    for (int c, k, j, i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            float buffer[3] = {0, 0, 0}, p;
            for (c = -1, p = 0; c < 2; c++)
            {
                for (k = -1; k < 2; k++)
                {
                    if ((i + c) != -1 && (i + c) != height && (j + k) != -1 && (j + k) != width)
                    {
                        buffer[0] += image[i + c][j + k].rgbtBlue;
                        buffer[1] += image[i + c][j + k].rgbtGreen;
                        buffer[2] += image[i + c][j + k].rgbtRed;
                        p++;
                    }
                }
            }
            // Temp Store
            temp[i][j].rgbtBlue = (buffer[0] / p) + 0.5;
            temp[i][j].rgbtGreen = (buffer[1] / p) + 0.5;
            temp[i][j].rgbtRed = (buffer[2] / p) + 0.5;
        }
    }
    // Apply changes
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Initializing variables
    RGBTRIPLE temp[height][width];
    const float gx[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
    const float gy[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
    for (int corner, c, k, j, i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            float bgx[3] = {0, 0, 0}, bgy[3] = {0, 0, 0}, buffer[3];
            for (corner = 0, c = -1; c < 2; c++)
            {
                for (k = -1; k < 2; k++)
                {
                    if ((i + c) != -1 && (i + c) != height && (j + k) != -1 && (j + k) != width)
                    {
                        bgx[0] += image[i + c][j + k].rgbtBlue  * gx[c + 1][k + 1];
                        bgx[1] += image[i + c][j + k].rgbtGreen * gx[c + 1][k + 1];
                        bgx[2] += image[i + c][j + k].rgbtRed   * gx[c + 1][k + 1];
                        bgy[0] += image[i + c][j + k].rgbtBlue  * gy[c + 1][k + 1];
                        bgy[1] += image[i + c][j + k].rgbtGreen * gy[c + 1][k + 1];
                        bgy[2] += image[i + c][j + k].rgbtRed   * gy[c + 1][k + 1];
                    }
                }
            }
            // Temp Store
            buffer[0] = sqrt(pow(bgx[0], 2) + pow(bgy[0], 2)) + 0.5;
            buffer[1] = sqrt(pow(bgx[1], 2) + pow(bgy[1], 2)) + 0.5;
            buffer[2] = sqrt(pow(bgx[2], 2) + pow(bgy[2], 2)) + 0.5;
            temp[i][j].rgbtBlue = buffer[0] > 255 ? 255 : buffer[0];
            temp[i][j].rgbtGreen = buffer[1] > 255 ? 255 : buffer[1];
            temp[i][j].rgbtRed = buffer[2] > 255 ? 255 : buffer[2];
        }
    }
    // Apply changes
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
}
