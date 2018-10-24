
#include <stdio.h>

using namespace std;

void enqueue(int fila[], int elemento);
void dequeue(int fila[]);
bool empty(int fila[]);

int tamanho;
int uso = 0;

int main(){
	
	int leitura;
	
	printf("Digite o tamanho da fila:\n");
	scanf("%d", &tamanho);
	
	int fila[tamanho];
	
	do{
	printf("\nDigite uma das opcoes para fazer na fila:\n0 - finalizar\n1 - inserir elemento\n2 - retirar\n3 - testar se e vazia\n");
	scanf("%d", &leitura);
	
	if(leitura == 1){
		printf("\nInforme o elemento a ser inserido: ");
		scanf("%d", &leitura);
	
		enqueue(fila, leitura);
	}else{
		if(leitura == 2){
			dequeue(fila);
		}else{
			if(leitura == 3){
				if(empty(fila)){
					printf("fila cheia\n");
				}else{
					printf("fila vazia\n");
				}
			}
		}
	}
	
	}while(leitura);
	
	
}

void enqueue(int fila[], int elemento){
	if(uso == tamanho){
		printf("Nao e possivel inserir elemento, fila cheia\n");
	}else{
		fila[uso++] = elemento;
		printf("O elemento %d foi inserido\n", elemento);
	}
}

void dequeue(int fila[]){
	if(uso == 0){
		printf("\nNao e possivel retirar elemnto, pilha vazia\n");
	}else{
		printf("\no elemento %d foi retirado\n", fila[0]);
		for(int i=1; i<uso; i++){
			fila[i-1] = fila[i];
		}
		uso--;
	}
}
bool empty(int fila[]){
	return uso;
}
