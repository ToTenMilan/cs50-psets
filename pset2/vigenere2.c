#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
// int main(int argc, string argv[])
// {
//     if(argc!=2)
//     {
//         printf("Error!");
//         return 1;
//     }
//     else
//     {
//         string k,p;
//         k=argv[1];
//         p=GetString();
//         char c[20];
//         int y=strlen(k);
//         int z=strlen(p);
//         for(int j=0;j<z;j++)
//         {
//             for(int i=0;i<y;i++)
//             {
//                 if(isalpha(p[j]))
//                 {
//                     if(islower(p[j]))
//                     c[j]=((p[i]-97)+(k[j%y]-97))%26+97;
//                     else if(isupper(p[j]))
//                     c[j]=((p[i]-65)+(k[j%y]-65))%26+65;
//                 }
//                 else if(isdigit(p[j]) || isspace(p[j]) || ispunct(p[j]))
//                 c[j]=p[j];
//             }
//             printf("%c",c[j]);
//         }
//         printf("\n");
//     }
// }


int main(int argc, string argv[])
{
    if ( argc != 2 ) // makes sure there are two command line arguments
    {
        printf("Please enter a keyword\n");
        return 1; 
    }
    for ( int i = 0, n = strlen(argv[1]); i < n; i++ ) // check to make sure keyword is alpha only
    {
        if ( !isalpha(argv[1][i]) )
        {
            printf("Your keyword may only contain alpha symbols\n");
            return 1;
        }
    }
    string plain_text = GetString();
    string key = argv[1];
    int length = strlen(key);
    int j = 0;
    for ( int i = 0, n = strlen(plain_text); i < n; i++ )
    {
        while ( j >= length )
        {
            j %= length; 
        }
        if ( isalpha(plain_text[i]) && isalpha(key[j]) )
        { 
            if ( islower(plain_text[i]) && islower(key[j]) )
            {
                int cipher = ((((plain_text[i] - 'a') + (key[j++] - 'a')) % 26));
                plain_text[i] = cipher + 'a';
                printf("%c", plain_text[i]);
            }
            if ( isupper(plain_text[i]) && isupper(key[j]) )
            {
                int cipher = ((((plain_text[i] - 'A') + (key[j++] - 'A')) % 26));
                plain_text[i] = cipher + 'A';
                printf("%c", plain_text[i]);
            }
        }
        else
        {
            printf("%c", plain_text[i]);
        }
    }
    printf("\n");
    return 0;
}