#include <iostream>
#include "Funciones.h"
#include "Matriz.h"

using namespace std;

int main(){ //Testeo de las funciones.
	
	TP3::Funciones func;

	Matriz* A = new Matriz(4,4);
	
	A->cambiarValor(1,1,6);
	
	Matriz* B = A->Identidad(5); 
	Matriz* C = new Matriz(*B);
	
	B->cambiarFilas(1,2);
	
	Matriz* sub = A->SubMatriz(1,1);
	
	
	Matriz* D = (*B)+C;

	Matriz* E = new Matriz(*C);
	(*E)*7;
	
	Matriz* F = (*D)*E;
	
	cout << A << endl;
	cout << B << endl;
	cout << D << endl;
	cout << E << endl;
	F->cambiarValor(1,2,1);
	F->cambiarValor(4,0,8);
	cout << F << endl;
	Matriz* G = F->Transponer();
	cout << G << endl;
	
	cout << sub << endl;
	
	delete A;
	delete B;
	delete C;
	delete D;
	delete E;
	delete F;
	delete G;
	delete sub;
	
	return 0;
}
