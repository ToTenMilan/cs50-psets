#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("How long do you take shower?\n");
    int x = GetInt();
    int y = 12;
    
    printf("Washing for %d minutes, you are spending %d bottles of water\n", x, x * y);
}