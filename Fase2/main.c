/**
 * @file main.c
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief Projeto de Avaliação de Estruturas de Dados Avançadas (EDA) FASE 2
 * @version 2.0
 * @date 2025-05-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "include/grafo.h"
int main()
{
    CodigoErro codigo;

    GrafoAntenas *grafo = CarregaGrafo("data/grafo.bin", &codigo);

    if (codigo != SUCESSO)
    {
        trataErro(&codigo);
        return 1;
    }
    if (GuardaGrafo("data/grafo.bin", grafo))
    {
        printf("Grafo guardado com sucesso.\n");
    }
    else
    {
        printf("Erro ao guardar o grafo.\n");
    }

    Listagem *pesquisa = DepthFirstSearch(grafo, 3, &codigo);
    if (codigo != SUCESSO)
    {
        trataErro(&codigo);
        return 1;
    }
    ImprimirListaResultado(pesquisa);
    return 0;
}