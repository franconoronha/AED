#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adiciona_dois(void* pBuffer);

int main() {
    int a, b, c;
    void *pBuffer = malloc(sizeof(int) * 3);
    adiciona_dois(pBuffer);
    memcpy(&a, pBuffer, sizeof(int));
    memcpy(&b, pBuffer+sizeof(int), sizeof(int));
    memcpy(&c, pBuffer+(2*sizeof(int)), sizeof(int));
    printf("%d %d %d", a, b, c);
    return 0;
}

void adiciona_dois(void *pBuffer){
    int a = 10;
    int b = 20;
    int c = 30;
    memcpy(pBuffer, &a, sizeof(int));
    memcpy(pBuffer+sizeof(int), &b, sizeof(int));
    memcpy(pBuffer+(2*sizeof(int)), &c, sizeof(int));
}