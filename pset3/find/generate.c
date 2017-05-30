/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // checks whether there are exactly two or three arguments (including name of the file)
    // if there aren't the message is printed, error is returned and program ends
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // converting a char from argv[1] to int and assigning it to n variable
    int n = atoi(argv[1]);

    // checks whether there are 3 cmd-line arguments
    // if so, srand48 (called before drand) is seeding drand48 out of number given as third argument
    // if not(if two args) srand48 is seeding drand48 out of actual time given in seconds
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // for loop is printing n times (int) drand48 multiplied by defined above constant
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}