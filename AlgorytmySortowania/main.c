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

#define T 1000 /* dzielnik mierzonego czasu */
#define dot() printf(".")

int main (int argc, const char** argv)
{
    srand(time(NULL));
    setbuf(stdout, NULL);

    int *tab, *wrk;
    int i, n, start, stop, inc, genid;
    clock_t mtime;
    FILE *file = fopen("wyniki.csv", "w");
    gen_t gen[5];

    strcpy(gen[0].name, "[v-ksztaltny]");
    gen[0].gen = genv;

    strcpy(gen[1].name, "[a-ksztaltny]");
    gen[1].gen = gena;

    strcpy(gen[2].name, "[losowy]");
    gen[2].gen = genr;

    strcpy(gen[3].name, "[rosnacy]");
    gen[3].gen = geni;

    strcpy(gen[4].name, "[malejacy]");
    gen[4].gen = gend;

    printf("Poczatek pomiaru: ");
    scanf("%d", &start);
    printf("Koniec pomiaru: ");
    scanf("%d", &stop);
    printf("Ilosc pomiarow: ");
    scanf("%d", &n);
    inc = (stop - start) / n;

    for(genid = 0; genid < 5; ++genid){
        printf("%s\n", gen[genid].name);
        fprintf(file, "%s\n", gen[genid].name);
        fprintf(file, "proba;heap;ins;merge;sel;quick-rec;quick-it\n");
        for(i = 0; i < n; ++i)
        {
            stop = start + i * inc; /* stop - rozmiar tablicy */
            printf("%d ", stop);
            fprintf(file, "%d;", stop);

            tab = (int*)malloc(stop * sizeof(int));
            wrk = (int*)malloc(stop * sizeof(int));
            gen[genid].gen(tab, stop);

            /* pomiar: heapsort */
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            heap_sort(wrk, stop);
            mtime = clock() - mtime;
            fprintf(file, "%ld;", mtime / T);

            /* pomiar: insertion sort */
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            insertion_sort(wrk, stop);
            mtime = clock() - mtime;
            fprintf(file, "%ld;", mtime / T);

            /* pomiar: merge sort */
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            merge_sort(tab, 0, stop - 1);
            mtime = clock() - mtime;
            fprintf(file, "%ld;", mtime / T);

            /* pomiar: selection sort */
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            selection_sort(wrk, stop);
            mtime = clock() - mtime;
            fprintf(file, "%ld;", mtime / T);

            /* pomiar: quick sort */
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            quick_sort(wrk, 0, stop - 1);
            mtime = clock() - mtime;
            fprintf(file, "%ld;", mtime / T);

            /* pomiar: quick sort iteracyjny */
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            quick_sort_it(wrk, 0, stop - 1);
            mtime = clock() - mtime;
            fprintf(file, "%ld", mtime / T);

            fprintf(file, "\n");
            printf("\n");
            free(wrk);
            free(tab);
        }
    }

    fclose(file);

    return 0;
}
