#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(void *pBuffer);
void listar(void *pBuffer);
void empty(void *pBuffer);
void buscar(void *pBuffer);
void apagar(void *pBuffer);

int main() {
    void *pBuffer = malloc(sizeof(void *) * 2 + sizeof(int) + sizeof(char) * 10);
    // fim | inicio | escolha | size | nome_apagar/busscar    *(void **)pBuffer = NULL;
    *(void **)(pBuffer + sizeof(void *)) = NULL;

    if(!pBuffer) {
        printf("Erro de memoria: pBuffer\n");
        exit(0);
    }

    for(;;) {
        printf(" --- Menu ---\n");
        printf("1) Adicionar\n");
        printf("2) Buscar\n");
        printf("3) Listar\n");
        printf("4) Apagar\n");
        printf("5) Sair\n");
        printf("Escolha: ");
        scanf("%d", (int *)(pBuffer + sizeof(void *) * 2));
        setbuf(stdin, NULL);

        switch(*(int *)(pBuffer + sizeof(void *) * 2)) {
            case 1:
                push(pBuffer);
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
                if(*(void **)pBuffer != NULL){
                    empty(pBuffer);
                } 
                free(pBuffer);
                exit(0);
            default:
                printf("Opcao Invalida.\n");
                break;
        }
    }
    return 0;
}

void push(void *pBuffer){
    void *novaPessoa = malloc(sizeof(void *) * 2 + sizeof(char) * 10 + sizeof(int) * 2);
    // anterior | prox | nome | idade | telefone
    if(!novaPessoa) {
        printf("Erro memoria: nodo\n");
        exit(0);
    }
    *(void **)novaPessoa = NULL;
    *(void **)(novaPessoa + sizeof(void *)) = NULL;
    void *ant_q = NULL;
    void *q = *(void **)pBuffer;
    void *inicio = *(void **)(pBuffer + sizeof(void *));

    char *nome = (char *)(novaPessoa + sizeof(void *) * 2); 
    char *nome_q = NULL;

    printf("Digite o nome: ");
    scanf("%s", (char *)(novaPessoa + sizeof(void *) * 2));
    setbuf(stdin, NULL);

    printf("Digite a idade: ");
    scanf("%d", (int *)(novaPessoa + sizeof(void *) * 2 + sizeof(char) * 10));
    setbuf(stdin, NULL);

    printf("Digite o telefone: ");
    scanf("%d", (int *)(novaPessoa + sizeof(void *) * 2 + sizeof(char) * 10 + sizeof(int)));
    setbuf(stdin, NULL);

   if(*(void **)pBuffer == NULL) {
       *(void **)pBuffer = novaPessoa;
       *(void **)(pBuffer + sizeof(void *)) = novaPessoa;
   } else {
        while(q != NULL) {
            nome_q = (char *)(q + sizeof(void *) * 2);
            if(strcmp(nome, nome_q) >= 0) {
                break;
            }
            q = *(void **)(q + sizeof(void *));
        }
        if(q == NULL) {
            *(void **)novaPessoa = inicio;
            *(void **)(inicio + sizeof(void *)) = novaPessoa;
            *(void **)(pBuffer + sizeof(void *)) = novaPessoa;
        } else {
            ant_q = *(void **)q;
            if(ant_q == NULL) {
                *(void **)pBuffer = novaPessoa;
            } else {
                *(void **)(ant_q + sizeof(void *)) = novaPessoa;
            }
            *(void **)novaPessoa = ant_q;
            *(void **)(novaPessoa + sizeof(void *)) = q;
            *(void **)q = novaPessoa;            
        }
   }
}

void listar(void *pBuffer) {
    void *q = *(void **)(pBuffer + sizeof(void *));

    if(*(void **)pBuffer == NULL) {
        printf("Agenda vazia.\n");
    } else {
        while(q != NULL) {
            printf("Nome: %s\n", (char *)(q + sizeof(void *)  * 2));
            printf("Idade: %d\n", *(int *)(q + sizeof(void *) * 2 + sizeof(char) * 10));
            printf("Telefone: %d\n", *(int *)(q + sizeof(void *) * 2 + sizeof(char) * 10 + sizeof(int)));
            printf("\n");
            q = *(void **)(q);
        }
    }
}

void empty(void *pBuffer) {
    void *q = *(void **)(pBuffer + sizeof(void *));
    void *p = NULL;

    while(q != NULL) {  
        p = q;
        q = *(void **)(q);
        free(p);
    }
}

void buscar(void *pBuffer) {
    void *q = *(void **)(pBuffer + sizeof(void *));
    char *nome_q;
    char *nome_busca = (char *)(pBuffer + sizeof(void *) * 2 + sizeof(int));

    if(*(void **)pBuffer == NULL) {
        printf("Agenda vazia.\n");
    } else {
        printf("Buscar contato: ");
        scanf("%s", nome_busca);

        while(q != NULL) {  
            nome_q = (char *)(q + sizeof(void *) * 2);
            if(strcmp(nome_q, nome_busca) == 0) {
                printf("Nome: %s\n", nome_q);
                printf("Idade: %d\n", *(int *)(q + sizeof(void *) * 2 + sizeof(char) * 10));
                printf("Telefone: %d\n\n", *(int *)(q + sizeof(void *) * 2 + sizeof(char) * 10 + sizeof(int)));
                break;
            }
            q = *(void **)(q);
        }

        if(q == NULL) {
            printf("Contato nao encontrado.\n");
        }
    }
}

void apagar(void *pBuffer) {
    void *q = *(void **)(pBuffer + sizeof(void *));
    void *prox_q;
    void *ant_q;
    char *nome_q;
    char *nome_apagar = (char *)(pBuffer + sizeof(void *) * 2 + sizeof(int));

    if(*(void **)pBuffer == NULL) {
        printf("Agenda vazia.\n");
    } else {
        printf("Apagar contato: ");
        scanf("%s", nome_apagar);

        while(q != NULL) {  
            nome_q = (char *)(q + sizeof(void *) * 2);
            if(strcmp(nome_q, nome_apagar) == 0) {
                ant_q = *(void **)q;
                prox_q = *(void **)(q + sizeof(void *));
                
                if(prox_q == ant_q) {
                    *(void **)pBuffer = NULL;
                    *(void **)(pBuffer + sizeof(void *)) = NULL;
                } 
                else if(prox_q == NULL) { 
                    *(void **)(ant_q + sizeof(void *)) = NULL;
                    *(void **)(pBuffer + sizeof(void *)) = ant_q;
                } 
                else if(ant_q == NULL) {
                    *(void **)prox_q = NULL;
                    *(void **)pBuffer = prox_q;
                } 
                else {
                    *(void **)prox_q = ant_q;
                    *(void **)(ant_q + sizeof(void *)) = prox_q;
                }
                printf("Contato apagado\n");
                free(q);
                break;
            }
            q = *(void **)(q);
        }

        if(q == NULL) {
            printf("Contato nao encontrado.\n");
        }
    }
}