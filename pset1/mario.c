#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    
    do
    {
        printf("Type an int from 0 to 23: ");
        n = GetInt();
    }
    while (n < 0 || n > 23);
    // if not working, refactor to two step "int j, i" declaration
    for (int j = 1; j <= n; j++)
    {
        // spaces
        for (int i = 0; i < n - j; i++)
        {
            printf(" ");
        }
        // hashes
        for (int i = 0; i < j; i++)
        {
        
            printf("#");
        }
        //new line
        printf("#\n");
    }
}