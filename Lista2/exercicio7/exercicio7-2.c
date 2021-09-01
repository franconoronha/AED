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
    void *pBuffer = malloc(sizeof(int) * 3); // size, for, escolha , [PESSOA, PESSOA, ....]
    if(!pBuffer) { 
        printf("erro de memoria inicio\n");
    }
    *(int *)pBuffer = 0;
    // pBuffer = size
    // pBuffer + sizeof(int) = for
    // pBuffer + sizeof(int) * 2 = escolha
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
                //buscar(pBuffer);
                break;
            case 3:
                listar(pBuffer);
                break;
            case 4:
                //apagar(pBuffer);
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
    while(*(int *)(pBuffer + sizeof(int)) < *(int *)pBuffer) {
        printf("  Nome: %s\n", pessoas[*(int *)(pBuffer + sizeof(int))].nome);
        printf("  Idade: %d\n", pessoas[*(int *)(pBuffer + sizeof(int))].idade);
        printf("  Altura: %d\n", pessoas[*(int *)(pBuffer + sizeof(int))].altura);
        printf("\n;")
        (*(int *)(pBuffer + sizeof(int)))++; 
    }
}
/*
void buscar(void *pBuffer) {

}
void apagar(void *pBuffer) { 

} */