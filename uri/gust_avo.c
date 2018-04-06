#include <stdio.h>
#include <string.h>



int main() {

    //Auxiliares a repeticao
    int i, j;

    //Numero indicando a quantidade de de instancia
    int N;

    //Contador de ocorrencias
    int oc = 0;

    scanf("%d", &N);

    for(i = 0; i < N; i++) {

        //Leitura das strings
        char *strA = malloc(sizeof(char));
        char *strB = malloc(sizeof(char));

        scanf("%s", strA);
        scanf("%s", strB);

        //Procurando a presenca de B em A
        int tam_str = strlen(strB);

        for(j = 0; j < tam_str; j++) {

            //Realizando a busca binaria
        }


    }

    return 0;
}