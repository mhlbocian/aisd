/**
 * POLITECHNIKA POZNANSKA - WYDZIAL INFORMATYKI - INFORMATYKA I
 * ALGORYTMY I STRUKTURY DANYCH
 *
 * Algorytmy grafowe - DFS, min. drzewo rozpinajace
 *
 * Autorzy: Michal Bocian, Ewa Fengler
 * Rok akademicki: 2016/2017
 */
#include "includes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void list_insert(item* current_item, int x){
    if (!current_item){
        current_item = (list_item*)malloc(sizeof(list_item));
        current_item->value = x;
        current_item->next = NULL;
    }

    else {
        list_insert(current_item->next, x);
    }
}

/*generowanie DAGu*/
void genDAGmatrix(int *tab, int rozm){

    //0 - zerowanie tablicy
    int i, j;
    for (i = 0; i < rozm; i++){
        for (j = 0; j < rozm; j++){
            tab[i][j] = 0;
        }
    }

    //1 - wypelnienie tablicy
    //nasycenie: 60%
    int numOfVertices = rozm * (rozm - 1) * 0.5 * 0.6;

    while (numOfVertices){
        i = rand() % rozm;
        j = rand() % (rozm - i) + i;

        if(tab[i][j] == 0){
            tab[i][j] = 1;
            numOfVertices--;
        }
    }

//2 - ew. przemieszanie

}

void genDAGlist((item*)* listArray, int *tab, int rozm){
    int i, j;

    for (i = 0; i < rozm; i++){
        listArray[i] = NULL;
    }

    for (i = 0; i < rozm; i++){
        for (j = i + 1; j < rozm; j++){
            if(tab[i][j]){
                // TODO: sprawdzi�, czy dzia�a jako funkcja typu void
                list_insert(listArray[i], j);
            }
        }
    }
}

item* topologicalSortMatrix(int* tab, int rozm){



}
