#include <iostream>
#include "Matriz.h"

using namespace std;

int main()
{
    Matriz* mat = new Matriz(5,5);
    mat->leer_Matriz("prueba");
    int n;
    cout << "Hello world!" << endl;
	cout << mat << endl;	//Es matriz banda 1,2
	//~ cout << "--------------" << endl;
	//~ cout << mat->elem(0,0) << endl;
	//~ cout << mat->elem(0,1) << endl;
	//~ cout << mat->elem(1,0) << endl;
	//~ cout << mat->elem(1,1) << endl;
	Matriz* mat2 = new Matriz(*mat,1,2);
	cout << "--------------" << endl;
	cout << mat2 << endl;
	
	delete mat;
	delete mat2;
}
