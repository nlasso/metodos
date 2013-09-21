#include <iostream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

Matriz::Matriz(Matriz& M, int p, int q){
	_p = p;
	_q = q;
	_fil = M.Filas();
	_col = M.Columnas();
	valores =  new double*[_fil]; // puntero a puntero de arrays
	for(int i=0; i < _fil; i++){
		valores[i] = new double [p+q+1]; //fila i tiene a lo sumo p+r+1 elementos
		valores[i] += p;				 //	offset de cada fila (?)
	}
	
	for (int i=0;i < _fil; i++){
		int ip = max(i - p, 0);			//p de la Fila 
		int iq = min(i + q, _fil-1);			//q de la fila
		for(int j = ip;j <= iq;j++){		//recorro todas las posiciones que quiero !=0
			valores[i][j-i] = M.elem(i,j);			//relacion de como esta almacenado el valor entre la esparsa y la que no lo es;

		}
	}

	
};

Matriz::Matriz(const int n,const int m){
	_p = -1;
	_q = -1;
	
    _fil = n;
    _col = m;
    valores =  new double*[n]; // puntero a puntero de arrays
    for (int i = 0; i < n; i++){
        valores[i] = new double [m]; // cada fila tengo el array
    }
    
    for (int i=0; i < n; i++){
        for (int j=0; j < m; j++) {         
    
           valores[i][j] = 0;
		}
	}
	
	//OTRA FORMA: PUNTEROS SIMPLES
	//_fil = n;
    //_col = m;
    //valores =  new double[n * m]; // puntero a puntero de arrays	


};

Matriz::~Matriz(){
	if (_p == -1){
		for(int i=0;i < _fil; i++){
			delete[] valores[i];
		}
		delete[] valores;
	}
	
	else{
		for(int i=0;i < _fil; i++){
		valores[i]	-= _p;
		delete[] valores[i];
		}
		delete[] valores;
	}	
};

double Matriz::elem(const int n,const int m){
	return valores[n][m];
};

double Matriz::elem2(const int i,const int j){
	if( (j < i-_p) || (j > i+_q)) return 0;
	else return valores[i][j-i];
};

void Matriz::cambiarValor(const int n,const int m, const int v){
	
	valores[n][m] = v;
};

int Matriz::Filas(){
		
	return _fil;	
};

int Matriz::Columnas(){
		
	return _col;	
};

void Matriz::leer_Matriz(const char* filename){

        ifstream texto(filename);
        double cant;
        double v;
        texto >> cant;
        for (int i=0;i<cant;i++){
            for (int j=0;j<cant;j++){
                texto >> v;
                valores[i][j] =v;
            }
        }
};

int Matriz::banda(){
	
		if( _p == -1)return 0;
		else return 1;
}

ostream& operator<<(ostream& ost,Matriz* A){
    
    int b = A->banda();
    ost << " ";
    for(int i=0; i<A->Filas();i++){
        if(i>0){
            ost << " ";
        }
        ost << "|";
        for(int j=0; j<A->Columnas();j++){
            if(j+1 ==A->Columnas()){
				if(b == 0){
					ost << A->elem(i,j) << "|";
					}
				else{
					ost << A->elem2(i,j) << "|";
					}
            }
            else{
				if (b == 0){
					ost << A->elem(i,j) << "|";
				}
				else{
					ost << A->elem2(i,j) << "|";
				}
            }
        }
        ost << endl;
    }
    return ost;
}

