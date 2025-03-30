/**
 * @file emissor.h
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief Estrutura da emissor e funções associadas
 * @version 1.0
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef EMISSOR_H
#define EMISSOR_H
#include <stdio.h>
#include <stdlib.h>

#pragma once

/**
 * @brief Estrutura de uma emissor
 * @var sinal -> frequencia da emissor (ex A,B,C...) ou simbolo
 * de efeito nefasto (#)
 * @var x -> coordenada x do emissor
 * @var y -> coordenada y da emissor
 * @var *next -> proximo emissor da lista
 *
 */
typedef struct Emissor
{
    char sinal;
    int x, y;
    struct Emissor *next;
} Emissor;

/**
 * @brief função para inserir novo emissor na lista
 *
 * @param head cabeça da lista de emissors
 * @param freq frequencia
 * @param x coordenada x
 * @param y  coordenada y
 * @return Lista ordenada com nova emissor inserida (emissor*)
 */
Emissor *inserir_emissor(Emissor *head, char sinal, int x, int y);

Emissor *remover_emissor(Emissor *head, int x, int y);

#endif