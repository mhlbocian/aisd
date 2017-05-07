/**
 * POLITECHNIKA POZNANSKA - WYDZIAL INFORMATYKI - INFORMATYKA I
 * ALGORYTMY I STRUKTURY DANYCH
 *
 * Cykl Hamiltona i obwod Eulera
 *
 * Autorzy: Michal Bocian, Ewa Fengler
 * Rok akademicki: 2016/2017
 */

#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define pomiar() cout<<mtime <<";"

using namespace std;

int stack[1000000];

bool** createMatrix(int n) {
    bool** matrix = new bool*[n];

    for (int i = 0; i < n; i++) {
        matrix[i] = new bool[n];
    }

    return matrix;
}

void deleteMatrix(bool** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete matrix[i];
    }
    delete[] matrix;
}

void printMatrix (bool **tab, int rozm) {
    for (int i = 0; i < rozm; i++) {
        for (int j = 0; j < rozm; j++)
            cout<<tab[i][j]<<" ";

        cout<<endl;
    }

}

void genGraphMatrix(bool **tab, float nasycenie, int rozm) {
    int i, j, k, sumOfEdges = 0, edgesToAdd;
    int *numberOfEdgesLeft;
    int *numberOfEdgesRight;
    numberOfEdgesLeft = new int[rozm];
    numberOfEdgesRight = new int[rozm];

    //zerowanie tablicy
    for (i = 0; i < rozm; i++) {
        for (j = 0; j < rozm; j++) {
            tab[i][j] = 0;
        }
        numberOfEdgesLeft[i] = 0;
        numberOfEdgesRight[i] = 0;
    }

    //tworzenie min drzewa rozpinajacego - spojnosc grafu
    for (i = 0; (i + 1) * 2 < rozm; i++) {
        j = i * 2 + 1;

        tab[i][j] = true;
        tab[j][i] = true;
        numberOfEdgesLeft[j++]++;

        tab[i][j] = true;
        tab[j][i] = true;
        numberOfEdgesLeft[j]++;

        numberOfEdgesRight[i] += 2;
    }

    if (rozm % 2 == 0) {
        i = rozm / 2 - 1;
        j = rozm - 1;

        tab[j][i] = true;
        tab[i][j] = true;

        numberOfEdgesRight[i]++;
        numberOfEdgesLeft[j]++;
    }

    //wypelnianie krawedzi
    for (i = 0; i < rozm - 1; i++) {
        edgesToAdd = (rozm - 1 - i) * nasycenie - numberOfEdgesRight[i];

        if((edgesToAdd + numberOfEdgesLeft[i] + numberOfEdgesRight[i]) % 2 == 1) {
            edgesToAdd += 1;
        }

        while(edgesToAdd > 0) {
            do {
                j = rand() % rozm;
            } while(j <= i || tab[i][j]);

            tab[i][j] = true;
            tab[j][i] = true;
            numberOfEdgesRight[i]++;
            numberOfEdgesLeft[j]++;
            edgesToAdd--;
        }
    }

    i = rozm - 1;
    if(numberOfEdgesLeft[i] % 2 == 1) {
        edgesToAdd = 2;

        for(k = 0; k < rozm - 1; k++) {
            if(tab[i][k] == false) {
                for(j = 0; j < rozm - 1; j++) {
                    if(tab[k][j] == tab[i][j] && k != j) {
                        tab[k][j] ^= 1;
                        tab[i][j] ^= 1;
                        tab[j][k] ^= 1;
                        tab[j][i] ^= 1;
                        tab[i][k] = true;
                        tab[k][i] = true;
                        edgesToAdd--;
                    }

                    if (edgesToAdd == 0) {
                        break;
                    }
                }
                break;
            }
        }
    }

    /*
        //sprawdzenie
        for(i = 0; i < rozm; i++){
            sumOfEdges += numberOfEdgesRight[i];
        }

        cout<<sumOfEdges<<endl;
    */
    delete [] numberOfEdgesLeft;
    delete [] numberOfEdgesRight;
}

/* funkcja pomocnicza sprawdza czy krawedz v moze byc dodana na
 * index pos w tworzonym cyklu Hamiltona */
bool isSafe(bool** graph, int v, int path[], int pos, int size)
{
    /* sprawdza czy wierzcholek jest incydentny do poprzenio
     * dodanego wierzcholka */
    if (graph[path[pos-1]][v] == 0)
        return false;
    /* sprawdza czy wierzcholek zostal juz uzyty */
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

/* rekurencyjna funkcja rozwiazujaca problem Hamiltona */
bool hamCycleUtil(bool** graph, int path[], int pos, int size)
{
    /* czy wszystkie wierzcholki zostaly juz uzyte */
    if (pos == size)
    {
        /* i czy jest krawedz od ostatniego do pierwszego */
        if (graph[path[pos-1]][path[0]] == 1)
            return true;
        else
            return false;
    }
    /* znajdowanie nastepnego wierzcholka */
    for (int v = 1; v < size; v++)
    {
        /* czy mozna dodac do cyklu */
        if (isSafe(graph, v, path, pos, size))
        {
            path[pos] = v;
            /* recur to construct rest of the path */
            if (hamCycleUtil (graph, path, pos+1, size) == true)
                return true;

            /* gdy dodana krawedz nie prowadzi do wyniku  */
            path[pos] = -1;
        }
    }
    /* gdy wierzcholek nie moze zostac dodany do konstruowanego cyklu */
    return false;
}

bool Hamilton(bool** graph, int size)
{
    int *path = new int[size];
    for (int i = 0; i < size; i++)
        path[i] = -1;

    path[0] = 0;
    if (hamCycleUtil(graph, path, 1, size) == false)
    {
        return false;
    }
    return true;
}

void Euler (bool **tab, int rozm) {
    bool visited[rozm][rozm] = {false};
    int top = -1;

    stack[++top] = 0;
DeepEuler:
    while (top != -1) {
        for (int i = 0; i < rozm; i++) {
            if (tab[stack[top]][i] && !visited[stack[top]][i]) {
                visited[stack[top]][i] = true;
                visited[i][stack[top]] = true;
                stack[++top] = i;
                goto DeepEuler;
            }
        }
        top--;
    }
}

int main() {
    srand(time(NULL));
    setbuf(stdout, NULL);
    
    int i, inc, n, start, stop;
    bool** matrix;
    clock_t mtime;

    cout<<"Poczatek pomiaru: ";
    cin>>start;
    cout<<"Koniec pomiaru: ";
    cin>>stop;
    cout<<"Ilosc krokow: ";
    cin>>n;
    inc = (stop - start) / n;
    cout<<"Proba;A-0,3;B-0,3;A-0,7;B-0,7;B-0,5"<<endl;

    for(i = 0; i < n + 1; i++) {
        stop = start + i * inc;
        matrix = createMatrix(stop);
        cout<<stop<<";";

        genGraphMatrix(matrix, 0.3, stop);
/* *
        mtime = clock();
        Euler(matrix, stop);
        mtime = clock() - mtime;
        pomiar();
/* */
        mtime = clock();
        Hamilton(matrix, stop);
        mtime = clock() - mtime;
        pomiar();
/* */
        genGraphMatrix(matrix, 0.7, stop);
/* */
        mtime = clock();
        Euler(matrix, stop);
        mtime = clock() - mtime;
        pomiar();
/* */
        mtime = clock();
        Hamilton(matrix, stop);
        mtime = clock() - mtime;
        pomiar();
/* */
        //zadanie drugie - prawdopodobnie mniejsze dane

        deleteMatrix(matrix, stop);
        cout<<endl;
    }

    return 0;
}
