#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[10];
    int idade;
    int altura;
} Pessoa;

Pessoa pessoas[10];

void incluir(void *pBuffer);
void buscar(void *pBuffer);
void listar(void *pBuffer);
void apagar(void *pBuffer);

int main() {
    void *pBuffer = malloc(sizeof(int) * 3 + sizeof(char) * 10); // size, for, int_aux, nome_auxiliar
    if(!pBuffer) { 
        printf("erro de memoria inicio\n");
    }
    *(int *)pBuffer = 0;
    // pBuffer = size
    // pBuffer + sizeof(int) = for
    // pBuffer + sizeof(int) * 2 = aux /// escolha |*int_aux
    for(;;){
        printf(" --- Menu ---\n");
        printf("1) Adicionar\n");
        printf("2) Buscar\n");
        printf("3) Listar\n");
        printf("4) Apagar\n");
        printf("5) Sair\n");
        printf("Escolha: ");
        scanf("%d", (int *)(pBuffer + sizeof(int) * 2));
        setbuf(stdin, NULL);

        switch(*(int *)(pBuffer + sizeof(int) * 2)) {
            case 1:
                incluir(pBuffer);
                break;
            case 2:
                buscar(pBuffer);
                break;
            case 3:
                listar(pBuffer);
                break;
            case 4:
                apagar(pBuffer);
                break;
            case 5:
                free(pBuffer);
                exit(0);
            default:
                printf("Opcao Invalida.\n");
                break;
        }
    }
    return 0;
}

void incluir(void *pBuffer) {
    if(*(int *)pBuffer < 10) { 
        printf("Digite o nome: ");
        scanf("%s", pessoas[*(int *)pBuffer].nome);

        printf("Digite a idade: ");
        scanf("%d", &(pessoas[*(int *)pBuffer].idade));

        printf("Digite a altura: ");
        scanf("%d", &(pessoas[*(int *)pBuffer].altura));

        (*(int *)pBuffer)++;
    } else {
        printf("Limite de pessoas atingido.\n");
    }
}

void listar(void *pBuffer) { 
    *(int *)(pBuffer + sizeof(int)) = 0;
    if(*(int *)pBuffer > 0) { 
        while(*(int *)(pBuffer + sizeof(int)) < *(int *)pBuffer) {
            printf("  Nome: %s\n", pessoas[*(int *)(pBuffer + sizeof(int))].nome);
            printf("  Idade: %d\n", pessoas[*(int *)(pBuffer + sizeof(int))].idade);
            printf("  Altura: %d\n", pessoas[*(int *)(pBuffer + sizeof(int))].altura);
            printf("\n");
            (*(int *)(pBuffer + sizeof(int)))++; 
        }
    } else {
        printf("Nenhum nome adicionado.\n");
    }
}

void buscar(void *pBuffer) {
    int *size = pBuffer;
    int *i = pBuffer + sizeof(int);
    int *int_aux = pBuffer + sizeof(int) * 2; 
    char *nome_auxiliar = pBuffer + sizeof(int) * 3;
    *int_aux = 0; // flag encontrou

    if(*size > 0) {
        printf(" - Busca - \n");
        printf("Digite o nome: ");
        scanf("%s", nome_auxiliar);
        for(*i = 0; *i < *size; (*i)++) {
            if(strcmp(pessoas[*i].nome, nome_auxiliar) == 0) {
                (*int_aux)++;
                printf("  Nome: %s\n", pessoas[*i].nome);
                printf("  Nome: %d\n", pessoas[*i].idade);
                printf("  Altura: %d\n", pessoas[*i].altura);
                printf("\n");
            }
        }
    } else {
        printf("Nenhuma pessoa adicionada.\n");
    }
    if(!(*int_aux)) printf("Nome nao encontrado.\n");
}


void apagar(void *pBuffer) { 
    int *size = pBuffer;
    int *i = pBuffer + sizeof(int);
    int *int_aux = pBuffer + sizeof(int) * 2; 
    char *nome_auxiliar = pBuffer + sizeof(int) * 3;
    *int_aux = 0; //flag encontrou

    if(*size > 0) {
        printf(" - Apagar - \n");
        printf("Digite o nome: ");
        scanf("%s", nome_auxiliar);
        for(*i = 0; *i < *size; (*i)++) {
            if(strcmp(pessoas[*i].nome, nome_auxiliar) == 0) {
                (*int_aux)++;
                break; // vai para na posição i = posicao a apagar
            }
        }
        if(*int_aux) {
            if(*size > 1) {
                for(; *i < (*size - 1); (*i)++) {
                    pessoas[*i] = pessoas[*i + 1]; 
                }
            } 
            (*size)--;
            printf("Nome apagado.\n");
        } else {
            printf("Nome nao encontrado.\n");
        }
    } else {
        printf("Nenhuma pessoa adicionada.\n");
    }
} 