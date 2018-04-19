#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define max_length 255

typedef struct root {
    struct root *right;
    struct root *left;
    char str[max_length]; //Valor do atributo
} root;

typedef struct node {
    char name[max_length];
    root *head;
} node;

uint32_t chaveC(char *word, int K)
{
    //Auxilixar no for
    int i = 0;

    uint32_t C = 0; //Chave C

    while(word[i] != '\0') {
        C = C * 2 + word[i];
        i++;
    }



    return (C % K);
}

node* init_hashtable(int Q) {

    int i; //Auxiliares do for

    node hashtable = (node *) malloc(Q * sizeof(node));

    for(i = 0; i < Q; i++){
        hashtable[i]->head = NULL;
    }

    return hashtable;
}

root* init_BST(char *nome_BST) {

    printf("Nome da BST: %s\n", nome_BST);

    root node = (root *) malloc(sizeof(root));
    node->right = NULL;
    node->left = NULL;

    return node;    
}

int main() {

    int N; //Qtd de BSTs
    scanf("%d", &N);

    int tam_hash = (2 * N) + 1;

    //Iniciando a hastable
    init_hashtable(tam_hash);

    int i; //Auxiliares no for

    char str_atr[max_length]; //String de leitura

    for(i = 0; i < N; i++) {
        scanf("%s", str_atr);
        uint32_t C = chaveC(str_atr, tam_hash);

        if() {

        }       
    }

    return 0;
}