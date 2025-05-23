/**
 * @file menu.h
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief Funções associadas ao menu da consola
 * @version 1.2
 * @date 2025-03-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef MENU_H
#define MENU_H
#include "efeito_nef.h"

#pragma once

/**
 * @brief indica se o ficheiro de memória data.bin está vazio
 *
 * @return ->1 se estiver vazio -> 0 caso contrários
 */
int memoria_esta_vazia(CodigoErro *codigo);
/**
 * @brief Exibe sequências de printfs alusivas ao menu.
 *
 */
void mostrar_menu(CodigoErro *codigo);

/**
 * @brief Pede ao utilizador o valor da frequencia e as suas coordenadas,
 * de seguida, insere a antena e guarda a matriz na memória
 *
 */
void menu_inserir_antena(CodigoErro *codigo);

/**
 * @brief Pede ao utilizador as coordenadas da antena,
 * de seguida, remove a antena e guarda a matriz na memória
 *
 */
void menu_remover_antena(CodigoErro *codigo);

/**
 * @brief Mostra e controla o menu principal do programa
 *
 */
void menu_principal();

/**
 * @brief Mostra a tabela de antenas e efeitos nefastos
 *
 */
void listar_antenas_efeitos(CodigoErro *codigo);
#endif