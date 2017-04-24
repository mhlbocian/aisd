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
#include<stdlib.h>
#include<time.h>

using namespace std;

struct List{
	int value;
	int num;
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

void list_insert(List*& item, int value, int num){
	if (!item){
        item = new List;
        item->num = num;
        item->value = value;
        item->next = NULL;
    } else {
        list_insert(item->next, value, num);
    }
}

void genDAGmatrix(int** tab, int rozm){
    int i, j;
    int numOfVertices = rozm * (rozm - 1) * 0.5 * 0.6;
    
    for (i = 0; i < rozm; i++){
        for (j = 0; j < rozm; j++){
            tab[i][j] = 0;
        }
    }

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


void genDAGlist(List** listArray, int **tab, int rozm){
    int i, j;

    for (i = 0; i < rozm; i++){
        listArray[i] = NULL;
    }

    for (i = 0; i < rozm; i++){
        for (j = i + 1; j < rozm; j++){
            if(tab[i][j]){
                list_insert(listArray[i], 0, j);
            }
        }
    }
}

List* topologicalSortMatrix(int* tab, int rozm){
    return NULL;
}

void genGraphMatrix(int **tab, float nasycenie, int rozm){
    int i, j, val;
    int numOfVertices = rozm * (rozm - 1) * 0.5 * nasycenie;
    
    for (i = 0; i < rozm; i++){
        for (j = 0; j < rozm; j++){
            tab[i][j] = 0;
        }
    }

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

void genGraphList(List** listArray, int **tab, int rozm){
    int i, j;

    for (i = 0; i < rozm; i++){
        listArray[i] = NULL;
    }

    for (i = 0; i < rozm; i++){
        for (j = i + 1; j < rozm; j++){
            if(tab[i][j]){
                list_insert(listArray[i], j, tab[i][j]);
                list_insert(listArray[j], i, tab[i][j]);
                tab[i][j] = 0;
                tab[j][i] = 0;
            }
        }
    }
}

int main(void){
	int i, inc, n, start, stop;
	
	cout<<"Poczatek pomiaru: ";
	cin>>start;
	cout<<"Koniec pomiaru: ";
	cin>>stop;
	cout<<"Ilosc krokow: ";
	cin>>n;
	inc = (stop - start) / n;
	
	for(i = 0; i < n + 1; i++){
		// stop to aktualna proba
		stop = start + i * inc;
		
	}
	
	return 0;
}
