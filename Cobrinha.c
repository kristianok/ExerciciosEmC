#include<windows.h>	
#include<stdlib.h>	
#include <stdio.h>
#include <time.h> 
#include<stdbool.h>
#include <conio.h> 
#define corpo 176  
#define pescoco 177	
#define cabeca 178		
#define tamanho 7 // tamanho da cobra (pode ser alterado)
#define qtdLinhas 30
#define qtdColunas 31 // ultima coluna da matriz preenchida com \n
char M[qtdLinhas][qtdColunas];
int cobraI[tamanho]; // Coordenada do contador i (linha) de cada parte da cobra
int cobraI2[tamanho];	// Coordenada do contador i2 (coluna) de cada parte da cobra
void nascer(){
	bool nasceu = false; // bool usado para confirmar se foi possivel nascer a cobra em uma direção
	int espacoLivreVert,espacoLivreHor;
	 for (int i=0;i<qtdLinhas;i++){
	 	if(nasceu){
	 		break;
	 	}
        for (int i2=0;i2<qtdColunas;i2++){       			
        if(M[i][i2] == 32) {
        	espacoLivreVert++;	// conta a quantidade espaços livres para a cobra nascer
		}
		else {
			espacoLivreVert = 0;
		}
		if(espacoLivreVert >= tamanho){	// se houver espaços suficientes a cobra nasce
        	M[i][i2] = cabeca;
        	M[i][i2-1] = pescoco;
        	cobraI[0] = i ;
			cobraI2[0] = i2;
			cobraI[1] = i ;
			cobraI2[1] = i2-1;
        	for(int a=2;a<= tamanho-1;a++){
        	M[i][i2-a] = corpo;
        	cobraI[a] = i ;
			cobraI2[a] = i2-a;
        	}  				
        	nasceu = true;
        	break;   
		}
	}
}
	if(!nasceu){ // se nao foi possivel nascer em uma direção continua tentando na outra
	 for (int i=0;i<qtdColunas;i++){
	 		if(nasceu){
	 		break;
	 		}
        for (int i2=0;i2<qtdLinhas;i2++){    
		if(M[i2][i] == 32) {
        	espacoLivreHor++;
		}
		else {
			espacoLivreHor = 0;
		}
		if(espacoLivreHor >= tamanho){	
        	M[i2][i] = cabeca;
        	M[i2-1][i] = pescoco;
        	cobraI[0] = i2;
			cobraI2[0] = i;
			cobraI[1] = i2-1 ;
			cobraI2[1] = i;
        	for(int a=2;a<= tamanho-1;a++){
        	M[i2-a][i] = corpo;
        	cobraI[a] = i2-a ;
			cobraI2[a] = i;
        	}  				
        	nasceu = true;
        	break;     
		}
	}
}
}
}
void mostrar(){
	for (int i=0;i<qtdLinhas;i++){
        for (int i2=0;i2<qtdColunas;i2++){   
         printf("%c",M[i][i2]);		// mostrar a arena 30x30 e a cobra por meio de uma matriz
    }
}
}
void movimento(){
int movI, movI2;
bool andou = false; 
int travado = 0;
srand(time(NULL));  
while(!andou){
int r = rand() % 8;																		//  0 1 2
// switch para escolher a direcao pra onde a cobra vai definidos pela seguinte ideia: 		3 C 4    No qual C é a cabeca da cobrinha	
																						//  5 6 7																													
switch(r){												
// cada um dos seguintes cases testa se o local escolhido permite que a cobra ande (32 vazio ou -80, ascii parece ficar negativo pois testei com 176 e nao funcionou
// e printando o valor daquele ponto na matriz retornou -80 o que representa a parte da cobra nao sendo o pescoco)
// os valores 1 -1 e 0 correspondem a mudanca na coordenada da matriz onde a cobra percorre, por exemplo no case 0 a cobra deve se mover na diagonal superior esquerda
// consequentemente o valor daquele ponto em relacao a cabeca da cobra possui indice i (linha) -1 e indice de i2 (coluna) -1 tambem
//	para o ponto da cabeca M[5][5], por exemplo, a diagonal superior esquerda esta em M[4][4]														
case 0:
	if((M[cobraI[0]-1][cobraI2[0]-1] == 32) || (M[cobraI[0]-1][cobraI2[0]-1] == -80)){
	movI = -1;
	movI2 = -1;
	andou = true;
	}
	break;
case 1:
	if((M[cobraI[0]-1][cobraI2[0]] == 32)|| (M[cobraI[0]-1][cobraI2[0]] == -80)){
	movI = -1;
	movI2 = 0; 
	andou = true;
	}
	break;
case 2:
	if((M[cobraI[0]-1][cobraI2[0]+1] == 32)|| (M[cobraI[0]-1][cobraI2[0]+1] == -80)){
	movI = -1;
	movI2 = 1; 
	andou = true;
	}
	break;
case 3:
	if((M[cobraI[0]][cobraI2[0]-1] == 32)|| (M[cobraI[0]][cobraI2[0]-1] == -80)){
	movI = 0;
	movI2 = -1;
	andou = true;
	}
	break;
case 4:
	if((M[cobraI[0]][cobraI2[0]+1] == 32)|| (M[cobraI[0]][cobraI2[0]+1] == -80)){
	movI = 0;
	movI2 = 1;
	andou = true;
	}
	break;
case 5:
	if((M[cobraI[0]+1][cobraI2[0]-1] == 32)|| (M[cobraI[0]+1][cobraI2[0]-1] == -80)){
	movI = 1;
	movI2 = -1;
	andou = true; 
	}
	break;
case 6:
	if((M[cobraI[0]+1][cobraI2[0]] == 32) || (M[cobraI[0]+1][cobraI2[0]] == -80)){
	movI = 1;
	movI2 = 0;
	andou = true; 
}
	break;
case 7:
	if((M[cobraI[0]+1][cobraI2[0]+1] == 32) || (M[cobraI[0]+1][cobraI2[0]+1] == -80)){
	movI = 1;
	movI2 = 1;
	andou = true; 
}
	break;
}
//caso a cobra tenha conseguido andar o resto do corpo e reajustado para seguir a cobra e a ultima coordenada fica em branco																					
	if(andou){	
	if(M[cobraI[tamanho-1]][cobraI2[tamanho-1]]!= M[cobraI[0]][cobraI2[0]]){
		M[cobraI[tamanho-1]][cobraI2[tamanho-1]] = 32;	// volta o ponto para "branco" para que a cobra nao deixe rastros 	
	}
		for(int a = 1; a < tamanho-1; a++){
			M[cobraI[a]][cobraI2[a]] = corpo;	
			}
		M[cobraI[0]][cobraI2[0]] = pescoco;	
		M[cobraI[0]+movI][cobraI2[0]+movI2] = cabeca;
		for(int a = tamanho-1; a >= 1; a--){
			cobraI[a] = cobraI[a-1]; 
			cobraI2[a] = cobraI2[a-1];
		}	
	cobraI[0] += movI;	
	cobraI2[0] += movI2;
}
travado++;
if(travado >= 200){ // caso depois de 200 tentativas nao seja possivel andar, o programa reconhece que a cobra esta presa e reinicia o jogo
	Sleep(2000);
	system("cls"); 
	main();
}
}
}

int main (void){
	srand(time(NULL)); 
	FILE *arq;
	char elemento;
	arq=fopen("obstaculos.txt","r");	// leitura do arquivo de texto
	 for (int i=0;i<qtdLinhas;i++){
        for (int i2=0;i2<qtdColunas;i2++){
            M[i][i2] = fgetc(arq);
            if(M[i][i2] == '0'){
            	M[i][i2] = 32;				// lugares com 0 se tornam caracteres vazios
			}
		}
	}	
	// as bordas da arena sao substituidas por "vidro" neste caso foram utilizados os caracteres ASCII 196 e 179 (barrinhas) 
 	for (int i=0; i < 30;i+=29){
 	    for (int i2=0;i2<qtdColunas-1;i2++){		// vidros horizontais
           	M[i][i2] = 196;						
		}
	}
	for (int i=0; i < 30;i+=29){
 	    for (int i2=0;i2<qtdColunas-1;i2++){
           	M[i2][i] = 179 ;						//vidros verticais
		}
	}
	// troca dos valores 1 dentro da arena por obstaculos aleatorios (barras com diferentes direcoes ou caixas)
	for (int i=0;i<qtdLinhas;i++){
        for (int i2=0;i2<qtdColunas;i2++){
        	if(M[i2][i] == '1'){ 
				int r = rand() % 3;
				if(r == 0){
					M[i2][i] = 254;
				}
				else if(r == 1){
					M[i2][i] = 47;
				}
				else if(r == 2){
					M[i2][i] = 124;
				}
			}
        }
    }
	Sleep(500);
	nascer();
	// flag de parada quando o usuario aperta qualquer tecla no teclado
	while (!kbhit()){
		// atualizacao a cada 500ms da posicao da cobra
		mostrar();
		movimento();
		Sleep(500);
		system("cls"); 
	}
}

