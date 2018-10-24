/*Igor Duarte
 * implementaçao pilha meio bost
 */
 
 #include <stdio.h>
 
 using namespace std;
 
 void push(int pilha[], int valor);
 void pop(int pilha[]);
 bool empty(int pilha[]);
 
 int uso = 0;
 int tamanho = 0;
 
 int main(){
	 int leitura, elemento;
	 
	 printf("Informe o tamanho maximo da pilha: ");
	
	 scanf("%d", &tamanho);
	 
	 int pilha[tamanho+1];
	 
	 do{
		 printf("\n///////////////////////////////////////////////////////////\n");
		 printf("Escolha uma das opcoes:\n0 - finalizar\n1 - acrescentar elemento\n2 - retirar elemento\n3 - testar se é vazia:\n");
		 printf("\n///////////////////////////////////////////////////////////\nopcao: ");
		 scanf("%d", &leitura);
		 
		 if(leitura == 1){
			 printf("Informe o elemento para acrescentar:\n");
			 scanf("%d", &elemento);
			 
			 push(pilha, elemento);
		 }else{
			 if(leitura == 2){
				 pop(pilha);
			 }else{
				 if(leitura == 3){
					 if(empty(pilha)){
						 printf("\nPilha vazia\n");
					 }else{
						 printf("\nPilha nao é vazia\n");
					 }
				 }
			}
		}
		 
		 
	 }while(leitura);
 
}


 void push(int pilha[], int valor){
	 
	 if(uso == tamanho){
		 printf("\nPilha cheia, nao é possivel adicionar elemento\n");
	 }else{
		pilha[uso++] = valor;
		printf("\nvalor %d acrescentado a pilha\n", valor);
	}
 }


 void pop(int pilha[]){
	 if(empty(pilha)){
		 printf("\nPilha vazia, nao é possivel retirar elemento\n");
	 }else{
		 printf("\nelemento retirado %d\n", pilha[--uso]);
	 }
 }
 
 bool empty(int pilha[]){
	 return !uso;
 }
