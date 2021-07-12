// KRISTIANO PASINI DE OLIVEIRA
#include<stdio.h>
#include <stdlib.h>
#define Tamanho 12
int** lerMatriz();
int testarLinhas(int** M);
int testarColunas(int** M);
int testarSubmatrizes(int** M);
int testarDiagonais(int** M);
int main(){
int** M;
M = lerMatriz();
//Testes para detectar se a solucao esta errada e de qual forma seja ela linha coluna diagonal etc
if(!testarSubmatrizes(M)){
	printf("Nao eh uma solucao do sudoku X12");
	return 0;
}
if(!testarLinhas(M)){
	printf("Nao eh uma solucao do sudoku X12");
	return 0;
}
if(!testarColunas(M)){
	printf("Nao eh uma solucao do sudoku X12");
	return 0;
}
if(!testarDiagonais(M)){
	printf("Nao eh uma solucao do sudoku X12");
	return 0;
}
//Caso nenhuma das condicoes de erro forem verdades temos que a matriz eh solucao do problema sudoku x12
printf("Eh uma solucao do sudoku X12");
}

//funcao para alocar memoria e ler a matriz do arquivo
int** lerMatriz(){
	int** M = malloc(sizeof(int*)*Tamanho);
	for(int i = 0;i<Tamanho;i++){
		*(M+i)= malloc(sizeof(int*)*Tamanho); 
	}
	FILE *arq;
	int elemento;
	arq=fopen("matriz.txt","r");	// leitura do arquivo de texto
	if (arq==NULL) { 
        printf("O arquivo matriz.txt nao existe"); 
        exit(0); 
    } 
	for (int i=0;i<Tamanho;i++){
        for (int i2=0;i2<Tamanho;i2++){
            fscanf(arq,"%d", &M[i][i2]);
            if(*(*(M+i)+i2) <= 0 || *(*(M+i)+i2)>12 ){
            	printf("A matriz possui elementos menores ou iguais a 0 ou maiores que 12");
            	exit(0);
			}
		}
	}
	for(int i = 0; i < Tamanho; i++){
        for(int i2 = 0; i2 < Tamanho; i2++){
            printf("%d ",*(*(M+i)+i2));
        }
        printf("\n");
    }
	printf("\n");	
	return M;
}

//funcao para checar se ha repeticao nas linhas da matriz
int testarLinhas(int** M){
	int elemento;
	for(int i = 0;i <Tamanho;i++){
		for(int i2 = 0; i2<Tamanho;i2++){
			elemento = *(*(M+i)+i2);
			for(int i3 = 0; i3<Tamanho;i3++){
				if(elemento == *(*(M+i)+i3) && i2 != i3){
					return 0;
				}
			}	
		}
	}
	return 1;
}

//funcao para checar se ha repeticao nas colunas da matriz
int testarColunas(int** M){
	int elemento;
	for(int i = 0;i <Tamanho;i++){
		for(int i2 = 0; i2<Tamanho;i2++){
			elemento = *(*(M+i2)+i);
			for(int i3 = 0; i3<Tamanho;i3++){
				if(elemento == *(*(M+i3)+i) && i2 != i3){
					return 0;
				}
			}	
		}
	}
	return 1;	
}

//funcao para checar se ha repeticao nas submatrizes 3x4 da matriz
int testarSubmatrizes(int** M){
	int elemento;
	for(int a = 0;a<Tamanho;a+=3){	
		for(int b = 0; b<Tamanho;b+=4){
			int i = a;
			int i2 = b;
			while(i < a+3){
				i2 = b;
				while(i2 < b+4){
				elemento = *(*(M+i)+i2);
					for(int i3 = a; i3<a+3;i3++){
						for(int i4 = b;i4<b+4;i4++){
							if(elemento == *(*(M+i3)+i4) && (i != i3 || i2 != i4)){
								return 0;		
							}
						}
					}
				i2++;
				}
			i++;
			}	
		}
	}
	return 1;
}

//funcao para testar se ha repeticao nas diagonais da matriz
int testarDiagonais(int** M){
	int elemento;
	for(int i = 0;i <Tamanho;i++){
		elemento = *(*(M+i)+i);
			for(int i2 = 0; i2<Tamanho;i2++){
				if(elemento == *(*(M+i2)+i2) && i != i2){
					return 0;
				}
	}
	int i2 = 0;
	for(int i = Tamanho-1;i >=0;i--){
		elemento = *(*(M+i)+i2);
		int i4 = 0;
		for(int i3 = Tamanho-1; i3>=0;i3--){
			if(elemento == *(*(M+i3)+i4) && (i != i3 || i2 != i4)){
				return 0;
			}
			i4++;
		}
	i2++;
	}
	}		
	return 1;
}




