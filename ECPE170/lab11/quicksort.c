// Demonstration program for Quick Sort of an array of 100 integers
// using recursion
//
// Compile this program:
//  unix>  make
// Run this program:
//  unix>  ./quick

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "quicksort.h"

// Global values for random number generator.
// Initialize the random number generator with fixed values
// for demonstration purposes.
uint32_t m_w = 50000;
uint32_t m_z = 60000;

int main()
{
  uint32_t b, a[100];

  for(int i=0; i<100; i++)
    {
      b = random_in_range(1,100000);
      a[i]=b;

    }

  quickSort(a,0,99);
  printf("\n Sorted array is:\n");
  for (int i=0;i<100;i++)
	printf("a[%d]=%d \n",i,a[i]);

  return 0;
}


//recursive quicksort
//source:http://www.comp.dit.ie/rlawlor/Alg_DS/sorting/quickSort.c
void quickSort( uint32_t a[], int l, int r)
{
   int j;

   if( l < r ) 
   {
   	// divide and conquer
        j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
	
}



int partition(uint32_t a[], int l, int r) {
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;
		
   while( 1)
   {
   	do ++i; while( a[i] <= pivot && i <= r );
   	do --j; while( a[j] > pivot );
   	if( i >= j ) break;
   	t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}


// Generate random number in range [low, high]
// (i.e. including low and high)
uint32_t random_in_range(uint32_t low, uint32_t high)
{
  uint32_t range = high-low+1;
  uint32_t rand_num = get_random();

  return (rand_num % range) + low;
}


// Generate random 32-bit unsigned number
// based on multiply-with-carry method shown
// at http://en.wikipedia.org/wiki/Random_number_generation
uint32_t get_random()
{
  uint32_t result;
  m_z = 36969 * (m_z & 65535) + (m_z >> 16);
  m_w = 18000 * (m_w & 65535) + (m_w >> 16);
  result = (m_z << 16) + m_w;  /* 32-bit result */
  return result;
}
