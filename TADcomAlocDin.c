#include <stdio.h>
#include <stdlib.h> 
#include <string.h>	

struct Node{
	int ligacoes;
	char nome[20], tel[10];
	struct Node * prox;
};

typedef struct Node node;



//INICIA UM NÓ APONTANDO PARA NULL
node * lista_inicia(){
	node * LISTA = (node*)malloc(sizeof(node));
	if(!LISTA){
		printf("Não alocada!\n");
		exit(1);
	}
	LISTA->prox = NULL;
	return LISTA;
}

//AUMENTA UM NAS LIGACOES DO NÓ EM QUE HÁ O NOME
void lista_liga(node * LISTA, char * nome){
	node * percorre = LISTA->prox;
	while(percorre!=NULL){
		if(strcmp(percorre->nome, nome) == 0){
			percorre->ligacoes++;
			break;
		}
		percorre = percorre->prox;
	}
}

//INSERE NA LISTA
void lista_insere(node * LISTA, const char * nome, const char * numero, int qnt){
	node * percorre = LISTA;
	node * novo = lista_inicia();

	while(percorre->prox != NULL) percorre = percorre->prox;

	percorre->prox = novo;
	memcpy(novo->nome, nome, strlen(nome)+1);
	memcpy(novo->tel, numero, strlen(numero)+1);
	novo->ligacoes = qnt;
}

//REMOVE DA LISTA
void lista_remove(node * LISTA, char * nome){
	node * atual = LISTA->prox;
	node * anterior = LISTA;

	while(atual!=NULL){
		if(strcmp(atual->nome, nome)==0){
			anterior->prox = atual->prox;
			free(atual);
			break;
		}
		anterior = atual;
		atual = atual -> prox;
	}
}

//IMPRIME LISTA
void lista_imprime(node * LISTA){
	node * percorre = LISTA->prox;

	while(percorre!=NULL){
		printf("%s - %s\n", percorre->nome, percorre->tel);
		percorre = percorre->prox;
	}
}

//RETORNA O TAMANHO DA LISTA
int lista_size(node * LISTA){
	int c=0;
	while(LISTA->prox!=NULL){
		LISTA = LISTA->prox;
		c++;
	}
	return c;
}

//RETORNA UM PONTEIRO PARA UM NÓ EM DETERMINADO INDICE 
node * atPos(node * LISTA, int index){
	int c= 0;
	node * percorre = LISTA;

	while(percorre!=NULL){
		if(c==index){
			return percorre;
		}
		percorre = percorre-> prox;
		c++;
	}
}

//RETORNA O INDICE DE DETERMINADO NÓ
int indexOf(node * LISTA, node * Node){
	int c=0;
	while(LISTA != NULL){
		if(LISTA == Node) return c;
		LISTA = LISTA->prox;
		c++;
	}
}

//TROCA DOIS NÓS DE POSICAO
void node_swipe(node * LISTA, node * nodeA, node * nodeB){
	if(nodeA == nodeB) return;
	int indexA = indexOf(LISTA, nodeA); // INDEX NÓ A
	int indexB = indexOf(LISTA, nodeB); // INDEX NÓ B

	// PONTEIRO PARA O NÓ ANTERIOR AO A
	node * pa = atPos(LISTA, indexA-1); 
	// PONTEIRO PARA O NÓ ANTERIOR AO B
	node * pb = atPos(LISTA, indexB-1);

	pa->prox = nodeB; //ANTERIOR DE A APONTA PARA B
	pb->prox = nodeA; //ANTERIOR DE B APONTA PARA A

	node * aux = nodeA->prox; //SALVA O ENDEREÇO NO QUE A APONTA
	nodeA->prox = nodeB->prox; //A APONTA PARA O PROX DE B
	nodeB->prox = aux; //B APONTA PARA O PROX DE A
}

//BUBBLE SORT
void lista_ordena(node * LISTA){
	int i, j;
	int size = lista_size(LISTA);

	for(i = 0 ; i < size-1; i++){
		for(j = 0 ; j < size -i -1 ; j++){
			node * nodeJ = atPos(LISTA, j+2);
			node * nodeI = atPos(LISTA, j+1);
			if(nodeI->ligacoes < nodeJ->ligacoes){
				node_swipe(LISTA, nodeI, nodeJ);
			}
		}	
	}

}






int main(){
	node * LISTA = lista_inicia();
	lista_insere(LISTA, (char *)"Hermanoteu", (char *)"4523-2248", 300);
	lista_insere(LISTA, (char *)"Oolonéia", (char *)"4523-4887", 299);

	while(1){
		char op;
		char nome[20], tel[10];
		int qntLigacoes;

		scanf(" %c", &op);
		if(op == 'F'){
			lista_ordena(LISTA);
			//printf("\n\n");
			lista_imprime(LISTA);
			return 0;	
		} 
		else if(op == 'L'){
			scanf(" %s", nome);
			lista_liga(LISTA, nome);
		}
		else if(op == 'I'){
			scanf(" %s", nome);
			scanf(" %s", tel);
			scanf(" %d", &qntLigacoes);
			lista_insere(LISTA, nome, tel, qntLigacoes);
		}
		else if(op == 'R'){
			scanf("%s", nome);
			lista_remove(LISTA, nome);
		}
		//else printf("OPÇÃO ERRADA!\n");
	}


}


