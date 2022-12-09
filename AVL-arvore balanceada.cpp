//Exercício de implementar uma árvore binária de busca balanceada\AUTIERUS.
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

typedef struct sNo{
	struct sNo *pai;
	struct sNo *esq;
	struct sNo *dir;
	int altura;
	int dado;
}No;
 
//Prototipação
No* criaNo(int, No*);
No* insereNaArvore(No*, No*, int);
No* removeNaArvore(No*, int);
No* removeNodoUmFilho(No*);
void preOrdem(No*);
void emOrdem(No*);
void posOrdem(No*);
void lerArvore(No*, int);
int maior(int,int);
int fatorDeBalanceamento(No*);
No* buscaNoDir(No*);
int altura(No*);
int alturaDoNo(No*);
No* rotacaoEsq(No*);
No* rotacaoDir(No*);
No* rotacaoDirEsq(No*);
No* rotacaoEsqDir(No*);
No* balancear(No*);

int main(){
	No* raiz;
	raiz = insereNaArvore(NULL, NULL, 15);
	raiz = insereNaArvore(raiz, NULL, 25);
	raiz = insereNaArvore(raiz, NULL, 35);
	raiz = insereNaArvore(raiz, NULL, 45);
	raiz = insereNaArvore(raiz, NULL, 65);
	raiz = insereNaArvore(raiz, NULL, 55);
	raiz = insereNaArvore(raiz, NULL, 44);
	raiz = insereNaArvore(raiz, NULL, 34);
	raiz = insereNaArvore(raiz, NULL, 24);
	raiz = insereNaArvore(raiz, NULL, 10);
	raiz = insereNaArvore(raiz, NULL, 15);
	raiz = removeNaArvore(raiz, 25);
	raiz = removeNaArvore(raiz, 35);
	raiz = removeNaArvore(raiz, 15);
	raiz = insereNaArvore(raiz, NULL, 42);
	raiz = insereNaArvore(raiz, NULL, 40);
	raiz = insereNaArvore(raiz, NULL, 43);
	raiz = removeNaArvore(raiz, 44);
	raiz = insereNaArvore(raiz, NULL, 60);
	raiz = insereNaArvore(raiz, NULL, 70);
	raiz = insereNaArvore(raiz, NULL, 50);
	raiz = insereNaArvore(raiz, NULL, 67);
	raiz = insereNaArvore(raiz, NULL, 64);
	raiz = removeNaArvore(raiz, 65);
	
	printf("\n");
	lerArvore(raiz, 1);
	printf("\n.......................................................");
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
		nodo->altura = 0;
	}
	return nodo;
}

No* insereNaArvore(No* nodo, No* pai, int dado){
	if(nodo == NULL){
		nodo =criaNo(dado, pai);	
		return nodo;
	}else{
		if(dado >= nodo->dado){
				nodo->dir = insereNaArvore(nodo->dir, nodo, dado);
		}else{
				nodo->esq = insereNaArvore(nodo->esq, nodo, dado);
		}		
	}
	nodo->altura = maior(alturaDoNo(nodo->esq), alturaDoNo(nodo->dir)) + 1;
	
	nodo = balancear(nodo);	
	return nodo;
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
	}
	nodo->altura = maior(alturaDoNo(nodo->esq), alturaDoNo(nodo->dir)) + 1;
	
	nodo = balancear(nodo);
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

void lerArvore(No* nodo, int op){
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

No* buscaNoDir( No* nodo){
	if(nodo->dir == NULL)
		return nodo;
	else
		buscaNoDir(nodo->dir);	
}

int maior(int dir, int esq){
	if(dir > esq)
		return dir;
	else
		return esq;	
}

int alturaDoNo(No* no){
	if(no == NULL)
		return -1;
	else
		return no->altura;
}

int fatorDeBalanceamento(No* no){
	int  aux;
	if(no != NULL){
		aux = alturaDoNo(no->esq) - alturaDoNo(no->dir);
		return aux;
	}else
		return 0;
}

No* rotacaoEsq(No* raiz){
	No* a;
	No* b;
	a = raiz->dir;
	if(a->esq != NULL ){
		b = a->esq;
		a->esq = raiz;
		raiz->dir = b;	
	}else{
		a->esq = raiz;
		raiz->dir = NULL;
	}
	
	
	raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;
	a->altura = maior(alturaDoNo(a->esq), alturaDoNo(a->dir)) + 1;
	return a;
}

No* rotacaoDir(No* raiz){
	No* a;
	No* b;
	a = raiz->esq;
	b = a->dir;
	
	
	a->dir = raiz;
	raiz->esq = b;
	
	raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;
	a->altura = maior(alturaDoNo(a->esq), alturaDoNo(a->dir)) + 1;
	return a;
}

No* rotacaoDirEsq(No* no){
	No* aux;
	no->dir = rotacaoDir(no->dir);
	aux = rotacaoEsq(no);
	return aux;
}

No* rotacaoEsqDir(No* no){
	No* aux;
	no->esq = rotacaoEsq(no->esq);
	aux = rotacaoDir(no);
	return aux;
}

No* balancear(No* nodo){
	int aux = fatorDeBalanceamento(nodo);
	
	if(aux < -1 && fatorDeBalanceamento(nodo->dir) <=0) //rotação para esquerda
		nodo = rotacaoEsq(nodo);
	else if (aux > 1 && fatorDeBalanceamento(nodo->esq)>=0) // rotação para esquerda
		nodo = rotacaoDir(nodo);
	else if (aux > 1 && fatorDeBalanceamento(nodo->esq) < 0){ // rotação dupla para esquerda
		nodo = rotacaoEsqDir(nodo);
	}else if (aux < -1 && fatorDeBalanceamento(nodo->dir) > 0) // rotação dupla para direira
	 nodo = rotacaoDirEsq(nodo);
	
	return nodo;
}


