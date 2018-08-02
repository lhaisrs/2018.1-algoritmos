#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
//#include <time.h>

typedef struct node
{
    struct node *next;
    int oc; //ocorrencias
} node;

typedef struct hash
{
    char *str; //valor da string
    node *front;
    node *rear;
    uint32_t key;
} hash;

//Valor de ocupacao da hash
int tam_oc = 0;

float fatorCarga(int tam_hash)
{
    return ( (float) tam_oc / tam_hash);
}

int hashCode(int Q, int C)
{
    C = C * ( (C < 0) * (-1) + (C > 0));
    return C % Q;
}

hash* create_hashtable(int Q)
{    
    int i;

    //Criando a hashtable
    hash *hashtable = (hash *) malloc(Q*sizeof(hash));

    for(i = 0; i < Q; i++)
    {
        hashtable[i].str = (char*)malloc(1024*sizeof(char));
        hashtable[i].front = NULL;
        hashtable[i].rear = NULL;
        hashtable[i].key = 0;
    }

    return hashtable;       
}

void insert_hashtable(hash *table, int tam_table, char table_kmers[], uint32_t C, int oc)
{
    //Auxiliares do for
    int i, pos, hc;

    hc = hashCode(tam_table, C);

    for(i = 0; i < tam_table; i++)
    {
        
        pos = (hc + i) % tam_table;

        if(table[pos].front == NULL)
        {

            node *ocorrencias = (node *) malloc(sizeof(node));
            ocorrencias->next = table[pos].rear;
            ocorrencias->oc = oc;

            table[pos].front = ocorrencias;
            table[pos].rear = ocorrencias;
            table[pos].str = table_kmers;
            table[pos].key = C;

            tam_oc++;

            return;
        }

        else if(table[pos].key == C) {
            if(strcmp(table[pos].str, table_kmers) == 0)
            {
                node *ocorrencias = (node *) malloc(sizeof(node));
                ocorrencias->oc = oc;
                ocorrencias->next = NULL;
                table[pos].rear->next = ocorrencias;
                table[pos].rear = ocorrencias;

                return;
            }
        }
    }
}

char *take_str(char *text, int l, int r)
{
    //Auxiliares do for
    int i;

    char *str = (char *) malloc(r * sizeof(char));
    //char str[1024];

    for(i = 0; i < r; i++) {
        str[i] = text[l + i];
    }

    return str;
}

hash *rehash_table(hash *oldhash, int Q, int K)
{
    int i, j, pos, hc, newQ = (2 * Q) + 1;
    uint32_t C;

    hash *newhash = create_hashtable(newQ);

    for(j= 0;j < Q;j++)
    {
        if (oldhash[j].front != NULL)
        {
            C = 0;

            for(i = 0; i < K; i++)
            {
                C = C * 128 + oldhash[j].str[i];
            }

            hc = hashCode(newQ, C);

            for(i = 0; i < newQ; i++)
            {
                
                pos = (hc + i) % newQ;

                if(newhash[pos].front == NULL)
                {
                    newhash[pos].front = oldhash[j].front;
                    newhash[pos].rear = oldhash[j].rear;
                    newhash[pos].str = oldhash[j].str;
                    newhash[pos].key = oldhash[j].key;

                    break;
                }
            }    
        }
    }

    return newhash;
}


int take_position(hash *table, char *kmers, int Q, int K)
{
    //Auxiliar ao for
    int i, pos, hc;

    uint32_t C;

    C = 0;

    for(i = 0; i < K; i++)
    {
        C = C * 128 + kmers[i];
    }

    hc = hashCode(Q, C);

    for(i = 0; i < Q; i++)
    {
        pos = (hc + i) % Q;

        if(table[pos].key == C) {
            if(strcmp(table[pos].str, kmers) == 0)
            {
                return pos;
            }
        }
    }

    return -1;
}

int main()
{
    //clock_t Ticks[5];
    //Ticks[0] = clock();

    //Auxiliares para o for
    int i, j;

    int K, Q;
    scanf("%d %d", &K, &Q);

    hash *hashtable = create_hashtable(Q);

    char str_txt[4], str_consulta[20];
    int Y, W;

    scanf("%s", str_txt);
    scanf("%d\n", &Y);

    char txt[3000000];
    int aux = 0, size = 0;

    //Lendo o texto
    while(aux < Y && size < 3000000) {
        scanf("%c", &txt[size]);
        if (txt[size] == '\n') aux++;
        size++;
    }

    txt[--size] = '\0';

    char *kmers;
    //char kmers[1024];
    int l = 0;
    uint32_t C;

    //Ticks[1] = clock();
    //Povoando a hashtable
    for (i = K; i < size; i++)
    {
        if(fatorCarga(Q) >= 0.5)
        {
            hashtable = rehash_table(hashtable, Q, K);

            Q = (2 * Q) + 1;
        }

        C = 0;

        for(j = l; j < i; j++)
        {
            C = C * 128 + txt[j];
        }

        kmers = take_str(txt, l, K);

        insert_hashtable(hashtable, Q, kmers, C, l);

        l++;
    }

    //Ticks[2] = clock();

    scanf("%s", str_consulta);
    scanf("%d\n", &W);

    char words[1024];

    //Realizando a consulta
    for(i = 0; i < W; i++)
    {
        scanf("%[^\n]\n", words);

        kmers = take_str(words, 0, K);

        int rsize = strlen(words) - K;
        int pos = take_position(hashtable, kmers, Q, K);
        char *ftest = words+K;

        printf("%d:", i);
        j = 1;

        if (pos >= 0)
        {
            node *aux;
            aux = hashtable[pos].front;

            while(aux != NULL)
            {

                char *ftxt = take_str(txt, aux->oc + K, rsize);

                if(strcmp(ftest, ftxt) == 0) {
                    printf(" %d", aux->oc);
                    j = 0;
                }

                aux = aux->next;
            }
        }

        if (j)
        {
            printf(" \n");
        }

        else
        {
            printf("\n");
        }
    }

    //Ticks[3] = clock();

    size = 0;
    j = 0;
    for (i = 0;i < Q; i++)
    {
        if (hashtable[i].front == NULL)
        {
            j = 0;
        }
        else
        {
            j++;
            size = size > j ? size : j;
        }
    }

    printf("%d %d %d\n", tam_oc, Q, size);
    
    /*Ticks[4] = clock();
    double Tempo;
    Tempo = (Ticks[2] - Ticks[1]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo gasto povoando a hashtable: %g ms.\n", Tempo);
    Tempo = (Ticks[3] - Ticks[2]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo gasto fazendo consultas: %g ms.\n", Tempo);
    Tempo = (Ticks[4] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo gasto total: %g ms.\n", Tempo);*/

    return 0;
}