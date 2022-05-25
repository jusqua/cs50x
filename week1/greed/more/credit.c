#include <cs50.h>
#include <stdio.h>
#include <math.h>

int sumCheck(long num);
void cardCheck(int sum, long num);

int main(void)
{
    // Prompt for card number
    long num = get_long("Number: ");
    // Generating sum
    int sum = sumCheck(num);
    // Checking card
    cardCheck(sum, num);
}

int sumCheck(long num)
{
    // Initializing variables
    int c;
    int product, sum = 0;
    long digit = 100;
    // Luhn’s Algorithm at work
    for (c = 0; c < 8; c++)
    {
        product = ((num % digit) / (digit / 10)) * 2;
        sum += (product / 10) + (product % 10);
        digit *= 100;
    }
    digit = 10;
    for (c = 0; c < 8; c++)
    {
        sum += (num % digit) / (digit / 10);
        digit *= 100;
    }
    return sum;
}

void cardCheck(int sum, long num)
{
    // Checking sum value
    if (!(sum % 10))
    {
        // Initializing variables
        int length = (int) round(log10(num)) % 100;
        long digit = pow(10, length);
        int index = (num % digit) / (digit / 100);
        // Get card
        if (length == 16)
        {
            if (index == 51 || index == 52 || index == 53 || index == 54 || index == 55)
            {
                printf("MASTERCARD\n");
            }
            else if (index / 10 == 4)
            {
                printf("VISA\n");
            }
            else 
            {
                printf("INVALID\n");
            }
        }
        else if (length == 15 && (index == 34 || index == 37))
        {
            printf("AMEX\n");
        }
        else if (length == 13 && (index / 10 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
