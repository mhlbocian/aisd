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

#define black 0
#define gray 1
#define white 2

using namespace std;

struct List {
    int value;
    int num;
    List* next;
};

struct slist { //do listy topologicznej
    int num;
    slist *next;
};

int** createMatrix(int n) {
    int** matrix = new int*[n];

    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    return matrix;
}

void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete matrix[i];
    }
}

void listInsert(List*& item, int value, int num) {
    if (!item) {
        item = new List;
        item->num = num;
        item->value = value;
        item->next = NULL;
    } else {
        listInsert(item->next, value, num);
    }
}

void listArrayDelete(List** list, int size) {
    List* temp;

    for (int i = 0; i < size; i++) {
        while (list[i]) {
            temp = list[i];
            list[i] = list[i]->next;
            delete temp;
        }
    }

    delete list;
}

void genDAGmatrix(int** tab, int rozm) {
    int i, j;
    int numOfVertices = rozm * (rozm - 1) * 0.5 * 0.6;

    for (i = 0; i < rozm; i++) {
        for (j = 0; j < rozm; j++) {
            tab[i][j] = 0;
        }
    }

    while (numOfVertices) {
        i = rand() % rozm;
        j = rand() % (rozm - i) + i;

        if(tab[i][j] == 0 && i != j) {
            tab[i][j] = 1;
            numOfVertices--;
        }
    }
}


void genDAGlist(List** listArray, int **tab, int rozm) {
    int i, j;

    for (i = 0; i < rozm; i++) {
        listArray[i] = NULL;
    }

    for (i = 0; i < rozm; i++) {
        for (j = i + 1; j < rozm; j++) {
            if(tab[i][j]) {
                listInsert(listArray[i], 0, j);
            }
        }
    }
}

void genGraphMatrix(int **tab, float nasycenie, int rozm) {
    int i, j, val;
    int numOfVertices = rozm * (rozm - 1) * 0.5 * nasycenie;

    for (i = 0; i < rozm; i++) {
        for (j = 0; j < rozm; j++) {
            tab[i][j] = 0;
        }
    }

    while (numOfVertices) {
        i = rand() % rozm;
        j = rand() % rozm;

        if(tab[i][j] == 0) {
            val = rand() % 1000 + 1;
            tab[i][j] = val;
            tab[j][i] = val;
            numOfVertices--;
        }
    }
}

void genGraphList(List** listArray, int **tab, int rozm) {
    int i, j;

    for (i = 0; i < rozm; i++) {
        listArray[i] = NULL;
    }

    for (i = 0; i < rozm; i++) {
        for (j = i + 1; j < rozm; j++) {
            if(tab[i][j]) {
                listInsert(listArray[i], j, tab[i][j]);
                listInsert(listArray[j], i, tab[i][j]);
                tab[i][j] = 0;
                tab[j][i] = 0;
            }
        }
    }
}

slist DFSVisit(int *color, int **tab, int i, slist element, int rozm) {
    //wierzcholek odwiedzony
    color[i] = gray;

    for (int j = i+1; j < rozm; j++) {
        if (tab[i][j]) {
            if(color[j] == white) {
                DFSVisit (color, tab, j, element, rozm);
            }
        }
    }
    //wierzcholek przetworzony
    color[i] = black;

    //tworzymy liste wynikowa, posortowana topologicznie
    slist newElem = {i, &element};
    return newElem;
}

slist DFSVisitList(int *color, List* tab[], int i, slist element, int rozm){ // TODO: ze tablica 2D
    //wierzcholek odwiedzony
    color[i] = gray;

    while (tab[i] != NULL){
        if(color[tab[i]->num] == white){
            DFSVisitList (color, tab, tab[i]->num, element, rozm);
        }
        tab[i] = (tab[i])->next;
    }
    //wierzcholek przetworzony
    color[i] = black;

    //tworzymy liste wynikowa, posortowana topologicznie
    slist newElem = {i, &element};
    return newElem;
}

slist topologicalSortMatrix (int *colors, int **tab, int rozm) {
    slist headTopological = {-1, NULL};

    for (int i = 0; i < rozm; i++) {
        colors[i] = white;
    }

    for (int i = 0; i < rozm; i++) {
        if (colors[i] == white) {
            headTopological = DFSVisit(colors, tab, i, headTopological, rozm);
        }
    }
    return headTopological;
}

slist topologicalSortList(int *colors, List **tab, int rozm){
    slist headTopological = {-1, NULL};

    for (int i = 0; i < rozm; i++){
        colors[i] = white;
    }

    for (int i = 0; i < rozm; i++){
        if (colors[i] == white){
            headTopological = DFSVisitList(colors, tab, i, headTopological, rozm);
        }
    }
    return headTopological;
}

int main(void) {
    srand(time(NULL));

    int i, inc, n, start, stop;
    int** matrix;
    List** list;

    cout<<"Poczatek pomiaru: ";
    cin>>start;
    cout<<"Koniec pomiaru: ";
    cin>>stop;
    cout<<"Ilosc krokow: ";
    cin>>n;
    inc = (stop - start) / n;

    for(i = 0; i < n; i++) {
        // stop to aktualna proba
        stop = start + i * inc;
        list = new List*[stop];

        cout<<stop<<":";
        matrix = createMatrix(stop);
        genDAGmatrix(matrix, stop);
        genDAGlist(list, matrix, stop);

        deleteMatrix(matrix, stop);
        listArrayDelete(list, stop);
        cout<<endl;
    }

    return 0;
}
