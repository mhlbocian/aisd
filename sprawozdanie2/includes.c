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

void print_list(list_item* head) {
    printf("[");
    while (head) {
	printf(" %d", head->value);
	head = head->next;
    }
    printf(" ]\n");
}

void print_array(int tab[], int size) {
    int i = 0;

    printf("[");
    for(; i < size; ++i)
    {
	printf(" %d", tab[i]);
    }
    printf(" ]\n");
}

void swap_element(int tab[], int indexA, int indexB) {
    int tmp = tab[indexA];
    tab[indexA] = tab[indexB];
    tab[indexB] = tmp;
}

void genr_uniq(int* tab, int size) {
    int i = 0;
    for(; i < size; ++i) tab[i] = i + 1;

    for (i = size + 1; i < 2*size; i++) tab[rand() % size] = i;
}

list_item* list_insert(list_item* current_item, int x){
    if (!current_item){
	current_item = (list_item*)malloc(sizeof(list_item));
	current_item->value = x;
	current_item->next = NULL;

	return current_item;
    }

    if (x < current_item->value){
	list_item * new_item;

	new_item = (list_item*)malloc(sizeof(list_item));
	new_item->value = x;
	new_item->next = current_item;

	return new_item;
    } else {
	current_item->next = list_insert(current_item->next, x);
    }
}

list_item* create_list (int tab[], int size){
    list_item *head = NULL;
    int i = 0;

    for (; i < size; ++i){
	head = list_insert(head, tab[i]);
    }

    return head;
}

void list_find (list_item *list_head, int x){
    while(list_head) {
	if (list_head->value != x) {
	    list_head = list_head->next;
	} else {
	    /* *
	    printf("[ %d ]\n", list_head->value);
	    /* */
	    return;
	}
    }
    /* *
    printf("[ NULL ]\n");
    /* */
}

void list_search (list_item *list_head, int tab[], int size){
    int i = 0;

    for (; i < size; ++i){
	list_find(list_head, tab[i]);
    }
}

void delete_list (list_item *list_head){
    list_item* ptr;

    while (list_head){
	ptr = list_head->next;
	free(list_head);
	list_head = ptr;
    }
}

node * BST_insert(node * current_node, int x) {
    if(!current_node) {
	current_node = (node*)malloc(sizeof(node));
	current_node->value = x;
	current_node->left = NULL;
	current_node->right = NULL;
	return current_node;
    }
    if (x < current_node->value) {
	current_node->left = BST_insert(current_node->left, x);
    } else {
	current_node->right = BST_insert(current_node->right, x);
    }

    return current_node;
}

node* create_BST (int tab[], int size){
    node *root = BST_insert (NULL, tab[0]);
    int i = 1;

    for (; i < size; i++){
	BST_insert (root, tab[i]);
    }

    return root;
}

node * BST_insert_with_height(node * current_node, int x, int *height) {
    if(!current_node) {
	current_node = (node*)malloc(sizeof(node));
	current_node->value = x;
	current_node->left = NULL;
	current_node->right = NULL;
	return current_node;
    }
    if(x < current_node->value){
	(*height)++;
	current_node->left = BST_insert_with_height(current_node->left, x, height);
    } else {
	(*height)++;
	current_node->right = BST_insert_with_height(current_node->right, x, height);
    }

    return current_node;
}

void create_BST_with_height(int tab[], int size, int *max_height){
    int i = 1;
    *max_height = 0;
    node *root = BST_insert (NULL, tab[0]);

    for (; i < size; i++){
	int height = 0;
	BST_insert_with_height(root, tab[i], &height);
	if (height > (*max_height)) *max_height = height;
    }
}


void BST_find (node *root, int x) {
    node *ptr;
    ptr = root;

    while(ptr->value != x) {
	if (x>ptr->value) ptr=ptr->right;
	else ptr=ptr->left;
    }
}

void BST_search (node *root, int tab[], int size){
    int i = 0;

    for (; i < size; i++){
	BST_find(root, tab[i]);
    }
}

void delete_BST (node *root){
    if (root->left){
	delete_BST(root->left);
    }
    if (root->right){
	delete_BST(root->right);
    }

    free(root);
}

void in_order_to_array(node* root, int** tab, int* size)
{
    if (root->left) in_order_to_array(root->left, tab, size);
    *tab = (int*)realloc(*tab, (*size + 1) * sizeof(int));
    (*tab)[(*size)++] = root->value;
    if (root->right) in_order_to_array(root->right, tab, size);
}

node* build_avl(int* tab, int start, int stop, int* max_height) {
    int mid = (start + stop) / 2;
    if (start > stop) return NULL;
    node* root = (node*)malloc(sizeof(node));
    root->value = tab[mid];
    root->left = build_avl(tab, start, mid - 1, max_height);
    root->right = build_avl(tab, mid + 1, stop, max_height);
    return root;
}

void create_AVL_tree (node* BST_root, int* max_height) {
    int* tab = NULL, len = 0;
    node* avl = NULL;
    in_order_to_array(BST_root, &tab, &len);
    avl = build_avl(tab, 0, len - 1, max_height);
    *max_height = 1; /* jezeli sam root wliczajac */
    while (avl->left) {
	(*max_height)++;
	avl = avl->left;
    }
}
