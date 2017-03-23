#include "includes.h"
#include <stdio.h>
#include <stdlib.h>

/* wyswietla nam zawartosc tablicy o rozmiarze size */
void print_array(int tab[], int size)
{
    int i = 0;
    for(; i < size; ++i)
    {
	printf("%d ", tab[i]);
    }
    printf("\n");
}

/* zamienia elementy tablicy ze soba */
void swap_element(int tab[], int indexA, int indexB)
{
    int tmp = tab[indexA];
    tab[indexA] = tab[indexB];
    tab[indexB] = tmp;
}

/* HEAP SORT */

/* ustawia liscie we wlasciwej kolejnosci */
void heapify(int heap[], int index, int size)
{
    int largest = index;
    if (index * 2 < size && heap[index * 2] > heap[largest])
    {
	largest = index * 2;
    }
    if (index * 2 + 1 < size && heap[index * 2 + 1] > heap[largest])
    {
	largest = index * 2 + 1;
    }
    if (largest != index)
    {
	swap_element(heap, index, largest);
	heapify(heap, largest, size);
    }
}

/* buduje nam kopiec */
void build_heap(int heap[], int size)
{
    int i = size / 2;
    while (i > 0) heapify(heap, --i, size);
}

/* sortowanie z uzyciem kopca */
void heap_sort(int heap[], int size)
{
    int i = size - 1;
    /* tworzy z tablicy kopiec, gdyby tablica nim nie byla */
    build_heap(heap, size);
    for(; i > 0; --i)
    {
	swap_element(heap, 0, i);
	build_heap(heap, i);
    }
}

/* INSERTION SORT */
void insertion_sort(int array[], int size)
{
    int i, j=1, key;

    for(; j < size; ++j)
    {
	key = array[j];
	i = j - 1;
	while(i >= 0 && array[i] > key)
	{
	    array[i + 1] = array[i];
	    --i;
	}
	array[i + 1] = key;
    }
}

/* MERGE SORT */
void merge(int tab[], int first, int middle, int last)
{
    // uszkodzony algo
}

void merge_sort(int tab[], int first, int last)
{
    int middle = (first + last) / 2;
    if(first == last) return;
    merge_sort(tab, first, middle);
    merge_sort(tab, middle + 1, last);
    merge(tab, first, middle, last);
}

/* SELECTION SORT */
void selection_sort(int tab[], int size)
{
    int i, j = size - 1, max, pom;
    for(; j >= 1; --j)
    {
	max = j;
	i = j - 1;
	for(; i >= 0; --i)
	{
	    if(tab[i] > tab[max]) max = i;
	}
	pom = tab[j];
	tab[j] = tab[max];
	tab[max] = pom;
    }
}

/* QUICKSORT */
int partition(int tab[], int p, int r)
{
    int i = p - 1, j, x = tab[r];

    for(j = p; j < r; ++j)
    {
	if(tab[j] <= x)
	{
	    ++i;
	    swap_element(tab, i, j);
	}
    }

    tab[r] = tab[i + 1];
    tab[i + 1] = x;

    return i + 1;
}

void quick_sort(int tab[], int p, int r)
{
    int q;
    if(p < r)
    {
	q = partition(tab, p, r);
	quick_sort(tab, p, q - 1);
	quick_sort(tab, q + 1, r);
    }
}

void quick_sort_it(int arr[], int l, int h)
{
    int stack[ h - l + 1 ];
    int top = -1;

    stack[++top] = l;
    stack[++top] = h;

    while(top >= 0)
    {
        h = stack[top--];
        l = stack[top--];

        int p = partition( arr, l, h );

        if (p - 1 > l)
        {
            stack[ ++top ] = l;
            stack[ ++top ] = p - 1;
        }

        if (p + 1 < h)
        {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}
