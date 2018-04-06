#include <stdio.h>

typedef struct carta
{

    struct carta *next;
    int val;

} carta;

void create_deck(carta *_deck, int value)
{

    //Auxiliar no for
    int i;

    //Inseriando N valores na lista
    for (i = 2; i <= value; i++)
    {
        carta *novo;
        novo = malloc(sizeof(carta));
        novo->next = NULL;

        if(_deck->next == NULL) {
             novo->val = i;
            _deck->next = novo;
        } else {
            carta *aux = _deck->next;

            while(aux->next != NULL) {
                aux = aux->next;
            }

            novo->val = i;
            aux->next = novo;
        }

    }
}

void show_deck(carta *_deck) {

    carta *aux;
    aux = _deck;

    while(aux != NULL) {
        printf("%d ", aux->val);
        aux = aux->next;
    }

}

void manipulate_deck(carta *_deck, carta *_discarte) {

    carta *aux;
    aux = _deck;

    while (aux->next != NULL) {
        carta *novo = malloc(sizeof(carta));
        novo->next = NULL;
        novo->val = aux->val;

        if(_discarte->next == NULL) {
            _discarte->next = novo;
        } else {
            carta *tmp = aux;

            while(tmp != NULL) {
                tmp = tmp->next;
            }

            tmp->next = novo;
        }

        
    }
    
}

int main()
{

    int N = 1;

    carta *deck = malloc(sizeof(carta));
    deck->next = NULL;
    deck->val = 1;

    carta *discarte_deck = malloc(sizeof(carta));
    discarte_deck->next = NULL;
    discarte_deck->val = 1;

    //Topo da carta
    while (N != 0)
    {
        //Recebendo a quantidade de cartas
        scanf("%d", &N);

        //Criando a fila de elementos
        create_deck(deck, N);
        //show_deck(deck);
    }

    return 0;
}