#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *adiciona(void* pBuffer);

int main() {
    int a;
    void *pBuffer = malloc(sizeof(int));
    adiciona(pBuffer);
    //pBuffer = adiciona(pBuffer);
    memcpy(&a, pBuffer, sizeof(int));
    printf("%d", a);
    return 0;
}

void* adiciona(void *pBuffer){
    int q = 10;
    int *i = &q;
    memcpy(pBuffer, i, sizeof(int));
    //return pBuffer;
}