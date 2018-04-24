#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define max_length 255

typedef struct root
{
    struct root *right;
    struct root *left;
    char str[max_length]; //Valor do atributo
    struct doc *ref;
} root;

typedef struct node
{
    char name[max_length];
    root *head;
} node;

typedef struct doc
{
    char name[max_length];
    char value[max_length];
} doc;

//Referencia dos docs
doc *_ref;

root *add_BST(root *_bst, char *str, doc *_doc)
{
    if (_bst == NULL)
    {
        root *node = (root *)malloc(sizeof(root));
        node->left = NULL;
        node->right = NULL;
        strcpy(node->str, str);
        node->ref = _doc;

        return node;
    }
    else if (strcmp(str, _bst->str) < 0)
    {
        _bst->left = add_BST(_bst->left, str, _doc);
        return _bst;
    }
    else
    {
        _bst->right = add_BST(_bst->right, str, _doc);
        return _bst;
    }
}

root *del_BST_min(root *_bst)
{
    // Não deleta corretamente
    root *node;

    if (_bst->left == NULL)
    {
        node = _bst->right;

        free(_bst);

        return node;
    }
    else
    {
        _bst->left = del_BST_min(_bst->left);
        return _bst;
    }
}

root *del_BST(root *_bst, char *str)
{
    if (_bst == NULL)
    {
        return NULL;
    }
    else if (strcmp(str, _bst->str) < 0)
    {
        _bst->left = del_BST(_bst->left, str);
        return _bst;
    }
    else if (strcmp(str, _bst->str) > 0)
    {
        _bst->right = del_BST(_bst->right, str);
        return _bst;
    }
    else
    {
        _ref = _bst->ref;

        if (_bst->left == NULL)
        {
            root *node;
            node = _bst->right;

            free(_bst);
            return node;
        }

        if (_bst->right == NULL)
        {
            root *node;
            node = _bst->left;

            free(_bst);
            return node;
        }
        else
        {
            _bst->right = del_BST_min(_bst->right);
            return _bst;
        }
    }
}

root *remove_BST(root *_bst, doc *ref)
{
    if (_bst == NULL)
    {
        return NULL;
    }

    if (_bst->ref == ref)
    {
        if (_bst->left == NULL)
        {
            root *node;
            node = _bst->right;

            free(_bst);
            return node;
        }

        if (_bst->right == NULL)
        {
            root *node;
            node = _bst->left;

            free(_bst);
            return node;
        }
        else
        {
            _bst->right = del_BST_min(_bst->right);
            return _bst;
        }
    }

    _bst->left = remove_BST(_bst->left, ref);
    _bst->right = remove_BST(_bst->right, ref);
}

uint32_t chaveC(char *word, int K, int j)
{
    //Auxilixar no for
    int i = 0;

    uint32_t C = 0; //Chave C

    while (word[i] != '\0')
    {
        C = C * 2 + word[i];
        i++;
    }

    return ((C + j) % K);
}

void find_BST(root *_bst, char **str_name_atr, char *str, int N, int tam_hash, doc *_hash)
{
    int i, j; //Auxiliares ao for
    uint32_t C;

    if (_bst == NULL)
    {
        return;
    }

    if (strcmp(str, _bst->str) == 0)
    {

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < tam_hash; j++)
            {
                C = chaveC(str_name_atr[i], tam_hash, j);

                if (strcmp(_hash[C].name, str_name_atr[i]) == 0)
                {
                    printf("%s ", _hash[C].value);
                    break;
                }
            }
        }

        printf("\n");

        find_BST(_bst->left, str_name_atr, str, N, tam_hash, _hash);
        find_BST(_bst->right, str_name_atr, str, N, tam_hash, _hash);
    }

    else if (strcmp(str, _bst->str) < 0)
    {
        find_BST(_bst->left, str_name_atr, str, N, tam_hash, _hash);
    }

    else
    {
        find_BST(_bst->right, str_name_atr, str, N, tam_hash, _hash);
    }
}

node *init_hashtable(int Q)
{

    int i; //Auxiliares do for

    node *hashtable = (node *)malloc(Q * sizeof(node));

    for (i = 0; i < Q; i++)
    {
        hashtable[i].head = NULL;
        strcpy(hashtable[i].name, " ");
    }

    return hashtable;
}
doc *init_hash(int Q)
{
    int i; //Auxiliares do for

    doc *hashtable = (doc *)malloc(Q * sizeof(doc));

    for (i = 0; i < Q; i++)
    {
        strcpy(hashtable[i].name, " ");
        strcpy(hashtable[i].value, " ");
    }

    return hashtable;
}

void print(root *_bst)
{

    if (_bst == NULL)
    {
        return;
    }

    printf("%s\n", _bst->str);
    print(_bst->left);
    print(_bst->right);
}

int main()
{

    int N; //Qtd de BSTs
    scanf("%d", &N);

    int tam_hash = (2 * N) + 1;

    //Iniciando a hastable de BSTs
    node *HASHTABLE = init_hashtable(tam_hash);
    doc *hash;

    int i, j, k, l; //Auxiliares no for

    char str_atr[max_length]; //String de leitura

    //Criando a Hashtable de BSTs
    for (i = 0; i < N; i++)
    {
        scanf("%s", str_atr);
        uint32_t C;

        for (j = 0; j < tam_hash; j++)
        {
            C = chaveC(str_atr, tam_hash, j);

            if (strcmp(HASHTABLE[C].name, " ") == 0)
            {
                strcpy(HASHTABLE[C].name, str_atr);
                break;
            }
        }
    }

    char str_comand[max_length];

    //Recebendo os comandos
    while (scanf("%s", str_comand) != EOF)
    {
        uint32_t C;

        //Comando: INSERT - adicionar na BST
        if (strcmp(str_comand, "INSERT") == 0)
        {
            int qtd_atr;
            char str_name[max_length];
            char _str_atr[max_length];

            hash = init_hash(tam_hash);

            scanf("%d", &qtd_atr);

            for (i = 0; i < qtd_atr; i++)
            {
                scanf("%s", str_name);
                scanf("%s", _str_atr);

                //Adicionando na Hash de documentos
                for (k = 0; k < tam_hash; k++)
                {
                    C = chaveC(str_name, tam_hash, k);

                    if (strcmp(hash[C].name, " ") == 0)
                    {
                        strcpy(hash[C].name, str_name);
                        strcpy(hash[C].value, _str_atr);
                        break;
                    }
                }

                for (j = 0; j < tam_hash; j++)
                {
                    C = chaveC(str_name, tam_hash, j);

                    if (strcmp(HASHTABLE[C].name, str_name) == 0)
                    {
                        HASHTABLE[C].head = add_BST(HASHTABLE[C].head, _str_atr, hash);
                        break;
                    }
                }
            }
        }

        //Comando: SELECT - retornar parâmetros da BSTs
        if (strcmp(str_comand, "SELECT") == 0)
        {
            int qtd_atr;
            char *str_atr_name[max_length];
            char aux_comand[max_length];
            char str_name[max_length];
            char _str_atr[max_length];

            scanf("%d", &N);

            for (i = 0; i < N; i++)
            {
                str_atr_name[i] = (char *)malloc(max_length * sizeof(char));
            }

            for (i = 0; i < N; i++)
            {
                scanf("%s", str_atr_name[i]);
            }

            scanf("%s", aux_comand);
            scanf("%s", str_name);
            scanf("%s", _str_atr);

            for (j = 0; j < tam_hash; j++)
            {
                C = chaveC(str_name, tam_hash, j);

                if (strcmp(HASHTABLE[C].name, str_name) == 0)
                {
                    printf("FETCH in BST: %s\n", HASHTABLE[C].name);
                    find_BST(HASHTABLE[C].head, str_atr_name, _str_atr, N, tam_hash, hash);
                    printf(" \n");
                    break;
                }
            }
        }

        //Comando: DELETE - removendo elementos na BST
        if (strcmp(str_comand, "DELETE") == 0)
        {
            char str_name[max_length];
            char _str_atr[max_length];

            scanf("%s", str_name);
            scanf("%s", _str_atr);

            for (j = 0; j < tam_hash; j++)
            {
                C = chaveC(str_name, tam_hash, j);

                if (strcmp(HASHTABLE[C].name, str_name) == 0)
                {
                    HASHTABLE[C].head = del_BST(HASHTABLE[C].head, _str_atr);
                    break;
                }
            }

            for (k = 0; k < tam_hash; k++)
            {
                printf("HASHTABLE: %s\n", HASHTABLE[k].name);
                //remove_BST(HASHTABLE[k].head, _ref);
                print(HASHTABLE[k].head);
            }

            free(_ref);
        }
    }

    return 0;
}