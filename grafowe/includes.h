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

typedef struct list_item item;
typedef struct tree_node node;

struct list_item {
    int succNum;
    int value;
    item *next;
};

struct tree_node{
    int value;
    node *left;
    node *right;
};

int** createMatrix(int m, int n);
void freeMatrix(int** matrix, int m, int n);

/*generowanie DAGu*/
void genDAGmatrix(int **tab, int rozm); //rozm - n - jeden wymiar!
void genDAGlist(item** listArray, int **tab, int rozm);

/*generowanie grafu nieskierowanego z wagami*/
void genGraphMatrix(int **tab, float nasycenie, int rozm); //nasycenie - wywolania 0.3 i 0.7!
//void genGraphList(tablica z wsk do list, tablica z grafem, int rozm);

/*sortowanie topologiczne*/
//item* topologicalSortMatrix(tablica, int rozm);
//item* topologicalSortList(tablica z wsk do list, int rozm);

/*min drzewo rozpinajace*/
//node* MST_matrix(tablica, int rozm);
//node* MST_list(tablica z wsk do list, int rozm);

#endif
