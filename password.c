#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max_str_length 256
#define num 10

//Tamanho do formato
int tam;
//Declarando os formatos
char str_format[max_str_length];
//Varivavel para contar palavras e casos
int N;
//String de Leitura
char **str;
//Array auxiliar
char number[num] = "0123456789";

void checkword (char *aux, int index){

    //Variavel auxilixar ao for
    int i;

    if(index == tam){
        printf("Aqui!");
        printf("%s\n", str);
    } else if(str_format[index] == '#'){
        printf("Aqui #!");
        for(i = 0; i < num; i++){
            printf("Indice: %d", index);
            sprintf(aux, "%s%s", aux, number[i]);
            printf("Auxiliar: %s", aux);
            checkword(aux, index + 1);
            printf("Oia");
        }
    } else {
        printf("Aqui X!");
        for(i = 0; i < N; i++){
            sprintf(aux, "%s%s", aux, str[i]);
            checkword(aux, index + 1);
        }
    }
}

int main(void)
{

    scanf("%d", &N);

    //Variavel auxilixar do for
    int i, j, k;

    //Alocando memoria da string
    str = malloc(N * sizeof(char *));

    for (i = 0; i < N; i++)
    {
        str[i] = malloc((max_str_length + 1) * sizeof(char));
        memset(str[i], 0, max_str_length + 1);
    }

    //Leitura das Palavras
    for (i = 0; i < N; i++)
    {
        scanf("%s", str[i]);
    }


    while (scanf("%s", str_format) != EOF)
    {

        tam = strlen(str_format);
        //Analisando as possibilidades
        checkword("", 0);
    }

    //Tirando alocação da memória
    for (i = 0; i < N; i++)
    {
        free(str[i]);
    }

    free(str);

    return 0;
}