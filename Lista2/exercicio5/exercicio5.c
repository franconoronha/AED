#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[30];
    int idade;
    int altura;
} Pessoa;

Pessoa* adicionar(Pessoa *pessoas, int *size);
void listar(Pessoa *pessoas, int size);

int main() {
    Pessoa *pessoas = NULL;
    int size = 0, escolha;

    for(;;) {
        printf("Deseja adicionar uma pessoa? (1 - SIM | 0 - NAO): ");
        scanf("%d", &escolha);
        setbuf(stdin, NULL);

        switch(escolha) {
            case 1:
                pessoas = adicionar(pessoas, &size);
                break;
            case 0:
                listar(pessoas, size);
                free(pessoas);
                exit(0);
            default:
                printf("Opcao invalida.");
                break;
        }
    }
    return 0;
}

Pessoa* adicionar(Pessoa *pessoas, int *size) {
    (*size)++;
    pessoas = realloc(pessoas, (*size) * sizeof(Pessoa));
    if(!pessoas) { 
        printf("erro de memoria1!");
    }

    printf("Digite o nome: ");
    scanf("%s", (pessoas + ((*size - 1)* sizeof(Pessoa)))->nome);

    printf("Digite o idade: ");
    scanf("%d", &(pessoas + ((*size - 1)* sizeof(Pessoa)))->idade);

    printf("Digite o altura: ");
    scanf("%d", &(pessoas + ((*size - 1)* sizeof(Pessoa)))->altura);

    return pessoas;
}

void listar(Pessoa *pessoas, int size) {
    int i;
    if(size > 0) {
        printf("  --- Lista de Pessoas ---\n");
        for(i = 0; i < size; i++) {
            printf("%d) Nome: %s\n", (i + 1), (pessoas + (i * sizeof(Pessoa)))->nome);
            printf("Idade: %d\n", (pessoas + (i * sizeof(Pessoa)))->idade);
            printf("Altura: %d\n", (pessoas + (i * sizeof(Pessoa)))->altura);
            printf("\n");
        }
    } else {
        printf("Nenhum nome adicionado.");
    }
}