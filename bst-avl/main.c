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

#ifdef __unix__
#define T 1000 /* dzielnik mierzonego czasu */
#else
#define T 1
#endif
#define progress() printf("%ld ", mtime / T)

int main (int argc, const char** argv)
{
    int *tab = NULL;
    int i, n, start, stop, inc;
    int BST_height, AVL_height;
    unsigned int seed;
    clock_t mtime;
    FILE *file = fopen("wyniki.csv", "w");
    list_item *list_head = NULL;
    node *bst = NULL, *avl = NULL;
#ifdef __unix__
    FILE* urandom = fopen("/dev/urandom", "r");
    fread(&seed, sizeof(int), 1, urandom);
    fclose(urandom);
#else
    seed = time(NULL);
#endif
    srand(seed);
    setbuf(stdout, NULL);

    printf("Poczatek pomiaru: ");
    scanf("%d", &start);
    printf("Koniec pomiaru: ");
    scanf("%d", &stop);
    printf("Ilosc pomiarow: ");
    scanf("%d", &n);
    inc = (stop - start) / n;

    fprintf(file, "PROBA;T-L;T-BST;P-L;P-BST;U-L;U-BST;H-BST;H-AVL\n");
    tab = (int*) malloc(sizeof(int) * stop);
    for(i = 0; i < n + 1; ++i)
    {
	BST_height = 1;
	AVL_height = 1;
	stop = start + i * inc;
	printf("%d ", stop);
	fprintf(file, "%d;", stop);
	genr_uniq(tab, stop);

	/* TWORZENIE */
	/* pomiar: lista */
	mtime = clock();
	list_head = create_list (tab, stop);
	mtime = clock() - mtime;
	fprintf(file, "%ld;", mtime / T);
	progress();
	/* pomiar: BST */
	mtime = clock();
	bst = create_BST (tab, stop);
	mtime = clock() - mtime;
	fprintf(file, "%ld;", mtime / T);
	progress();

	/* PRZESZUKIWANIE */
	/* pomiar: lista */
	mtime = clock();
	list_search (list_head, tab, stop);
	mtime = clock() - mtime;
	fprintf(file, "%ld;", mtime / T);
	progress();
	/* pomiar: BST */
	mtime = clock();
	BST_search (bst, tab, stop);
	mtime = clock() - mtime;
	fprintf(file, "%ld;", mtime / T);
	progress();

	/* USUWANIE */
	/* pomiar: lista */
	mtime = clock();
	delete_list (list_head);
	mtime = clock() - mtime;
	fprintf(file, "%ld;", mtime / T);
	progress();
	/* pomiar: BST */
	mtime = clock();
	delete_tree (bst);
	mtime = clock() - mtime;
	fprintf(file, "%ld;", mtime / T);
	progress();

	/* TWORZENIE BST */
	bst = create_BST(tab, stop);
	tree_height(bst, &BST_height, 1);
	fprintf(file, "%d;", BST_height);
	printf("%d ", BST_height);

	/* TWORZENIE AVL */
	avl = create_AVL(bst);
	tree_height(avl, &AVL_height, 1);
	fprintf(file, "%d", AVL_height);
	printf("%d ", AVL_height);

	fprintf(file, "\n");
	printf("\n");

	delete_tree(bst);
	delete_tree(avl);
    }
    free(tab);
    fclose(file);

    return 0;
}
