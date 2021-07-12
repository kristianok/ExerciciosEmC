//KRISTIANO PASINI DE OLIVEIRA
#include<stdio.h>
#include<stdlib.h>

void desalocarMemoria(float** M, float* V, int n);
void escreverRaizes(float* raizes,int n);
float* determinarRaizes(float** M, float* V, int n);
float** lerMatrizTriangular(FILE *arq,int n);
float* lerTermosIndependentes(FILE *arq,int n);

int main(){
	int n;
	float** MatrizTriangular;
	float *raizes,*vetorIndependentes;
	FILE *arq;
	arq=fopen("Sistema.txt","r");	// leitura do arquivo de texto
	if (arq==NULL) { 
        printf("O arquivo Sistemas.txt nao existe"); 
        return 0; 
    }  
	fscanf(arq,"%d",&n);
	MatrizTriangular = lerMatrizTriangular(arq,n);
	vetorIndependentes = lerTermosIndependentes(arq,n);
	raizes = determinarRaizes(MatrizTriangular,vetorIndependentes,n);
	escreverRaizes(raizes,n);
	desalocarMemoria(MatrizTriangular,vetorIndependentes, n);
	MatrizTriangular = NULL;
	vetorIndependentes = NULL;
}
//FUNCAO PARA DESALOCAR A MEMORIA DO VETOR E DA MATRIZ UTILIZADA
void desalocarMemoria(float** M, float* V, int n){
	for(int i = 0;i<n;i++){
		free(M[i]);
	}
	free(V);
}

//FUNCAO PARA ESCREVER OS VALORES DE X1 ATE XN (RAIZES)
void escreverRaizes(float* raizes,int n){
	for(int i = 0; i < n;i++){
		printf("\nX%d: %f",i+1,raizes[i]);
	}
}

//FUNCAO PARA CALCULAR O VETOR COM AS RAIZES DA EQUACAO
float* determinarRaizes(float** M, float* V, int n){
	float* X, termoAnterior = 0;
	X = malloc(sizeof(float)*n);
	for (int i=0;i<n;i++){
		termoAnterior = 0;
        for (int i2=0;i2<i;i2++){  
				termoAnterior += M[i][i2] * X[i2]; 
			}
		X[i] = (V[i] - termoAnterior)/M[i][i];
	}
	return X;	
}

//FUNCAO PARA LER A MATRIZ TRIANGULAR DO ARQUIVO DE TEXTO
float** lerMatrizTriangular(FILE *arq,int n){
	float** M;
	M = malloc(sizeof(float*)*n);
	for(int i = 0;i<n;i++){
		M[i] = malloc(sizeof(float*)*n);
	}
    for (int i=0;i<n;i++){
        for (int i2=0;i2<i;i2++){  
        	M[i][i2] = 0;
    	}
	}
	for (int i=0;i<n;i++){
        for (int i2=0;i2<n;i2++){    
			if(i2<=i){
            fscanf(arq,"%f", &M[i][i2]);
        	}
		}
	}	
	return M;
}

//FUNCAO PARA LER O VETOR DE TERMOS INDEPENDENTES DO ARQUIVO DE TEXTO
float* lerTermosIndependentes(FILE *arq,int n){
	float* V;
	V = malloc(sizeof(float)*n);
	for (int i=0;i<n;i++){       
        fscanf(arq,"%f", &V[i]);
	}	
	return V;	
}





