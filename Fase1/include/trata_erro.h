/**
 * @file trata_erro.h
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief Estrutura de erro e funções associadas
 * @version 1.2
 * @date 2025-05-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef TRATAERRO_H
#define TRATAERRO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma once

/**
 * @brief Estrutura do enumerador de erros
 *
 */
typedef enum CodigoErro
{
    SUCESSO,
    ERRO_SEM_MEMORIA,
    ERRO_FICHEIRO_NAO_ENCONTRADO,
    ERRO_FICHEIRO_VAZIO,
    ERRO_LISTA_VAZIA,
    ERRO_EMISSOR_NAO_ENCONTRADO,
    ERRO_NENHUM_EFEITO,
} CodigoErro;

/**
 * @brief Função para tratar erros
 *
 * @param codigo -> código de erro
 */
void trataErro(CodigoErro *codigo);

#endif
