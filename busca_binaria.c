#include <stdio.h>

int binary_search(int *vet, int value, int tam) {

    //Auxiliares das busca binaria
    int l, r, m;

    //Iniciando
    l = 0;
    r = tam - 1;

    do {
        m = (l + r) / 2;
        if(value == vet[m]) {
                return 1;
        } else if (value < vet[m]) {
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
	int tam_vet = 1;
	int vetor[N];


    while(N != EOF) {
        scanf("%d", &N);

        if(binary_search(vetor, N, tam_vet) == 1) {
            printf("O vetor ja possui o valor informado: %d \n", N);
        } else if (binary_search(vetor, N, tam_vet) == -1){
            vetor[i] = N;
            i++;
            tam_vet = tam_vet + 1;
        }
    } 

    return 0;
}