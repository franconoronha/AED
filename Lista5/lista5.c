#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  Windows
#ifdef _WIN32
    #include <Windows.h>
    double get_cpu_time() {
        FILETIME a,b,c,d;
        if(GetProcessTimes(GetCurrentProcess(),&a,&b,&c,&d) != 0) {
            return
                (double)(d.dwLowDateTime |
                ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
        } else {
            return 0;
        }
    }

//  Linux
#else
    double get_cpu_time() {
        return (double)clock() / CLOCKS_PER_SEC;
    }
#endif

void merge(int array[], int l, int m, int r);
void mergeSort(int array[], int l, int r);
void selection_sort(int array[], int size);
void insertion_sort(int array[], int size);
void quicksort(int array[], int left, int right);
int verifica(int array[], int size);

int main() {
    srand(time(NULL));
    double begin, end, tempo;
    int num_elementos, i, escolha, mostrar = -1;

    
    for(;;) {
        printf("--- Menu ---");
        printf("\n 1 - Selection Sort");
        printf("\n 2 - Insertion Sort");
        printf("\n 3 - Quick Sort");
        printf("\n 4 - Merge Sort");
        printf("\n 5 - Mostrar Array(on/off default=off)");
        printf("\n 6 - Sair");
        printf("\nEscolha o algoritmo desejado: ");
        scanf("%d", &escolha);
        
        if(escolha == 5) {
                mostrar *= -1;
                continue;
        }
        if(escolha == 6) exit(0);

        printf("Escolha a quantidade de elementos do array: ");
        scanf("%d", &num_elementos);
        setbuf(stdin, NULL);
        int *array = (int *)malloc(sizeof(int) * num_elementos);

        for(i = 0; i < num_elementos; i++) {
            array[i] = rand() % 10000;
        }

        if(mostrar == 1) {
            printf("Array: ");
            for(i = 0; i < num_elementos; i++) {
                printf("%d ", array[i]);
            }
            printf("\n----------------");
        }

        begin = get_cpu_time();
        switch(escolha) {
            case 1:
                selection_sort(array, num_elementos);
                break;
            case 2:
                insertion_sort(array, num_elementos);
                break;
            case 3:
                quicksort(array,0,(num_elementos - 1));
                break;
            case 4:
                mergeSort(array,0,(num_elementos - 1));
                break;
            default:
                printf("Opcao invalida.");
        }

        end = get_cpu_time();
        tempo = (end - begin);

        if(mostrar == 1) {
            printf("\nResultado: ");
            for(i = 0; i < num_elementos; i++){
                printf("%d ", array[i]);
            }
        }

        printf("Tempo decorrido: %0.6lfs\n", tempo);

        if(verifica(array, num_elementos))
            printf("Sucesso: O vetor foi ordenado corretamente!\n");
        else 
            printf("\nErro: O vetor nao foi ordenado corretamente\n");

        free(array);
    }

    return 0;
}

void quicksort(int array[], int left, int right) {
    int pivo, tmp, i, j;
    i = left;
    j = right;
    pivo = array[rand() % (right + 1 - left) + left];

    do {
        while(array[i] < pivo) i++;
        while(pivo < array[j]) j--;
        if(i <= j) {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);

    if(left < j) quicksort(array,left,j);
    if(i < right) quicksort(array,i,right);
}

int verifica(int array[], int size) {
    int i;
    for(i = 0; i < (size - 1); i++) {
        if(array[i] > array[i + 1]) return 0;
    }
    return 1;
}

void selection_sort(int array[], int size){
    int i, j, pos, menor;
    for(i = 0; i < (size - 1); i++) {
        menor = array[i];
        pos = i;
        for(j = (i + 1); j < size; j++) {
            if(array[j] < menor) {
                menor = array[j];
                pos = j;
            }
        }
        array[pos] = array[i];
        array[i] = menor;
    }
}

void insertion_sort(int array[], int size) {
    int i, j, ins;
    for(i = 1; i < size; i++) {
        ins = array[i];
        for(j = (i - 1); j >= 0; j--) {
            if(ins <= array[j])
                array[j+1] = array[j];
             else 
                break;
        }
        array[j+1] = ins;
    }
}

void merge(int array[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    int *L = (int *)malloc(sizeof(int) * (n1));
    if(L == NULL){
        printf("Erro");
        return;
    }
    int *R = (int *)malloc(sizeof(int) * (n2));
    if(R == NULL){
        printf("Erro!\n");
        free(L);
        return;
    }
    for (i = 0; i < n1; i++)
        L[i] = array[l + i];
    for (j = 0; j < n2; j++)
        R[j] = array[m + 1 + j];
  
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
    }
  
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }
  
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}
  
void mergeSort(int array[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
  
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
  
        merge(array, l, m, r);
    }
}
  