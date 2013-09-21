#include <iostream>
#include "Matriz.h"

using namespace std;

int main()
{
    Matriz* mat = new Matriz(5,5,1,2);   //Los indices se toman desde [0...n-1]
    mat->leer_Matriz("prueba");
    //~ int n;
    //~ cout << "Hello world!" << endl;
	cout << mat << endl;	//Es matriz banda 1,2
	cout << "--------------" << endl;
	Matriz* mat2 = new Matriz(*mat,1,2);
	cout << mat2 << endl;
	cout << "--------------" << endl;
	
	Matriz* mat3 = mat->Identidad(5);
	cout << mat3 << endl;
	cout << "--------------" << endl;
	
	Matriz* mat4 = (*mat2)+mat3;
	cout << mat2 << endl;
	cout << "--------------" << endl;	
	(*mat3)*12;
	cout << mat3 << endl;
	cout << "--------------" << endl;
	//~ 
	//~ //Test Submatriz
	Matriz* mat20 = (mat2->SubMatriz(2,2));
	cout << mat20 << endl;
	cout << "--------------" << endl;

	//~ //Test buscar max
	int f1 = mat20->buscarMaximo(0);
	int f2 = mat20->buscarMaximo(1);
	int f3 = mat20->buscarMaximo(2);
	cout << f1 << endl;
	cout << "--------------" << endl;
	cout << f2 << endl;
	cout << "--------------" << endl;
	cout << f3 << endl;
	cout << "--------------" << endl;

	//Test Producto
	Matriz* mat5 = new Matriz(3,3,2,2);
	mat5->cambiarValor(0,0,11);
	mat5->cambiarValor(0,2,1);
	mat5->cambiarValor(1,0,1);
	mat5->cambiarValor(1,1,23);
	mat5->cambiarValor(2,2,2);
	mat5->cambiarValor(2,0,1);
	Matriz* mat7 = new Matriz(3,3,2,2);
	mat7->cambiarValor(0,0,4);
	mat7->cambiarValor(0,1,1);
	mat7->cambiarValor(1,1,2);
	mat7->cambiarValor(1,2,1);
	mat7->cambiarValor(2,2,12);
	mat7->cambiarValor(2,1,1);
	cout << mat5 << endl;
	cout << "--------------" << endl;
	cout << mat7 << endl;
	cout << "--------------" << endl;
	Matriz* mat8 = (*mat5)*mat7;
	cout << mat8 << endl;
	
	
	//Test cambio fila
	//~ cout << mat2 << endl;
	//~ mat2->cambiarFilas(0,1);
	//~ cout << "--------------" << endl;
	//~ cout << mat2 << endl;
	
	//~ //Test LU
	//~ cout << mat2 << endl;
	//~ cout << "--------------" << endl;
	//~ tuple<Matriz*, Matriz*, Matriz*> fact = mat2->factorizacion_PLU();
 //~ 
    //~ cout << "P=" << endl;
    //~ cout << get<0>(fact) << endl;
    //~ cout << "L=" << endl;
    //~ cout << get<1>(fact) << endl;
    //~ cout << "U=" << endl;
    //~ cout << get<2>(fact) << endl;
	//~ 
	//~ Matriz* matP = get<1>(fact);
	//matPL = (*matPL)*get<1>(fact);
	//~ matP = (*matP)*get<2>(fact);
	//~ cout << matP << endl;
	//~ cout << "--------------" << endl;
	//~ cout << mat2 << endl;
	
	
	delete mat;
	delete mat2;
	delete mat3;
	delete mat4;
	delete mat5;
	delete mat7;
	delete mat8;
	delete mat20;
}
