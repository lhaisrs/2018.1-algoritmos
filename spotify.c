#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam_str 2560
#define tam_cmd 4

//Estrutura: Musica
typedef struct song
{
    struct song *next;
    char name_song[tam_str];
} song;

//Estrutura: Playlist
typedef struct playlist
{
    struct playlist *next;
    struct song *front; //front
    struct song *rear;  //rear
    char name_playlist[tam_str];

} playlist;

//Estrutura: Lista de reproducao
typedef struct play
{
    struct song *prev; //historico
    struct song *rear; //rear
    struct song *front; //front
} play;

//Lista de playlists
playlist *list_playlist;

//Lista de reproducao
play *list_play;

//Inicializando lista de reproducao
void init_play()
{
    list_play = malloc(sizeof(play));
    list_play->rear = NULL;
    list_play->front = NULL;
    list_play->prev = NULL;
}

//Encontrando a playlist
playlist *find_playlist(char *name_playlist)
{
    playlist *node;
    node = list_playlist;

    while (node != NULL)
    {

        if (strcmp(node->name_playlist, name_playlist) == 0)
        {
            return node;
        }

        node = node->next;
    }

    return node;
}

//Encontrando a musica
song *find_song(char *name_song, playlist *list)
{

    song *aux;
    aux = list->front;

    while (aux != NULL)
    {

        if (strcmp(aux->name_song, name_song) == 0)
        {
            return aux;
        }

        aux = aux->next;
    }

    return aux;
}

//Adicionando musicas na playlists
void enqueue(playlist *list, char *_song)
{
    song *novo = malloc(sizeof(song));
    strcpy(novo->name_song, _song);
    novo->next = NULL;

    if (list->front == NULL)
    {
        list->front = novo;
        list->rear = novo;
    }
    else
    {
        list->rear->next = novo; //song
        list->rear = novo; //playlist
    }
}

//Adicionando musica na playlist
void add(char *name_playlist, char *song)
{
    //Encontrando a playlist
    playlist *hasPlaylist = find_playlist(name_playlist);

    if (hasPlaylist == NULL)
    {
        //Criando a playlist
        hasPlaylist = malloc(sizeof(playlist));
        strcpy(hasPlaylist->name_playlist, name_playlist);
        hasPlaylist->front = NULL;
        hasPlaylist->rear = NULL;
        hasPlaylist->next = NULL;
        if (list_playlist == NULL)
        {
            list_playlist = hasPlaylist;
        }
        else
        {
            hasPlaylist->next = list_playlist; 
            list_playlist = hasPlaylist;
        }
    }

    //Adicionando song
    enqueue(hasPlaylist, song);
}

//Deletando musica na playlist
void del(char *name_playlist, char *music)
{
    playlist *myPlaylist = find_playlist(name_playlist);

    song *aux, *target;
    aux = myPlaylist->front;

    //Checar se o target e o front
    if (strcmp(aux->name_song, music) == 0)
    {
        target = aux;
        myPlaylist->front = target->next;

        if (myPlaylist->front == NULL)
        {
            myPlaylist->rear = NULL;
        }
    }
    else
    {

        while (aux->next != NULL)
        {
            if (strcmp(aux->next->name_song, music) == 0)
            {
                target = aux->next;
                aux->next = target->next;

                if (target->next == NULL)
                {
                    myPlaylist->rear = aux;
                }

                break;
            }

            aux = aux->next;
        }
    }

    free(target);
}

//Trocando as musicas na playlist
void swp(char *name_playlist, char *music, char *_music)
{
    playlist *myPlaylist = find_playlist(name_playlist);

    song *aux, *tmp;
    char _swp[tam_str];

    aux = find_song(music, myPlaylist);
    tmp = find_song(_music, myPlaylist);

    //Trocando os nomes das musicas
    strcpy(_swp, aux->name_song);
    strcpy(aux->name_song, tmp->name_song);
    strcpy(tmp->name_song, _swp);
}

//Adicionando a musica na lista de reproducao
void pls(char *music)
{
    song *novo = malloc(sizeof(song));
    strcpy(novo->name_song, music);
    novo->next = NULL;

    if (list_play->front == NULL)
    {
        list_play->front = novo;
        list_play->rear = novo;
    }
    else
    {
        list_play->rear->next = novo; //song
        list_play->rear = novo; //lista reproducao
    }
}

//Limpando a lista de reproducao
void clean_play()
{
    song *aux;

    while (list_play->front != NULL)
    {

        aux = list_play->front;
        list_play->front = aux->next;

        free(aux);
    }

    while (list_play->prev != NULL)
    {

        aux = list_play->prev;
        list_play->prev = aux->next;

        free(aux);
    }

    list_play->rear = NULL;
}

//Colocando as musicas da playlist na lista de reproducao
void plp(char *name_playlist)
{

    //Limpando a lista de reproducao
    clean_play();

    playlist *myPlaylist = find_playlist(name_playlist);

    song *aux;
    aux = myPlaylist->front;

    while (aux != NULL)
    {
        //Adicionando a musica na lista de reproducao
        pls(aux->name_song);

        aux = aux->next;
    }
}

//Colocando a proxima musica na lista de reproducao
void nxt(){
    song *aux;
    aux = list_play->front;
    list_play->front = aux->next;

    if(list_play->front == NULL){
        list_play->rear = NULL;
    } 

    aux->next = list_play->prev;
    list_play->prev = aux;
}

//Colocando a musica anterior na lista de reproducao
void prv(){

    song *aux;
    aux = list_play->prev;
    list_play->prev = aux->next;

    if(list_play->rear == NULL){
        list_play->rear = aux;
    }

    aux->next = list_play->front;
    list_play->front = aux;

}

//Debugando
void debug(){
    printf("\nDEBUGANDO GERAL\n");

    playlist *aux;
    aux = list_playlist;

    song *tmp;

    while (aux != NULL)
    {

        printf("Playlist %s\n", aux->name_playlist);

        tmp = aux->front;

        while (tmp != NULL)
        {
            printf("+Song: %s\n", tmp->name_song);

            tmp = tmp->next;
        }

        aux = aux->next;
    }

    printf("Reproduzindo agora\n");

    tmp = list_play->front;

    while (tmp != NULL)
    {
        printf("+Song: %s\n", tmp->name_song);

        tmp = tmp->next;
    }

    printf("Historico de Reproducao\n");

    tmp = list_play->prev;

    while (tmp != NULL)
    {
        printf("+Song: %s\n", tmp->name_song);

        tmp = tmp->next;
    }
}

int main()
{

    int N;
    char comando[tam_cmd];
    char nome_playlist[tam_str];
    char music[tam_str];
    char _music[tam_str];

    //Auxiliares ao for
    int i, j;

    //Recebendo a quantidade de operacoes
    scanf("%d", &N);

    //Inicializar a lista de reproducao
    init_play();

    for (i = 0; i < N; i++)
    {
        //Leitura do Comando
        scanf("%s", comando);

        //Comando: ADD
        if (strcmp(comando, "ADD") == 0)
        {
            scanf("%s", nome_playlist);
            scanf("%s", music);

            add(nome_playlist, music);
        }

        //Comando: DEL
        if (strcmp(comando, "DEL") == 0)
        {
            scanf("%s", nome_playlist);
            scanf("%s", music);

            del(nome_playlist, music);
        }

        //Comando: INF
        if (strcmp(comando, "INF") == 0)
        {
            if (list_play->front == NULL)
            {
                printf("UNKNOWN\n");
            }
            else
            {
                printf("%s\n", list_play->front->name_song);
            }
        }

        //Comando: SWP
        if (strcmp(comando, "SWP") == 0)
        {
            scanf("%s", nome_playlist);
            scanf("%s", music);
            scanf("%s", _music);

            swp(nome_playlist, music, _music);
        }

        //Comando: PLS
        if (strcmp(comando, "PLS") == 0)
        {
            scanf("%s", music);

            pls(music);
        }

        //Comando: PLP
        if (strcmp(comando, "PLP") == 0)
        {
            scanf("%s", nome_playlist);

            plp(nome_playlist);
        }

        //Comando: NXT
        if (strcmp(comando, "NXT") == 0)
        {
            nxt();
        }

        //Comando: PRV
        if (strcmp(comando, "PRV") == 0)
        {
            prv();
        }

        //Comando: CLR
        if (strcmp(comando, "CLR") == 0)
        {
            clean_play();
        }
    }

    //debug();
}