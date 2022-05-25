#include "helpers.h"

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Initializing variables
    float buffer[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculating sepia
            buffer[0] = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue + 0.5;
            buffer[1] = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue + 0.5;
            buffer[2] = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue + 0.5;
            
            for (int c = 0; c < 3; c++)
            {
                buffer[c] = buffer[c] > 255 ? 255 : buffer[c];
            }
            // Aplly changes
            image[i][j].rgbtBlue = buffer[0];
            image[i][j].rgbtGreen = buffer[1];
            image[i][j].rgbtRed = buffer[2];
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
    // Ugliest code :P
    // Initializing variables
    RGBTRIPLE blured[height][width];
    float buffer[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                // Top-Left corner
                if (j == 0)
                {
                    buffer[0] = ((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4.0) +
                                0.5;
                    buffer[1] = ((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4.0)
                                + 0.5;
                    buffer[2] = ((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.0) +
                                0.5;
                }
                // Top-Right corner
                else if (j == width - 1)
                {
                    buffer[0] = ((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4.0) +
                                0.5;
                    buffer[1] = ((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4.0)
                                + 0.5;
                    buffer[2] = ((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4.0) +
                                0.5;
                }
                // Top edge
                else
                {
                    buffer[0] = ((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + 
                                  image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 6.0) + 0.5;
                    buffer[1] = ((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                  image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen) / 6.0) + 0.5;
                    buffer[2] = ((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                  image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed) / 6.0) + 0.5;
                }
            }
            else if (i == height - 1)
            {
                // Bottom-Left corner
                if (j == 0)
                {
                    buffer[0] = ((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4.0) +
                                0.5;
                    buffer[1] = ((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4.0)
                                + 0.5;
                    buffer[2] = ((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4.0) +
                                0.5;
                }
                // Bottom-Right Corner
                else if (j == width - 1)
                {
                    buffer[0] = ((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4.0) +
                                0.5;
                    buffer[1] = ((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4.0)
                                + 0.5;
                    buffer[2] = ((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0) +
                                0.5;
                }
                // Bottom edge
                else
                {
                    buffer[0] = ((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + 
                                  image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 6.0) + 0.5;
                    buffer[1] = ((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + 
                                  image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen) / 6.0) + 0.5;
                    buffer[2] = ((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + 
                                  image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed) / 6.0) + 0.5;
                }
            }
            // Left edge
            else if (j == 0)
            {
                buffer[0] = ((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + 
                              image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue) / 6.0) + 0.5;
                buffer[1] = ((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                              image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen) / 6.0) + 0.5;
                buffer[2] = ((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + 
                              image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed) / 6.0) + 0.5;
            }
            // Right edge
            else if (j == width - 1)
            {   
                buffer[0] = ((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + 
                              image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue) / 6.0) + 0.5;
                buffer[1] = ((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + 
                              image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen) / 6.0) + 0.5;
                buffer[2] = ((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + 
                              image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed) / 6.0) + 0.5;
            }
            // Middle pixel
            else
            {
                buffer[0] = 0;
                buffer[1] = 0;
                buffer[2] = 0;
                for (int c = -1; c < 2; c++)
                {
                    for (int k = -1; k < 2; k++)
                    {
                        buffer[0] += image[i + c][j + k].rgbtBlue;
                        buffer[1] += image[i + c][j + k].rgbtGreen;
                        buffer[2] += image[i + c][j + k].rgbtRed;
                    }
                }
                buffer[0] = (buffer[0] / 9.0) + 0.5;
                buffer[1] = (buffer[1] / 9.0) + 0.5;
                buffer[2] = (buffer[2] / 9.0) + 0.5;
            }
            // Temp Store
            blured[i][j].rgbtBlue = buffer[0];
            blured[i][j].rgbtGreen = buffer[1];
            blured[i][j].rgbtRed = buffer[2];
        }
    }
    // Apply changes
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blured[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blured[i][j].rgbtGreen;
            image[i][j].rgbtRed = blured[i][j].rgbtRed;
        }
    }
}
