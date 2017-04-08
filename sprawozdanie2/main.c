/**
 * POLITECHNIKA POZNANSKA - WYDZIAL INFORMATYKI - INFORMATYKA I
 * ALGORYTMY I STRUKTURY DANYCH
 *
 * Zlozone struktury danych - lista jednokierunkowa, BST, drzewo AVL
 *
 * Autorzy: Michal Bocian, Ewa Fengler
 * Rok akademicki: 2016/2017
 */

#include "includes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define T 1 /* dzielnik mierzonego czasu */
#define progress() printf("%ld ", mtime)

int main (int argc, const char** argv)
{
    srand(time(NULL));
    setbuf(stdout, NULL);

    list_item *list_head; /*poczatek listy*/
    node *root;
    int *tab;//, *wrk;
    int i, n, start, stop, inc;
    int BST_max_height = 0, AVL_tree_max_height = 0;
    clock_t mtime;
    FILE *file = fopen("wyniki.csv", "w");


    printf("Poczatek pomiaru: ");
    scanf("%d", &start);
    printf("Koniec pomiaru: ");
    scanf("%d", &stop);
    printf("Ilosc pomiarow: ");
    scanf("%d", &n);
    inc = (stop - start) / n;

    fprintf(file, ";tworzenie;;przeszukiwanie;;usuwanie\n");
    fprintf(file, "proba;lista jednokierunkowa;BST;lista jednokierunkowa;BST;lista jednokierunkowa;BST;wys. BST;wys. AVL\n");

    for(i = 0; i < n + 1; ++i)
    {
        stop = start + i * inc; /* stop - rozmiar tablicy */
        printf("%d ", stop);
        fprintf(file, "%d;", stop);

        tab = (int*)malloc(stop * sizeof(int));

        genr_uniq(tab, stop);

        /* I ZADANIE */

        /* TWORZENIE */
        /* pomiar: lista */
        mtime = clock();
        //list_head = create_list (tab, stop);
        mtime = clock() - mtime;
        fprintf(file, "%ld;", mtime / T);
        progress();
        /* pomiar: BST */
        mtime = clock();
        root = create_BST (tab, stop);
        mtime = clock() - mtime;
        fprintf(file, "%ld;", mtime / T);
        progress();

        /* PRZESZUKIWANIE */
        /* pomiar: lista */
        mtime = clock();
        //list_search (list_head, tab, stop);
        mtime = clock() - mtime;
        fprintf(file, "%ld;", mtime / T);
        progress();
        /* pomiar: BST */
        mtime = clock();
        BST_search (root, tab, stop);
        mtime = clock() - mtime;
        fprintf(file, "%ld;", mtime / T);
        progress();

        /* USUWANIE */
        /* pomiar: lista */
        mtime = clock();
        //delete_list (list_head);
        mtime = clock() - mtime;
        fprintf(file, "%ld;", mtime / T);
        progress();
        /* pomiar: BST */
        mtime = clock();
        delete_BST (root);
        mtime = clock() - mtime;
        fprintf(file, "%ld;", mtime / T);
        progress();


        /* II ZADANIE */

        /* TWORZENIE BST */
        create_BST_with_height (tab, stop, &BST_max_height);
        fprintf(file, "%d;", BST_max_height);
        printf(" %d ", BST_max_height);

        /* TWORZENIE AVL - TODO */
        //create_AVL_tree (root, /*...*/ &AVL_tree_max_height);
        fprintf(file, "%d", AVL_tree_max_height);
        printf(" %d ", AVL_tree_max_height);


        fprintf(file, "\n");
        printf("\n");
        //free(wrk);
        free(tab);
    }



    fclose(file);

    return 0;
}
