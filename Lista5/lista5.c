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

//  Posix/Linux
#else
    double get_cpu_time() {
        return (double)clock() / CLOCKS_PER_SEC;
    }
#endif

int verifica(int array[], int size);
void selection_sort(int array[], int size);
void insertion_sort(int array[], int size);
void quicksort(int array[], int left, int right);

void main() {
    srand(time(NULL));
    double begin, end, elapsed;
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
        int *array = (int *)malloc(sizeof(int) * num_elementos);

        if(mostrar == 1) {
            printf("Array: ");
            for(i = 0; i < num_elementos; i++) {
                array[i] = rand() % 1000;
                printf("%d ", array[i]);
            }
            printf("\n----------------");
        }

        switch(escolha) {
            case 1:
                begin = get_cpu_time();
                selection_sort(array, num_elementos);
                break;
            case 2:
                begin = get_cpu_time();
                insertion_sort(array, num_elementos);
                break;
            case 3:
                begin = get_cpu_time();
                quicksort(array,0,(num_elementos - 1));
                break;
            case 4:
                begin = get_cpu_time();
                break;
            default:
                printf("Opcao invalida.");
        }

        end = get_cpu_time();
        double elapsed = (end - begin);

        if(mostrar == 1) {
            printf("\nResultado: ");
            for(i = 0; i < num_elementos; i++){
                printf("%d ", array[i]);
            }
        }

        printf("Tempo decorrido: %0.6lfs\n", elapsed);

        if(verifica(array, num_elementos))
            printf("Sucesso: O vetor foi ordenado corretamente!\n");
        else 
            printf("\nErro: O vetor nao foi ordenado corretamente\n");

        free(array);
    }
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
