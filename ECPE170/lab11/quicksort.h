#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <stdint.h>
void quickSort(uint32_t a[],int l, int r);
int partition(uint32_t a[],int l, int r);
uint32_t random_in_range(uint32_t, uint32_t);
uint32_t get_random(void);

#endif // QUICKSORT_H

