#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXMORSE 10

//Definicao de estruturas
typedef struct inf
{
    char letra;
    char morse[MAXMORSE];
} INF;

typedef struct avl
{
    INF chave;
    int FB;
    struct AVL *dir;
    struct AVL *esq;
} AVL;

typedef struct abp
{
    INF chave;
    struct ABP *dir;
    struct ABP *esq;
} ABP;

//Inicializa arvore
AVL *inicia_AVL(void);
ABP *inicia_ABP(void);

//Rotacoes AVL, recebem uma AVL e retornam uma AVL com as devidas rotacoes feitas
AVL* simples_esq(AVL* arvore);
AVL* simples_dir(AVL* arvore);
AVL* dupla_dir(AVL* arvore);
AVL* dupla_esq(AVL* arvore);
//Casos de desbalanceamento na insercao, recebem uma AVL e uma flag para ser resetada
AVL* Caso1(AVL* a, int *ok);
AVL* Caso2(AVL* a, int *ok);

//Funcoes de insercao
//Recebe uma arvore, o item a ser inserido e um flag que indica se a arvore esta balanceada, retorna a mesma arvore com o item nela
AVL* Insere_Avl(INF codigo, AVL *arv,int *ok);
//Recebe uma arvore e o item a ser inserido, retorna a mesma arvore com o item nela
ABP* Insere_Abp(INF codigo, ABP *arv);

//Funcao para lidar com acentos
void procura_acento(char *letra);

//Funcoes de procura
//Recebe uma letra, coloca seu equivalente em morse no vetor e retorna a quantidade de comparacoes necessarias para encontra-la
int procura_avl(char morse[], AVL *arvore, char letra);
int procura_abp(char morse[], ABP *arvore, char letra);
