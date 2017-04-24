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

int** createMatrix(int m, int n){
    int i = 0;
    int** matrix = (int**)malloc(m * sizeof(int*));
    
    for (; i < m; ++i){
	matrix[i] = (int*)malloc(n * sizeof(int));
    }

    return matrix;
}

void freeMatrix(int** matrix, int m, int n){
    int i = 0;
    
    for (; i < m; ++i){
	free(matrix[i]);
    }
}

void list_insert(item* current_item, int succ, int val){
    if (!current_item){
        current_item = (item*)malloc(sizeof(item));
        current_item->succNum = succ;
        current_item->value = val;
        current_item->next = NULL;
    }

    else {
        list_insert(current_item->next, succ, val);
    }
}

/*generowanie DAGu*/
void genDAGmatrix(int **tab, int rozm){

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


void genDAGlist(item** listArray, int **tab, int rozm){
    int i, j;

    for (i = 0; i < rozm; i++){
        listArray[i] = NULL;
    }

    for (i = 0; i < rozm; i++){
        for (j = i + 1; j < rozm; j++){
            if(tab[i][j]){
                // TODO: sprawdziæ, czy dzia³a jako funkcja typu void
                list_insert(&listArray[i], j, 0);

            }
        }
    }
}

item* topologicalSortMatrix(int* tab, int rozm){
    return NULL;
}



void genGraphMatrix(int **tab, float nasycenie, int rozm){

    int i, j, val;
    for (i = 0; i < rozm; i++){
        for (j = 0; j < rozm; j++){
            tab[i][j] = 0;
        }
    }

    int numOfVertices = rozm * (rozm - 1) * 0.5 * nasycenie;

    while (numOfVertices){
        i = rand() % rozm;
        j = rand() % rozm;

        if(tab[i][j] == 0){
            val = rand() % 1000 + 1;
            tab[i][j] = val;
            tab[j][i] = val;
            numOfVertices--;
        }
    }
}

void genGraphList(item** listArray, int **tab, int rozm){
    int i, j;

    for (i = 0; i < rozm; i++){
        listArray[i] = NULL;
    }

    for (i = 0; i < rozm; i++){
        for (j = i + 1; j < rozm; j++){
            if(tab[i][j]){
                list_insert(&listArray[i], j, tab[i][j]);
                list_insert(&listArray[j], i, tab[i][j]);
                tab[i][j] = 0;
                tab[j][i] = 0;
            }
        }
    }
}
