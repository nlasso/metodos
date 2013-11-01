#include <iostream>
#include "Funciones.h"
#include "Matriz.h"

using namespace std;

int main(int argc, char *argv[]){ 
	
	TP3::Funciones func;

	Matriz* W = func.MatrizW("ej.txt");
	
	cout << "W:" << endl;
	cout << W << endl;
	
	Matriz* v = func.VectorV(float(W->Filas()));
	cout << "v:" << endl;
	cout << v << endl;
	Matriz* D = func.MatrizD(W,v);
	cout << "D:" << endl;
	cout << D << endl;
	Matriz* P = func.MatrizP(W,D);
	cout << "P:" << endl;
	cout << P << endl;
	
	Matriz* P2 = func.MatrizP2(P,v,0.5);
	cout << "P2:" << endl;
	cout << P2 << endl;
	
	Matriz* x0 = new Matriz(P2->Columnas(),1);
	x0->Random();
	cout << "x0:" << endl;
	cout << x0 << endl;
	
	Matriz* x1 = P2->MetodoPotencia(x0,0.000000000005);
	cout << "x1:" << endl;
	cout << x1 << endl;
	
	
	
	W->Transponer();
	cout << "Wt:" << endl;
	cout << W << endl;
	
	return 0;
}
