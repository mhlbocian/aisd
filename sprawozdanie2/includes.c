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

void print_array(int tab[], int size)
{
    int i = 0;
    for(; i < size; ++i)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void swap_element(int tab[], int indexA, int indexB)
{
    int tmp = tab[indexA];
    tab[indexA] = tab[indexB];
    tab[indexB] = tmp;
}

void genr_uniq(int* tab, int size)
{
    int i = 0;
    for(; i < size; ++i) tab[i] = i + 1;

    for (i = size + 1; i < 2*size; i++) tab[rand() % size] = i;
}
/*
list_item* list_insert(list_item* current_item, int x){
    if(!current_item) {
		current_item = (list_item*)malloc(sizeof(list_item));
		current_item->value = x;
		current_item->next = NULL;
		return(current_item);
    }

	if(current_item->value < x)
	     current_node->next = insert(NULL, x);
    else {
		if(current_node->value < x)
			current_node->right = insert(current_node->right, x);
	}
}
*/
list_item* create_list (int tab[], int size){
    int i = 0;
    for (; i < size; i++){

    }
    return NULL;//*list_head;
}

void list_search (list_item *list_head, int tab[], int size){
    int i = 0;
    for (; i < size; i++){

    }
    //TODO
}

void delete_list (list_item *list_head){
    //TODO
}

/*
node * BST_insert(node * current_node, int x) {
	if(!current_node) {
		current_node = (node*)malloc(sizeof(node));
		current_node->value = x;
		current_node->left = NULL;
		current_node->right = NULL;
		return(current_node);
	}
	if(current_node->value > x)
	     current_node->left = insert(current_node->left, x);
    else {
		if(current_node->value < x)
			current_node->right = insert(current_node->right, x);
	}

	return(current_node);
}
*/
node* create_BST (int tab[], int size){
    node *root;
    root = malloc(sizeof(node));
    root->value = tab[0];
    root->left =NULL;
    root->right = NULL;
    /*
    int i = 0;
    for(; i < size; i++){
        BST_insert(root, tab[i]);
    }
    */
    return root;
}

void create_BST_with_height (int tab[], int size, int max_height){
    //TODO
}

void BST_search (node *root, int tab[], int size){
    //TODO
}

void delete_BST (node *root){
    //TODO
}

/* TODO */
void create_AVL_tree (node *BST_root, /*...*/ int max_height){
    //TODO
}
