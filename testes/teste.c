#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int tam;
    char *buffer1 = (char *)malloc(sizeof(char) * 50);
    if(!buffer1) printf("erro1");
    char *buffer2 = (char *)malloc(sizeof(char) * 1);
    char *inicio2 = buffer2;

    scanf("%s", buffer1);
    tam = strlen(buffer1) + 1;

    buffer2 = (char *) realloc(buffer2, sizeof(char) * tam);
    if(!buffer2) printf("erro realloc1");

    while(*buffer1 != '\0'){ 
        *buffer2 = *buffer1;
        buffer1++;
        buffer2++;
    }
    *buffer2 = '@';
    free(buffer1);
    buffer1 = (char *)malloc(sizeof(char) * 50);
    scanf("%s", buffer1);
    tam += strlen(buffer1) + 1;

    buffer2 = inicio2;
    buffer2 = (char *) realloc(buffer2, sizeof(char) * tam);
    if(!buffer2) printf("erro realloc2");

    while(*buffer2 != '@') {
        buffer2++;
    }
    buffer2++;

    while(*buffer1 != '\0'){ 
        *buffer2 = *buffer1;
        buffer1++;
        buffer2++;
    }
    *buffer2 = '\0';
    buffer2 = inicio2;
    while(*buffer2 != '\0'){
        printf("%c", *buffer2);
        buffer2++;
    }
    free(buffer2);
    free(buffer1);
    return 0;
}