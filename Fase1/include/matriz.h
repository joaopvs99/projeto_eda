/**
 * @file matriz.h
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief Estrutura da matriz e função associadas
 * @version 1.0
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef MATRIZ_H
#define MATRIZ_H
#include "emissor.h"
#pragma once

/**
 * @brief Estrutura de uma matriz
 * @var x -> tamanho x da matriz
 * @var y -> tamanho y da matriz
 * @var *lista_emissors -> lista de emissors da matriz
 *
 */
typedef struct Matriz
{
    int x, y;
    struct Emissor *lista_emissores;
} Matriz;

/**
 * @brief carrega emissors para uma lista ligada apartir de um ficheiro de texto
 * com uma matriz
 *
 * @param filename de um ficheiro TXT com mapa das emissors
 * @return Matriz* lista de emissors
 */
Matriz *importar_matriz(const char *filename);

/**
 * @brief guarda a matriz com as emissors e efeitos para um ficheiro binário.
 *
 * @param m
 * @return int (0 -> sucesso, 1 -> erro)
 */
int guardar_matriz(Matriz *head);

/**
 * @brief lê a matriz guardada no ficheiro binário e traduz para a estrura
 *
 * @return Matriz*
 */
Matriz *ler_matriz();
/**
 * @brief Imprime a matriz recebida por parametro na consola
 *
 * @param m
 */
void imprime_matriz(Matriz *head);

#endif
