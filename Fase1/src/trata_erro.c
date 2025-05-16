/**
 * @file trata_erro.c
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief funções relativasao tratamento de erro
 * @version 1.0
 * @date 2025-03-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../include/trata_erro.h"

/**
 * @brief Função para tratar erros
 *
 * @param codigo -> código de erro
 */
void trataErro(CodigoErro *codigo)
{
    // Verifica se o código de erro é válido
    switch (*codigo)
    {
    case SUCESSO:
        break;
    case ERRO_SEM_MEMORIA:
        printf("ERRO: Sem memória para o procedimento\n");
        break;
    case ERRO_FICHEIRO_NAO_ENCONTRADO:
        printf("ERRO: Nenhum ficheiro encontrado\n");
        break;
    case ERRO_FICHEIRO_VAZIO:
        printf("ERRO: O ficheiro está vazio\n");
        break;
    case ERRO_LISTA_VAZIA:
        printf("ERRO: A lista está vazia.\n");
        break;
    case ERRO_EMISSOR_NAO_ENCONTRADO:
        printf("ERRO: Nenhum emissor encontrado.\n");
        break;
    case ERRO_NENHUM_EFEITO:
        printf("Nenhum efeito nefasto encontrado.\n");
        break;
    default:
        printf("ERRO: Erro desconhecido\n");
    }
}