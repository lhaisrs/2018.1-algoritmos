#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

    typedef struct node
{

    struct node *next;
    int oc; //ocorrencias

} node;

typedef struct hash
{

    char *str; //valor da string
    node *next;

} hash;

//Valor de ocupacao da hash
int tam_oc = 0;

node *ocorrencias;
hash *nil;

void init_node()
{

    ocorrencias = malloc(sizeof(node));
    ocorrencias->next = NULL;
    ocorrencias->oc = 0;
}

void init_hashtable()
{
    nil = malloc(sizeof(hash));
    nil->next = ocorrencias;
    nil->str = "aaaa";
}

uint32_t chaveC(char *kmer, int K)
{
    //Auxilixar no for
    int i;

    uint32_t C = 0; //Chave C

    for (i = 0; i < K; i++)
    {
        C = C * 128 + kmer[i];
    }

    return C;
}

float fatorCarga(int tam_hash)
{
    return ( (float) tam_oc / tam_hash);
}

int main()
{

    //Auxiliares para o for
    int i, j;

    int K, Q;
    scanf("%d %d", &K, &Q);

    //Criando a hashtable
    hash hashtable[Q];

    //Inicializando as structs
    init_node();
    init_hashtable();

    //Inicializando a hashtable
    hashtable[0].str = nil->str;
    hashtable[0].next = nil->next;

    char *str_txt, *str_consulta;
    str_txt = (char *)malloc(sizeof(char));
    str_consulta = (char *)malloc(sizeof(char));
    int Y, W;

    scanf("%s", str_txt);
    scanf("%d", &Y);

    char *txt[Y];

    //Alocando vetor para a leitura do texto
    for (i = 0; i < Y; i++)
    {
        txt[i] = (char *)malloc(sizeof(char));
    }

    //Lendo o texto
    for (i = 0; i < Y; i++)
    {
        scanf("%s", txt[i]);
    }

    scanf("%s", str_consulta);
    scanf("%d", &W);

    char *words[W];

    //Alocando vetor para a leitura do texto
    for (i = 0; i < W; i++)
    {
        words[i] = (char *)malloc(sizeof(char));
    }

    //Lendo o texto
    for (i = 0; i < W; i++)
    {
        scanf("%s", words[i]);
    }

    //Povoando a hashtable
    for (i = 0; i < Y; i++)
    {
        for (j = 0; j < strlen(txt[i]); j++)
        {
            //Enviando k tamanho da string
            char *kmers = "la";
            uint32_t C = chaveC(kmers, K);
            printf("Chave: %d\n", C);
            printf("Fator carga: %f\n", fatorCarga(Q));
            

            //Verificando se a hashtable pode ser povoada
            // if (fatorCarga(Q) < 0.5)
            // {
            //     //Validando a string no indice C
            //     if (hashtable[C].str == NULL)
            //     {
            //         //Adicionar ocorrencia e a string
            //     }
            //     else if (strcmp(hashtable[C].str, kmers) == 0)
            //     {
            //         //Adicionar a ocorrencia
            //     }
            //     else
            //     {
            //         //Calcular o hashing
            //     }
            // } else {
            //     //Calculando o novo Q
            //     Q = (2 * Q) + 1;
            // }
        }
    }

    return 0;
}
    