/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"
/**
 * Returns true if value is in array of n values, else false.
 * Binary Search 
 * Big O(log n)
 */
 
bool search(int value, int values[], int n)
{
    if(n < 0)
    {
        return false;
    }
    
    int min = 0 ;
    int max = n - 1 ;
    
    
    while( max >= min )
    {
        int mid = ( min + max ) / 2 ;
        if(values[mid] == value)
        {
            return true;
        }
        else if( value > values[mid] ) 
        {
            min = mid + 1 ;
        }
        else
        {
            max = mid - 1 ;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 * selecton sort
 * Big O(n^2)
 */
 void sort(int values[], int n)
{
     for (int i = 0 ; i < n  ; i++)
     {
         int min = i ;
         for(int j = i + 1 ; j < n ; j++)
         {
             if(values[min] > values[j])
             {
                 min = j;
             }
         }
         int temp = values[i];
         values[i] = values[min];
         values[min] = temp;
     }
     return;
 }
