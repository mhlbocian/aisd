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
#include<cstring>
#include<limits.h>
#include<vector>

#define black 0
#define gray 1
#define white 2

using namespace std;

struct List {
    int value;
    int num;
    List* next;
};

struct slist {
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
    } else if (value > item->value) {
        listInsert(item->next, value, num);
    } else {
        List* temp = item;
        item = new List;
        item->num = num;
        item->value = value;
        item->next = temp;
    }
}

void slistInsert(slist*& list, int num) {
    if(!list) {
        list = new slist;
        list->num = num;
        list->next = NULL;
    } else {
        slistInsert(list->next, num);
    }
}

bool isOnList(slist* list, int element) {
    while(list) {
        if(list->num == element) return true;
        list = list->next;
    }

    return false;
}

void printGraph(List** graph, int size) {
    List* temp;
    for(int i=0; i<size; i++) {
        cout<<i<<": ";
        temp = graph[i];
        while(temp) {
            cout<<temp->num<<" ";
            temp = temp->next;
        }
        cout<<endl;
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
                listInsert(listArray[i], tab[i][j], j);
                listInsert(listArray[j], tab[i][j], i);
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

slist DFSVisitList(int *color, List* tab[], int i, slist element, int rozm) { // TODO: ze tablica 2D
    //wierzcholek odwiedzony
    color[i] = gray;

    while (tab[i] != NULL) {
        if(color[tab[i]->num] == white) {
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

slist topologicalSortList(int *colors, List **tab, int rozm) {
    slist headTopological = {-1, NULL};

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

void primMST(int** graph, int V)
{
    int parent[V]; // Array to store constructed MST
    int key[V];   // Key values used to pick minimum weight edge in cut
    bool mstSet[V];  // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Always include first 1st vertex in MST.
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet, V);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < V; v++)

            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
                parent[v]  = u, key[v] = graph[u][v];
    }
}

void PrimList(List** graph, int size) {
    slist* tv = NULL;
    int currVertex = 0;
    int edges = 0;
    while(edges < size - 1 && currVertex < size) {
        slistInsert(tv, currVertex);
        while(graph[currVertex]) {
            if(!isOnList(tv, graph[currVertex]->num)) {
                slistInsert(tv, graph[currVertex]->num);
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
    List** list;
    clock_t mtime;

    cout<<"Poczatek pomiaru: ";
    cin>>start;
    cout<<"Koniec pomiaru: ";
    cin>>stop;
    cout<<"Ilosc krokow: ";
    cin>>n;
    inc = (stop - start) / n;

    cout<<"Proba;TSortM;TSortL;0.3M;0.3L;0.7M;0.7L"<<endl;
    for(i = 0; i < n; i++) {
        stop = start + i * inc;
        list = new List*[stop];
        colors = new int[stop];

        cout<<stop<<";";
        matrix = createMatrix(stop);
        
        genDAGmatrix(matrix, stop);
        genDAGlist(list, matrix, stop);

        mtime = clock();
        topologicalSortMatrix(colors, matrix, stop);
        mtime = clock() - mtime;
        cout<<mtime<<";";

        mtime = clock();
        topologicalSortList(colors, list, stop);
        mtime = clock() - mtime;
        cout<<mtime<<";";
        
        genGraphMatrix(matrix, 0.3, stop);
        genGraphList(list, matrix, stop);

        mtime = clock();
        primMST(matrix, stop);
        mtime = clock() - mtime;
        cout<<mtime<<";";

        mtime = clock();
        PrimList(list, stop);
        mtime = clock() - mtime;
        cout<<mtime<<";";

        genGraphMatrix(matrix, 0.7, stop);
        genGraphList(list, matrix, stop);

        mtime = clock();
        primMST(matrix, stop);
        mtime = clock() - mtime;
        cout<<mtime<<";";

        mtime = clock();
        PrimList(list, stop);
        mtime = clock() - mtime;
        cout<<mtime;

        deleteMatrix(matrix, stop);
        listArrayDelete(list, stop);
        delete[] colors;
        cout<<endl;
    }

    return 0;
}
