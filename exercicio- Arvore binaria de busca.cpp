//Exercício de implementar uma arvore binária de busca,AUTIERUS.
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

typedef struct sNo{
	struct sNo *pai;
	struct sNo *esq;
	struct sNo *dir;
	int dado;
}No;
 
//Prototipação
No* criaNo(int, No*);
No* insereNaArvore(No*, No*, int);
No* removeNaArvore(No*, int);
void preOrdem(No*);
void emOrdem(No*);
void posOrdem(No*);
int lerArvore(No*, int);
int altura(No*);
No* buscaNoDir(No*);
No* buscaNo(No*, int);
No* removeNodoUmFilho(No*);

int main(){
	No* raiz;
	raiz = insereNaArvore(NULL, NULL, 15);
	insereNaArvore(raiz, NULL, 25);
	insereNaArvore(raiz, NULL, 35);
	insereNaArvore(raiz, NULL, 45);
	insereNaArvore(raiz, NULL, 65);
	insereNaArvore(raiz, NULL, 55);
	insereNaArvore(raiz, NULL, 44);
	insereNaArvore(raiz, NULL, 34);
	insereNaArvore(raiz, NULL, 24);
	insereNaArvore(raiz, NULL, 10);
	insereNaArvore(raiz, NULL, 15);
	removeNaArvore(raiz, 25);
	removeNaArvore(raiz, 35);
	removeNaArvore(raiz, 15);
	insereNaArvore(raiz, NULL, 42);
	insereNaArvore(raiz, NULL, 40);
	insereNaArvore(raiz, NULL, 43);
	removeNaArvore(raiz, 44);
	insereNaArvore(raiz, NULL, 60);
	insereNaArvore(raiz, NULL, 70);
	insereNaArvore(raiz, NULL, 50);
	insereNaArvore(raiz, NULL, 67);
	insereNaArvore(raiz, NULL, 64);
	removeNaArvore(raiz, 65);
	
	printf("\n");
	lerArvore(raiz, 1);
	printf("\n..........................................................................");
	printf("\n");
	lerArvore(raiz, 2);
	
	return 0;	
}

No* criaNo(int dado, No* pai){
	No* nodo;
	nodo = (No*)malloc(sizeof(No));
	if(nodo == NULL)
		return NULL;
	else{
		nodo->pai = pai;
		nodo->esq = NULL;
		nodo->dir = NULL;
		nodo->dado = dado;
	}
	return nodo;
}

No* insereNaArvore(No* nodo, No* pai, int dado){
	if(nodo == NULL){
		nodo =criaNo(dado, pai);	
		return nodo;
	}else{
		if(dado <= nodo->dado){
			nodo->esq = insereNaArvore(nodo->esq, nodo, dado);
		}else{
			nodo->dir = insereNaArvore(nodo->dir, nodo, dado);		
		}
		return nodo;		
	}
}

No* removeNaArvore(No* nodo, int dado){
	No* aux;

	if(nodo == NULL)
		return NULL;
	else{
		if(nodo->dado == dado){
			if((nodo->esq == NULL) && (nodo->dir == NULL)){
					
				free(nodo);
				return NULL;
			}else{
				if((nodo->esq != NULL) && (nodo->dir != NULL)){
						aux = buscaNoDir(nodo->esq);
						nodo->dado = aux->dado;
						aux->dado = dado;
						nodo->esq = removeNaArvore(nodo->esq, dado);
						return nodo;	
				}else{
					aux = removeNodoUmFilho(nodo);
					return aux;		
				} 
			}
		}
		if(nodo->dado < dado) 
			nodo->dir = removeNaArvore(nodo->dir, dado);
		else
			nodo->esq = removeNaArvore(nodo->esq, dado);
		return nodo;
	}
	
}

int lerArvore(No* nodo, int op){
	if((op < 1) || (op > 4)){
		printf("As opcoes sao apenas os numeros 1, 2, 3 e 4");
	}else{

		switch(op){
			case 1:
				preOrdem(nodo);
				break;
			case 2:
				emOrdem( nodo);	
				break;
			case 3:
				posOrdem(nodo);
				break;
			case 4:
				emOrdem(nodo);
				printf("\n");
				preOrdem(nodo);
				printf("\n");
				posOrdem(nodo);	
				break;	
		}		
	}
	return op;
}

void preOrdem(No* nodo){
	printf("%i, ", nodo->dado);
	if(nodo->esq !=NULL)
		preOrdem(nodo->esq);
		
	if(nodo->dir != NULL)
		preOrdem(nodo->dir);		
}

void emOrdem(No* nodo){
    if (nodo->esq !=NULL)
	    emOrdem(nodo->esq);
	    
	printf("%i, ", nodo->dado);
	if (nodo->dir != NULL)
	    emOrdem(nodo->dir);
}

void posOrdem(No* nodo){
	if(nodo->esq !=NULL)
		posOrdem(nodo->esq);
		
	if(nodo->dir != NULL)
		posOrdem(nodo->dir);
		
	printf("%i, ", nodo->dado);
}

int altura(No* nodo){
	if(nodo == NULL){
		return -1;
	}else{
		int esq = altura(nodo->esq);
		int dir = altura(nodo->dir);
		if(esq > dir)
			esq + 1;
		else
			dir + 1;
	}
}

No* buscaNo(No* nodo, int dado){
	if(nodo != NULL){
		if(nodo->dado == dado)
			return nodo;
		else if(dado < nodo->dado)
			return buscaNo(nodo->esq, dado);
		else
			return buscaNo(nodo->dir, dado);
	}
	return NULL;
}

No* buscaNoDir(No* nodo){  //Função pecorrer e encontra o nodo  mais a direita.
	if(nodo->dir != NULL)
		buscaNoDir(nodo->dir);
	else
		return nodo;	
}

No* removeNodoUmFilho(No* nodo){   //Remove nodo quando tem apenas um filho.
	No* aux;
	if(nodo->esq != NULL)
		aux = nodo->esq;
	else
		aux = nodo->dir;
	free(nodo);
	return aux;
}






