#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo nodo;
struct nodo{
    int valor;
    nodo* nEsquerda;
    nodo* nDireita;
};

void insere(int valor, nodo** raiz);
int altura(nodo* raiz);
int FB(nodo* raiz);
int verificaAVL(nodo* raiz);
void RSE(nodo** raiz);
void RSD(nodo** raiz);
void balanceia(nodo** raiz);

int main() {
    srand(time(0));
    nodo* raiz = NULL;
    int num_nodos, i;
    int a;
    printf("Escolha a quantidade de nodos da arvore AVL: ");
    scanf("%d", &num_nodos);

    for(i = 0; i < num_nodos; i++) {
        a = rand();
        printf("%d ", a);
        insere(a, &raiz);
    }

    printf("\nResultado: %d", verificaAVL(raiz));
    return 0;
}

void insere(int valor, nodo** raiz) {
    if((*raiz) == NULL) {
        (*raiz) = (nodo*) malloc(sizeof(nodo));
        (*raiz)->valor = valor;
        (*raiz)->nEsquerda = NULL;
        (*raiz)->nDireita = NULL;
        return;
    }
    if(valor < (*raiz)->valor) {
        insere(valor, &((*raiz)->nEsquerda));
        balanceia(raiz);
        return;
    }
    else if(valor > (*raiz)->valor) {
        insere(valor, &((*raiz)->nDireita));
        balanceia(raiz);
        return;
    } else {
        printf("Erro: valor ja consta na arvore.\n");
    }
}

int altura(nodo* raiz) {
    int a_Esq, a_Dir;

    if(raiz == NULL) return 0;

    a_Esq = altura(raiz->nEsquerda);
    a_Dir = altura(raiz->nDireita);

    if(a_Esq > a_Dir) {
        return (a_Esq + 1);
    } else {
        return (a_Dir + 1);
    }
}

int FB(nodo* raiz) {
    if(raiz == NULL) return 0;
    
    return altura(raiz->nEsquerda) - altura(raiz->nDireita);
}

int verificaAVL(nodo* raiz) {
    int fb;
    if (raiz == NULL) return 1;
    
    if (!verificaAVL(raiz->nEsquerda)) return 0;
    if (!verificaAVL(raiz->nDireita)) return 0;

    fb = FB(raiz);
    if ((fb > 1) || (fb < -1) ){
        return 0;
    } else {
        return 1;
    }
}

void RSE(nodo** raiz) {
    nodo* aux;
    aux = (*raiz)->nDireita;
    (*raiz)->nDireita = aux->nEsquerda;
    aux->nEsquerda = (*raiz);
    (*raiz) = aux;
}

void RSD(nodo** raiz) {
    nodo *aux;
    aux = (*raiz)->nEsquerda;
    (*raiz)->nEsquerda = aux->nDireita;
    aux->nDireita = (*raiz);
    (*raiz) = aux;
}

void balanceia(nodo** raiz) {
    int fb = FB(*raiz);
    if(fb > 1) {
        if(FB((*raiz)->nEsquerda) < 0) {
            RSE(&((*raiz)->nEsquerda));
            RSD(raiz);
        } else {
            RSD(raiz);
        }
    } else if(fb < 0) {
        if(FB((*raiz)->nDireita) > 0) {
            RSD(&((*raiz)->nDireita));
            RSE(raiz);
        } else {
            RSE(raiz);
        }
    }
}