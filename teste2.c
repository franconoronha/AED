#include <stdio.h>
#include <stdlib.h>

int main(){
    char *buffer = (char *) malloc(sizeof(char) * 1);
    char *inicio = buffer;
    int tam = 0;
    char c = 'a';
    do {
        scanf("%c", &c);
        buffer = (char *) realloc(buffer, sizeof(char) * tam + 1);
        buffer[tam] = c;
        tam++;
    } while(c != '\n');
    buffer[tam] = '\0';

    buffer = inicio;

    while(*buffer != '\0') { 
        printf("%c", *buffer);
        buffer++;
    }

    free(buffer);
    return 0;
}