/**
 * @file busca.h
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief  Estruturas e funções para busca  no grafo
 * @version 1.2
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef BUSCA_H
#define BUSCA_H
#pragma once
#include "grafo.h"
typedef struct Listagem
{
    Vertice *vertice; // Ponteiro para o vértice original
    struct Listagem *next;
} Listagem;

/**
 * @brief Adiciona um vértice à stack (LIFO)
 *
 * @param topo
 * @param v
 * @return Listagem*
 */
void pushStack(Listagem **topo, Vertice *v, CodigoErro *codigo);

/**
 * @brief Remove um vértice da stack (LIFO)
 *
 * @param topo
 * @return Vertice*
 */
Vertice *popStack(Listagem **topo);

/**
 * @brief  Realiza uma busca em profundidade no grafo a partir de um vértice de origem
 *
 * @param grafo
 * @param idOrigem
 * @param codigo
 * @return ResultadoPesquisa*
 */

/**
 * @brief Liberta a memória ocupada pela lista de resultados
 *
 * @param lista
 */
void LimparLista(Listagem *lista);

Listagem *DepthFirstSearch(GrafoAntenas *grafo, int idOrigem, CodigoErro *codigo);

/**
 * @brief Realiza uma busca em largura no grafo a partir de um vértice de origem
 *
 * @param grafo
 * @param idOrigem
 * @param codigo
 * @return ResultadoPesquisa*
 */
Listagem *BreadthFirstSearch(GrafoAntenas *grafo, int idOrigem, CodigoErro *codigo);

/**
 * @brief Imprime a lista de resultados de uma pesquisa (DFS, BFS)
 *
 * @param lista
 */
void ImprimirListaResultado(Listagem *lista);

/**
 * @brief  Estrutura dos caminhos encontrados
 *
 */
typedef struct Caminho
{
    Listagem *caminho;
    float distanciaTotal; // Lista de vértices visitados
    struct Caminho *next;
} Caminho;

/**
 * @brief Função que inicializa a busca de caminhos entre dois vértices
 *
 * @param grafo
 * @param idOrigem
 * @param idDestino
 * @param codigo
 * @return Caminho*
 */
Caminho *ProcuraCaminhos(GrafoAntenas *grafo, int idOrigem, int idDestino, CodigoErro *codigo);

/**
 * @brief Imprime todos os caminhos encontrados
 *
 * @param listaCaminhos
 */
void ImprimirTodosCaminhos(Caminho *listaCaminhos);

/**
 * @brief  Liberta a memória ocupada pela lista de resultados
 *
 * @param lista
 */
void LimparVisitados(GrafoAntenas *grafo);

/**
 * @brief Liberta a memória ocupada pela lista de caminhos
 *
 * @param c
 */

void LimparCaminhos(Caminho *c);
/**
 * @brief Procura interceções entre dois vértices
 *
 * @param grafo
 * @param id1
 * @param id2
 * @param codigo
 * @return Caminho*
 */
Caminho *ProcuraIntercetores(GrafoAntenas *grafo, int id1, int id2, CodigoErro *codigo);

#endif