#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Initializing variables
    int changeOwed = -1;
    int coin[] = {25, 10, 5, 1};
    int remaning, amount = 0;
    // Prompt for Change owed
    while (changeOwed < 0)
    {
        changeOwed = round(100 * get_float("Change owed: "));
    }
    // Generating Change
    for (int i = 0; i < 4; i++)
    {
        amount += changeOwed / coin[i];
        remaning = changeOwed / coin[i];
        changeOwed -= coin[i] * remaning;
    }
    // Print amount
    printf("%d\n", amount);
}
