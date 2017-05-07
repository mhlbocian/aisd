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
#include <string.h>
#include <time.h>

#define OUT_FILE1 "wyniki1.csv"
#define OUT_FILE1_HEADER "Proba;ISort;SSort;HSort;MSort\n"

#define OUT_FILE2 "wyniki2.csv"
#define OUT_FILE2_HEADER "Proba;Q-Rec;Q-Iter\n"

#define OUT_FILE3 "wyniki3.csv"
#define OUT_FILE3_HEADER "Proba;Prawy;Srodek;Losowy\n"

#define T 1000 /* dzielnik mierzonego czasu */
#define progress() printf("%ld ", mtime / T)

int main (int argc, const char** argv)
{
    srand(time(NULL));
    setbuf(stdout, NULL);

    int *tab, *wrk;
    int i, n, start, stop, inc, genid;
    clock_t mtime;
    FILE *file;
    gen_t gen[6] = {
	{"v-ksztaltny", genv},
	{"a-ksztaltny", gena},
	{"pseudolosowy", genr},
	{"rosnacy", geni},
	{"malejacy", gend},
	{"staly", genc}
    };
    goto test2;
test1:
    printf("Poczatek pomiaru: ");
    scanf("%d", &start);
    printf("Koniec pomiaru: ");
    scanf("%d", &stop);
    printf("Ilosc pomiarow: ");
    scanf("%d", &n);
    inc = (stop - start) / n;

    file = fopen(OUT_FILE1, "w");
    for(genid = 0; genid < 6; ++genid){
	printf("%s\n", gen[genid].name);
	fprintf(file, "%s\n", gen[genid].name);
	fprintf(file, OUT_FILE1_HEADER);
	for(i = 0; i < n + 1; ++i)
	{
	    stop = start + i * inc; /* stop - rozmiar tablicy */
	    printf("%d ", stop);
	    fprintf(file, "%d;", stop);

	    tab = (int*)malloc(stop * sizeof(int));
	    wrk = (int*)malloc(stop * sizeof(int));
	    gen[genid].gen(tab, stop);

	    /* pomiar: insertion sort */
	    memcpy(wrk, tab, stop * sizeof(int));
	    mtime = clock();
	    insertion_sort(wrk, stop);
	    mtime = clock() - mtime;
	    fprintf(file, "%ld;", mtime / T);
	    progress();

	    /* pomiar: selection sort */
	    memcpy(wrk, tab, stop * sizeof(int));
	    mtime = clock();
	    selection_sort(wrk, stop);
	    mtime = clock() - mtime;
	    fprintf(file, "%ld;", mtime / T);
	    progress();

	    /* pomiar: heapsort */
	    memcpy(wrk, tab, stop * sizeof(int));
	    mtime = clock();
	    heap_sort(wrk, stop);
	    mtime = clock() - mtime;
	    fprintf(file, "%ld;", mtime / T);
	    progress();

	    /* pomiar: merge sort */
	    memcpy(wrk, tab, stop * sizeof(int));
	    mtime = clock();
	    merge_sort(tab, 0, stop - 1);
	    mtime = clock() - mtime;
	    fprintf(file, "%ld", mtime / T);
	    progress();

	    fprintf(file, "\n");
	    fflush(file);
	    printf("\n");
	    free(wrk);
	    free(tab);
	}
    }
    fclose(file);

test2:
    printf("Poczatek pomiaru: ");
    scanf("%d", &start);
    printf("Koniec pomiaru: ");
    scanf("%d", &stop);
    printf("Ilosc pomiarow: ");
    scanf("%d", &n);
    inc = (stop - start) / n;

    file = fopen(OUT_FILE2, "w");
    printf("\nTesty Quicksort\n%s\n", gen[2].name);
    fprintf(file, "%s\n", gen[2].name);
    fprintf(file, OUT_FILE2_HEADER);
    for(i = 0; i < n + 1; ++i)
    {
	stop = start + i * inc; /* stop - rozmiar tablicy */
	printf("%d ", stop);
	fprintf(file, "%d;", stop);

	tab = (int*)malloc(stop * sizeof(int));
	wrk = (int*)malloc(stop * sizeof(int));
	gen[2].gen(tab, stop);

	memcpy(wrk, tab, stop * sizeof(int));
	mtime = clock();
	quick_sort(wrk, 0, stop - 1, partition);
	mtime = clock() - mtime;
	fprintf(file, "%ld;", mtime / T);
	progress();

	memcpy(wrk, tab, stop * sizeof(int));
	mtime = clock();
	quick_sort_it(wrk, 0, stop - 1);
	mtime = clock() - mtime;
	fprintf(file, "%ld", mtime / T);
	progress();

	fprintf(file, "\n");
	fflush(file);
	printf("\n");
	free(wrk);
	free(tab);
    }
    fclose(file);

test3:
    printf("Poczatek pomiaru: ");
    scanf("%d", &start);
    printf("Koniec pomiaru: ");
    scanf("%d", &stop);
    printf("Ilosc pomiarow: ");
    scanf("%d", &n);
    inc = (stop - start) / n;
    
    file = fopen(OUT_FILE3, "w");
    printf("\nTesty Quicksort - 2\n%s\n", gen[1].name);
    fprintf(file, "%s\n", gen[1].name);
    fprintf(file, OUT_FILE3_HEADER);
    for(i = 0; i < n + 1; ++i)
    {
	stop = start + i * inc; /* stop - rozmiar tablicy */
	printf("%d ", stop);
	fprintf(file, "%d;", stop);

	tab = (int*)malloc(stop * sizeof(int));
	wrk = (int*)malloc(stop * sizeof(int));
	gen[1].gen(tab, stop);

	memcpy(wrk, tab, stop * sizeof(int));
	mtime = clock();
	quick_sort(wrk, 0, stop - 1, partition_right);
	mtime = clock() - mtime;
	fprintf(file, "%ld;", mtime / T);
	progress();

	memcpy(wrk, tab, stop * sizeof(int));
	mtime = clock();
	quick_sort(wrk, 0, stop - 1, partition_middle);
	mtime = clock() - mtime;
	fprintf(file, "%ld;", mtime / T);
	progress();

	memcpy(wrk, tab, stop * sizeof(int));
	mtime = clock();
	quick_sort(wrk, 0, stop - 1, partition_random);
	mtime = clock() - mtime;
	fprintf(file, "%ld", mtime / T);
	progress();

	fprintf(file, "\n");
	fflush(file);
	printf("\n");
	free(wrk);
	free(tab);
    }
    fclose(file);

    return 0;
}
