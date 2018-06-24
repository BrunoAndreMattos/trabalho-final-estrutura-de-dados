#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arvore.h"


FILE *arq1,*arq2;
//Função de traduzir texto,atualiza o numero de comparações totais feitas no progrmama e atualiza o string morse que será inserido no arquivo de texto
void Traduz_Abp(ABP *arvore, char letra, int *comparacoes, char morse[])
{
    if(letra == ' ')
        strcpy(morse, "/");
    else
    {
        *comparacoes = *comparacoes + procura_abp(morse, arvore, letra);//Atualiza o numero de comparações e a string
        if(strcmp(morse, " "))//Caso não encontre na arvore, string==" "
        {
            procura_acento(&letra);//Verifica se a letra tem um acento,se tiver ela sera modificada para sua repectiva letra sem acento e maiuscula
            *comparacoes = *comparacoes + procura_abp(morse, arvore, letra);//Procura novamene na arvore
        }
    }
    *comparacoes++;//Primeiro if,compara letra com espaço
}
//Mesma funcionalidade da função Traduz_Abp, muda como entrada uma arvore avl em vez de uma abp
void Traduz_Avl(AVL *arvore, char letra, int *comparacoes, char morse[])
{
    if(letra == ' ')
        strcpy(morse, "/");
    else
    {
        *comparacoes = *comparacoes + procura_avl(morse, arvore, letra);
        if(strcmp(morse," "))
        {
            procura_acento(&letra);
            *comparacoes = *comparacoes + procura_avl(morse, arvore, letra);
        }
    }
    *comparacoes++;
}

int main(int argc, char *argv[])
{
    AVL *arvore_avl;
    ABP *arvore_abp;

    int ok, comparacoes;

    char letra;
    INF chave;
    char morse[MAXMORSE];
    comparacoes= 0;//Comparações inicia com zero
    if(argc==5)//Se o numero de argumentos for 4, 1)tabela morse,2)texto de entrada, 3)texto de saida, 4)opção de arvore
    {
        arq1 = fopen(argv[1],"r");//Abre o arquivo com a tabela morse

        if(arq1!=NULL)//Se for aberto corretamente
        {
         if(strcmp(argv[4],"1") || strcmp(argv[4],"2"))//Caso a opção selecionada for 1 ou 2
          {

              if(strcmp(argv[4],"1")==0)//Caso a opçao for 1 -> cria uma arvore abp
            {

              arvore_abp = inicia_ABP();
                while(!feof(arq1))//Lê do arquivo até o final
                {
                    fscanf(arq1,"%c       %s\n", &chave.letra, chave.morse);
                    arvore_abp = Insere_Abp(chave, arvore_abp);//Insere na arvore
                }
            }
            else//Ao contrario faz o mesmo procedimento para arvore avl
            {
                arvore_avl = inicia_AVL();
                while(!feof(arq1))
                {
                    fscanf(arq1,"%c       %s\n", &chave.letra, chave.morse);
                    arvore_avl = Insere_Avl(chave, arvore_avl,&ok);
                }
            }
            fclose(arq1);//Fecha o arquivo
            arq1 = fopen(argv[2],"r");//Abre o arquivo que sera traduzido
            if(arq1!=NULL)
            {
                arq2 = fopen(argv[3],"w");//Abre o arquivo de saida, que terá a tradução para morse
                if(arq2!=NULL)
                {
                    while(!feof(arq1))
                    {
                        letra = fgetc(arq1);//Le letra do arquivo
                        letra = toupper(letra);//Transforma a letra em maiuscula
                        if(strcmp(argv[4],"2")==0)//Se opção ==2 -> procura em uma arvore avl
                            Traduz_Avl(arvore_avl, letra, &comparacoes, morse);
                        else//Ao contrario memso procedimento em uma abp
                            Traduz_Abp(arvore_abp, letra, &comparacoes, morse);
                        if(strcmp(morse, " ")!=0);//caso morse==" ", a letra não foi achada na arvore é ignorada
                        {
                            fprintf(arq2, morse, "%s");//grava a string no arquivo de saida
                            fputc(' ', arq2);//grava espaço para separação das letra
                        }
                    }
                    fclose(arq1);
                }
                fclose(arq2);
            }
            else
                printf("Erro abrir o segundo arquivo ");//Caso não consiga abrir o arquivo que deseja ser traduzido
            fclose(arq1);
            printf("Comparacoes: %d\n", comparacoes);//Imprime o numero de comparações feitas no programa
          }
          else
            printf("Opcao invalida: 1-ABP 2-AVL\n");//Caso não tenha colocado uma das opções disponiveis*/
        }
        else
            printf("Erro a abrir o primeiro arquivo");//Caso não consiga abir a table morse
        fclose(arq1);
    }
    else
        printf("Numero invalido de argumentos");//Caso o numero de argumentos for invalido( maior ou menor que 5)
    return 0;
}
