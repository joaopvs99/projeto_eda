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
#include "busca.h"

#pragma once

/**
 * @brief indica se o ficheiro de memória data.bin está vazio
 *
 * @return ->1 se estiver vazio -> 0 caso contrários
 */
int MemoriaEstaVazia(CodigoErro *codigo);
/**
 * @brief Exibe sequências de printfs alusivas ao menu.
 *
 */
void MostrarMenu(CodigoErro *codigo);

/**
 * @brief Mostra menu de pesquisa em profundidade
 *
 * @param codigo
 */
void MostrarMenuDfs(CodigoErro *codigo);

/**
 * @brief Mostra menu de pesquisa em largura
 *
 * @param codigo
 */
void MostrarMenuBfs(CodigoErro *codigo);

/**
 * @brief Mostra e controla o menu principal do programa
 *
 */
void MenuPrincipal();

#endif