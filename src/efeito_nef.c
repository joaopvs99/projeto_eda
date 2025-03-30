/**
 * @file efeito_nef.c
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief funções relativas ao efeito nefasto
 * @version 1.0
 * @date 2025-03-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/efeito_nef.h"

Matriz *calcular_efeito(Matriz *head)
{
    if (!head)
    {
        perror("Não foi possível carregar a matriz.\n");
        return NULL;
    }
    Matriz *matriz_efeitos = head;
    Emissor *aux = head->lista_emissores;
    Emissor *aux2 = NULL;
    int efeito_encontrado = 0;
    while (aux)
    {
        aux2 = aux->next;

        while (aux2)
        {
            // se o sinal for igual
            if (aux->sinal == aux2->sinal)
            {
                // distancia em x das duas antenas com a mesma freq
                int vetorX = aux2->x - aux->x;
                // distancia em y das duas antenas com a mesma freq
                int vetorY = aux2->y - aux->y;
                // coordenada x do primeiro ponto nefasto
                int nef1X = vetorX + aux2->x;
                // coordenada y do primeiro ponto nefasto
                int nef1Y = vetorY + aux2->y;
                // coordenada x do segundo ponto nefasto
                int nef2X = aux->x - vetorX;
                // coordenada y do segundo ponto nefasto
                int nef2Y = aux->y - vetorY;

                if (nef1X < head->x && nef1Y < head->y)
                {
                    matriz_efeitos->lista_emissores =
                        inserir_emissor(matriz_efeitos->lista_emissores, '#', nef1X, nef1Y);
                    efeito_encontrado = 1;
                }

                if (nef2X >= 0 && nef2Y >= 0)
                {
                    matriz_efeitos->lista_emissores =
                        inserir_emissor(matriz_efeitos->lista_emissores, '#', nef2X, nef2Y);
                    efeito_encontrado = 1;
                }
            }

            aux2 = aux2->next;
        }
        aux = aux->next;
    }

    if (!efeito_encontrado)
    {
        printf("Nenhum efeito nefasto encontrado para a matriz\n");
        return NULL;
    }
    return matriz_efeitos;
};
void alerta()
{
    printf("\033[1;31m");
}
void reset_alerta()
{
    printf("\033[0m"); // Reseta para a cor padrão do terminal
}

void imprime_matriz_efeito(Matriz *matriz_efeitos)
{
    if (!matriz_efeitos)
    {
        perror("Erro ao carregar lista de antenas");
        return;
    }

    for (int i = 0; i < matriz_efeitos->y; i++)
    {
        for (int j = 0; j < matriz_efeitos->x; j++)
        {
            Emissor *aux = matriz_efeitos->lista_emissores;

            // flag para verificar emissores encontrados
            int emissor_encontrado = 0;
            // Verifica se existe um emissor nas coordenadas (i, j)
            while (aux)
            {
                if (aux->x == j && aux->y == i)
                {
                    // verifica a existencia de dois emissores com a mesmas coordenadas
                    //(presença de efeito nefasto)
                    if (aux->next && (aux->x == aux->next->x && aux->y == aux->next->y))
                    {
                        // prensença de dois efeitos nefastos na mesma zona
                        if (aux->sinal == '#' && aux->next->sinal == '#')
                        {
                            // não imprime sinal de alerta
                            printf("%c", aux->sinal);
                            emissor_encontrado = 1;
                        }
                        else
                            // imprime apenas a frequencia da antena com alerta a
                            // vermelho
                            if (aux->sinal == '#')
                            {
                                alerta();
                                printf("%c", aux->next->sinal);
                                reset_alerta();
                                emissor_encontrado = 1;
                            }
                            else
                            {
                                alerta();
                                printf("%c", aux->sinal);
                                reset_alerta();
                                emissor_encontrado = 1;
                            }
                        aux = aux->next;
                    }
                    else
                    {
                        printf("%c", aux->sinal);
                        emissor_encontrado = 1;
                    }
                    break;
                }
                aux = aux->next;
            }

            if (!emissor_encontrado)
            {
                printf(".");
            }
        }
        printf("\n");
    }
};
