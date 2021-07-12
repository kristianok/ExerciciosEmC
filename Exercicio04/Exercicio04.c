//KRISTIANO PASINI DE OLIVEIRA
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>	
#define MAX_LIN 20
#define MAX_COL 20
#define T 1500

//STRUCT QUE CONTEM A INFORMACAO DE CADA ELEMENTO DA MATRIZ JANELA
struct go {
 char elemento;
 int i;
 int i2;
 //CASO A VELOCIDADE SEJA 0 O ELEMENTO NAO E UMA GOTA
 int velocidade;
 };
 
typedef struct go gota;

gota** alocarMatriz();
void escrevaMatriz(gota** M);
void lerMatriz(gota** janela);
void movimentarGotas(gota** janela);

int main(){
	gota** janela;
	janela = alocarMatriz();
	lerMatriz(janela);
	escrevaMatriz(janela);
	Sleep(T);
	system("cls"); 
	movimentarGotas(janela);
}

//FUNCAO QUE MOVIMENTA AS GOTAS NA JANELA E SE ENCERRA QUANDO NAO HA MAIS GOTAS
void movimentarGotas(gota** janela){
	int velocidadeTotal=1;
	int iprox = 0;
	//CASO A VELOCIDADE TODAS DE TODOS OS ELEMENTOS FOR 0 A MATRIZ N POSSUI MAIS GOTAS E A FUNCAO PARA DE EXECUTAR
	while(velocidadeTotal != 0){
		velocidadeTotal=0;
		for(int i = 0;i<MAX_LIN;i++){
			for(int i2 = 0; i2 < MAX_COL; i2++){
				velocidadeTotal+=janela[i][i2].velocidade;
			}
		}	
		if(velocidadeTotal == 0){
			break;
		}
		//MOVIMENTAR AS GOTAS COM VELOCIDADE 1
		for(int i = MAX_LIN-1;i>=0;i--){
			for(int i2 = MAX_COL-1; i2 >=0;i2--){
				if((janela[i][i2].velocidade)==1){
					iprox=i+1;
					janela[i][i2].elemento = ' ';
					janela[i][i2].velocidade = 0;
					if(iprox<MAX_LIN-1){
						janela[iprox][i2].elemento = 'G';
						janela[iprox][i2].velocidade = 1;
					}	
				}
			}
		}
		//MOVIMENTAR AS GOTAS COM VELOCIDADE 2
		for(int i = MAX_LIN-1;i >=0;i--){
			for(int i2 = MAX_COL-1; i2 >=0;i2--){
				if((janela[i][i2].velocidade)==2){
					iprox=i+2;
					janela[i][i2].elemento = ' ';
					janela[i][i2].velocidade = 0;
					if(iprox<MAX_LIN-1){
						if(janela[iprox-1][i2].elemento == 'G'){
							janela[iprox-1][i2].elemento = ' ';
							janela[iprox-1][i2].velocidade = 0;
						}
						janela[iprox][i2].elemento = 'G';
						janela[iprox][i2].velocidade = 2;
					}
				}
			}
		}
	//ESCRITA DA MATRIZ E DELAY PARA PROXIMO INSTANTE T
	escrevaMatriz(janela);
	Sleep(T);
	system("cls"); 
	}
}

//FUNCAO PARA ESCREVER A JANELA(MATRIZ) COM AS GOTAS
void escrevaMatriz(gota** M){
	for(int i = 0;i<MAX_LIN;i++){
		for(int i2 = 0; i2 < MAX_COL; i2++){
			printf("%c", M[i][i2].elemento);
		}
		printf("\n");
	}
}

//FUNCAO QUE ALOCA A MATRIZ
gota** alocarMatriz(){
	gota **M;
	M = malloc(sizeof(gota)*MAX_LIN);
	for(int i = 0;i<MAX_COL;i++){
		M[i] = malloc(sizeof(gota)*MAX_COL);		
	}
	return M;
}

//FUNCAO QUE LE DE UM ARQUIVO DE TEXTO AS COORDENADAS ONDE HA GOTAS E INICIALIZA OS ESPACOS VAZIOS E AS BORDAS DA JANELA
void lerMatriz(gota** janela){
	int a=1,b=1;
	for(int i = 0;i < MAX_LIN;i++){
		for(int i2 = 0;i2 < MAX_COL;i2++){
			janela[i][i2].elemento=' ';
			janela[i][i2].i=i;
			janela[i][i2].i2=i2;
			janela[i][i2].velocidade=0;
			
		}
	}
	int i = 0,i2 = 0;
	for(i = 0;i < MAX_LIN;i++){
		for(i2 = 0;i2 < MAX_COL;i2++){
			if(i==0 || i+1 == MAX_LIN || i2 == 0 || i2+1 == MAX_COL){
				janela[i][i2].elemento='#';
			}
		}
	}
	FILE *arq;
	int elemento;
	arq=fopen("entrada.txt","r");	// leitura do arquivo de texto
	if (arq==NULL) { 
        printf("O arquivo entrada.txt nao existe"); 
        return ; 
    } 
	while (a!=0 && b!= 0){
        fscanf(arq,"%d", &a);
        fscanf(arq,"%d", &b);
        if(a==0 && b==0){
        	break;
		}
        if(a<MAX_LIN-1 && b<MAX_COL-1 && a>=1 && b>=1){
        	janela[a][b].elemento ='G';
        	janela[a][b].velocidade = 1;
        	if(a==1){
        		janela[a][b].velocidade = 2;	
			}
        }
	}	
	return;
}
