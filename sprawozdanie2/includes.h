/**
 * POLITECHNIKA POZNANSKA - WYDZIAL INFORMATYKI - INFORMATYKA I
 * ALGORYTMY I STRUKTURY DANYCH
 *
 * Zlozone struktury danych - lista jednokierunkowa, BST, drzewo AVL
 *
 * Autorzy: Michal Bocian, Ewa Fengler
 * Rok akademicki: 2016/2017
 */
#ifndef INCLUDES_H
#define INCLUDES_H

typedef struct item list_item;
typedef struct tree_node node;

struct item{
    int value;
    list_item *next;
};

struct tree_node{
    int value;
    node *left;
    node *right;
};

/*generator nieuporzadkowanej tablicy bez powtorzen*/
void genr_uniq(int* tab, int size);

/* funkcje list */
list_item* create_list (int tab[], int size);
list_item* list_insert(list_item* current_item, int x);
void delete_list (list_item *list_head);
void list_search (list_item *list_head, int tab[], int size);
void list_find (list_item *list_head, int x);

/* funkcje drzewa */
node* create_BST (int tab[], int size);
node * BST_insert(node * current_node, int x);
void BST_find (node *root, int x);
void BST_search (node *root, int tab[], int size);
void BST_to_array(node* root, int** tab, int* size);
void tree_height(node* node, int* global, int local);
void delete_tree (node *root);
/* AVL */
node* build_avl(int* tab, int start, int stop);
node* create_AVL(node *BST_root);
#endif
