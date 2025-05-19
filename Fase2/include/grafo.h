/**
 * @file grafo.h
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief Tipos de dados e funções associadas ao grafo de antenas
 * @version 1.2
 * @date 2025-05-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef GRAFO_H
#define GRAFO_H
#pragma once
#include "trata_erro.h"
#include <stdbool.h>
#include <math.h>

/**
 * @brief Estrutura de um vértice
 *
 */
typedef struct Vertice
{
    char sinal; // Ex: 'A', 'B', etc. (frequência da antena)
    int x, y;   // Coordenadas na matriz
    int id;
    bool visitado;           // Identificador único do vértice
    struct Adj *adjacencias; // Lista de adjacências (arestas)
    struct Vertice *prox;    // Próximo vértice na lista
} Vertice;

/**
 * @brief  Cria um novo vértice
 *
 * @param sinal
 * @param x
 * @param y
 * @param id
 * @return Vertice*
 */
Vertice *CriarVertice(char sinal, int x, int y, int id);
/**
 * @brief  Insere um novo vértice na lista de vértices
 *
 * @param novo
 * @param head
 * @param codigo
 * @return Vertice*
 */
Vertice *InsereVertice(Vertice *novo, Vertice *head, CodigoErro *codigo);
/**
 * @brief  Procura um vértice na lista de vértices
 *
 * @param head
 * @param id
 * @return Vertice*
 */
Vertice *ProcurarVertice(Vertice *head, int id);

/**
 * @brief  LMostra todos os vértices da lista
 *
 * @param head
 */
void MostraVertices(Vertice *head);

/**
 * @brief Estrutura de uma adjacência
 *
 */
typedef struct Adj
{
    float distancia; // distância entre antenas
    int idDestino;   // ID do vértice de destino
    struct Adj *next;
} Adj;

/**
 * @brief Cria uma nova adjacência
 *
 * @param dist
 * @param idDestino
 * @return AdjD*
 */
Adj *CriaAdjacencia(float dist, int idDestino);

/**
 * @brief Insere uma nova adjacência na lista de adjacências
 *
 * @param head
 * @param nova
 * @param idOrigem
 * @param idDestino
 * @param codigo
 * @return Vertice*
 */
Vertice *InsereAdjacencia(Vertice *head, Adj *nova, int idOrigem, int idDestino, CodigoErro *codigo);

/**
 * @brief Calcula a distância entre dois vértices
 *
 * @param v1
 * @param v2
 * @return float
 */
float CalculaDistancia(Vertice *v1, Vertice *v2);
/**
 * @brief Mostra todas as adjacências de um vértice
 *
 * @param head
 */
void MostraListaAdjacencias(Vertice *head);

/**
 * @brief Estrutura do grafo
 *
 */
typedef struct GrafoAntenas
{
    int numVertices;
    Vertice *head;
} GrafoAntenas;

/**
 * @brief Cria um novo grafo
 *
 * @return GrafoAntenas*
 */
GrafoAntenas *CriarGrafo();

void ImprimeGrafo(GrafoAntenas *grafo);
/**
 * @brief  Guarda o grafo num ficheiro binário
 *
 * @param fileName
 * @param grafo
 * @return true
 * @return false
 */
bool GuardaGrafo(const char *fileName, GrafoAntenas *grafo);
/**
 * @brief  Lê o grafo de um ficheiro binário
 *
 * @param fileName
 * @return GrafoAntenas*
 */
GrafoAntenas *CarregaGrafo(char *fileName, CodigoErro *codigo);

/**
 * @brief Importa um grafo de um ficheiro de texto
 *
 * @param fileName
 * @return GrafoAntenas*
 */
GrafoAntenas *ImportaGrafo(const char *fileName, CodigoErro *codigo);

/**
 * @brief Cria todas as adjacências entre os vértices do grafo
 *
 * @param grafo
 * @param codigo
 * @return GrafoAntenas*
 */
GrafoAntenas *CriarTodasAdjacencias(GrafoAntenas *grafo, CodigoErro *codigo);

/**
 * @brief Realiza uma busca em profundidade no grafo a partir de um vértice de origem
 *
 * @param grafo
 * @param idOrigem
 * @param codigo
 * @return GrafoAntenas*
 */

/**
 * @brief  Estrutura de um resultado de pesquisa
 *
 */

#endif
