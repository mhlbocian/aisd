#ifndef INCLUDES_H
#define INCLUDES_H

void print_array(int tab[], int size);
void swap_element(int tab[], int indexA, int indexB);

void heapify(int heap[], int index, int size);
void build_heap(int heap[], int size);
void heap_sort(int heap[], int size);

void insertion_sort(int array[], int size);

void merge(int tab[], int first, int middle, int last);
void merge_sort(int tab[], int first, int last);

void selection_sort(int tab[], int size);

int partition(int tab[], int p, int r);
void quick_sort(int tab[], int p, int r);
void quick_sort_it(int tab[], int p, int r);
#endif
