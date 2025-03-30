/**
 * @file efeito_nef.h
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief Estrura do efeito nefasto e funções a associadas
 * @version 1.0
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef EFEITONEF_H
#define EFEITONEF_H
#include <string.h>
#include "matriz.h"

#pragma once

/**
 * @brief Calcula os efeitos nefasto para uma dada matriz
 *
 * @param m -> matriz sem efeitos nefastos
 * @return Emissor* -> lista de efeitos nefastos
 */
Matriz *calcular_efeito(Matriz *head);

/**
 * @brief Imprime na consola a matriz correspondente com antenas e
 * efeitos nefastos aplicados
 *
 * @param matriz_efeitos -> matriz com efeitos nefastos aplicados

 */
void imprime_matriz_efeito(Matriz *matriz_efeitos);

/**
 * @brief muda cor do texto para vermelho para alertar de efeito nefasto
 *
 */
void alerta();

/**
 * @brief reset da cor para o original
 *
 */
void reset_alerta();

#endif
