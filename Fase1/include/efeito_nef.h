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
#include "mapa.h"

#pragma once

/**
 * @brief Calcula os efeitos nefasto para uma dada mapa
 *
 * @param m -> mapa sem efeitos nefastos
 * @return Emissor* -> lista de efeitos nefastos
 */
Mapa *calcular_efeito(Mapa *head, CodigoErro *codigo);

/**
 * @brief Imprime na consola a mapa correspondente com antenas e
 * efeitos nefastos aplicados
 *
 * @param mapa_efeitos -> mapa com efeitos nefastos aplicados

 */
void imprime_mapa_efeito(Mapa *mapa_efeitos, CodigoErro *codigo);

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

/**
 * @brief Copia a lista de emissores para efeitos de pesquisa
 *
 * @param origem
 * @return Emissor*
 */
Emissor *copiar_lista_emissores(Emissor *origem, CodigoErro *codigo);

#endif
