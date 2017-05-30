/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
#include <cs50.h>
#include "helpers.h"
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int size)
{
    // int length = size;
    int min = 0, max = size - 1;
    int mid = (min + max)/2;
    while (min <= max)
    {
        
        if (values[mid] == value)
        {
            return true;
        }
        else if (values[mid] < value )
        {
            min = mid + 1;
            
        }
        else if (values[mid] > value )
        {
            max = mid - 1;
        }
        mid = (min + max) / 2;
    }
    return false;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int i, j, temp;
    int swapCtr = -1;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (swapCtr != 0)
            swapCtr = 0;
            if (values[i] < values[j])
            {
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
                swapCtr++;
            }
        }
    }
    return;
}

// bool search(int value, int values[], int size)
    // {
    //     int min = 0, max = size - 1;
    //     return binarySearch(value, values, min, max);
    // }
    
    // if (max < min)
    // return -1;
    // else
    // {
    //     int mid = min + ((max - min) / 2);
    //     if (values[mid] < value)
    //     binarySearch(value, values, mid + 1, max);
    //     else if (values[mid] > value)
    //     binarySearch(value, values, min, mid - 1);
    //     else
    //     return values[mid];
    // }
    // return false;

// int i;
    // for (i = 0; i < n; i++)
    // {
    //     if (values[i] == value)
    //     {
    //         return true;
    //     }
    // }
    // return false;