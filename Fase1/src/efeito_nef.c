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

/**
 * @brief Calcula os efeitos nefasto para uma dada mapa
 *
 * @param m -> mapa sem efeitos nefastos
 * @return Emissor* -> lista de efeitos nefastos
 */
Mapa *calcular_efeito(Mapa *head, CodigoErro *codigo)
{
    if (!head)
    {
        *codigo = ERRO_LISTA_VAZIA;
        return NULL;
    }

    // Copiar só antenas válidas
    Emissor *emissores_originais = copiar_lista_emissores(head->lista_emissores, codigo);
    Emissor *mapa_emissores = head->lista_emissores;

    Emissor *a = emissores_originais;
    int efeito_encontrado = 0;

    while (a)
    {
        Emissor *b = a->next;
        while (b)
        {
            // Apenas se os sinais forem iguais
            if (a->sinal == b->sinal)
            {
                int dx = b->x - a->x;
                int dy = b->y - a->y;

                // Ponto nefasto 1: b + vetor
                int x1 = b->x + dx;
                int y1 = b->y + dy;

                // Ponto nefasto 2: a - vetor
                int x2 = a->x - dx;
                int y2 = a->y - dy;

                // Verifica se está dentro da mapa
                if (x1 >= 0 && x1 < head->x && y1 >= 0 && y1 < head->y)
                {
                    mapa_emissores = inserir_emissor(mapa_emissores, '#', x1, y1, codigo);
                    efeito_encontrado = 1;
                }

                if (x2 >= 0 && x2 < head->x && y2 >= 0 && y2 < head->y)
                {
                    mapa_emissores = inserir_emissor(mapa_emissores, '#', x2, y2, codigo);
                    efeito_encontrado = 1;
                }
            }

            b = b->next;
        }
        a = a->next;
    }

    // Atualizar a lista da mapa
    head->lista_emissores = mapa_emissores;

    // Libertar cópia temporária
    while (emissores_originais)
    {
        Emissor *temp = emissores_originais;
        emissores_originais = emissores_originais->next;
        free(temp);
    }

    if (!efeito_encontrado)
    {
        *codigo = ERRO_NENHUM_EFEITO;
        return NULL;
    }
    *codigo = SUCESSO;
    return head;
}
/**
 * @brief Copia a lista de emissores para efeitos de pesquisa
 *
 * @param origem
 * @return Emissor*
 */
Emissor *copiar_lista_emissores(Emissor *origem, CodigoErro *codigo)
{
    Emissor *nova_lista = NULL;
    Emissor *atual = origem;

    while (atual)
    {

        nova_lista = inserir_emissor(nova_lista, atual->sinal, atual->x, atual->y, codigo);

        atual = atual->next;
    }
    *codigo = SUCESSO;
    return nova_lista;
}
/**
 * @brief muda cor do texto para vermelho para alertar de efeito nefasto
 *
 */
void alerta()
{
    printf("\033[1;31m");
}

/**
 * @brief reset da cor para o original
 *
 */
void reset_alerta()
{
    printf("\033[0m"); // Reseta para a cor padrão do terminal
}

/**
 * @brief Imprime na consola a mapa correspondente com antenas e
 * efeitos nefastos aplicados
 *
 * @param mapa_efeitos -> mapa com efeitos nefastos aplicados

 */
void imprime_mapa_efeito(Mapa *mapa_efeitos, CodigoErro *codigo)
{
    if (!mapa_efeitos)
    {
        *codigo = ERRO_LISTA_VAZIA;
        return;
    }

    for (int i = 0; i < mapa_efeitos->y; i++)
    {
        for (int j = 0; j < mapa_efeitos->x; j++)
        {
            Emissor *aux = mapa_efeitos->lista_emissores;

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
    *codigo = SUCESSO;
};
