/**
 * @file busca.c
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief  Estruturas e funções para busca  no grafo
 * @version 1.2
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../include/busca.h"
#pragma region Listagem

/**
 * @brief Adiciona um vértice à stack (LIFO)
 *
 * @param topo
 * @param v
 * @return Listagem*
 */
void pushStack(Listagem **topo, Vertice *v, CodigoErro *codigo)
{
    Listagem *novo = malloc(sizeof(Listagem));
    if (!novo)
    {
        *codigo = ERRO_MEMORIA;
        return;
    }
    novo->vertice = v;
    novo->next = *topo;
    *topo = novo;
    *codigo = SUCESSO;
}

/**
 * @brief Remove um vértice da stack (LIFO)
 *
 * @param topo
 * @return Vertice*
 */
Vertice *popStack(Listagem **topo)
{
    if (*topo == NULL)
        return NULL;

    Listagem *tmp = *topo;
    Vertice *v = tmp->vertice;
    *topo = tmp->next;
    free(tmp);
    return v;
}

/**
 * @brief  Realiza uma busca em profundidade no grafo a partir de um vértice de origem
 *
 * @param grafo
 * @param idOrigem
 * @param codigo
 * @return ResultadoPesquisa*
 */
Listagem *DepthFirstSearch(GrafoAntenas *grafo, int idOrigem, CodigoErro *codigo)
{
    if (!grafo || !grafo->head)
    {
        *codigo = ERRO_GRAFO_VAZIO;
        return NULL;
    }

    Vertice *origem = ProcurarVertice(grafo->head, idOrigem);
    if (!origem)
    {
        *codigo = ERRO_VERTICE_NAO_EXISTE;
        return NULL;
    }

    Listagem *stack = NULL;
    Listagem *res = NULL;
    Listagem *resFim = NULL;
    pushStack(&stack, origem, codigo);
    while (stack != NULL)
    {
        Vertice *atual = popStack(&stack);
        if (atual->visitado)
            continue;

        atual->visitado = true;

        Listagem *novo = (Listagem *)malloc(sizeof(Listagem));
        if (!novo)
        {
            *codigo = ERRO_MEMORIA;
            free(stack);
            return res; // Devolve o que tiver conseguido até aqui
        }

        // Insere no fim da lista
        novo->vertice = atual;
        novo->next = NULL;

        if (!res)
        {
            res = novo;
            resFim = novo;
        }
        else
        {
            resFim->next = novo;
            resFim = novo;
        }

        // Push dos adjacentes na stack
        Adj *adj = atual->adjacencias;
        while (adj != NULL)
        {
            Vertice *vizinho = ProcurarVertice(grafo->head, adj->idDestino);
            if (vizinho && !vizinho->visitado)
            {
                pushStack(&stack, vizinho, codigo);
            }
            adj = adj->next;
        }
    }
    // Limpa a stack
    while (stack != NULL)
    {
        Listagem *temp = stack;
        stack = stack->next;
        free(temp);
    }
    LimparVisitados(grafo);
    *codigo = SUCESSO;
    return res;
}

/**
 * @brief Realiza uma busca em largura no grafo a partir de um vértice de origem
 *
 * @param grafo
 * @param idOrigem
 * @param codigo
 * @return ResultadoPesquisa*
 */
Listagem *BreadthFirstSearch(GrafoAntenas *grafo, int idOrigem, CodigoErro *codigo)
{
    if (!grafo || !grafo->head)
    {
        *codigo = ERRO_GRAFO_VAZIO;
        return NULL;
    }

    Vertice *origem = ProcurarVertice(grafo->head, idOrigem);
    if (!origem)
    {
        *codigo = ERRO_VERTICE_NAO_EXISTE;
        return NULL;
    }

    Listagem *queue = malloc(sizeof(Listagem));
    if (!queue)
    {
        *codigo = ERRO_MEMORIA;
        return NULL;
    }

    queue->vertice = origem;
    queue->next = NULL;

    origem->visitado = true;

    Listagem *res = NULL;
    Listagem *resFim = NULL; // para manter fim da lista de resultados

    while (queue != NULL)
    {
        // Remove da cabeça da queue
        Vertice *atual = queue->vertice;
        Listagem *temp = queue;
        queue = queue->next;
        free(temp);

        // Adiciona ao fim de res
        Listagem *novo = malloc(sizeof(Listagem));
        if (!novo)
        {
            *codigo = ERRO_MEMORIA;
            return res;
        }

        novo->vertice = atual;
        novo->next = NULL;

        if (!res)
        {
            res = novo;
            resFim = novo;
        }
        else
        {
            resFim->next = novo;
            resFim = novo;
        }

        // Adiciona os vizinhos à queue (fim da lista)
        Adj *adj = atual->adjacencias;
        Listagem *queueFim = queue;
        while (queueFim && queueFim->next)
            queueFim = queueFim->next;

        while (adj != NULL)
        {
            Vertice *vizinho = ProcurarVertice(grafo->head, adj->idDestino);
            if (vizinho && !vizinho->visitado)
            {
                Listagem *novoVizinho = malloc(sizeof(Listagem));
                if (!novoVizinho)
                {
                    *codigo = ERRO_MEMORIA;
                    return res;
                }

                vizinho->visitado = true;
                novoVizinho->vertice = vizinho;
                novoVizinho->next = NULL;

                if (!queue)
                {
                    queue = novoVizinho;
                    queueFim = novoVizinho;
                }
                else
                {
                    queueFim->next = novoVizinho;
                    queueFim = novoVizinho;
                }
            }
            adj = adj->next;
        }
    }

    LimparVisitados(grafo);
    *codigo = SUCESSO;
    return res;
}

/**
 * @brief Imprime a lista de resultados de uma pesquisa (DFS, BFS)
 *
 * @param lista
 */
void ImprimirListaResultado(Listagem *lista)
{
    while (lista)
    {
        printf("ID: %d | Sinal: %c | Coordenadas: (%d, %d)\n",
               lista->vertice->id,
               lista->vertice->sinal,
               lista->vertice->x,
               lista->vertice->y);
        lista = lista->next;
        if (lista)
        {
            printf("|\n");
            printf("V\n");
        }
    }
}
#pragma endregion
// caminhos

#pragma region Caminho

/**
 * @brief Função que inicializa a busca de caminhos entre dois vértices
 *
 * @param grafo
 * @param idOrigem
 * @param idDestino
 * @param codigo
 * @return Caminho*
 */
Caminho *ProcuraCaminhos(GrafoAntenas *grafo, int idOrigem, int idDestino, CodigoErro *codigo)
{
    if (!grafo || !grafo->head)
    {
        *codigo = ERRO_GRAFO_VAZIO;
        return NULL;
    }

    Vertice *origem = ProcurarVertice(grafo->head, idOrigem);
    if (!origem)
    {
        *codigo = ERRO_VERTICE_NAO_EXISTE;
        return NULL;
    }

    // queue BFS de caminhos parciais (tipo Caminho)
    Caminho *queue = NULL;
    Caminho *queueFim = NULL;

    // Inicializa caminho parcial com só o vértice origem
    Listagem *inicio = malloc(sizeof(Listagem));
    if (!inicio)
    {
        *codigo = ERRO_MEMORIA;
        return NULL;
    }
    inicio->vertice = origem;
    inicio->next = NULL;

    Caminho *inicial = malloc(sizeof(Caminho));
    if (!inicial)
    {
        free(inicio);
        *codigo = ERRO_MEMORIA;
        return NULL;
    }
    inicial->caminho = inicio;
    inicial->distanciaTotal = 0;
    inicial->next = NULL;

    // poe na queue o caminho inicial
    queue = queueFim = inicial;

    Caminho *resultados = NULL; // Lista ligada para caminhos completos encontrados

    while (queue != NULL)
    {
        // tira da queue o primeiro caminho parcial
        Caminho *atual = queue;
        queue = queue->next;
        if (queue == NULL)
        {
            queueFim = NULL;
        }

        // Último vértice do caminho atual
        Listagem *ultimo = atual->caminho;
        while (ultimo->next != NULL)
            ultimo = ultimo->next;
        Vertice *vAtual = ultimo->vertice;

        if (vAtual->id == idDestino)
        {
            // Encontrou caminho completo, adiciona aos resultados

            atual->next = resultados;
            resultados = atual;
            continue; // Não criar novos caminhos a partir daqui
        }

        // Explorar adjacentes do vértice atual
        Adj *adj = vAtual->adjacencias;
        while (adj != NULL)
        {
            // Verifica se adjacente já está no caminho (para evitar ciclos)
            bool jaVisitado = false;
            Listagem *p = atual->caminho;
            while (p != NULL)
            {
                if (p->vertice->id == adj->idDestino)
                {
                    jaVisitado = true;
                    break;
                }
                p = p->next;
            }

            if (!jaVisitado)
            {
                // Copiar o caminho atual
                Listagem *copiaCaminho = NULL;
                Listagem *copiaFim = NULL;
                Listagem *orig = atual->caminho;

                while (orig != NULL)
                {
                    Listagem *novoNo = malloc(sizeof(Listagem));
                    if (!novoNo)
                    {
                        *codigo = ERRO_MEMORIA;
                        // Liberta tudo que estiver pendente (não implementado aqui)
                        return resultados;
                    }
                    novoNo->vertice = orig->vertice;
                    novoNo->next = NULL;

                    if (!copiaCaminho)
                    {
                        copiaCaminho = copiaFim = novoNo;
                    }
                    else
                    {
                        copiaFim->next = novoNo;
                        copiaFim = novoNo;
                    }
                    orig = orig->next;
                }

                // Adicionar o vértice adjacente à cópia do caminho
                Listagem *novoNo = malloc(sizeof(Listagem));
                if (!novoNo)
                {
                    *codigo = ERRO_MEMORIA;
                    return resultados;
                }
                novoNo->vertice = ProcurarVertice(grafo->head, adj->idDestino);
                novoNo->next = NULL;
                copiaFim->next = novoNo;

                // Criar novo caminho parcial
                Caminho *novoParcial = malloc(sizeof(Caminho));
                if (!novoParcial)
                {
                    *codigo = ERRO_MEMORIA;
                    return resultados;
                }
                novoParcial->caminho = copiaCaminho;
                novoParcial->distanciaTotal = atual->distanciaTotal + adj->distancia;
                novoParcial->next = NULL;

                // poe na queue novo caminho parcial
                if (queueFim == NULL)
                {
                    queue = queueFim = novoParcial;
                }
                else
                {
                    queueFim->next = novoParcial;
                    queueFim = novoParcial;
                }
            }
            adj = adj->next;
        }
        // Liberta o caminho parcial atual

        Listagem *lst = atual->caminho;
        LimparLista(lst);
        free(atual);
    }

    *codigo = SUCESSO;
    return resultados;
}

/**
 * @brief Imprime todos os caminhos encontrados
 *
 * @param listaCaminhos
 */
void ImprimirTodosCaminhos(Caminho *caminhos)
{
    int contador = 1;
    while (caminhos != NULL)
    {
        printf("Caminho %d (Distância total: %.2f): ", contador, caminhos->distanciaTotal);

        Listagem *p = caminhos->caminho;
        while (p != NULL)
        {
            printf("%d", p->vertice->id);
            if (p->next != NULL)
                printf(" -> ");
            p = p->next;
        }
        printf("\n");
        caminhos = caminhos->next;
        contador++;
    }
}

/**
 * @brief  Liberta a memória ocupada pela lista de resultados
 *
 * @param lista
 */
void LimparVisitados(GrafoAntenas *grafo)
{
    Vertice *v = grafo->head;
    while (v)
    {
        v->visitado = false;
        v = v->prox;
    }
}

/**
 * @brief Liberta a memória ocupada pela lista de caminhos
 *
 * @param c
 */
void LimparCaminhos(Caminho *c)
{
    while (c != NULL)
    {
        Caminho *tmp = c;
        LimparLista(c->caminho);
        c = c->next;
        free(tmp);
    }
}
/**
 * @brief Liberta a memória ocupada pela lista de vértices
 *
 * @param lista
 */
void LimparLista(Listagem *lista)
{
    while (lista)
    {
        Listagem *temp = lista;
        lista = lista->next;
        free(temp);
    }
}
#pragma endregion
