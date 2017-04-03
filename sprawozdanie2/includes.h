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

/* funkcje tablic */
void print_array(int tab[], int size);
void swap_element(int tab[], int indexA, int indexB);

/* lista jednokierunkowa */
struct item{
    int value;
    list_item *next;
};

struct tree_node{
    int value;
    //node *parent = NULL;
    node *left;
    node *right;
};

/*generator nieuporzadkowanej tablicy bez powtorzen*/
void genr_uniq(int* tab, int size);

/* funkcje list */
list_item* create_list (int tab[], int size);
void list_search (list_item *list_head, int tab[], int size);
void delete_list (list_item *list_head);

/* funkcje drzewa */
node* create_BST (int tab[], int size);
void create_BST_with_height (int tab[], int size, int max_height);
void BST_search (node *root, int tab[], int size);
void delete_BST (node *root);


/* AVL */
void create_AVL_tree (node *BST_root, /*...*/ int max_height); //TODO


#endif
