#include "Funciones.h"



TP3::Funciones::Funciones(){}

Matriz* TP3::Funciones::MatrizW(const char* filename){

		ifstream texto(filename);
        float tam;
        float links;
        texto >> tam;
		texto >> links;
		//~ cout << tam << endl;
		//~ cout << links << endl;

		int i;
		int j;
		Matriz* m = new Matriz(tam,tam);
		for(int k=0;k<links;k++){

			texto >>j;
			texto >>i;
			//~ cout << "i =" << i << "j =" << j << endl;
			m->cambiarValor(i-1,j-1,1);
		}

		return m;
};

Matriz* TP3::Funciones::VectorV(float n){

	Matriz* v = new Matriz(n,1);
	for(int i=0;i<n;i++){
		
	    v->cambiarValor(i,0,1/n);
	}
	return v;
};

Matriz* TP3::Funciones::MatrizD(Matriz* W, Matriz* v){
    Matriz* d = new Matriz(1,W->Columnas());
    float sum;
    for (int i=0; i<W->Filas(); i++){
        sum = 0;
        for (int j=0; j<W->Columnas(); j++){
         
            sum = sum + W->elem(i,j);
        }
        if(sum==0){
			d->cambiarValor(0,i,1);
		}
        else{
			d->cambiarValor(0,i,0);
		}	
    }
    Matriz* D = (*v)*d;
	return D;
};

Matriz* TP3::Funciones::MatrizP(Matriz* W, Matriz* D){
	float sum;
	int chequeo;
	Matriz* P = new Matriz(W->Filas(),W->Columnas());
	for (int j=0; j<W->Columnas(); j++){
	    chequeo = 0;
	    sum = 0;
	    for (int i=0; i<W->Filas(); i++){
            if(chequeo==0){
                for (int k=0; k<W->Filas(); k++){
                    sum = sum + W->elem(k,j);
                }
            }
            chequeo = 1;
            if (W->elem(i,j)== 1) P->cambiarValor(i,j,1/sum);
            else P->cambiarValor(i,j,0);
	    }
	}
	P = (*P)+D;
	return P;
};

Matriz* TP3::Funciones::MatrizP2(Matriz* P1, Matriz* v, float c){

	int n = v->Filas();
	Matriz* uno = new Matriz(1,n);
	for (int i=0; i<n; i++){
        uno->cambiarValor(0,i,1);
	}
	Matriz* E = (*v)*uno;
	
	cout << E << endl;
	(*E)*(1-c);
	cout << E << endl;
	(*P1)*(c);
	Matriz* P2 = (*P1)+E;

	return P2;
};

