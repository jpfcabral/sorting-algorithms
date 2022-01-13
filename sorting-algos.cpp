#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define N_MAX_VETOR 100000

void troca(int* v, int i, int j);
void selectionSortIP(int* v, int tamanho);


void selectionSortIP(int* v, int tamanho) {
    for (int i = 0; i < (tamanho - 1); i++) {
        int iMenor = i;             
        for (int j = i + 1; j < tamanho; j++) {
            if (v[j] < v[iMenor]) {
                iMenor = j;
            }
        }

        troca(v, i, iMenor);
    }
}

void insertionSortIPV5(int* v, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int valor = v[i];
        int j;
        for (j = i; j > 0 && v[j - 1] > valor; j--) {
            v[j] = v[j - 1];
        }
        v[j] = valor;
    }
}

void bubbleSort(int* v, int n) {
    for (int varredura = 0; varredura < n - 1; varredura++) {
        bool trocou = false;
        for (int i = 0; i < n - varredura - 1; i++) {
            if (v[i] > v[i + 1]) {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                trocou = true;
            }
        }
        if (trocou == false)
            return;
    }
}


void troca(int* v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void merge(int* v, int tamV, int* e, int tamE, int* d, int tamD) {
    int indexV = 0;
    int indexE = 0;
    int indexD = 0;
    while (indexE < tamE && indexD < tamD) {
        if (e[indexE] <= d[indexD]) {
            v[indexV] = e[indexE];
            indexE++;
        }
        else {
            v[indexV] = d[indexD];
            indexD++;
        }
        indexV++;
    }
    //ainda poderíamos ter elementos no vetor E que não foram copiados para V
    while (indexE < tamE) {
        v[indexV] = e[indexE];
        indexE++;
        indexV++;
    }
    //ainda poderíamos ter elementos no vetor D que não foram copiados para V
    while (indexD < tamD) {
        v[indexV] = d[indexD];
        indexD++;
        indexV++;
    }
}

void mergeSort(int* v, int tamV) {
    if (tamV > 1) {
        //primeiro quebramos o vetor em 2 vetores menores
        int meio = tamV / 2;

        int tamV1 = meio;
        int* v1 = (int*)malloc(tamV1 * sizeof(int));
        for (int i = 0; i < meio; i++) {
            v1[i] = v[i];
        }

        int tamV2 = tamV - meio;
        int* v2 = (int*)malloc(tamV2 * sizeof(int));
        for (int i = meio; i < tamV; i++) {
            v2[i - meio] = v[i];
        }

        mergeSort(v1, tamV1);
        mergeSort(v2, tamV2);
        merge(v, tamV, v1, tamV1, v2, tamV2);

        free(v1);
        free(v2);
    }
}

void swap(int* v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int particiona(int* v, int ini, int fim) {
    int pIndex = ini;
    int pivo = v[fim];
    for (int i = ini; i < fim; i++) {
        if (v[i] <= pivo) {
            swap(v, i, pIndex);
            pIndex++;
        }
    }
    swap(v, pIndex, fim);
    return pIndex;
}

void quickSort(int* v, int ini, int fim) {
    if (fim > ini) {
        int indexPivo = particiona(v, ini, fim);
        quickSort(v, ini, indexPivo - 1);
        quickSort(v, indexPivo + 1, fim);   //indexPivo já está no seu local
    }
}

void alimenta_randn(int* vetor, int n) {
    for (int i = 0; i < n; i++) {
        vetor[i] = rand() % 100;
    }
}

void alimenta_ordn(int* vetor, int n) {
    for (int i = 0; i < n; i++) {
        vetor[i] = i;
    }
}

void alimenta_decr(int* vetor, int n) {
    for (int i = 0; i < n; i++) {
        vetor[i] = n - i;
    }
}

void mostrar(int* vetor, int n) {
    for (int i = 0; i < n; i++) {
        printf(" %d ", vetor[i]);
    }
    printf("\n");
}

int main() {

    // Ponteiro para vetor que aponta para os algoritmos de ordenação
    void (*sort_algo[])(int*, int) = { selectionSortIP , bubbleSort, insertionSortIPV5, mergeSort};
    // Ponteiro para vetor que aponta para funções de inicialização de vetores
    void (*tipo_vetor[])(int*, int) = { alimenta_randn , alimenta_ordn, alimenta_decr};

    clock_t t;

    // Ponteiro para vetor
    int* vetor;
    vetor = (int*)malloc(N_MAX_VETOR * sizeof(int)); // Alocando a maior quantidade possivel para os testes



    // Percorre algoritmos dentro de sort_algo
    for (int i_algo = 0; i_algo < 4; i_algo++) {
        printf("Algoritmo numero %d \n", i_algo);
        for (int j = 0; j < 30; j++) {
            // Percorre tipo de vetor (randomico, ordenado, decrescente)
            for (int i_tipo = 0; i_tipo < 3; i_tipo++) {
                // Percorre tamanho dos vetores
                for (int tam_vetor = 1000; tam_vetor <= 100000; tam_vetor *= 10) {
                    (*tipo_vetor[i_tipo])(vetor, tam_vetor); // Preeche o vetor conforme o tipo e tamanho desejado
                    t = clock();
                    (*sort_algo[i_algo])(vetor, tam_vetor); // Ordena o vetor
                    t = clock() - t; // Mede o tempo apenas do processo de ordenação
                    printf("%lf ", ((double)t) / ((CLOCKS_PER_SEC)));
                }
            }
            printf("\n");
        }
        
    }

    free(vetor);

    return 0;
}