//KRISTIANO PASINI DE OLIVEIRA
#include<stdio.h>
#include<stdlib.h>
#define vazio -1
struct cel {
 int vet[3];
 struct cel *prox;
 }; 
 typedef struct cel celula;
 
 void insereElemento(celula **lista);
 void imprimeLista(celula* lista);
 void removeElemento(celula** lista);
 void compactaLista(celula** lista);
 int menu();
 static int tamanho;
 
 int main(){
	celula *inicio;
	inicio = NULL;
	int op=0;
	while(op !=5){
		op = menu();
		//SWITCH PARA A CRIACAO DO MENU
		 switch (op){
			case 1:
				insereElemento(&inicio);
				break;	
			case 2:
				removeElemento(&inicio);
				break;
			case 3:
				compactaLista(&inicio);
				break;	
			case 4:
				imprimeLista(inicio);
				break;			
			case 5:
				break;			
			default:
				printf("\n Opcao incorreta");
				break;
		 }
	}
	return 0;
}
//FUNCAO QUE DEFINE O MENU
int menu(){
	int op;
	printf("\n1 - Inserir Elemento");
	printf("\n2 - Remover Elemento");
	printf("\n3 - Compactar Lista");
	printf("\n4 - Imprime Lista");
	printf("\n5 - Encerrar\n\n");
	printf("Digite a escolha: ");
	scanf("%d",&op);
	return op;
}

//FUNCAO PARA INSERIR ELEMENTOS NA LISTA
void insereElemento(celula **lista){
	celula *aux;
	int elemento;
	aux= *lista;
	printf("\nDigite o elemento a ser inserido: ");
	scanf("%d",&elemento);
	if(aux==NULL){
	tamanho+=3;
	aux = (celula*)malloc(sizeof(celula));
	aux->prox=NULL;	
	aux->vet[0]=elemento;
	aux->vet[1]=vazio;
	aux->vet[2]=vazio;
	*lista=aux;
	}
	else {
		int i = 0;
		while(i<=3){
			if(i==3){
				aux=aux->prox;
				i=0;
			}
			if(aux->vet[i]==vazio){
				aux->vet[i]=elemento;
				break;
			}
			else{
				if(aux->prox==NULL && i == 2){
					celula *cel;
					cel = (celula*)malloc(sizeof(celula));
					cel->prox=NULL;
					aux->prox=cel;	
					cel->vet[0]=elemento;
					cel->vet[1]=vazio;
					cel->vet[2]=vazio;
					tamanho+=3;
					break;
				}
			}
		i++;
		}
	}
}

//FUNCAO PARA REMOVER ELEMENTOS DA LISTA
void removeElemento(celula** lista){
	celula* aux,*eleAnterior,*proxElemento;
	aux = *lista;
	eleAnterior=aux;
	int i = 0, n=0, elementosVazios=0;
	if(aux == NULL){
		printf("\nLista Vazia!!\n");
		return;
	}
	proxElemento=aux->prox;
	printf("\nDigite o elemento a ser removido: ");
	scanf("%d",&n);
		while(aux!=NULL){
			if(i==3){
				eleAnterior=aux;
				aux=aux->prox;
				i=0;
				if(aux==NULL){
					printf("\n===Elemento nao encontrado===\n");
					break;
				}
				proxElemento=aux->prox;
			}
			if(aux->vet[i]==n){
				printf("\n===Elemento Removido===\n");
				aux->vet[i]=vazio;
				for(int a=0;a<3;a++){
					if(aux->vet[a]==vazio){
					elementosVazios++;
					}
					if(elementosVazios == 3){
						tamanho-=3;
						if(aux==eleAnterior){
							*lista = proxElemento;
							free(aux);
							return;
						}					
						eleAnterior->prox = proxElemento;
						free(aux);
						return;
					}
				}
				break;
			}
			i++;
		}
}

//FUNCAO PARA COMPACTAR A LISTA
void compactaLista(celula** lista){
	int elementosVazios=0,i=0,i2=0,i3=0;
	if(*lista==NULL){
		printf("\nLista vazia!!\n");
		return;
	}
	celula *aux,*proxEle,*eleAnterior,*aux2;
	eleAnterior = *lista;
	aux = *lista;
	proxEle=aux->prox;
	i3 = tamanho;
	while(i2<i3*i3){
		if(aux->vet[i] == vazio && i!=2){
			aux->vet[i] = aux->vet[i+1];
			aux->vet[i+1] = vazio;
		}
		if(i==2){
			if(eleAnterior != aux)
				eleAnterior=eleAnterior->prox;	
				
			aux = aux->prox;
			if(aux!=NULL && eleAnterior->vet[2] == vazio){	
				eleAnterior->vet[2] = aux->vet[0];
				aux->vet[0] = vazio;
			}	
			i=-1;	
		}
		i++;
		i2++;	
		//SEMPRE QUE PERCORRER A LISTA UMA VEZ A FUNCAO PERCORRE NOVAMENTE PARA LEVAR OS OUTROS ELEMENTOS VAZIOS PARA O FINAL
		if(aux==NULL){
			eleAnterior = *lista;
			aux = *lista;
		}
	}
	//DEPOIS DE JOGAR TODOS OS VAZIOS PARA O FINAL DA LISTA A FUNCAO PERCORRE A LISTA NOVAMENTE PARA DELETAR AS CELULAS CUJOS 3 ELEMENTOS DO VETOR SAO VAZIOS
	aux = *lista;
	eleAnterior = *lista;
	proxEle = aux->prox;
	i=0;
	//SE O PRIMEIRO ELEMENTO DO PRIMEIRO VETOR DA LISTA FOR VAZIO A LISTA EH APAGADA
	if(aux->vet[0]==vazio){
		while(aux!=NULL){
			free(aux);
			aux=aux->prox;
		}
		*lista = NULL;
	}
	else{
		aux=aux->prox;
	}
	while(aux!=NULL){
		if(i==3){
			eleAnterior=eleAnterior->prox;
			aux=aux->prox;
			if(proxEle!=NULL)
				proxEle=proxEle->prox;
								
			i=0;
			elementosVazios = 0;
		}
		if(aux==NULL)
			break;
			
		if(aux->vet[i]==vazio){
			elementosVazios++;
		}
		if(elementosVazios == 3){
			tamanho-=3;
			free(aux);
			eleAnterior->prox=NULL;
			eleAnterior=aux;
			aux=proxEle;
			if(proxEle!=NULL)
			proxEle=proxEle->prox;
							
			i=-1;
			elementosVazios = 0;
		}
		i++;
	}
}

//FUNCAO PARA IMPRIMIR A LISTA
void imprimeLista(celula* lista){
	celula *aux;
	aux = lista;
	if(aux==NULL){
		printf("\nLista Vazia!!\n");
		return;	
	}
	printf("\n=========================\n");
	while(aux!=NULL){
		printf("(%d",aux->vet[0]);
		printf(",%d,",aux->vet[1]);
		printf("%d)-->",aux->vet[2]);
		aux=aux->prox;
	}
	printf("\n=========================\n");
}

