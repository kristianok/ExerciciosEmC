//KRISTIANO PASINI DE OLIVEIRA
#include<stdio.h>
#include <stdlib.h>
#define Tamanho 15
struct cel
 	{
 	   int v;
       int i;
       int i2;
       struct cel *prox;
    };

typedef struct cel celula;
int** alocarMatriz();
int** lerMatriz(FILE *arq);
void EscreveMatrizCompleta(celula* lista, int** completa);
void gerarMatrizCondensada(celula** inicio, int** M);
void InsereInicio(celula **ini,int v,int i, int i2);
void InsereFim(celula **ini, int v, int i, int i2);
void somarMatrizesCondensadas(celula *lista, celula *lista2);
int* somarDiagonalPrincipal(celula *lista, celula *lista2);
void escrevaVetorSomaDiagonal(int* vetor);
void calcularAreaAbaixoDiagonal(celula* lista);

int main(){
int** M1;
int** M2;
int* vetorSomaDiagonal;
FILE *arq;
arq=fopen("matrizes02.txt","r");
M1 = lerMatriz(arq);
M2 = lerMatriz(arq);
celula *inicio;
inicio = NULL;
celula *inicio2;
inicio2 = NULL;
gerarMatrizCondensada(&inicio, M1);
gerarMatrizCondensada(&inicio2, M2);	
EscreveMatrizCompleta(inicio, M1); 
EscreveMatrizCompleta(inicio2,M2); 
somarMatrizesCondensadas(inicio,inicio2);
vetorSomaDiagonal = somarDiagonalPrincipal(inicio,inicio2);
printf("\n\nSoma Diagonal\n");
escrevaVetorSomaDiagonal(vetorSomaDiagonal);
calcularAreaAbaixoDiagonal(inicio);
}

//FUNCAO PARA CALCULAR A SOMA DOS ELEMENTOS ABAIXO DA DIAGONAL PRINCIPAL DA MATRIZ
void calcularAreaAbaixoDiagonal(celula* lista){
	celula* aux = lista;
	int soma=0;
	while(aux != NULL){
		if(aux->i2 < aux->i){
			soma += aux->v;
		}
		aux=aux->prox;
	}	
	printf("\n\nSoma dos valores abaixo da diagonal principal de M1: \n%d ", soma);
}

//ESCREVER O VETOR DA SOMA DAS DIAGONAIS
void escrevaVetorSomaDiagonal(int* vetor){
	for(int i = 0;i<Tamanho;i++){
		printf("%d ",*(vetor+i));
		}
	}

//CALCULAR A SOMA DAS DIAGONAIS PRINCIPAIS DAS MATRIZES M1 E M2
int* somarDiagonalPrincipal(celula* lista, celula* lista2){
	celula *aux;
  	aux=lista;	
  	celula *aux2;
  	aux2=lista2;
  	celula *listaSoma;
  	int soma = 0;
  	int* vetorSoma;
  	vetorSoma = malloc(sizeof(int)*Tamanho);
  	int i=0;
  	while(i < Tamanho){	
  		while(aux!= NULL && (aux->i < i || aux->i2 < i)){
  			aux=aux->prox;
		}
		while(aux2!= NULL && (aux2->i < i || aux2->i2 < i)){
  			aux2=aux2->prox;
		}
  		if(aux!= NULL && (aux->i == i) && (aux->i2 == i)){
  			soma += aux->v;
  		}
  		if(aux2!=NULL && (aux2->i == i) && (aux2->i2 == i)){
  			soma += aux2->v;
  		}
  		vetorSoma[i] = soma;
  		i++;
  		soma = 0;
	}
	return vetorSoma;
}

//ALOCAR AS DUAS MATRIZES
int** alocarMatriz(){
	int** M = malloc(sizeof(celula)*Tamanho);
	for(int i = 0;i<Tamanho;i++){
		M[i] = malloc(sizeof(celula)*Tamanho); 
	}
	return M;
}

//FUNCAO PARA A SOMA DAS DUAS MATRIZES CONDENSADAS
void somarMatrizesCondensadas(celula *lista, celula *lista2){
	celula *aux;
  	aux=lista;	
  	celula *aux2;
  	aux2=lista2;
  	celula *listaSoma;
  	listaSoma = NULL;
  	int valorSoma=0;
    while(aux != NULL && aux2 != NULL){
		if(aux->i == aux2->i && aux->i2 == aux2->i2){
  			valorSoma = (aux->v) + (aux2->v);
  			InsereFim(&listaSoma,valorSoma,aux->i,aux->i2);
			aux=aux->prox;
  			aux2=aux2->prox;
		}
		else {
			if(aux->i > aux2->i || (aux->i2 > aux2->i2 && aux->i == aux2->i)){
				InsereFim(&listaSoma,aux2->v,aux2->i,aux2->i2);
				aux2=aux2->prox;
			}
			if(aux2->i > aux->i || (aux2->i2 > aux->i2 && aux->i == aux2->i)){
				InsereFim(&listaSoma,aux->v,aux->i,aux->i2);
				aux=aux->prox;
			}
		}	
	}
	while(aux != NULL ){
		InsereFim(&listaSoma,aux->v,aux->i,aux->i2);
		aux=aux->prox;
	}
	while(aux2 != NULL ){
		InsereFim(&listaSoma,aux2->v,aux2->i,aux2->i2);
		aux=aux->prox;
	}	
	printf("\n\nSoma(M1 + M2)");	
	//ESCRITA DA MATRIZ CONDENSADA REFERENTE A SOMA DAS MATRIZES
	EscreveMatrizCompleta(listaSoma, NULL);
}

//FUNCAO PARA ESCREVER A MATRIZ COMPLETA POR MEIO DA MATRIZ CONDENSADA E DA PROPRIA MATRIZ COMPLETA
void EscreveMatrizCompleta(celula *lista, int** completa)
{
	celula *aux;
	aux = lista;
	
	printf("\n\nMatriz Condensada\n\n");
	for(int i = 0; i < Tamanho; i++) {
		printf("\n");
		for(int i2 = 0; i2 < Tamanho; i2++) {
			if (aux!=NULL && aux->i == i && aux->i2 == i2) {
				printf("%d ",aux->v);
				aux = aux->prox;
			} 
			else{
				printf("0 ");		
			} 
		}
	}
	if(completa != NULL){
		printf("\n\nMatriz Completa\n\n");
		for(int i = 0; i < Tamanho; i++) {
			printf("\n");
			for(int i2 = 0; i2 < Tamanho; i2++) {
				printf("%d ",completa[i][i2]);		
			}
		}
	}
}

//FUNCAO PARA INSERIR OS VALORES NAO NULOS DA MATRIZ DE LEITURA EM UMA LISTA LIGADA
void gerarMatrizCondensada(celula** ini,int** M){
	for(int i = 0; i<Tamanho; i++){
		for(int i2 = 0; i2<Tamanho;i2++){
			if(M[i][i2] != 0){
				InsereFim(ini, M[i][i2], i, i2);
			}
		}
	}
return;
}

//FUNCAO PARA INSERIR NO INICIO DA LISTA LIGADA
void InsereInicio(celula **ini,int v,int i, int i2){ 
celula *aux;
aux= (celula*)malloc (sizeof (celula));
aux ->v = v;
aux->i = i;
aux->i2 = i2;
aux->prox=NULL;

if (*ini!=NULL)
	aux->prox=*ini;

*ini=aux;

return ;

}

//FUNCAO PARA INSERIR NO FIM DA LISTA LIGADA
void InsereFim(celula **ini, int v, int i, int i2)
{ 
celula *aux, *fim;
    aux= (celula*)malloc (sizeof (celula));
	aux ->v = v;
  	aux->i = i;
  	aux->i2 = i2;
   fim=*ini;
   if (fim==NULL){
     InsereInicio(ini, v,i,i2);
	}
   else
   {
      while (fim->prox!=NULL){
      fim=fim->prox;
 	  }
  
      aux->prox=NULL;
      fim->prox=aux;
   }
   return ;

}

//LEITURA DA MATRIZ M1 DE UM ARQUIVO
int** lerMatriz(FILE* arq){
	int** M = malloc(sizeof(celula)*Tamanho);
	for(int i = 0;i<Tamanho;i++){
		M[i] = malloc(sizeof(celula)*Tamanho); 
	}
	int elemento;
	if (arq==NULL) { 
        printf("O arquivo matrizes02.txt nao existe"); 
        exit(0);
    } 
	for (int i=0;i<Tamanho;i++){
        for (int i2=0;i2<Tamanho;i2++){      
            fscanf(arq,"%d", &M[i][i2]);
		}
	}	
	return M;
}
