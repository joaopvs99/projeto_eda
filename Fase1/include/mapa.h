/**
 * @file mapa.h
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief Estrutura da mapa e função associadas
 * @version 1.0
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef mapa_H
#define mapa_H
#include "emissor.h"
#pragma once

/**
 * @brief Estrutura de uma mapa
 * @var x -> tamanho x da mapa
 * @var y -> tamanho y da mapa
 * @var *lista_emissors -> lista de emissors da mapa
 *
 */
typedef struct Mapa
{
    int x, y;
    struct Emissor *lista_emissores;
} Mapa;

/**
 * @brief carrega emissors para uma lista ligada apartir de um ficheiro de texto
 * com uma mapa
 *
 * @param filename de um ficheiro TXT com mapa das emissors
 * @return mapa* lista de emissors
 */
Mapa *importar_mapa(const char *filename, CodigoErro *codigo);

/**
 * @brief guarda a mapa com as emissors e efeitos para um ficheiro binário.
 *
 * @param m
 * @return int (0 -> sucesso, 1 -> erro)
 */
int guardar_mapa(Mapa *head, CodigoErro *codigo);

/**
 * @brief lê a mapa guardada no ficheiro binário e traduz para a estrura
 *
 * @return mapa*
 */
Mapa *ler_mapa(CodigoErro *codigo);
/**
 * @brief Imprime a mapa recebida por parametro na consola
 *
 * @param m
 */
void imprime_mapa(Mapa *head, CodigoErro *codigo);

#endif
