#include "includes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define THO 1000
#define dot() printf(".")

typedef struct {
    char name[20];
    void (*gen)(int*,int);
} gen_t;

void genv(int* tab, int size)
{
    int i = 0, val = size + 1;
    
    for(; i < size; ++i)
    {
        if(i > size / 2) tab[i] = ++val;
        else tab[i] = --val;
    }
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

void genr(int* tab, int size)
{
    int i = 0;

    for(; i < size; ++i) tab[i] = rand() % 10000;
}

void geninc(int* tab, int size)
{
    int i = 0;

    for(; i < size; ++i) tab[i] = i + 1;
}

void gendec(int* tab, int size)
{
    int i = 0;
    for(; i< size; ++i) tab[i] = size - i;
}

int main (int argc, const char** argv)
{
    srand(time(NULL));
    setbuf(stdout, NULL);

    int *tab, *wrk;
    int i, n, start, stop, inc, genno;
    clock_t mtime;
    FILE *file = fopen("wyniki.csv", "w");
    gen_t gen[5];

    strcpy(gen[0].name, "V-KSZTALTNY");
    gen[0].gen = genv;

    strcpy(gen[1].name, "A-KSZTALTNY");
    gen[1].gen = gena;

    strcpy(gen[2].name, "LOSOWY");
    gen[2].gen = genr;

    strcpy(gen[3].name, "ROSNACY");
    gen[3].gen = geninc;

    strcpy(gen[4].name, "MALEJACY");
    gen[4].gen = gendec;

    printf("Poczatek pomiaru: ");
    scanf("%d", &start);
    printf("Koniec pomiaru: ");
    scanf("%d", &stop);
    printf("Ilosc pomiarow: ");
    scanf("%d", &n);
    inc = (stop - start) / n;

    for(genno = 0; genno < 5; ++genno){
        printf("%s\n", gen[genno].name);
        fprintf(file, "%s\n", gen[genno].name);
        fprintf(file, "N;HEA;INS;MER;SEL;QRC;QIT\n");
        for(i = 0; i < n; ++i)
        {
            stop = start + i * inc; //niepotrzebny stop przechowuje rozmiar tablicy
            printf("%d ", stop); //zeby widziec postep prac
            fprintf(file, "%d;", stop);

            tab = (int*)malloc(stop * sizeof(int));
            wrk = (int*)malloc(stop * sizeof(int));
            gen[genno].gen(tab, stop);

            //HEAP-SORT POMIAR
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            heap_sort(wrk, stop);
            mtime = clock() - mtime;
            fprintf(file, "%ld;", mtime / THO);

            //INSERTION-SORT POMIAR
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            insertion_sort(wrk, stop);
            mtime = clock() - mtime;
            fprintf(file, "%ld;", mtime / THO);

            //MERGE-SORT POMIAR
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            merge_sort(tab, 0, stop - 1);
            mtime = clock() - mtime;
            fprintf(file, "%ld;", mtime / THO);

            //SELECTION-SORT POMIAR
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            selection_sort(wrk, stop);
            mtime = clock() - mtime;
            fprintf(file, "%ld;", mtime / THO);

            //QUICK-SORT REKURENCYJNY POMIAR
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            quick_sort(wrk, 0, stop - 1);
            mtime = clock() - mtime;
            fprintf(file, "%ld;", mtime / THO);

            //QUICK-SORT ITERACYJNY POMIAR
            dot();
            memcpy(wrk, tab, stop * sizeof(int));
            mtime = clock();
            quick_sort_it(wrk, 0, stop - 1);
            mtime = clock() - mtime;
            fprintf(file, "%ld", mtime / THO);

            fprintf(file, "\n");
            printf("\n");
            free(wrk);
            free(tab);
        }
    }

    fclose(file);

    return 0;
}
