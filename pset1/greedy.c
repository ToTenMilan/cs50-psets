#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)  
{
    float owedChange;
    int quarters, dimes, nickels, cents, sum;
    
    // Get from user, non negative
    do
    {
        printf("How much change is owed?\n");
        owedChange = GetFloat();
    }
    while (owedChange < 0);

    // converting
    cents = (int) round(owedChange * 100);
    
    // 
    quarters = cents / 25;
    cents -= quarters * 25;
    
    dimes = cents / 10;
    cents -= dimes * 10;
    
    nickels = cents / 5;
    cents -= nickels * 5;
    
    sum = quarters + dimes + nickels + cents;
    
    printf("%i\n", sum);
}