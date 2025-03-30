/**
 * @file matriz.c
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief funções relativas à matriz
 * @version 1.0
 * @date 2025-03-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/matriz.h"

int guardar_matriz(Matriz *head)
{
    if (!head) // Primeiro verifica se a matriz é nula
    {
        perror("Erro: Matriz inválida.\n");
        return 1;
    }

    FILE *fp = fopen("./data/data.bin", "wb");
    if (!fp)
    {
        perror("Erro ao abrir ficheiro para escrita.\n");
        return 1;
    }
    Emissor *aux = NULL;

    // guardar a estrutura da matriz
    fwrite(head, 1, sizeof(Matriz), fp);

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

Matriz *ler_matriz()
{
    FILE *fp = fopen("./data/data.bin", "rb");
    if (!fp)
    {
        perror("Erro ao abrir ficheiro para leitura.\n");
        return NULL;
    }

    // Alocar memória para a matriz
    Matriz *m = (Matriz *)malloc(sizeof(Matriz));
    if (!m)
    {
        perror("Erro ao alocar memória para matriz.\n");
        free(m);
        fclose(fp);
        return NULL;
    }

    // Ler a estrutura da Matriz
    fread(m, sizeof(Matriz), 1, fp);
    m->lista_emissores = NULL;

    // Reconstruir a lista de emissors
    Emissor temp;
    while (fread(&temp, sizeof(Emissor), 1, fp) == 1)
    {

        m->lista_emissores = inserir_emissor(m->lista_emissores, temp.sinal, temp.x, temp.y);
    }

    fclose(fp);
    printf("Matriz carregada com sucesso.\n");
    return m;
}

void imprime_matriz(Matriz *head)
{

    if (!head)
    {
        perror("Erro ao carregar matriz");
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

Matriz *importar_matriz(const char *filename)
{
    Matriz *nova = (Matriz *)malloc(sizeof(Matriz));
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror("Erro: não foi possível abrir o ficheiro\n");
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
            nova->lista_emissores = inserir_emissor(nova->lista_emissores, c, x, y);
            x++;
        }
        else // Espaços devem ser contados
        {
            x++;
        }
    }

    fclose(fp);

    // dimensões da matriz
    nova->x = x;
    nova->y = y + 1;

    guardar_matriz(nova);
    // Matriz *teste = ler_matriz();
    // imprime_matriz(teste);
    // emissor *nova_lista = NULL;
    // nova_lista = libertar_emissor(lista_emissores, 0, 0);
    // printf("\n");
    // imprimir_emissors(nova_lista);
    return nova;
}