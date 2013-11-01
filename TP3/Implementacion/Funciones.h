#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <math.h>
#include "Matriz.h"
                

namespace TP3{
    class Funciones{
    public:
    Funciones();
	
	//void Llenar_Matriz(Matriz* A,float cos,float sen,int n);
	
	//Matriz* Resolver_Sistema(Matriz* A, Matriz* B);		
	
	//int Fuerza_Maxima(Matriz* x,float FMAX,int n); // RET = Fi, Fuerza Maxima o -1 si no es necesario insertar pilar
		
	//tuple<float,float> Insertar_Pilar(Matriz* b,int span,int span2,int h,int n,int n2,float COST,int& pilares,float FMAX);		
	////Muchos argumentos, pero necesarios!
	
	
	Matriz* MatrizW(const char* filename);
	
	Matriz* VectorV(float n);
	
	Matriz* MatrizD(Matriz* W, Matriz* v);
	
	Matriz* MatrizP(Matriz* W, Matriz* D);
	
	Matriz* MatrizP2(Matriz* P1, Matriz* v, float c);
	
	
    };
}

#endif // FUNCIONES_H_INCLUDED
