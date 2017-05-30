#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// function declaration
void cap(char string[]);

int main(void)
{
    int i, n;
    
    // prompt user for his name
    string name = GetString();
    cap(name);
    printf("%c", name[0]);
    for(i = 0, n = strlen(name); i < n; i++)
    {
        if (isspace(name[i]))
        printf("%c", toupper(name[i+1]));
    }
    printf("\n");
}

// modified function declaration code snippet from:
// http://stackoverflow.com/questions/20036553/c-function-to-capitalize-first-letter-of-words-in-an-array
void cap(char string[])
{     
    int i;
    int x = strlen(string);
    for (i=0;i<x;i++){
         if (isalpha(string[0]))
         {
             string[0]= toupper(string[0]);
         }
    }
}