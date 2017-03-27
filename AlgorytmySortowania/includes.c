/**
 * POLITECHNIKA POZNANSKA - WYDZIAL INFORMATYKI - INFORMATYKA I
 * ALGORYTMY I STRUKTURY DANYCH
 * 
 * Algorytmy sortowania - mierzenie czasow wykonywania
 * 
 * Autorzy: Michal Bocian, Ewa Fengler
 * Rok akademicki: 2016/2017
 */
#include "includes.h"
#include <stdio.h>
#include <stdlib.h>

void print_array(int tab[], int size)
{
    int i = 0;
    for(; i < size; ++i)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void swap_element(int tab[], int indexA, int indexB)
{
    int tmp = tab[indexA];
    tab[indexA] = tab[indexB];
    tab[indexB] = tmp;
}

void gena(int* tab, int size)
{
    int i = 0, val = 0;  
    for(; i < size; ++i)
    {
        if(i > size / 2) tab[i] = --val;
        else tab[i] = ++val;
    }
}

void genc(int* tab, int size)
{
    int i = 0;
    for(; i < size; ++i) tab[i] = 1;
}

void gend(int* tab, int size)
{
    int i = 0;
    for(; i < size; ++i) tab[i] = size - i;
}

void geni(int* tab, int size)
{
    int i = 0;
    for(; i < size; ++i) tab[i] = i + 1;
}

void genr(int* tab, int size)
{
    int i = 0;
    for(; i < size; ++i) tab[i] = rand() % 10000;
}

void genv(int* tab, int size)
{
    int i = 0, val = size + 1;
    for(; i < size; ++i)
    {
        if(i > size / 2) tab[i] = ++val;
        else tab[i] = --val;
    }
}

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

void build_heap(int heap[], int size)
{
    int i = size / 2;
    while (i > 0) heapify(heap, --i, size);
}

void heap_sort(int heap[], int size)
{
    int i = size - 1;
    build_heap(heap, size);
    for(; i > 0; --i)
    {
        swap_element(heap, 0, i);
        build_heap(heap, i);
    }
}

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

void merge(int tab[], int first, int middle, int last)
{
    int pom[last - first];
    int i = first, j = middle + 1, k = 0;
    while(i <= middle && j <= last)
    {
        if(tab[j] < tab[i])
        {
            pom[k] = tab[j];
            ++j;
        }
        else
        {
            pom[k] = tab[i];
            ++i;
        }
        ++k;
    }
    if(i <= middle)
    {
        while(i <= middle)
        {
            pom[k] = tab[i];
            ++i;
            ++k;
        }
    }
    else
    {
        while(j <= last)
        {
            pom[k] = tab[j];
            ++j;
            ++k;
        }
    }
    for (i = 0; i <= last - first; ++i)
        tab[first + i] = pom[i];
}

void merge_sort(int tab[], int first, int last)
{
    int middle;
    if(first == last) return;
    middle = (first + last) / 2;
    merge_sort(tab, first, middle);
    merge_sort(tab, middle + 1, last);
    merge(tab, first, middle, last);
}

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

int partition(int tab[], int p, int r)
{
    int pv = tab[p];
    int i = p - 1;
    int j = r + 1;
    for(;;)
    {
        do{++i;} while(tab[i] < pv);
        do{--j;} while(tab[j] > pv);
        if(i >= j) return j;
        swap_element(tab, i, j);
    }
}

void quick_sort(int tab[], int p, int r)
{
    int q;
    if(p < r)
    {
        q = partition(tab, p, r);
        quick_sort(tab, p, q);
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
        if(h - l < 2) continue;
        int p = partition(arr, l, h);
        stack[++top] = p+1;
        stack[++top] = h;
        stack[++top] = l;
        stack[++top] = p;
    }
}
