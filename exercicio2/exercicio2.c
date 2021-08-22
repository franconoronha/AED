#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *adicionar_nome(char *nomes, int *size);
char *remover_nome(char *nomes, int *size);
void listar_nomes(char *nomes, int size);

int main() {
    int escolha, size = 0;
    char *nomes = (char *) malloc(sizeof(char));
    if(!nomes) {
        printf("erro: falta de memoria\n");
        exit(1);
    }

    for(;;){
        printf("\n --- Menu ---\n");
        printf("1) Adicionar nome\n");
        printf("2) Remover nome\n");
        printf("3) Listar\n");
        printf("4) Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        setbuf(stdin, NULL);

        switch(escolha) {
            case 1:
                nomes = adicionar_nome(nomes, &size);
                break;
            case 2:
                nomes = remover_nome(nomes, &size);
                break;
            case 3:
                listar_nomes(nomes, size);
                break;
            case 4:
                free(nomes);
                exit(0);
            default:
                printf("Opcao Invalida.\n");
                break;
        }
    }
    return 0;
}

char *adicionar_nome(char *nomes, int *size) {
	char c;
    // troca o \0 por um @ e aloca um espaco para esse caractere que identifica onde acaba um nome
    // o \0 era contado no +1 e agora temos o /0 + @ 
	if((*size) > 0) { 
        nomes[(*size)] = '@';
        (*size)++;
        nomes = (char *)realloc(nomes, (sizeof(char) * ((*size) + 1)));
        if(!nomes) {
            printf("Erro: falta de memoria\n");
            exit(1);
        }
    }
    // le o nome a ser adicionado
	printf("Digite um nome: ");
	while((c = getchar()) != '\n') { 
		nomes[*size] = c;
		(*size)++;
		nomes = (char *)realloc(nomes, (sizeof(char) * ((*size) + 1)));
        if(!nomes) {
            printf("Erro: falta de memoria\n");
            exit(1);
        }
    }

	nomes[(*size)] = '\0';
	return nomes;
}

void listar_nomes(char *nomes, int size) {
	int i;
    if(size == 0) {
        printf("Nao ha nomes para listar.");
    } else {
        printf(" - Lista de nomes -\n");
        for(i = 0; i < size; i++) {
            if(nomes[i] == '@') {
                printf("\n"); 
            } else {
                printf("%c", nomes[i]);
            }
        }
    }
}

char* remover_nome(char *nomes, int *size){
    char *nome_remover = (char *)malloc(sizeof(char));
    char *string_nome = (char *)malloc(sizeof(char));
    char c;
    int i = 0, j, size_remover = 0, inicio = 0, size_string;
    int flag_encontrou = 0, apos;

    if(*size == 0) {
        printf("Nao ha nomes para remover.");
    } else {
        printf("Digite um nome: ");
        // le o nome a ser removido
        while((c = getchar()) != '\n') { 
            nome_remover[size_remover] = c;
            size_remover++;
            nome_remover = realloc(nome_remover, (sizeof(char) * (size_remover + 1)));
            if(!nome_remover) {
                printf("Erro: falta de memoria1\n");
                exit(1);
            }
        }
        nome_remover[size_remover] = '\0';

        while(nomes[i] != '\0') {
            // reinicia os dados da string comparada
            string_nome = (char *)realloc(string_nome, sizeof(char));
            size_string = 0;
            inicio = i;
            if(!string_nome) {
                printf("Erro: falta de memoria2\n");
                exit(1);
            }

            // conta quantos caracteres tem, aloca o espaço e prepara o i (inicio da proxima string)
            while(nomes[i] != '@' && nomes[i] != '\0') {
                size_string++;
                i++;
            }  
            i++;
            string_nome = (char *) realloc(string_nome, sizeof(char) * (size_string + 1));
            if(!string_nome) {
                printf("Erro: falta de memoria3\n");
                exit(1);
            }
            // copia o conteudo dessa substring para a string comparada
            strncpy(string_nome, nomes+inicio, size_string);
            string_nome[size_string] = '\0'; 

            if(strcmp(nome_remover, string_nome) == 0){
                flag_encontrou = 1;
                break;
            }
        }
        if(flag_encontrou == 1){
        // calcula quantas letras tem entre o final do nome removido e o final da agenda
        apos = ((*size)+1) - (inicio + size_string + 1);   

        // traz esse numero de letras para as posiçoes a partir do inicio sequencialmente
        for(j = 0; j < apos; j++) {
                nomes[inicio + j] = nomes[inicio + j + (size_string+1)];
            }
        (*size) -= (size_string + 1);
        if((*size) < 0) (*size) = 0;
        nomes = (char *) realloc(nomes, sizeof(char) * ((*size) + 1));
        } else {
        printf("O nome nao esta na lista.");
        }
    }

    free(string_nome);
    free(nome_remover);
    return nomes;
}