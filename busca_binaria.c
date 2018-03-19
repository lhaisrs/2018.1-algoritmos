#include <stdio.h>

#define tam_vet 100

//Vetor da busca binaria
int vetor[tam_vet];
int tam = 1;

int binary_search(int value) {

    //Auxiliares das busca binaria
    int l, r, m;

    //Iniciando
    l = 0;
    r = tam - 1;

    do {
        m = (l + r) / 2;
        if(value == vetor[m]) {
                return 1;
        } else if (value < vetor[m]) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    
    } while (l <= r);

    return -1;
}

int main() {

    printf("Avaliador de vetores para busca binaria: \n");
    printf("Coloquem os valores em ordem: \n");

    int N = 0, i = 0;


    while(N != EOF) {
        scanf("%d", &N);

        if(binary_search(N) == 1) {
            printf("O vetor ja possui o valor informado: %d \n", N);
        } else if (binary_search(N) == -1){
            vetor[i] = N;
            i++;
            tam++;
        }
    } 

    return 0;
}