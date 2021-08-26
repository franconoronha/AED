#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *incluir(void *pBuffer);
void buscar(void *pBuffer);
void listar(void *pBuffer);
void *apagar(void *pBuffer);

int main() {
    int escolha;
    void *pBuffer = malloc(sizeof(int));
    if(!pBuffer) {
        printf("erro de memoria inicio");
        exit(1);
    }
    *(int *)pBuffer = 0;

    for(;;){
        printf(" --- Menu ---\n");
        printf("1) Adicionar\n");
        printf("2) Buscar\n");
        printf("3) Listar\n");
        printf("4) Apagar\n");
        printf("5) Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        setbuf(stdin, NULL);

        switch(escolha) {
            case 1:
                pBuffer = incluir(pBuffer);
                break;
            case 2:
                buscar(pBuffer);
                break;
            case 3:
                listar(pBuffer);
                break;
            case 4:
                pBuffer = apagar(pBuffer);
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

void *incluir(void *pBuffer){
    char nome[10];
    (*(int *)pBuffer)++;
    pBuffer = realloc(pBuffer, (sizeof(int) + ((*(int *)pBuffer) * (sizeof(nome) + sizeof(int) * 2))));
    printf("Digite o nome: ");
    scanf("%s", nome);
    setbuf(stdin, NULL);
    strcpy((char *)(pBuffer + (sizeof(int) + (((*(int *)pBuffer)- 1) * (sizeof(nome) + sizeof(int) * 2)))), nome);

    printf("Digite a idade: ");
    scanf("%d", (int *)(pBuffer + (sizeof(int) + (((*(int *)pBuffer)- 1) * (sizeof(nome) + sizeof(int) * 2)) + (sizeof(char) * 10))));
    setbuf(stdin, NULL);

    printf("Digite o telefone: ");
    scanf("%d",(int *)(pBuffer + (sizeof(int) + (((*(int *)pBuffer)- 1) * (sizeof(nome) + sizeof(int) * 2)) + (sizeof(char) * 10) + sizeof(int))));
    setbuf(stdin, NULL);

    if(!pBuffer) {
        printf("erro de memoria (incluir 1)");
        exit(1);
    }
    return pBuffer;
}


void buscar(void *pBuffer){
    char nome_comparar[10];
    int i, flag = 0;

    if(*(int *)pBuffer > 0) { 
        printf("Buscar contato: ");
        scanf("%s", nome_comparar);
        for(i = 0; i < *(int *)pBuffer; i++) {
            if(strcmp(nome_comparar, (char *)(pBuffer + (sizeof(int) + (i * (sizeof(char) * 10 + sizeof(int) * 2))))) == 0) {
                flag++;
                printf("\tNome: %s\n", (char *)(pBuffer + (sizeof(int) + (i * (sizeof(char) * 10 + sizeof(int) * 2)))));
                printf("\tIdade: %d\n", *(int *)(pBuffer + (sizeof(int) + (i * (sizeof(char) * 10 + sizeof(int) * 2)) + sizeof(char) * 10)));
                printf("\tTelefone: %d\n", *(int *)(pBuffer + (sizeof(int) + (i * (sizeof(char) * 10 + sizeof(int) * 2)) + sizeof(char) * 10 + sizeof(int))));
                printf("\n");
            }
        }
        if(!flag) printf("Nome nao foi encontrado.\n");
   } else {
       printf("Nenhum contato na agenda.\n");
   }
}

void listar(void *pBuffer){
   int i;
   if(*(int *)pBuffer > 0) { 
       for(i = 0; i < *(int *)pBuffer; i++) {
           printf("\tNome: %s\n", (char *)(pBuffer + (sizeof(int) + (i * (sizeof(char) * 10 + sizeof(int) * 2)))));
           printf("\tIdade: %d\n", *(int *)(pBuffer + (sizeof(int) + (i * (sizeof(char) * 10 + sizeof(int) * 2)) + sizeof(char) * 10)));
           printf("\tTelefone: %d\n", *(int *)(pBuffer + (sizeof(int) + (i * (sizeof(char) * 10 + sizeof(int) * 2)) + sizeof(char) * 10 + sizeof(int))));
           printf("\n");
       }
   } else {
       printf("Nenhum contato na agenda.\n");
   }
}


void *apagar(void *pBuffer){
    char nome_apagar[10];
    int i, encontrou = 0, pos = -1;
    if(*(int *)pBuffer > 0) { 
        printf("Buscar contato: ");
        scanf("%s", nome_apagar);

        for(i = 0; i < *(int *)pBuffer; i++) {
           if(strcmp(nome_apagar, (char *)(pBuffer + (sizeof(int) + (i * (sizeof(char) * 10 + sizeof(int) * 2))))) == 0) {
                encontrou++;
                pos = i;
                break;
            }
       }

        if(encontrou) { 
            if(*(int *)pBuffer == 1){
                *(int *)pBuffer = 0;
                pBuffer = realloc(pBuffer, sizeof(int));
                if(!pBuffer) {
                    printf("erro de memoria apagar1");
                    exit(1);
                }
            } else {
                for(i = pos; i < (*(int *)pBuffer) - 1; i++) {
                    strcpy((char *)(pBuffer + (sizeof(int) + (pos * (sizeof(char) * 10 + sizeof(int) * 2)))), (char *)(pBuffer + (sizeof(int) + ((pos + 1) * (sizeof(char) * 10 + sizeof(int) * 2)))));
                    *(int *)(pBuffer + (sizeof(int) + (pos * (sizeof(char) * 10 + sizeof(int) * 2)) + sizeof(char) * 10)) = *(int *)(pBuffer + (sizeof(int) + ((pos + 1) * (sizeof(char) * 10 + sizeof(int) * 2)) + sizeof(char) * 10));
                    *(int *)(pBuffer + (sizeof(int) + (pos * (sizeof(char) * 10 + sizeof(int) * 2)) + sizeof(char) * 10 + sizeof(int))) =  *(int *)(pBuffer + (sizeof(int) + ((pos + 1) * (sizeof(char) * 10 + sizeof(int) * 2)) + sizeof(char) * 10 + sizeof(int)));
                }
                (*(int *)pBuffer)--;
                pBuffer = realloc(pBuffer, (sizeof(int) + ((*(int *)pBuffer) * (sizeof(char) * 10 + sizeof(int) * 2))));
                printf("Contato apagado.\n");
                if(!pBuffer) {
                    printf("erro de memoria apagar2");
                    exit(1);
                }
            }
        } else {
            printf("Nome nao foi encontrado.\n");
        }

    } else {
       printf("Nenhum contato na agenda.\n");
    }
   return pBuffer;
}
