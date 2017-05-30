#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, string argv[])
{   // captures argv[1] to key variable
    string key = argv[1];
    if(key != NULL)
    {
        // convert the key  to int and to value between 1 and 26
        int k = atoi(key) % 26;
        if (k == 0)
        {
            printf("give me the non zero key");
            return 1;
        }
        // get string from user and checks whether it is not empty
        string p = GetString();
        if (p != NULL)
        {
            // looping through plaintext
            for (int i = 0, n = strlen(p); i < n; i++)
            {
                // encrypting with given key
                if (isalpha(p[i]))
                {
                    if (islower(p[i]))
                    printf("%c", ((p[i] - 97 + k ) % 26 ) + 97);
                    else if (isupper(p[i]))
                    printf("%c", ((p[i] - 65 + k ) % 26 ) + 65);
                }
                // print spaces, commas etc
                else
                {
                    printf("%c", p[i]);
                }
            }
        }
        printf("\n");
        return 0;
    }
    // if cmd-line arg is empty
    else
    {
        printf("PLease give me the numeric key as an argument");
        return 1;
    }
}