/**
 * @file menu.c
 * @author João Paulo Viana Soares (a26593@alunos.ipca.pt)
 * @brief Funções associadas ao menu da consola
 * @version 1.0
 * @date 2025-03-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/menu.h"

/**
 * @brief indica se o ficheiro de memória data.bin está vazio
 *
 * @return ->1 se estiver vazio -> 0 caso contrário
 */
int MemoriaEstaVazia(CodigoErro *codigo)
{
    FILE *f = fopen("data/grafo.bin", "rb");
    if (!f)
    {
        *codigo = ERRO_FICHEIRO_NAO_ENCONTRADO;
        return 1;
    }

    fseek(f, 0, SEEK_END);   // Move para o final do ficheiro
    long tamanho = ftell(f); // Obtém a posição atual, que indica o tamanho

    fclose(f);

    *codigo = SUCESSO;
    return tamanho == 0;
}

/**
 * @brief Exibe sequências de printfs alusivas ao menu.
 *
 */
void MostrarMenu(CodigoErro *codigo)
{
    GrafoAntenas *temp = NULL;

    // se o ficheiro bin não existir ou estive vazio, importar mapa do ficheira txt
    if (MemoriaEstaVazia(codigo))
    {
        temp = ImportaGrafo("import/mapa.txt", codigo);

        if (*codigo != SUCESSO)
        {
            trataErro(codigo);
        }
        puts("");
        puts("Grafo importado do ficheiro texto fornecido");
        puts("--------------------------------------------");
        puts("");
        ImprimeGrafo(temp);
    }
    else // se o ficheiro bin existir, ler mapa apartir do ficheiro bin
    {
        temp = CarregaGrafo("data/grafo.bin", codigo);
        if (*codigo != SUCESSO)
        {
            trataErro(codigo);
        }
        puts("");
        puts("Grafo importado da memória");
        puts("--------------------------------------------");
        puts("");
        ImprimeGrafo(temp);
    }

    puts("1. Iniciar Pesquisa em Profundidade");
    puts("2. Iniciar Pesquisa em Largura");
    puts("3. Calculo de caminhos entre dois vértices");
    puts("4. Sair");
};

void MostrarMenuPesquisaCaminhos(CodigoErro *codigo)
{
    GrafoAntenas *temp = NULL;
    Caminho *resultado = NULL;
    temp = CarregaGrafo("data/grafo.bin", codigo);
    if (*codigo != SUCESSO)
    {
        trataErro(codigo);
    }
    int v1, v2;

    system("clear");
    puts("Pesquisa de Caminhos entre dois vértices");
    fflush(stdin);
    puts("ID do Vértice 1");
    scanf("%d", &v1);
    puts("ID do Vértice 2");
    scanf("%d", &v2);
    fflush(stdin);
    resultado = ProcuraCaminhos(temp, v1, v2, codigo);
    if (*codigo != SUCESSO)
    {
        trataErro(codigo);
    }
    ImprimirTodosCaminhos(resultado);
    LimparCaminhos(resultado);
}

/**
 * @brief Mostra menu de pesquisa em profundidade
 *
 * @param codigo
 */
void MostrarMenuDfs(CodigoErro *codigo)
{
    GrafoAntenas *temp = NULL;
    Listagem *resultado = NULL;
    int v;
    temp = CarregaGrafo("data/grafo.bin", codigo);
    if (*codigo != SUCESSO)
    {
        trataErro(codigo);
    }
    system("clear");
    puts("Pesquisa em profundidade apartir de um vértice");
    fflush(stdin);
    puts("ID do Vértice");
    scanf("%d", &v);
    resultado = DepthFirstSearch(temp, v, codigo);
    puts("");
    puts("Resultado da pesquisa em profundidade (DFS)");
    puts("--------------------------------------------");
    puts("");
    ImprimirListaResultado(resultado);
    LimparLista(resultado);
};
/**
 * @brief Mostra menu de pesquisa em largura
 *
 * @param codigo
 */
void MostrarMenuBfs(CodigoErro *codigo)
{
    GrafoAntenas *temp = NULL;
    Listagem *resultado = NULL;
    int v;
    temp = CarregaGrafo("data/grafo.bin", codigo);
    if (*codigo != SUCESSO)
    {
        trataErro(codigo);
    }
    system("clear");
    puts("Pesquisa em largura apartir de um vértice");
    fflush(stdin);
    puts("ID do Vértice");
    scanf("%d", &v);
    resultado = DepthFirstSearch(temp, v, codigo);
    puts("");
    puts("Resultado da pesquisa em largura (BFS)");
    puts("--------------------------------------------");
    puts("");
    ImprimirListaResultado(resultado);
    LimparLista(resultado);
};
/**
 * @brief Mostra e controla o menu principal do programa
 *
 */
void MenuPrincipal()
{
    CodigoErro codigo;
    int escolha = 0;
    while (escolha != 4)
    {
        MostrarMenu(&codigo);
        if (codigo != SUCESSO)
        {
            trataErro(&codigo);
        }
        scanf("%d", &escolha);
        fflush(stdin);
        switch (escolha)
        {
        case 1:
            system("clear");
            MostrarMenuDfs(&codigo);
            if (codigo != SUCESSO)
            {
                trataErro(&codigo);
            }
            system("read -p 'Pressione Enter para continuar...' var");
            system("clear");
            break;
        case 2:
            system("clear");
            MostrarMenuBfs(&codigo);
            if (codigo != SUCESSO)
            {
                trataErro(&codigo);
            }
            system("read -p 'Pressione Enter para continuar...' var");
            system("clear");

            break;

        case 3:
            system("clear");
            MostrarMenuPesquisaCaminhos(&codigo);
            if (codigo != SUCESSO)
            {
                trataErro(&codigo);
            }
            system("read -p 'Pressione Enter para continuar...' var");
            system("clear");

            break;
        case 4:
            system("clear");
            printf("\n\t\t\t\tA sair...\n\n");
            exit(0);

        default:
            system("clear");
            printf("\n\t\t\t\t\tInsira uma opcao valida\n\n");
            system("read -p 'Pressione Enter para continuar...' var");

            system("clear");
            break;
        }
    }
    system("read -p 'Pressione Enter para continuar...' var");
}
