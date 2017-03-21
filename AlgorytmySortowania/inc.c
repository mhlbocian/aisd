#include "inc.h"
#include <stdio.h>
#include <stdlib.h>

/* wyswietla nam zawartosc tablicy o rozmiarze size */
void print_array(int tab[], int size)
{
    int i = 0;
    for(; i < size; i++)
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
