#include <stdio.h>

int mult(int x, int y){

    /*Funcao auxilixar para realizacao da multiplicacao*/

    if (y == 0){
        return 0;
    } 

    if(y > 0){
        return (x + mult(x, y-1));
    }

    if(y < 0){
        return -mult(x, -y);
    }

}

int main(void)
{

    //Valores inteiros
    int a, b;
    //Variavel para a realizacao da soma
    int soma;
    //Variaveis auxiliares do for
    int i;

    //Leitura dos inteiros
    scanf("%d %d", &a, &b);

    //Realizacao da soma
    soma = mult(a, b);

    //Visualizacao
    printf("%d\n", soma);

    return 0;
}