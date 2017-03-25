/**
 * POLITECHNIKA POZNANSKA - WYDZIAL INFORMATYKI - INFORMATYKA I
 * ALGORYTMY I STRUKTURY DANYCH
 * 
 * Algorytmy sortowania - mierzenie czasow wykonywania
 * 
 * Autorzy: Michal Bocian, Ewa Fengler
 * Rok akademicki: 2016/2017
 */
#ifndef INCLUDES_H
#define INCLUDES_H

/* funkcje tablic */
void print_array(int tab[], int size);
void swap_element(int tab[], int indexA, int indexB);
/* generatory */
typedef struct {
    char name[20];
    void (*gen)(int*,int);
} gen_t;
void gena(int* tab, int size); /* a-ksztaltny */
void gend(int* tab, int size); /* malejacy */
void geni(int* tab, int size); /* rosnacy */
void genr(int* tab, int size); /* pseudolosowy */
void genv(int* tab, int size); /* v-ksztaltny */
/* sortowanie przez kopcowanie */
void heapify(int heap[], int index, int size);
void build_heap(int heap[], int size);
void heap_sort(int heap[], int size);
/* sortowanie przez wstawianie */
void insertion_sort(int array[], int size);
/* sortowanie prez scalanie */
void merge(int tab[], int first, int middle, int last);
void merge_sort(int tab[], int first, int last);
/* sortowanie przez wybór */
void selection_sort(int tab[], int size);
/* sortowanie przez podział */
int partition(int tab[], int p, int r);
void quick_sort(int tab[], int p, int r);
void quick_sort_it(int tab[], int p, int r);
#endif
