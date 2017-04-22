/**
 * POLITECHNIKA POZNANSKA - WYDZIAL INFORMATYKI - INFORMATYKA I
 * ALGORYTMY I STRUKTURY DANYCH
 *
 * Algorytmy grafowe - DFS, min. drzewo rozpinajace
 *
 * Autorzy: Michal Bocian, Ewa Fengler
 * Rok akademicki: 2016/2017
 */

//#include "includes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int main (int argc, const char** argv)
{
    int *tab = NULL;
    int i, n, start, stop, inc;

    printf("Poczatek pomiaru: ");
    scanf("%d", &start);
    printf("Koniec pomiaru: ");
    scanf("%d", &stop);
    printf("Ilosc pomiarow: ");
    scanf("%d", &n);
    inc = (stop - start) / n;


    tab = (int*) malloc(sizeof(int) * stop);

    for(i = 0; i < n + 1; ++i){

        stop = start + i * inc;
        printf("%d ", stop);

    }

    free(tab);

    return 0;
}
