/**
 * POLITECHNIKA POZNANSKA - WYDZIAL INFORMATYKI - INFORMATYKA I
 * ALGORYTMY I STRUKTURY DANYCH
 *
 * Algorytmy grafowe - DFS, min. drzewo rozpinajace
 *
 * Autorzy: Michal Bocian, Ewa Fengler
 * Rok akademicki: 2016/2017
 */
#include<iostream>

using namespace std;

struct List{
	int value;
	int nedge;
	List* next;
};

int** createMatrix(int n){
	int** matrix = new int*[n];
	
	for (int i = 0; i < n; i++){
		matrix[i] = new int[n];
	}
	
	return matrix;
}

void deleteMatrix(int** matrix, int n){
	for (int i = 0; i < n; i++){
		delete matrix[i];
	}
}

void list_insert(List*& item, int value, int nedge){
	if (!item){
        item = new List;
        item->nedge = nedge;
        item->value = value;
        item->next = NULL;
    } else {
        list_insert(item->next, value, nedge);
    }
}

int main(void){
	return 0;
}
