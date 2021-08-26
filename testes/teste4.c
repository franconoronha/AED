#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adiciona(void* pBuffer);

int main() {
    int a, b, c;
    char d;
    char nome[10];
    void *pBuffer = malloc(sizeof(int) * 3 + sizeof(char));
    adiciona(pBuffer);
    a = *(int *)pBuffer;
    b = *(int *)(pBuffer + sizeof(int));
    c = *(int *)(pBuffer + (2 * sizeof(int)));
    d = *(char *)(pBuffer + (3 * sizeof(int)));
    //memcpy(&a, pBuffer, sizeof(int));
    //memcpy(&b, pBuffer+sizeof(int), sizeof(int));
    //memcpy(&c, pBuffer+(2*sizeof(int)), sizeof(int));
    printf("%d %d %d %c", a, b, c, d);
    pBuffer = realloc(pBuffer, (sizeof(int) + (a * (sizeof(nome) + sizeof(int) * 2))));
    if(!pBuffer) printf("erro\n");
    pBuffer = realloc(pBuffer, (sizeof(int) + (b * (sizeof(nome) + sizeof(int) * 2))));
    if(!pBuffer) printf("erro\n");
    pBuffer = realloc(pBuffer, (sizeof(int) + (c * (sizeof(nome) + sizeof(int) * 2))));
    if(!pBuffer) printf("erro\n");
    free(pBuffer);
    return 0;
}

void adiciona(void *pBuffer){
    int a = 10;
    int b = 20;
    int c = 30;
    char d = 'c';
    *(int *)pBuffer = a;
    *(int *)(pBuffer + sizeof(int)) = b;
    *(int *)(pBuffer + (2 * sizeof(int))) = c;
    *(char *)(pBuffer + 3 * sizeof(int)) = d;
}