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

public:
    Matriz(Matriz& M);												//OK
    Matriz(const int n,const int m); 								//OK
    ~Matriz(); 														//OK
    float elem(const int n,const int m); 							//OK
    void cambiarValor(const int n,const int m,float v); 			//OK
    Matriz* Identidad(const unsigned int n); 						//OK
	void Transponer();
	Matriz* MetodoPotencia(Matriz* x, float c);
	float norma1();
	void Random();

    Matriz* SubMatriz(const unsigned int k,const unsigned int l);	//OK 

	Matriz* operator+(Matriz* B);//A+B=res 							//OK
	Matriz* operator-(Matriz* B);
	void operator*(float k);//A*k=res 								//OK
    Matriz* operator*(Matriz* B);//A*B = C 							//OK
    int eq(Matriz* B);//A == C 										//OK

    void cambiarFilas(int n, int m);//Fn <-> Fm debe seguir banda-pq//OK	
	int buscarMaximo(int c); //Indice maxVal en columna c (i-1) 	//OK

	int Filas(); 													//OK
	int Columnas(); 												//OK
	void leer_Matriz(const char* filename); 						//OK
	friend ostream& operator<<(ostream& o, Matriz* A); 				//OK

private:

    float **valores;
    int _fil;	
    int _col;
};


#endif // MATRIZ_H_INCLUDED
