#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, string argv[])
{   
    // Assign argv[1] to key variable
    // checks if there is a one cmd-line argument
    string key = (argv[1]);
    if (argc > 2 || key == NULL) {
        printf("type just one key with only alphabetical characters\n");
        return 1;
    }
    // Checks whether key is all alpha
    else
    {
        for (int i = 0, l = strlen(key); i < l; i++)
        {
            if (!isalpha(key[i]))
            {
                printf("type key with only alphabetical characters\n");
                return 1;
            }
        }
    }
    string p = GetString();
    int keyLength = strlen(key);
    int keyCtr = 0;
    if (p != NULL)
    {
        // looping through plaintext
        for (int i = 0, n = strlen(p); i < n; i++)
        {
            // looping through key
            while ( keyCtr >= keyLength )
            {
                keyCtr %= keyLength;
            }
            // enscrypting the plaintext with key
            if isalpha(p[i])
            {
                if (islower(p[i]))
                printf("%c", ((p[i] - 97 + (tolower(key[keyCtr++]) - 97)) % 26 ) + 97);
                else if (isupper(p[i]))
                printf("%c", ((p[i] - 65 + (toupper(key[keyCtr++]) - 65)) % 26 ) + 65);
            }
            // putting space, commas etc.
            else
            {
                printf("%c", p[i]);
            }
        }
        
    }
    printf("\n");
    return 0;
}

