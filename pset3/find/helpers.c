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
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    
    int beg = 0;
    int mid = 0;
    int end = 0;
    
    if (value > values[n-1] || value < values[0])
    {
        return false;
    }
    
    beg = 0;
    end = n - 1;
    
    while (beg <= end)
    {
        mid = (beg + end) / 2;
        if (value == values[mid])
        {
            return true;
        }
        
        else if (value > values[mid])
        {
            beg = mid + 1;
        }
        
        else
        {
            end = mid - 1;
        }
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    
    int i = 0;
    int j = 0;
    int temp = 0;
    
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (values[i] > values [j])
            {
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
    return;
}
