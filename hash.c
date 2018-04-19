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

    char str[1024]; //valor da string
    node *front;
    node *rear;

} hash;

//Valor de ocupacao da hash
int tam_oc = 0;

float fatorCarga(int tam_hash)
{
    return ( (float) tam_oc / tam_hash);
}

int hashCode(int Q, int C, int j) {

    return ((C + j) % Q);
}

hash* create_hashtable(int Q) {
    
    int i;

    //Criando a hashtable
    hash *hashtable = (hash *) malloc(Q*sizeof(hash));

    for(i = 0; i < Q; i++) {
        hashtable[i].front = NULL;
        hashtable[i].rear = NULL;
    }

    return hashtable;       
}

void insert_hashtable(hash *table, int tam_table, char *table_kmers, uint32_t C, int oc) {

    //Auxiliares do for
    int i, pos;

    for(i = 0; i < tam_table; i++) {
        
        pos = hashCode(tam_table, C, i);

        if(table[pos].front == NULL) {

            node *ocorrencias = (node *) malloc(sizeof(node));
            ocorrencias->next = table[pos].rear;
            ocorrencias->oc = oc;

            table[pos].front = ocorrencias;
            table[pos].rear = ocorrencias;
            strcpy(table[pos].str, table_kmers);

            tam_oc++;

            return;

        } else if(strcmp(table[pos].str, table_kmers) == 0) {

            node *ocorrencias = (node *) malloc(sizeof(node));
            ocorrencias->oc = oc;
            ocorrencias->next = NULL;
            table[pos].rear->next = ocorrencias;
            table[pos].rear = ocorrencias;

            return;
        }
    }
}

char *take_str(char *text, int l, int r) {
    //Auxiliares do for
    int i;

    char *str = (char *) malloc(r * sizeof(char));
    //char str[1024];

    for(i = 0; i < r; i++) {
        str[i] = text[l + i];
    }

    return str;
}

hash *rehash_table(hash *oldhash, int Q, int K) {
    int i, j, pos, newQ = (2 * Q) + 1;
    uint32_t C;

    hash *newhash = create_hashtable(newQ);

    for(j=0;j<Q;j++){
        if (oldhash[j].front != NULL) {
            C = 0;

            for(i = 0; i < K; i++) {
                C = C * 128 + oldhash[j].str[i];
            }

            for(i = 0; i < newQ; i++) {
            
                pos = hashCode(newQ, C, i);

                if(newhash[pos].front == NULL) {

                    newhash[pos].front = oldhash[j].front;
                    newhash[pos].rear = oldhash[j].rear;
                    strcpy(newhash[pos].str, oldhash[j].str);

                    break;

                }
            }    
        }
    }

    return newhash;
}


int take_position(hash *table, char *kmers, int Q, int K) {

    //Auxiliar ao for
    int i, pos;

    uint32_t C;

    C = 0;

    for(i = 0; i < K; i++) {
        C = C * 128 + kmers[i];
    }

    for(i = 0; i < Q; i++) {

        pos = hashCode(Q, C, i);

        if(strcmp(table[pos].str, kmers) == 0) {
            return pos;
        }
    }

    return -1;
}

int main()
{

    //Auxiliares para o for
    int i, j;

    int K, Q;
    scanf("%d %d", &K, &Q);

    hash *hashtable = create_hashtable(Q);

    char str_txt[20], str_consulta[20];
    int Y, W;

    scanf("%s", str_txt);
    scanf("%d\n", &Y);

    char txt[3030000];

    //Lendo o texto
    char phrase[330];
    for (i = 0; i < Y; i++)
    {
        scanf("%[^\n]\n", phrase);
        strcat(phrase, "\n");
        strcat(txt, phrase);
    }
        
    char *kmers = (char *) malloc(K*sizeof(char));
    //char kmers[1024];
    int l = 0, size = strlen(txt);
    uint32_t C;

    //Povoando a hashtable
    for (i = K; i < size; i++){
        if(fatorCarga(Q) >= 0.5) {

            hashtable = rehash_table(hashtable, Q, K);

            Q = (2 * Q) + 1;
        }


        C = 0;

        for(j = l; j < i; j++) {
            C = C * 128 + txt[j];
        }

        kmers = take_str(txt, l, K);
        //printf("Aqui\n");
        //strcpy(kmers, take_str(txt, l, K));
        //printf("Deu problema aqui!\n");

        insert_hashtable(hashtable, Q, kmers, C, l);

        l++;

    }

    scanf("%s", str_consulta);
    scanf("%d\n", &W);

    char words[1024];

    //Realizando a consulta
    for(i = 0; i < W; i++) {

        //scanf("%[^\n]", words);
        gets(words);

        kmers = take_str(words, 0, K);
        //strcpy(kmers, take_str(words, 0, K));

        int pos = take_position(hashtable, kmers, Q, K);

        printf("%d:", i);
        j = 1;

        if (pos >= 0) {
            node *aux;
            aux = hashtable[pos].front;


            while(aux != NULL) {
                int rsize = strlen(words) - K;

                char *ftxt = take_str(txt, aux->oc + K, rsize);
                char *ftest = take_str(words, K, rsize);

                if(strcmp(ftest, ftxt) == 0) {
                    printf(" %d", aux->oc);
                    j = 0;
                }

                aux = aux->next;
            }
    
        }

        if (j) {
            printf(" \n");
        } else {
            printf("\n");
        }

        strcpy(words, "");
        
    }

    size = 0;
    j = 0;
    for (i=0;i<Q;i++){
        if (hashtable[i].front == NULL) {
            j = 0;
        } else {
            j++;
            size = size > j ? size : j;
        }
    }

    printf("%d %d %d\n", tam_oc, Q, size);
    
    return 0;
}