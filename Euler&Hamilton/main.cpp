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
#include<stdlib.h>
#include<time.h>
#include<limits.h>

#define pomiar() cout<<mtime<<";"

using namespace std;

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
    for (i = 0; (i + 1) * 2 < rozm; i++){
        j = i * 2 + 1;

        tab[i][j] = true;
        tab[j][i] = true;
        numberOfEdgesLeft[j++]++;

        tab[i][j] = true;
        tab[j][i] = true;
        numberOfEdgesLeft[j]++;

        numberOfEdgesRight[i] += 2;
    }

    if (rozm % 2 == 0){
        i = rozm / 2 - 1;
        j = rozm - 1;

        tab[j][i] = true;
        tab[i][j] = true;

        numberOfEdgesRight[i]++;
        numberOfEdgesLeft[j]++;
    }

     //wypelnianie krawedzi
    for (i = 0; i < rozm - 1; i++){
        edgesToAdd = (rozm - 1 - i) * nasycenie - numberOfEdgesRight[i];

        if(edgesToAdd + numberOfEdgesLeft[i] + numberOfEdgesRight[i] % 2 == 1){
            edgesToAdd += 1;
        }

        while(edgesToAdd-- > 0){
            do{
                j = rand() % rozm;
            }while(j <= i || tab[i][j]);

            tab[i][j] = true;
            tab[j][i] = true;
            numberOfEdgesRight[i]++;
            numberOfEdgesLeft[j]++;
        }
    }

    i = rozm - 1;
    if(numberOfEdgesLeft[i] % 2 == 1){
        edgesToAdd += 2;

        for(k = 0; k < rozm; k++){
            if(tab[i][k] == false){
                for(j = 0; j < rozm; j++){
                    if(tab[k][j] == tab[i][j]){
                        tab[k][j] ^= 1;
                        tab[i][j] ^= 1;
                        tab[j][k] ^= 1;
                        tab[j][i] ^= 1;
                        tab[i][k] = true;
                        tab[k][i] = true;
                        edgesToAdd--;
                    }

                    if (edgesToAdd == 0){
                        break;
                    }
                }
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

void printMatrix (bool **tab, int rozm){
    for (int i = 0; i < rozm; i++){
        for (int j = 0; j < rozm; j++)
            cout<<tab[i][j]<<" ";

        cout<<endl;
    }

}

void Hamilton (bool **tab, int rozm){}

void Euler (bool **tab, int rozm){}

int main(){
    srand(time(NULL));
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

        //cout<<stop<<";";
        matrix = createMatrix(stop);

        genGraphMatrix(matrix, 0.3, stop);
        //printMatrix(matrix, stop);
        cout<<endl;
        /*
        mtime = clock();
        Euler(matrix, stop);
        mtime = clock() - mtime;
        pomiar();

        mtime = clock();
        Hamilton(matrix, stop);
        mtime = clock() - mtime;
        pomiar();
*/
        genGraphMatrix(matrix, 0.7, stop);
        //printMatrix(matrix, stop);
        cout<<endl;
/*
        mtime = clock();
        Euler(matrix, stop);
        mtime = clock() - mtime;
        pomiar();

        mtime = clock();
        Hamilton(matrix, stop);
        mtime = clock() - mtime;
        pomiar();
*/
        //zadanie drugie - prawdopodobnie mniejsze dane

        deleteMatrix(matrix, stop);
        cout<<endl;
    }

    return 0;
}
