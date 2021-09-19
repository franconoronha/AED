#include <stdio.h>
#include <stdlib.h>


int main() {

    // 
    //
    void *pBuffer = malloc(sizeof(int) + sizeof(void *));
    void *nodo = malloc(sizeof(int) + sizeof(void *));
    void *nodo2 = malloc(sizeof(int) + sizeof(void *));
    void *nodo3 = malloc(sizeof(int) + sizeof(void *));
    void *a = NULL;

    *(void **)(pBuffer + sizeof(int)) = nodo;
    *(void **)(nodo + sizeof(int)) = nodo2;
    *(void **)(nodo2 + sizeof(int)) = NULL;

    void **q = *(void **)(pBuffer + sizeof(int)); 
    void *p = *(void **)(pBuffer + sizeof(int)); 
    void *prox = *(void **)(p + sizeof(int));

    //a = *(void **)(pBuffer + sizeof(int)); // a = nodo
    a = q;
    a = *(void **)(a + sizeof(int)); // a = a-> prox


    *(int *)q = 10;
    printf("%d\n", *(int *)q);

    *(int *)p = 20;
    printf("%d\n", *(int *)p);

    *(int *)prox = 5;
    printf("%d\n", *(int *)prox);

    printf("a: %d\n", *(int *)a);

    printf("%p\n", *(void **)(pBuffer + sizeof(int)));
    printf("%p\n", *(void **)(nodo + sizeof(int)));

    printf("%p\n", p);
    printf("%p\n", q);

    free(pBuffer);
    free(nodo);
    free(nodo2);
    free(nodo3);
    return 0;
}

