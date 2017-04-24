/**
 * POLITECHNIKA POZNANSKA - WYDZIAL INFORMATYKI - INFORMATYKA I
 * ALGORYTMY I STRUKTURY DANYCH
 *
 * Algorytmy grafowe - DFS, min. drzewo rozpinajace
 *
 * Autorzy: Michal Bocian, Ewa Fengler
 * Rok akademicki: 2016/2017
 */

#ifndef INCLUDES_H
#define INCLUDES_H

typedef struct{
    int value;
    list_item *next;
} item;

typedef struct{
    int value;
    node *left;
    node *right;
} node;

/*generowanie DAGu*/
void genDAGmatrix(int *tab, int rozm); //rozm - n - jeden wymiar!
void genDAGlist((item*)* listArray, int *tab, int rozm);

/*generowanie grafu nieskierowanego z wagami*/
//void genGraphMatrix(tablica, int nasycenie, int rozm);
//void genGraphList(tablica z wsk do list, tablica z grafem, int rozm);

/*sortowanie topologiczne*/
//item* topologicalSortMatrix(tablica, int rozm);
//item* topologicalSortList(tablica z wsk do list, int rozm);

/*min drzewo rozpinajace*/
//node* MST_matrix(tablica, int rozm);
//node* MST_list(tablica z wsk do list, int rozm);

#endif
