#include <stdio.h>

int main(void)
{

    //Variavel para receber N casos
    int n;
    //Variavel auxiliar para a leitura dos casos
    int k;

    scanf("%d", &n);

    for (k = 0; k < n; k++)
    {
        //Varivavel para receber a dimensao da matriz
        int N;

        scanf("%d", &N);

        //Criando a Matriz
        int matriz[N][N];

        //Variaveis auxiliares do for para leitura da matriz
        int i, j;

        //Leitura da Matriz
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                scanf("%d", &matriz[i][j]);
            }
        }

        //Realização do calculo da matriz
        int valid;

        //Variavel soma para auxilio
        int soma_diagonal = 0;

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (i == j)
                {
                    soma_diagonal = soma_diagonal + matriz[i][j];
                }
            }
        }

        //Variavel soma para auxilio
        int soma_linhas;

        for (i = 0; i < N; i++)
        {
            soma_linhas = 0;
            for (j = 0; j < N; j++)
            {
                soma_linhas = soma_linhas + matriz[i][j];
            }

            if(soma_diagonal == soma_linhas){
                valid = 1;
            } else {
                valid = 0;
                break;
            }

        }

        //Variavel soma para auxilio
        int soma_colunas;

        for (i = 0; i < N; i++)
        {
            soma_colunas = 0;

            for (j = 0; j < N; j++)
            {
                soma_colunas = soma_colunas + matriz[j][i];
            }

            if(soma_diagonal == soma_colunas){
                valid = 1;
            } else {
                valid = 0;
                break;
            }

        }

        if (valid == 1)
        {
            printf("matrix #%d is magic\n", k);
        }
        else
        {
            printf("matrix #%d is not magic\n", k);
        }
    }

    return 0;
}