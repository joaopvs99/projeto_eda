/**
 * @file grafo.c
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief Funções associadas ao grafo
 * @version 1.2
 * @date 2025-05-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../include/grafo.h"

GrafoAntenas *CriarGrafo()
{
    GrafoAntenas *novo = (GrafoAntenas *)malloc(sizeof(GrafoAntenas));
    if (novo == NULL)
        return NULL;

    novo->head = NULL;     // Lista de vértices começa vazia
    novo->numVertices = 0; // Ainda não há vértices

    return novo;
}

void ImprimeGrafo(GrafoAntenas *grafo)
{
    if (grafo == NULL)
    {
        printf("Grafo está vazio.\n");
        return;
    }

    Vertice *atual = grafo->head;
    printf("Grafo com %d vértice(s):\n\n", grafo->numVertices);

    while (atual != NULL)
    {
        printf("Vértice ID: %d | Sinal: %c | Coordenadas: (%d, %d)\n", atual->id, atual->sinal, atual->x, atual->y);

        Adj *adj = atual->adjacencias;
        if (adj == NULL)
        {
            printf("  -> Sem adjacências\n");
        }
        else
        {
            printf("  -> Adjacências:\n");
            while (adj != NULL)
            {
                printf("     -> Para ID: %d | Distância: %.2f\n", adj->idDestino, adj->distancia);
                adj = adj->next;
            }
        }

        printf("\n");
        atual = atual->prox;
    }
}

GrafoAntenas *ImportaGrafo(const char *filename, CodigoErro *codigo)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        *codigo = ERRO_FICHEIRO_NAO_ENCONTRADO;
        return NULL;
    }

    GrafoAntenas *grafo = CriarGrafo();
    if (!grafo)
    {
        *codigo = ERRO_MEMORIA;
        fclose(fp);
        return NULL;
    }

    grafo->head = NULL;
    grafo->numVertices = 0;

    int x = 0, y = 0, id = 0;
    char c;

    // Leitura do ficheiro caractere a caractere
    while ((c = fgetc(fp)) != EOF)
    {
        // Debug: Mostra o caractere lido
        if (c == '\n')
        {
            x = 0;
            y++;
        }
        else if (c != '.' && c != '\r') // Se for uma antena
        {
            Vertice *novo = CriarVertice(c, x, y, id++);
            if (!novo)
            {
                *codigo = ERRO_MEMORIA;
                fclose(fp);
                return grafo;
            }

            grafo->head = InsereVertice(novo, grafo->head, codigo);
            if (*codigo != SUCESSO)
            {
                fclose(fp);
                return grafo;
            }

            grafo->numVertices++;
            x++;
        }
        else
        {
            x++;
        }
    }

    fclose(fp);

    *codigo = SUCESSO;
    if (!GuardaGrafo("../data/grafo.bin", grafo))
        *codigo = ERRO_FICHEIRO_NAO_ENCONTRADO;
    return grafo;
}

bool GuardaGrafo(const char *fileName, GrafoAntenas *grafo)
{
    FILE *fp = fopen(fileName, "wb");
    if (!fp)
    {
        return false;
    }

    // Escrever o número de vértices
    fwrite(&grafo->numVertices, sizeof(int), 1, fp);

    // Escrever os vértices (dados básicos)
    Vertice *v = grafo->head;
    while (v != NULL)
    {
        fwrite(&v->id, sizeof(int), 1, fp);
        fwrite(&v->sinal, sizeof(char), 1, fp);
        fwrite(&v->x, sizeof(int), 1, fp);
        fwrite(&v->y, sizeof(int), 1, fp);
        fwrite(&v->visitado, sizeof(float), 1, fp); // Escrever o valor de visitado (não utilizado)

        v = v->prox;
    }

    fclose(fp);
    return true;
}

GrafoAntenas *CarregaGrafo(char *fileName, CodigoErro *codigo)
{
    FILE *fp = fopen(fileName, "rb");
    if (!fp)
    {
        *codigo = ERRO_FICHEIRO_NAO_ENCONTRADO;
        return NULL;
    }

    GrafoAntenas *grafo = CriarGrafo();
    if (!grafo)
    {
        *codigo = ERRO_MEMORIA;
        fclose(fp);
        return NULL;
    }

    // Lê o número de vértices
    fread(&grafo->numVertices, sizeof(int), 1, fp);

    int id;
    char sinal;
    int x, y;
    float visitado;
    // Lê os vértices
    grafo->head = NULL;
    for (int i = 0; i < grafo->numVertices; i++)
    {
        fread(&id, sizeof(int), 1, fp);
        fread(&sinal, sizeof(char), 1, fp);
        fread(&x, sizeof(int), 1, fp);
        fread(&y, sizeof(int), 1, fp);
        fread(&visitado, sizeof(float), 1, fp); // Lê o valor de visitado (não utilizado)

        Vertice *novo = CriarVertice(sinal, x, y, id);
        novo = InsereVertice(novo, grafo->head, codigo);
        if (*codigo != SUCESSO)
        {
            fclose(fp);
            return grafo;
        }
        grafo->head = novo;
    }
    // Depoid de carregar os vértices, cria todas as adjacências automaticamente
    grafo = CriarTodasAdjacencias(grafo, codigo);
    if (*codigo != SUCESSO)
    {
        fclose(fp);
        return grafo;
    }
    fclose(fp);
    *codigo = SUCESSO;
    return grafo;
}

Vertice *CriarVertice(char sinal, int x, int y, int id)
{
    Vertice *novo = (Vertice *)malloc(sizeof(Vertice));
    if (novo == NULL)
        return NULL;

    novo->sinal = sinal;
    novo->x = x;
    novo->y = y;
    novo->id = id;
    novo->visitado = false;
    novo->adjacencias = NULL;
    novo->prox = NULL;

    return novo;
}

Vertice *InsereVertice(Vertice *novo, Vertice *head, CodigoErro *codigo)
{
    if (!novo)
    {
        *codigo = ERRO_MEMORIA;
        return head;
    }

    // Caso a lista esteja vazia ou o vertice deva ser o primeiro elemento
    if (!head || (novo->y < head->y) || (novo->y == head->y && novo->x < head->x))
    {
        novo->prox = head;
        *codigo = SUCESSO;
        return novo;
    }

    // Percorrer a lista até encontrar a posição correta
    Vertice *aux = head;
    while (aux->prox && ((aux->prox->y < novo->y) ||
                         (aux->prox->y == novo->y && aux->prox->x < novo->x)))
    {
        aux = aux->prox;
    }

    // Inserir o novo vertice
    novo->prox = aux->prox;
    aux->prox = novo;
    *codigo = SUCESSO;
    return head;
}

Vertice *ProcurarVertice(Vertice *head, int id)
{
    Vertice *atual = head;

    while (atual != NULL)
    {
        if (atual->id == id)
        {
            return atual;
        }
        atual = atual->prox;
    }

    return NULL; // Não encontrou
}

// adjacencias

Adj *CriaAdjacencia(float dist, int idDestino)
{
    Adj *nova = (Adj *)malloc(sizeof(Adj));
    if (!nova)
        return NULL;

    nova->distancia = dist;
    nova->idDestino = idDestino;
    nova->next = NULL;

    return nova;
}
Vertice *InsereAdjacencia(Vertice *head, Adj *nova, int idOrigem, int idDestino, CodigoErro *codigo)
{
    Vertice *origem = ProcurarVertice(head, idOrigem);
    Vertice *destino = ProcurarVertice(head, idDestino);

    if (!origem || !destino)
    {
        *codigo = ERRO_VERTICE_NAO_EXISTE;
        return head;
    }

    // Inserir no início da lista de adjacências do vértice de origem
    nova->next = origem->adjacencias;
    origem->adjacencias = nova;

    // Como o grafo é não orientado, criamos também a adjacência inversa
    Adj *inversa = CriaAdjacencia(nova->distancia, idOrigem);
    inversa->next = destino->adjacencias;
    destino->adjacencias = inversa;

    *codigo = SUCESSO;
    return head;
}
GrafoAntenas *CriarTodasAdjacencias(GrafoAntenas *grafo, CodigoErro *codigo)
{
    if (!grafo || !grafo->head)
    {
        *codigo = ERRO_GRAFO_VAZIO;
        return NULL;
    }

    Vertice *v1 = grafo->head;

    while (v1 != NULL)
    {
        Vertice *v2 = v1->prox;
        while (v2 != NULL)
        {
            if (v1->sinal == v2->sinal)
            {
                float dist = CalculaDistancia(v1, v2);

                // Cria e insere adjacência de v1 para v2
                Adj *a1 = CriaAdjacencia(dist, v2->id);
                grafo->head = InsereAdjacencia(grafo->head, a1, v1->id, v2->id, codigo);

                if (*codigo != SUCESSO)
                    return NULL; // falha crítica

                // A InsereAdjacencia já cria a inversa (v2->v1), por isso não é necessário repetir
            }

            v2 = v2->prox;
        }
        v1 = v1->prox;
    }

    *codigo = SUCESSO;
    return grafo;
}

float CalculaDistancia(Vertice *v1, Vertice *v2)
{
    return sqrt(pow(v2->x - v1->x, 2) + pow(v2->y - v1->y, 2));
}