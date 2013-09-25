#include <iostream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

Matriz::Matriz(Matriz& M, int p, int q){

	_p = p;
	_q = q;
	_fil = M.Filas();
	_col = M.Columnas();
	valores =  new float*[_fil]; // puntero a puntero de arrays
	for(int i=0; i < _fil; i++){
		valores[i] = new float [p+q+1]; //fila i tiene a lo sumo p+q+1 elementos
		valores[i] += p;				 //	offset de cada fila (?)
	}
	
	for (int i=0;i < _fil; i++){
		int ip = max(i - p, 0);			//p de la Fila 
		int iq = min(i + q, _fil-1);			//q de la fila
		for(int j = ip;j <= iq;j++){		//recorro todas las posiciones que quiero !=0
			valores[i][j-i] = M.elem(i,j);			//relacion de como esta almacenado el valor entre la esparsa y la que no lo es;
			//~ cout << valores[i][j-i] << endl;
		}
	}
	
};

Matriz::Matriz(const int n,const int m, int p, int q){

	_p = p;
	_q = q;
	_fil = n;
	_col = m;
	valores =  new float*[_fil]; // puntero a puntero de arrays
	for(int i=0; i < _fil; i++){
		valores[i] = new float [p+q+1]; //fila i tiene a lo sumo p+r+1 elementos
		valores[i] += p;				 //	offset de cada fila (?)
	}
	
	//~ //Inicializacion, no es necesaria
	for (int i=0;i < _fil; i++){
		int ip = max(i - p, 0);			//p de la Fila 
		int iq = min(i + q, _fil-1);			//q de la fila
		for(int j = ip;j <= iq;j++){		//recorro todas las posiciones que quiero !=0
			valores[i][j-i] = 0;			//relacion de como esta almacenado el valor entre la esparsa y la que no lo es;
			//~ cout << valores[i][j-i] << endl;
			//~ cout << "..........." << endl;
		}
	}

};

Matriz::~Matriz(){

	for(int i=0;i < _fil; i++){
		valores[i]	-= _p;
		delete[] valores[i];
	}
	delete[] valores;	
};

float Matriz::elem(const int i,const int j){
		
		if((j < i-_p) || (j > i+_q) )
		{return 0;}
		
		else {return valores[i][j-i];}

};

void Matriz::cambiarValor(const int i,const int j, float v){
	
	if( (j < i-_p) || (j > i+_q)){ 
		
		//~ cout << "esta posicion debe ser cero, sino no queda matriz banda" << endl;	
	}
	else{
		valores[i][j-i] = v;
	}
};

Matriz* Matriz::Identidad(const unsigned int n){

    Matriz* res = new Matriz(n,n,n-1,n-1);
    for(int i =0;i<n;i++){

        res->cambiarValor(i,i,1);
    }
    return res;
}

Matriz* Matriz::SubMatriz(const unsigned int k,const unsigned int l){  //Submatriz cuad.

    int tam = _fil - k;
    Matriz* res = new Matriz(tam,tam,_p,_q);
    for(int i=0; i<tam;i++){
            for(int j=0;j<tam;j++){
                float newVal = elem(k+i,l+j);
                res->cambiarValor(i,j,newVal);
            }
    }
    return res;
}

//~ void Matriz::Transponer() {
//~ 
    //~ int c = Columnas();
    //~ int f = Filas();
    //~ Matriz* copia = new Matriz(c,f,_p,_q);
	//~ for(int i =0; i<f;i++){
		//~ for(int j=0; j<c;j++){
				//~ double temp = elem(i,j);
				//~ copia->cambiarValor(j,i,temp);
			//~ }
    //~ }
    //~ *this = *copia;
    //~ delete copia;
//~ };

Matriz* Matriz::operator+(Matriz* B){

    Matriz* res = new Matriz(*B,_p,_q);
    for(int i=0; i< _fil;i++){
        for(int j=0; j<_col;j++){
            float newVal = elem(i,j) + (*B).elem(i,j);
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
	
	int maxP = max(_p,B->_p);
	int maxQ = max(_q,B->_q);
    Matriz* res = new Matriz(_fil,B->Columnas(), maxP, maxQ);
    //Matriz res = *this;
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

tuple<Matriz*, Matriz*, Matriz*> Matriz::factorizacion_PLU(){      //Basada en el codigo de matlab del taller

    int f = _fil;
    Matriz* P = P->Identidad(f);
    P->_p = _p + _q;
    P->_q = _p + _q;
    Matriz* L = L->Identidad(f);
	L->_p = _p;
	L->_q = _q;
    Matriz* U = new Matriz (*this, _p, _q);
    for(int k=0;k<_col-1; k++){

            //~ Matriz* sub = U->SubMatriz(k,k);
            //~ int maxFila = sub->buscarMaximo(0);
			//~ maxFila = maxFila+k;
            //~ if(maxFila > k){
                //~ U->cambiarFilas(maxFila,k);
                //~ P->cambiarFilas(k,maxFila);  // k o k+1..
				//L->cambiarFilas(maxFila,k);// La L no tengo idea porque carajo no hay que permutarla...
                //~ if(k > 0){
                    //~ for(int l=0;l<k;l++){   // 0 < l < k-1  // l = 0:k-1
                        //~ double temp = L->elem(k,l);
                        //~ double temp2 = L->elem(maxFila,l);
//~ 
                        //~ L->cambiarValor(maxFila,l,temp);
                        //~ L->cambiarValor(k,l,temp2);
                    //~ }


                //~ }
            //~ }
            for(int i=k+1;i<_fil;i++){
	
                if(U->elem(k,k) != 0){

                    float newVal = ((U->elem(i,k)) / (U->elem(k,k)));
                    //~ cout << newVal << endl;
                    L->cambiarValor(i,k,newVal);     //Valor de la L, multiplicador
                    U->cambiarValor(i,k,0);          //Valor triangulado queda en 0
                }
                for(int j= k+1;j< _col;j++){
                    float newVal = U->elem(i,j) - (L->elem(i,k) * U->elem(k,j));  //Lleno el resto de la fila
                    U->cambiarValor(i,j,newVal);

                }
            }


    }
    //~ L->_p = _p;
	//~ L->_q = 0;	
    tuple<Matriz*, Matriz*, Matriz*> res = make_tuple (P, L, U);
    return res;
};

void Matriz::cambiarFilas(int n, int m){

	int exq = _q;
	_q = _p + _q;
	
		//~ double* temp = new double [c];
		//~ for(int i=0;i<c;i++){
		//~ 
		//~ temp[i] = i;
		//~ 
		//~ }
		//~ 
			//~ 
		//~ valores[n] = temp;

		//~ valores[n]	+= _p;
		//~ valores[n]	-= n;
		
		if( n != 0){
		
			valores[n] -= _p;		//Vuelvo el offset  d-p al primer valor
			//~ cout << valores[n][0] << endl;
			//~ cout << valores[n][1] << endl;
		}
		else{
			
		//~ cout << valores[n][0] << endl; //No hace falta correr offset (0,0) = Diag.	
			
		}
		
		if(m != 0){
			
				valores[m] -= _p;		//Vuelvo el offset  d-p al primer valor	
				//~ cout << valores[m][0] << endl;
				//~ cout << valores[m][1] << endl;
		}
		
		
		if( m > n){  // F1 > F0
		
			if(n != 0){
				for(int i= 0;i< _q+1;i++){
					float temp = valores[m][i];
				
					valores[m][i] = valores[n][_p+i];//Fila N <<--  Fila M
				
					valores[n][_p+i] = temp;
				
				}
				
				valores[n][0] = 0;
			}	
			else{
				for(int i= 0;i< exq+1;i++){	//Para fila 0
					float temp = valores[m][i];
								
					valores[m][i] = valores[n][m-1+i];//Fila N <<--  Fila M
				
					valores[n][m-1+i] = temp;
				
				}
				
				
					
				
				for(int i= exq+1; i<_q;i++){	//LLeno el resto de los valores
					valores[m][i] = 0;
				
				}
			
			}
			
			
				
			
		
		}else{
			
			if(m != n){
				
				if(m != 0){
					for(int i= 0;i< _q+1;i++){
						float temp = valores[n][i];
				
						valores[n][i] = valores[m][_p+i];//Fila N <<--  Fila M
				
						valores[m][_p+i] = temp;
				
					}
				
					valores[m][0] = 0;
				}	
				else{
					for(int i= 0;i< exq+1;i++){	//Para fila 0
						float temp = valores[n][i];
								
						valores[n][i] = valores[m][n-1+i];//Fila N <<--  Fila M
				
						valores[m][n-1+i] = temp;
				
					}
				
				
					
				
					for(int i= exq+1; i<_q;i++){	//LLeno el resto de los valores
						valores[n][i] = 0;
				
					}
			
				}	
			
			}	
				
			
			
		}
			if(n!=0){
				valores[n] += _p;
			}
		
			if(m!=0){
				valores[m] += _p;
			}
}		
		
		//~ valores[n]	-= 1;
	
	
	//~ for(int i= c-2;i >= 0;i--){   //c-2 = _p + _q - d - 1
	//~ 
		//~ cout << valores[n][i] << endl;
		//~ cout << valores[m][i] << endl;
		//~ cout << "----------" << endl;
	//~ 
	//~ }
	
	
	//~ for(int i=0;i< c;i++){	// para n
		//~ 
		//~ if((i <(n+exq+1)) && (valores[n][exq - i] == elem(n,exq-i+n)) ){
		//~ 
		//~ temp[n+exq-i] = valores[n][exq - i];
		//~ cout << valores[n][exq - i] << "   " << elem(n,exq-i+n) << endl;
		//~ cout << "----------" << endl;
		//~ }
//~ 
	//~ }
	//~ 
	//~ for(int i=0;i< c;i++){	// para m
		//~ 
		//~ if((i <(m+exq+1)) && (valores[m][exq - i] == elem(m,exq-i+m)) ){
		//~ temp2[m+exq-i] = valores[m][exq - i];
		//~ cout << valores[m][exq - i] << "   " << elem(m,exq-i+m) << endl;
		//~ cout << "----------" << endl;
		//~ }
//~ 
	//~ }
	
	
	
	
	
	
	
	//~ for(int i=c-1;i > 0;i--){
		//~ valores[m] -= _p;
		//~ valores[n] -= _p;
		
		//~ if (valores[n][i] == 0) {cout << "VIEJAA" << endl;}
		//~ temp[i] = valores[n][i];
		//~ valores[n][i] = valores[m][i];
		//~ valores[m][i] = temp[i];
		//~ cout << i << " = " << valores[m][i] << endl;
		//~ cout << valores[n][i] << endl;
		//~ cout << valores[m][i] << endl;
		//~ valores[m] += _p;
		//~ valores[n] += _p;
	//~ }
	//~ 
		
		
		
		//~ valores[n]	-= _p;
		//~ valores[m]	-= _p;
		//~ ;
		//~ 
		//~ for(int i=0;i< 3;i++){
			//~ 
		//~ std::swap(valores[n][i+1],valores[m][i]);	
		//~ }
		//~ valores[m]	+= _p;
		//~ valores[n]	+= _p;
		
		
		
		//~ 
		//~ valores[m] = NULL;		
		
		// Show Array
		//~ for(int i=0;i<_fil;i++){
			//~ for(int j=0;j<_col;j++){
				//~ if( (j < i-_p) || (j > i+_q) ){
				//~ cout << "(" << i << "," << j-i << ") = " << endl;}
				//~ else{
				//~ cout << "(" << i << "," << j-i << ") = " <<  valores[i][j-i] << endl;}
			//~ }
		//~ }

	    //~ for(int j=0; j< _col;j++){	//n=0 m=1
	    	//~ 
	    	//~ double a;
	    	//~ double b;
	    	//~ 
			//~ if( (j<= n+exq) || (j<= m+exq)){
			//~ double elemM = elem(n,j);
			//~ double elemN = elem(m,j);
			//~ 
				//~ 
				//~ 
				//~ cambiarValor(m,j,elemM);
				//~ cout << "(" << m << "," << -m+j << ") = " << elemN << "->" << elemM << endl;
				//~ cambiarValor(n,j,elemN);
				//~ cout << "(" << n << "," << -n+j << ") = " << elemM << "->"  << elemN << endl;
				//~ 
			//~ }
			
			//~ else {
				//~ if( j <= _q){
					//~ cambiarValor(m,j,0);
				//~ }
				//~ if( j <= _q){
					//~ cambiarValor(n,j,0);
				//~ }
			//~ }
		//~ }	

			//~ if(j<= n+exq){
			//~ double elemM = elem(n,j);
			//~ a = elemM;
			//~ }
			//~ else{a=0;}
			//~ 
			//~ if(j <= m+exq){
			//~ double elemN = elem(m,j);
			//~ b = elemN;
			//~ }
			//~ else{b=0;}
			//~ 
			//~ if(j <= exq+m){
			//~ 
				//~ if(j > _q){
				//~ cout << "WARNING" << endl;
				//~ }						
				//~ else{
					//~ valores[m][j-m] = b;
					//~ cout << "(" << m << "," << -m+j << ") = " <<  a << endl;
				//~ }
			//~ 
			//~ }
//~ 
			//~ if(j<= exq+n){						
			//~ 
				//~ if(j > _q){ 
					//~ cout << "WARNING" << endl;
				//~ }						
				//~ else{
					//~ valores[n][j-n] = b;
					//~ cout << "(" << n << "," << -n+j << ") = " <<  b << endl;
				//~ }	
			//~ }


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

int Matriz::Filas(){
		
	return _fil;	
};

int Matriz::Columnas(){
		
	return _col;	
};

double Matriz::Rango(){

    double Maximo = elem(0,0);
    double Minimo = elem(0,0);

    for(int j=0;j < _col;j++){
        for(int i=0;i < _fil;i++){

            double temp = elem(i,j);

            if (temp < Minimo){
                Minimo = elem(i,j);
            }
            if (temp > Maximo){
                elem(i,j);
            }
        }
    }
    double res = Maximo - Minimo;
    return res;


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
    
    ost << " ";
    for(int i=0; i<A->Filas();i++){
        if(i>0){
            ost << " ";
        }
        ost << "|";
        for(int j=0; j<A->Columnas();j++){
            if(j+1 ==A->Columnas()){
				//~ if((j < i- A->_p) || (j > i+ A->_q)){
					//~ ost << 0 << "|";
				//~ }
				//~ else{
					//~ ost << A->valores[i][j-i] << "|";
					ost << A->elem(i,j) << "|";
				//~ }
            }
            else{
				//~ if((j < i- A->_p) || (j > i+ A->_q)){
					//~ ost << 0 << "|";
				//~ }
				//~ else{
				//~ ost << A->valores[i][j-i] << "|";
				ost << A->elem(i,j) << "|";
				//~ }
            }
        }
        ost << endl;
    }
    return ost;
}

