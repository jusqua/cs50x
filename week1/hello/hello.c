#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // prints into screen "Hello, name!"
    string name = get_string("What is your name?\n");
    printf("Hello, %s!\n", name);
    return 0;
}
