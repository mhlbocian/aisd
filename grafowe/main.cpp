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
#include<limits.h>

#define pomiar() cout<<mtime<<";"

#define black 0
#define gray 1
#define white 2

using namespace std;

struct tList {
    int value;
    int num;
    tList* next;
};

struct tSimpleList {
    int num;
    tSimpleList *next;
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
    delete[] matrix;
}

void listInsert(tList*& item, int value, int num) {
    if (!item) {
        item = new tList;
        item->num = num;
        item->value = value;
        item->next = NULL;
    } else if (value > item->value) {
        listInsert(item->next, value, num);
    } else {
        tList* temp = item;
        item = new tList;
        item->num = num;
        item->value = value;
        item->next = temp;
    }
}

void listArrayDelete(tList** list, int size) {
    tList* temp;

    for (int i = 0; i < size; i++) {
        while (list[i]) {
            temp = list[i];
            list[i] = list[i]->next;
            delete temp;
        }
    }
    delete[] list;
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

void genDAGlist(tList** listArray, int **tab, int rozm) {
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

void genGraphList(tList** listArray, int **tab, int rozm) {
    int i, j;

    for (i = 0; i < rozm; i++) {
        listArray[i] = NULL;
    }

    for (i = 0; i < rozm; i++) {
        for (j = i + 1; j < rozm; j++) {
            if(tab[i][j]) {
                listInsert(listArray[i], tab[i][j], j);
                listInsert(listArray[j], tab[i][j], i);
                tab[i][j] = 0;
                tab[j][i] = 0;
            }
        }
    }
}

tSimpleList DFSVisit(int *color,
                     int **tab,
                     int i,
                     tSimpleList element,
                     int rozm) {
    color[i] = gray;

    for (int j = i+1; j < rozm; j++) {
        if (tab[i][j]) {
            if(color[j] == white) {
                DFSVisit (color, tab, j, element, rozm);
            }
        }
    }
    color[i] = black;
    tSimpleList newElem = {i, &element};

    return newElem;
}

tSimpleList DFSVisitList(int *color,
                         tList* tab[],
                         int i,
                         tSimpleList element,
                         int rozm) {
    color[i] = gray;
    while (tab[i] != NULL) {
        if(color[tab[i]->num] == white) {
            DFSVisitList (color, tab, tab[i]->num, element, rozm);
        }
        tab[i] = (tab[i])->next;
    }
    color[i] = black;
    tSimpleList newElem = {i, &element};

    return newElem;
}

tSimpleList topologicalSortMatrix (int *colors, int **tab, int rozm) {
    tSimpleList headTopological = {-1, NULL};

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

tSimpleList topologicalSortList(int *colors, tList **tab, int rozm) {
    tSimpleList headTopological = {-1, NULL};

    for (int i = 0; i < rozm; i++) {
        colors[i] = white;
    }

    for (int i = 0; i < rozm; i++) {
        if (colors[i] == white) {
            headTopological = DFSVisitList(colors, tab, i, headTopological, rozm);
        }
    }
    return headTopological;
}

int minKey(int key[], bool mstSet[], int V)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void PrimMST(int** G, int size)
{
    int parent[size];
    int key[size];
    bool mstSet[size];

    for (int i = 0; i < size; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    for (int count = 0; count < size-1; count++)
    {
        int u = minKey(key, mstSet, size);

        mstSet[u] = true;
        for (int v = 0; v < size; v++)
            if (G[u][v] && mstSet[v] == false && G[u][v] <  key[v])
                parent[v]  = u, key[v] = G[u][v];
    }
}

void PrimList(tList** graph, int size) {
    int tv[size] = {0};
    int currVertex = 0;
    int edges = 0;
    
    while(edges < size - 1 && currVertex < size) {
        tv[currVertex] = 1;
        while(graph[currVertex]) {
            if(tv[graph[currVertex]->num] == 0) {
                tv[graph[currVertex]->num] == 1;
                edges++;
            }
            graph[currVertex] = graph[currVertex]->next;
        }
        currVertex++;
    }
}

int main(void) {
    srand(time(NULL));

    int i, inc, n, start, stop;
    int* colors;
    int** matrix;
    tList** list;
    clock_t mtime;

    cout<<"Poczatek pomiaru: ";
    cin>>start;
    cout<<"Koniec pomiaru: ";
    cin>>stop;
    cout<<"Ilosc krokow: ";
    cin>>n;
    inc = (stop - start) / n;

    cout<<"Proba;TSortM;TSortL;0.3M;0.3L;0.7M;0.7L;"<<endl;
    for(i = 0; i < n + 1; i++) {
        stop = start + i * inc;
        list = new tList*[stop];
        colors = new int[stop];

        cout<<stop<<";";
        matrix = createMatrix(stop);

        genDAGmatrix(matrix, stop);
        genDAGlist(list, matrix, stop);

        mtime = clock();
        topologicalSortMatrix(colors, matrix, stop);
        mtime = clock() - mtime;
        pomiar();

        mtime = clock();
        topologicalSortList(colors, list, stop);
        mtime = clock() - mtime;
        pomiar();

        genGraphMatrix(matrix, 0.3, stop);
        genGraphList(list, matrix, stop);

        mtime = clock();
        PrimMST(matrix, stop);
        mtime = clock() - mtime;
        pomiar();

        mtime = clock();
        PrimList(list, stop);
        mtime = clock() - mtime;
        pomiar();

        genGraphMatrix(matrix, 0.7, stop);
        genGraphList(list, matrix, stop);

        mtime = clock();
        PrimMST(matrix, stop);
        mtime = clock() - mtime;
        pomiar();

        mtime = clock();
        PrimList(list, stop);
        mtime = clock() - mtime;
        pomiar();

        deleteMatrix(matrix, stop);
        listArrayDelete(list, stop);
        delete[] colors;
        cout<<endl;
    }

    return 0;
}
