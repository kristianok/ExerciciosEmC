#include <stdio.h>

int main () {
	int qtd100, qtd50, qtd20, qtd10,saque100,saque50,saque20,saque10;
	int resto,saque;
	// Leituta da quantidade de cada uma das cedulas no caixa
	printf("Digite a quantidade de cedulas de 100 reais do caixa \n");
	scanf("%d",&qtd100);
	printf("Digite a quantidade de cedulas de 50 reais do caixa \n");
	scanf("%d",&qtd50);
	printf("Digite a quantidade de cedulas de 20 reais do caixa \n");	
	scanf("%d",&qtd20);
	printf("Digite a quantidade de cedulas de 10 reais do caixa \n");
	scanf("%d",&qtd10);
	printf("Digite o valor a ser sacado \n");
	scanf("%d",&saque);
	//Definição do flag de parada para o saque = 0
    while(saque!=0){
    	resto = saque;
    	//Calculo da quantidade de notas de 100 reais utilizadas (menor quantidade possível de notas)
   		saque100 = resto / 100;
   		while (saque100 > qtd100){
   			//Caso não haja o suficiente de notas de 100 para o modelo "perfeito" o restante do valor é liberado para ser composto por cedulas de outros valores
   			saque100 -= 1;
	   }
		resto = resto - saque100 * 100;
		//Calculo da quantidade de notas de 50 reais utilizadas (menor quantidade possível de notas)
   		saque50 = resto / 50;
   		while (saque50 > qtd50){
   			//Caso não haja o suficiente de notas de 100 para o modelo "perfeito" o restante do valor é liberado para ser composto por cedulas de outros valores
   			saque50 -= 1;
	   }
		resto -= saque50 * 50;
		//Calculo da quantidade de notas de 20 reais utilizadas (menor quantidade possível de notas)
   		saque20 = resto / 20;
   		while (saque20 > qtd20){
   			//Caso não haja o suficiente de notas de 100 para o modelo "perfeito" o restante do valor é liberado para ser composto por cedulas de outros valores
   			saque20 -= 1;
	   }
 		resto -= saque20 * 20;
 		//Calculo da quantidade de notas de 10 reais utilizadas (menor quantidade possível de notas)
   		saque10 = resto / 10;
    	while (saque10 > qtd10){
    		//Caso não haja o suficiente de notas de 100 para o modelo "perfeito" o restante do valor é liberado para ser composto por cedulas de outros valores
   			saque10 -= 1;
	    }
   		resto -= saque10 * 10;
   		//Teste para descobrir se essas notas são capazes de compor o saque como um todo
   		if(resto != 0){
   			//Definição do caso no qual o saque seja possível mas a quantidade de notas do caixa não seja suficiente para compor o valor do saque
   			if(saque100 == qtd100 && saque50 == qtd50 && saque20 == saque20 && saque10 == qtd10){
   			    printf("Nao ha saldo suficiente para o saque");
			   }
			   //Caso com valores da unidade diferente de 0. Pois não é possível formar valores como 365 através destas cédulas
			   else {
   				    printf("Nao ha cedulas suficientes para compor o saque solicitado");
	           }
     	}
   		else {
   		//Apresentacao de como o saque foi realizado
	   	printf("O saque de %d reais e dado por: \n",saque);
	   
	   	if(saque100 != 0){
	   		printf("%d nota",saque100);
	   		if(saque100 != 1){
	   			printf("s");	
			   }
			printf(" de 100 \n");
		   }
		if(saque50 != 0){
	   		printf("%d nota",saque50);
	   		if(saque50 != 1){
	   			printf("s");	
			   }
			printf(" de 50 \n");
		   }
		   
		if(saque20 != 0){
	   		printf("%d nota",saque20);
	   		if(saque20 != 1){
	   			printf("s");	
			   }
			printf(" de 20 \n");
		   }
		if(saque10 != 0){
	   		printf("%d nota",saque10);
	   		if(saque10 != 1){
	   			printf("s");	
			   }
			printf(" de 10 \n");
		   }
		//Retirada das notas utilizas no saque da totalidade disponível no caixa
	   	qtd100 -= saque100;
	   	qtd50 -= saque50;
	   	qtd20 -= saque20;
	  	qtd10 -= saque10;
	    }
	    printf("\nCedulas disponiveis: 100: %d, 50: %d, 20: %d, 10: %d",qtd100,qtd50,qtd20,qtd10);
	    printf("\nDigite o valor a ser sacado \n");
	    scanf("%d",&saque);
	}
}
			
