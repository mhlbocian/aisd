/**
 * POLITECHNIKA POZNANSKA - WYDZIAL INFORMATYKI - INFORMATYKA I
 * ALGORYTMY I STRUKTURY DANYCH
 *
 * Problem plecakowy
 *
 * Autorzy: Michal Bocian, Ewa Fengler
 * Rok akademicki: 2016/2017
 */

#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

#define pomiar() cout<<mtime <<";"
#define elo(x) cout<<"elo "<<x<<endl;

using namespace std;

void losuj(int tab[], int rozm, int limit){
    for (int i = 0; i < rozm; i++){
        tab[i] = rand() % limit + 1;
    }
}

void wypiszTab(int tab[], int rozm){
    for (int i = 0; i < rozm; i++){
        cout<<tab[i]<<" ";
    }
    cout<<endl;
}

void wypiszTab(double tab[], int rozm){
    for (int i = 0; i < rozm; i++){
        cout<<tab[i]<<" ";
    }
    cout<<endl;
}

void merge(double tabSortowana[], int tab1[], int tab2[], int first, int middle, int last){
    double *pom1;
    int *pom2, *pom3;
    pom1 = new double[last - first];
    pom2 = new int[last - first];
    pom3 = new int[last - first];

    int i = first, j = middle + 1, k = 0;

    while(i <= middle && j <= last){
        if(tabSortowana[j] > tabSortowana[i]){
            pom1[k] = tabSortowana[j];
            pom2[k] = tab1[j];
            pom3[k] = tab2[j];

            ++j;
        }

        else{
            pom1[k] = tabSortowana[i];
            pom2[k] = tab1[i];
            pom3[k] = tab2[i];
            ++i;
        }
        ++k;
    }

    if(i <= middle){
        while(i <= middle){
            pom1[k] = tabSortowana[i];
            pom2[k] = tab1[i];
            pom3[k] = tab2[i];
            ++i;
            ++k;
        }
    }

    else{
        while(j <= last){
            pom1[k] = tabSortowana[j];
            pom2[k] = tab1[j];
            pom3[k] = tab2[j];
            ++j;
            ++k;
        }
    }

    for (i = 0; i <= last - first; ++i){
        tabSortowana[first + i] = pom1[i];
        tab1[first + i] = pom2[i];
        tab2[first + i] = pom3[i];
    }
}

void merge_sort_rev(double tabSortowana[], int tab1[], int tab2[], int first, int last){
    int middle;

    if(first == last) return;

    middle = (first + last) / 2;

    merge_sort_rev(tabSortowana, tab1, tab2, first, middle);
    merge_sort_rev(tabSortowana, tab1, tab2, middle + 1, last);
    merge(tabSortowana, tab1, tab2, first, middle, last);
}

int zachlannyPlecak(int rozm, int ladownosc, int ciezar[], int wart[]){
    double *wartWzgl;
    int sumaWart, waga;
    wartWzgl = new double[rozm];

    for (int i = 0; i < rozm; i++){
        wartWzgl[i] = wart[i]/(double)ciezar[i];
    }

    /*
    cout<<"Przed sortem: "<<endl;
    wypiszTab(wartWzgl, rozm);
    wypiszTab(ciezar, rozm);
    wypiszTab(wart, rozm);
    */

    merge_sort_rev(wartWzgl, ciezar, wart, 0, rozm - 1);

    /*
    cout<<"Po sorcie: "<<endl;
    wypiszTab(wartWzgl, rozm);
    wypiszTab(ciezar, rozm);
    wypiszTab(wart, rozm);
    */

    for (int i = 0; i < rozm; i++){
        if(waga == ladownosc){
            break;
        }

        if(waga + ciezar[i] <= ladownosc){
            waga += ciezar[i];
            sumaWart += wart[i];
            //cout<<ciezar[i]<<" "<<wart[i]<<endl;
        }
    }

    delete wartWzgl;
    return sumaWart;
}

int dynamicznyPlecak(int rozm, int ladownosc, int ciezar[], int wart[]){
	int** tab = new int*[rozm+ 1];
	int wartosc;
	
	//wiersze = rozm [ciezar][rozm]
	for(int i = 0; i < rozm+1; i++){
		tab[i] = new int[ladownosc+1];
	}
	
	for (int i = 0; i <= ladownosc; i++){
		tab[0][i] = 0;
	}
	
	for (int i = 0; i <= rozm; i++){
		tab[i][0] = 0;
	}
	
	for (int i = 1; i <= rozm; i++){
		for(int j = 0; j <= ladownosc; j++){
			if(ciezar[i-1] > j){
				tab[i][j] = tab[i-1][j];
			}
			else{
				tab[i][j] = max(tab[i-1][j], tab[i-1][j-ciezar[i-1]] + wart[i-1]);
			}
			cout<<tab[i][j]<<" ";
		}
		cout<<endl;
	}
	
	wartosc = tab[rozm][ladownosc];
	
	for(int i = 0; i < rozm + 1; i++){
		delete [] tab[i];
	}
	
	delete [] tab;
	
	return wartosc;
}

int main() {
    srand(time(NULL));
    setbuf(stdout, NULL);

    int i, n, b, x, wartosc, *wart, *ciezar;
    //int wart[] = {};
    //int ciezar[] = {};
    clock_t mtime;

    cout<<"Liczba elementow: ";
    cin>>n;
	//
    cout<<"Ladownosc: ";
    cin>>b;
	//
    cout<<"Ilosc powtorzen: ";
    cin>>x;
	//x = 1;

    cout<<"rozm;wartosc zachlanny; czas zachlanny; wartosc dynamiczny; czas dynamiczny"<<endl;

    for(i = 0; i < x; i++) {
        ciezar = new int[n]; //
        wart = new int[n]; //

        losuj(ciezar, n, b * 0.3);//
        losuj(wart, n, b);//
		
        wypiszTab(ciezar, n);
        wypiszTab(wart, n);

        mtime = clock();
        wartosc = zachlannyPlecak(n, b, ciezar, wart);
        cout<<wartosc<<";";
        mtime = clock() - mtime;
        //pomiar();

        mtime = clock();
        wartosc = dynamicznyPlecak(n, b, ciezar, wart);
        cout<<wartosc<<";";
		mtime = clock() - mtime;
        //pomiar();

        delete ciezar;//
        delete wart;//
        cout<<endl;
    }

    return 0;
}
