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

/**
 * @brief função para inserir novo emissor na lista
 *
 * @param head cabeça da lista de emissors
 * @param freq frequencia
 * @param x coordenada x
 * @param y  coordenada y
 * @return Lista ordenada com nova emissor inserida (emissor*)
 */
Emissor *inserir_emissor(Emissor *head, char sinal, int x, int y, CodigoErro *codigo)
{
    // Criar novo nó
    Emissor *novo = (Emissor *)malloc(sizeof(Emissor));
    if (!novo)
    {
        *codigo = ERRO_SEM_MEMORIA;
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
        *codigo = SUCESSO;
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
    *codigo = SUCESSO;
    return head;
}

/**
 * @brief função para remover emissor da lista
 *
 * @param head cabeça da lista de emissores
 * @param freq frequencia
 * @param x coordenada x
 * @param y  coordenada y
 * @return Nova lista sem o emissor (emissor*)
 */
Emissor *remover_emissor(Emissor *head, int x, int y, CodigoErro *codigo)
{
    if (!head)
    {
        // "Não há emissores a ser removidos"
        *codigo = ERRO_LISTA_VAZIA;
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
                *codigo = SUCESSO;
                return aux2;
            }
            else
            {
                aux2->next = aux->next;
                free(aux);
                *codigo = SUCESSO;
                return head;
            }
        }

        aux2 = aux;
        aux = aux->next;
    }
    //"Não existe emissor nas coordenadas introduzidas '(%d,%d)'\n"
    *codigo = ERRO_EMISSOR_NAO_ENCONTRADO;
    return head;
}
