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
    int i, n, start, stop, inc;
    srand(time(NULL));

    printf("Poczatek pomiaru: ");
    scanf("%d", &start);
    printf("Koniec pomiaru: ");
    scanf("%d", &stop);
    printf("Ilosc pomiarow: ");
    scanf("%d", &n);
    inc = (stop - start) / n;

    // TODO: zrobic tablice tab intow stop*stop
    /*
    int** tab2 = (int**)malloc(stop*sizeof(int*));
    for(i=0; i<stop; ++i){
        tab2[i] = (int*)malloc(stop*sizeof(int));
    }

    */

    // TODO:  tablice ptrItem wsk do item dlugosci stop
    //item** ptrItem = (item**)malloc(stop*sizeof(item*));

    for(i = 0; i < n + 1; ++i){

        stop = start + i * inc;
        printf("%d ", stop);

        // TODO: wrk - kopia tab

        //

    }

    //free(tab);

    return 0;
}
