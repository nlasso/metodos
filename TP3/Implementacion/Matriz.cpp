#include <iostream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

Matriz::Matriz(Matriz& M){

	_fil = M.Filas();
	_col = M.Columnas();
	valores =  new float*[_fil]; // puntero a puntero de arrays
	for(int i=0; i < _fil; i++){
		
		valores[i] = new float [_col]; 
	}
	for (int i=0;i < _fil; i++){
		for (int j=0;j < _col; j++){
		
			valores[i][j] = M.elem(i,j);
		}
	}
	
};

Matriz::Matriz(const int n,const int m){  

	_fil = n;
	_col = m;
	valores =  new float*[_fil]; 
	for(int i=0; i < _fil; i++){
		
		valores[i] = new float [_col];
	}
	
	for(int i=0;i < _fil; i++){
		for(int j=0;j<_col;j++){		//Inicializacion req. por valgrind
		
			valores[i][j] = 0;		
		}
	}
	
};

Matriz::~Matriz(){

	for(int i=0;i < _fil; i++){

		delete[] valores[i];
	}
	delete[] valores;	
};

float Matriz::elem(const int i,const int j){
		
		return valores[i][j];

};

void Matriz::cambiarValor(const int i,const int j, float v){
	
		valores[i][j] = v;
};

Matriz* Matriz::Identidad(const unsigned int n){

    Matriz* res = new Matriz(n,n);
    for(int i =0;i<n;i++){

        res->cambiarValor(i,i,1);
    }
    return res;
}


void Matriz::Transponer(){
	if(_fil == _col){
	for(int i =0; i<_fil;i++){
		for(int j=0; j<=i;j++){
				float temp = valores[i][j];
				float temp2 = valores[j][i];
				valores[i][j] = temp2;
				valores[j][i] = temp;
			}
		}
	}

};

Matriz* Matriz::SubMatriz(const unsigned int k,const unsigned int l){  //Submatriz cuad.

    int tam = _fil - k;
    Matriz* res = new Matriz(tam,tam);
    for(int i=0; i<tam;i++){
            for(int j=0;j<tam;j++){
                float newVal = elem(k+i,l+j);
                res->cambiarValor(i,j,newVal);
            }
    }
    return res;
}

void Matriz::Random(){
	for (int i=0; i<_fil; i++){
		for(int j=0; j<_col; j++){valores[i][j] = rand() %100;}
		}
	}

Matriz* Matriz::MetodoPotencia(Matriz* x0, float c){
	
	//Matriz* x0 = x;
	Matriz* x1 = (*this)*x0;
	Matriz* dif = *x1-x0;
	while (dif->norma1() > c){
		x0 = x1;
		x1 = (*this)*(x1);
		dif = (*x1)-(x0);
		}
	cout<< c <<endl;
	return x1;
	
}

float Matriz::norma1(){
	float suma = 0;
	for(int i = 0; i < _fil; i++){
		suma  = suma + fabs(valores[i][0]);
	}
	return suma;
}


Matriz* Matriz::operator+(Matriz* B){

    Matriz* res = new Matriz(*B);
    for(int i=0; i< _fil;i++){
        for(int j=0; j<_col;j++){
            float newVal = elem(i,j) + (*B).elem(i,j);
				res->cambiarValor(i,j,newVal);
            }
        }
    return res;
}

Matriz* Matriz::operator-(Matriz* B){

    Matriz* res = new Matriz(*B);
    for(int i=0; i< _fil;i++){
        for(int j=0; j<_col;j++){
            float newVal = elem(i,j) - (*B).elem(i,j);
				res->cambiarValor(i,j,newVal);
            }
        }
    return res;
}

void Matriz::operator*( float k){
    
    for(int i=0; i< _fil;i++){
        float temp = 0;
        for(int j=0; j<_col;j++){
         temp = elem(i,j);
         cambiarValor(i,j,(temp*k));
        }
    }
};

Matriz* Matriz::operator*(Matriz* B){
	
	
    Matriz* res = new Matriz(_fil,B->Columnas());

    for(int i =0; i< _fil;i++){
        for(int j=0; j<B->Columnas();j++){
            float temp = 0;
            for (int k = 0; k < _col; k++){
                temp = temp + ((elem(i,k) * B->elem(k,j)));
            }

            res->cambiarValor(i,j,temp);
        }
    }
    return res;
};

void Matriz::cambiarFilas(int n, int m){

	for(int i=0;i< _col;i++){
		float newVal = elem(n,i);	
		cambiarValor(n,i,elem(m,i));	
		cambiarValor(m,i,newVal);
	}

}		
		

int Matriz::buscarMaximo(int c){
    
    int res = 0;
    float valInicial = fabs(elem(0,c));
    for(int i=0; i< _fil;i++){
        float ValAct = fabs((elem(i,c)));
        if(valInicial < ValAct){
            valInicial = ValAct;
            res = i;
        }
    }
    return res;
};


int Matriz::eq(Matriz* B){
	
	int res = 1;
	for(int i=0;i<_col;i++){
		for(int j=0;j<_fil;j++){
			
			if(fabs(elem(i,j) - B->elem(i,j)) >= 1e-4) {
				cout << "No coincide el valor:("<< i << "," << j << ")" << endl;
				return 0;
			}
		}
	}
	return res;
	
};

int Matriz::Filas(){
		
	return _fil;	
};

int Matriz::Columnas(){
		
	return _col;	
};

void Matriz::leer_Matriz(const char* filename){

        ifstream texto(filename);
        float cant;
        float v;
        texto >> cant;
        for (int i=0;i<cant;i++){
            for (int j=0;j<cant;j++){
                texto >> v;
                cambiarValor(i,j,v);
            }
        }
};


ostream& operator<<(ostream& ost,Matriz* A){
    
    ost <<"[";
    for(int i=0; i<A->Filas();i++){
        if(i>0){
            ost << " "; 			// i -> indice de Fila
        }
        ost << " ";
        for(int j=0; j<A->Columnas();j++){
			
			ost << A->elem(i,j) << " ";
        }
        ost << ";" <<  endl;
    }
    ost << "]" <<endl;
    return ost;
}

