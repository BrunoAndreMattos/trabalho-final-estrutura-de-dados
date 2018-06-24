#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arvore.h"
//Função de iniciar arvore
AVL* inicia_AVL(void)
{
    return NULL;
}

ABP* inicia_ABP(void)
{
    return NULL;
}

//Rotação simples a esquerda para avl
AVL* simples_esq(AVL* arvore)
{
    AVL *aux;
    aux = arvore->dir;
    arvore->dir = aux->esq;
    aux->esq = arvore;
    arvore->FB = 0;
    arvore = aux;
    return arvore;
}
//Rotação simples a direita para avl
AVL* simples_dir(AVL* arvore)
{
    AVL *aux;
    aux = arvore->esq;
    arvore->esq = aux->dir;
    aux->dir = arvore;
    arvore->FB = 0;
    arvore = aux;
    return arvore;
}
//Rotação dupla a direita para avl
AVL* dupla_dir(AVL* arvore)
{
    AVL *aux1, *aux2;
    aux1 = arvore->esq;
    aux2 = aux1->dir;
    aux1->dir = aux2->esq;
    aux2->esq = aux1;
    arvore->esq = aux2->dir;
    aux2->dir = arvore;
    if (aux2->FB == 1)
        arvore->FB = -1;
    else arvore->FB = 0;
    if (aux2->FB == -1)
        aux1->FB = 1;
    else aux1->FB = 0;
    arvore = aux2;
    return arvore;
}
//Rotação dupla a esquerda para avl
AVL* dupla_esq(AVL* arvore)
{
    AVL *aux1, *aux2;
    aux1 = arvore->dir;
    aux2 = aux1->esq;
    aux1->esq = aux2->dir;
    aux2->dir = aux1;
    arvore->dir = aux2->esq;
    aux2->esq = arvore;
    if (aux2->FB == -1)
        arvore->FB = 1;
    else arvore->FB = 0;
    if (aux2->FB == 1)
        aux1->FB = -1;
    else aux1->FB = 0;
    arvore = aux2;
    return arvore;
}
//CAso1 e Caso2 : Funções para equilibrar a arvore avl para certos casos
AVL* Caso1(AVL* a, int *ok)
{
    AVL *aux;
    aux = a->esq;
    if (aux->FB == 1)
        a = simples_dir(a);
    else
        a = dupla_dir(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

AVL* Caso2(AVL* a, int *ok)
{
    AVL *aux;
    aux = a->dir;
    if (aux->FB == -1)
        a = simples_esq(a);
    else
        a = dupla_esq(a);
    a->FB = 0;
    *ok = 0;
    return a;
}
//Função de inserir codigo em avl
AVL* Insere_Avl(INF codigo, AVL *arv,int *ok)
{
    if (arv == NULL)
    {
        arv = (AVL*) malloc(sizeof(AVL));
        arv->chave = codigo;
        arv->esq = NULL;
        arv->dir = NULL;
        arv->FB = 0;
        *ok = 1;
    }
    else if (codigo.letra < arv->chave.letra)
    {
        arv->esq = Insere_Avl(codigo, arv->esq, ok);
        if (*ok)
        {
            switch (arv->FB)
            {
            case -1:
                arv->FB = 0;
                *ok = 0;
                break;
            case 0:
                arv->FB = 1;
                break;
            case 1:
                arv = Caso1(arv, ok);
                break;
            }
        }
    }
    else
    {
        arv->dir = Insere_Avl(codigo,arv->dir,ok);
        if (*ok)
        {
            switch (arv->FB)
            {
            case 1:
                arv->FB = 0;
                *ok = 0;
                break;
            case 0:
                arv->FB = -1;
                break;
            case -1:
                arv = Caso2(arv, ok);
                break;
            }
        }
    }
    return arv;
}
//Função de inserir codigo em abp
ABP* Insere_Abp(INF codigo, ABP *arv)
{
    if(arv == NULL)//Caso a arvore seja vazia
    {
        arv = (ABP*) malloc(sizeof(ABP));
        arv->chave = codigo;
        arv->esq = NULL;
        arv->dir = NULL;
    }
    else
    {
        if(codigo.letra < arv->chave.letra)//Caso a letra do nodo da arvore tenha um valor maior que a letra do codigo a ser enserido
        {
            arv->esq = Insere_Abp(codigo, arv->esq);
        }
        else//Caso a letra do nodo da arvore tenha um valor menor que a letra do codigo a ser enserido
        {
            arv->dir = Insere_Abp(codigo, arv->dir);
        }
    }
    return arv;
}
//Funão de procurar acentos, caso a letra for um dos casos ela muda para sua respectiva letra sem acento e maiuscula
void procura_acento(char *letra)
{
    switch(*letra)
    {
    case 'Б':
    case 'В':
    case 'Г':
    case 'А':
    case 'г':
    case 'б':
    case 'а':
    case 'в':
        *letra = 'A';
        break;
    case 'з':
        *letra = 'C';
        break;
    case 'Й':
    case 'К':
    case 'к':
    case 'й':
        *letra = 'E';
        break;
    case 'ъ':
    case 'Ъ':
        *letra = 'U';
        break;
    case 'у':
    case 'ф':
    case 'У':
    case 'Ф':
        *letra = 'O';
        break;
    case 'н':
    case 'М':
        *letra='I';
        break;
    }
}
//Procura em uma arvore avl uma char desejado, caso em contre a string morse se torna a forma morse da letra e o numero de comparações nessessárias para encontra-la,
//caso não encontre a palavra, apenas devolve o número de comparações que ocorreram até encontrar o fim da arvore
int procura_avl(char morse[],AVL *arvore,char letra)
{
    if(arvore!=NULL)
    {
        if(letra == arvore->chave.letra)
        {
            strcpy(morse,arvore->chave.morse);//Caso ache a letra, morse = forma morse da letra
            return 1;//Houve apenas duas comparações
        }
        else
            strcpy(morse," ");//caso ao contrario, enquanto não achar morse = " ".
        if(letra < arvore->chave.letra)//se o valor da letra for menor que o valor da letra apontada na arvore, vai para o nodo-filho a esquerda desse.
            return (2 + procura_avl(morse,arvore->esq,letra));
        else
            return (2 + procura_avl(morse,arvore->dir,letra));//Ao contrário vai para o nodo-filho a direita, soma 2(houve 2 comparações)
    }
    return 0;//Arvore vazia não houve comparações
}
//Procura em uma arvore abp uma char desejado, caso em contre a string morse se torna a forma morse da letra e o numero de comparações nessessárias para encontra-la,
//caso não encontre a palavra, apenas devolve o número de comparações que ocorreram até encontrar o fim da arvore
int procura_abp(char morse[], ABP *arvore, char letra)//Funcionamento igual ao procura_avl, diferença na entrada existe uma arvore ABP e não avl
{
    if(arvore != NULL)
    {
        if(letra == arvore->chave.letra)
        {
            strcpy(morse, arvore->chave.morse);
            return 1;
        }
        else
            strcpy(morse, " ");
        if(letra < arvore->chave.letra)
            return (2 + procura_abp(morse, arvore->esq, letra));
        else
            return (2 + procura_abp(morse, arvore->dir, letra));
    }
    return 0;
}
