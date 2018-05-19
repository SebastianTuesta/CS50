/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

bool search(int value, int values[], int n)
{
    //BINARY SEARCH
    int inf = 0;
    int sup = n-1;
    
    if (n<=0) return false;
    else
    {
        while(inf<=sup)
        {
            int center = ((sup - inf) / 2) + inf;
            if(values[center]==value) return true;
            else if(value<values[center])
            {
                sup=center-1;
            }
            else
                inf=center+1;
        }
        return false;
    }
}

void sort(int values[], int n)
{
    // SELECTION SORT
   int aux;
   int min;
   
   for (int i=0; i<n; i++)
   {
     min=i;
     for (int j=i+1; j<n; j++)
     {
        if(values[j]<values[min])
            min=j;
     }
     aux = values[i];
     values[i] = values[min];
     values[min] = aux;
    }    
}
