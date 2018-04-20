#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max_length 225

int tam = 0; //Tamanho da BST

typedef struct root
{
    struct root *right;
    struct root *left;
    char str[225];
} root;

root *init_BST()
{

    root *node = (root *)malloc(sizeof(root));
    node = NULL;

    return node;
}

root *add_BST(root *_bst, char *str)
{
    if (_bst == NULL)
    {
        root *node = (root *)malloc(sizeof(root));
        node->left = NULL;
        node->right = NULL;
        strcpy(node->str, str);

        tam++;

        return node;
    }
    else if (strcmp(str, _bst->str) < 0)
    {
        _bst->left = add_BST(_bst->left, str);
        return _bst;
    }
    else
    {
        _bst->right = add_BST(_bst->right, str);
        return _bst;
    }
}

root *find_BST(root *_bst, char *str)
{
    if (_bst == NULL)
    {
        return NULL;
    }

    if (strcmp(str, _bst->str) == 0)
    {
        return _bst;
    }
    else if (strcmp(str, _bst->str) < 0)
    {
        return find_BST(_bst->left, str);
    }
    else
    {
        return find_BST(_bst->right, str);
    }
}

root *del_BST_min(root *_bst)
{

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

    root *BST = init_BST();

    int N; //Qtd de comandos
    scanf("%d", &N);

    int i; //Auxiliares ao for

    char str_input[max_length]; //Comando de entrada

    for (i = 0; i < N; i++)
    {

        scanf("%s", str_input);

        if (strcmp(str_input, "ADD") == 0)
        {

            char elem[max_length]; //Elemento da BST
            scanf("%s", elem);

            BST = add_BST(BST, elem);
        }

        if (strcmp(str_input, "FIND") == 0)
        {

            char elem[max_length]; //Elemento da BST
            scanf("%s", elem);

            if (find_BST(BST, elem) != NULL)
            {
                printf("We got it!\n");
            }
            else
            {
                printf("We don't have it!\n");
            }
        }

        if (strcmp(str_input, "DEL") == 0)
        {

            char elem[max_length]; //Elemento da BST
            scanf("%s", elem);

            if(tam == 0) {
                printf("Add elements first!\n");
            } else {
                BST = del_BST(BST, elem);
            }

        }

        if (strcmp(str_input, "PRINT") == 0)
        {
            print(BST);
        }
    }

    return 0;
}