/**
 * @file mapa.c
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief funções relativas ao mapa
 * @version 1.0
 * @date 2025-03-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/mapa.h"

int guardar_mapa(Mapa *head, CodigoErro *codigo)
{
    if (!head) // Primeiro verifica se a mapa é nula
    {
        *codigo = ERRO_LISTA_VAZIA;
        return 1;
    }

    FILE *fp = fopen("data/data.bin", "wb");
    if (!fp)
    {
        *codigo = ERRO_FICHEIRO_NAO_ENCONTRADO;
        return 1;
    }
    Emissor *aux = NULL;

    // guardar a estrutura da mapa
    fwrite(head, 1, sizeof(Mapa), fp);

    // guardar a lista de emissors associada
    aux = head->lista_emissores;
    while (aux)
    {
        fwrite(aux, sizeof(Emissor), 1, fp);
        aux = aux->next;
    }

    fclose(fp);
    return 0;
}

Mapa *ler_mapa(CodigoErro *codigo)
{
    FILE *fp = fopen("data/data.bin", "rb");
    if (!fp)
    {
        *codigo = ERRO_FICHEIRO_NAO_ENCONTRADO;
        return NULL;
    }

    // Alocar memória para a mapa
    Mapa *m = (Mapa *)malloc(sizeof(Mapa));
    if (!m)
    {
        *codigo = ERRO_SEM_MEMORIA;
        free(m);
        fclose(fp);
        return NULL;
    }

    // Ler a estrutura da mapa
    fread(m, sizeof(Mapa), 1, fp);
    m->lista_emissores = NULL;

    // Reconstruir a lista de emissors
    Emissor temp;
    while (fread(&temp, sizeof(Emissor), 1, fp) == 1)
    {

        m->lista_emissores = inserir_emissor(m->lista_emissores, temp.sinal, temp.x, temp.y, codigo);
    }

    fclose(fp);
    *codigo = SUCESSO;
    return m;
}

void imprime_mapa(Mapa *head, CodigoErro *codigo)
{

    if (!head)
    {
        *codigo = ERRO_LISTA_VAZIA;
    }
    for (int i = 0; i < head->y; i++)
    {
        for (int j = 0; j < head->x; j++)
        {
            Emissor *aux = head->lista_emissores;

            // flag para verificar emissores encontrados
            int emissor_encontrado = 0;
            // Verifica se existe um emissor nas coordenadas (i, j)
            while (aux)
            {
                if (aux->x == j && aux->y == i)
                {
                    // Se encontrou, imprime o sinal do emissor
                    printf("%c", aux->sinal);
                    emissor_encontrado = 1;
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
}

/**
 * @brief carrega emissors para uma lista ligada apartir de um ficheiro de texto
 * com uma mapa
 *
 * @param filename de um ficheiro TXT com mapa das emissors
 * @return mapa* lista de emissors
 */
Mapa *importar_mapa(const char *filename, CodigoErro *codigo)
{
    Mapa *nova = (Mapa *)malloc(sizeof(Mapa));
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        *codigo = ERRO_FICHEIRO_NAO_ENCONTRADO;
        return NULL;
    }

    nova->lista_emissores = NULL;
    int x = 0, y = 0;
    char c;

    // Leitura do ficheiro char a char
    while ((c = fgetc(fp)) != EOF) // Verifica se leu corretamente
    {
        if (c == '\n') // Nova linha -> incrementa y e reset ao x
        {
            x = 0;
            y++;
        }
        else if (c != '.' && c != '\r') // Se não for ponto ou carriage return, é uma emissor
        {
            nova->lista_emissores = inserir_emissor(nova->lista_emissores, c, x, y, codigo);
            x++;
        }
        else // Espaços devem ser contados
        {
            x++;
        }
    }

    fclose(fp);

    // dimensões da mapa
    nova->x = x;
    nova->y = y + 1;

    guardar_mapa(nova, codigo);
    if (codigo != SUCESSO)
    {
        trataErro(codigo);
    }
    *codigo = SUCESSO;
    return nova;
}