#include "includes.h"
#include <stdio.h>
#include <stdlib.h>

void genV(int** tab, int size)
{
    int i = 0, val = size + 1;
    *tab = (int*)malloc(size * sizeof(int));

    for(; i < size; ++i)
    {
	if(i > size / 2) (*tab)[i] = ++val;
	else (*tab)[i] = --val;
    }
}

int main (int argc, const char** argv)
{
    int* tab;
    int size = 31;
    genV(&tab, size);
    print_array(tab, size);
    quick_sort_it(tab, 0, size - 1);
    print_array(tab, size);
    return 0;
}
