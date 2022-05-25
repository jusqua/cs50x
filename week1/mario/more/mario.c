#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Initializing variables
    int c, k;
    int height = 0;
    // Prompt for height
    while (height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }
    // Block managemant
    for (c = 0; c < height; c++)
    {
        int spaces = height - c - 1;
        // Generate spaces
        for (k = spaces; k > 0; k--)
        {
            printf(" ");
        }
        // Generate first blocks
        for (k = spaces; k < height; k++)
        {
            printf("#");
        }
        // Put hole
        printf("  ");
        // Generate last blocks
        for (k = spaces; k < height; k++)
        {
            printf("#");
        }
        // New line
        puts("");
    }
}
