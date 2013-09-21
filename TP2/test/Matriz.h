#ifndef MATRIZ_H_
#define MATRIZ_H_
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

class Matriz{

private:

    double **valores;
    int _fil;
    int _col;
    int _p;
    int _q;

public:
    Matriz(Matriz& M, int p, int q);
    Matriz(const int n,const int m);
    double elem(const int n,const int m);
    double elem2(const int n,const int m);
    void cambiarValor(const int n,const int m,const int v);
    ~Matriz();
	int Filas();
	int Columnas();
	void leer_Matriz(const char* filename);
	friend ostream& operator<<(ostream& o, Matriz* A);
	int banda();

};


#endif // MATRIZ_H_INCLUDED
