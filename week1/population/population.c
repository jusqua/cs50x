#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Initializing variables
    int startSize = 0;
    int endSize = 0;
    int years = 0;
    // Prompt for start size
    while (startSize < 9)
    {
        startSize = get_int("Start size: ");
    }
    // Prompt for end size
    while (endSize < startSize)
    {
        endSize = get_int("End size: ");
    }
    // Calculate number of years until we reach threshold
    for (; startSize < endSize; years++)
    {
        startSize += (startSize / 3) - (startSize / 4);
    }
    // Print number of years
    printf("Years: %d \n", years);
}
