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
    Matriz(Matriz& M, int p, int q);								//OK
    Matriz(const int n,const int m, int p, int q); 					//OK
    ~Matriz(); 														//OK
    float elem(const int n,const int m); 							//OK
    void cambiarValor(const int n,const int m,float v); 		//OK
    Matriz* Identidad(const unsigned int n);//Construir I 			//OK
    Matriz* SubMatriz(const unsigned int k,const unsigned int l);	//OK 
    //~ void Transponer();											//OK
	Matriz* operator+(Matriz* B);//A+B=res 							//OK
	void operator*(float k);//A*k=res 								//OK
    Matriz* operator*(Matriz* B);//A*B = C 							//OK

    void cambiarFilas(int n, int m);//Fn <-> Fm debe seguir banda-pq//OK	
	int buscarMaximo(int c); //Indice maxVal en columna c (i-1) 	//OK
	double Rango();             									//OK
    //double MaximoValor() const;//Necesario para PSNR MAXx

    tuple<Matriz*, Matriz*,Matriz*> factorizacion_PLU();
    Matriz* B_substitution(Matriz* b) const; //X despejando desde abajo
    Matriz* F_substitution(Matriz* b) const; //X despejando desde arriba
	
	int Filas(); 													//OK
	int Columnas(); 												//OK
	void leer_Matriz(const char* filename); 						//OK
	friend ostream& operator<<(ostream& o, Matriz* A); 				//OK

private:

    float **valores;
    int _fil;
    int _col;
    int _p;
    int _q;
	int _b;

};


#endif // MATRIZ_H_INCLUDED
