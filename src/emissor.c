/**
 * @file emissor.c
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief funções relativas aos emissores
 * @version 1.0
 * @date 2025-03-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/emissor.h"
Emissor *inserir_emissor(Emissor *head, char sinal, int x, int y)
{
    // Criar novo nó
    Emissor *novo = (Emissor *)malloc(sizeof(Emissor));
    if (!novo)
    {
        perror("Erro ao alocar memória\n");
        return head;
    }

    novo->sinal = sinal;
    novo->x = x;
    novo->y = y;
    novo->next = NULL;

    // Caso a lista esteja vazia ou o emissor deva ser o primeiro elemento
    if (!head || (y < head->y) || (y == head->y && x < head->x))
    {
        novo->next = head;
        return novo;
    }

    // Percorrer a lista até encontrar a posição correta
    Emissor *aux = head;
    while (aux->next && ((aux->next->y < y) ||
                         (aux->next->y == y && aux->next->x < x)))
    {
        aux = aux->next;
    }

    // Inserir a novo emissor
    novo->next = aux->next;
    aux->next = novo;

    return head;
}

Emissor *remover_emissor(Emissor *head, int x, int y)
{
    if (!head)
    {
        printf("Não há emissores a ser removidos\n");
        return NULL;
    }
    Emissor *aux = head;
    Emissor *aux2 = NULL;
    while (aux)
    {
        // se for um efeito nefasto, avança na lista
        if (aux->sinal == '#')
        {
            aux2 = aux;
            aux = aux->next;
        }
        if ((aux->x == x) && (aux->y == y))
        {

            if (!aux2) // caso seja o primeiro elemento da lista
            {
                aux2 = aux->next;
                free(aux);
                return aux2;
            }
            else
            {
                aux2->next = aux->next;
                free(aux);
                return head;
            }
        }

        aux2 = aux;
        aux = aux->next;
    }
    printf("Não existe emissor nas coordenadas introduzidas '(%d,%d)'\n", x, y);
    return head;
}
