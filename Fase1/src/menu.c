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
int memoria_esta_vazia(CodigoErro *codigo)
{
    FILE *f = fopen("data/data.bin", "rb");
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
void mostrar_menu(CodigoErro *codigo)
{
    Mapa *temp = NULL;

    // se o ficheiro bin não existir ou estive vazio, importar mapa do ficheira txt
    if (memoria_esta_vazia(codigo))
    {
        temp = importar_mapa("import/mapa.txt", codigo);

        if (*codigo != SUCESSO)
        {
            trataErro(codigo);
        }
        temp = calcular_efeito(temp, codigo);
        if (*codigo != SUCESSO)
        {
            trataErro(codigo);
        }
        puts("");
        puts("mapa importada do ficheiro texto fornecido");
        puts("--------------------------------------------");
        puts("");
        imprime_mapa_efeito(temp, codigo);
        if (*codigo != SUCESSO)
        {
            trataErro(codigo);
        }
        puts("");
        puts("----------------------LEGENDA----------------------");
        puts("# -> Efeitos Nefastos");
        puts("(a->z) -> Antenas");
        alerta();
        printf("(a->z) ");
        reset_alerta();
        puts("-> Antenas efetadas por efeitos nefastos");
        puts("");
        puts("-----------------------MENU------------------------");
    }
    else // se o ficheiro bin existir, ler mapa apartir do ficheiro bin
    {
        temp = ler_mapa(codigo);
        if (*codigo != SUCESSO)
        {
            trataErro(codigo);
        }
        if (temp == NULL)
        {
            trataErro(codigo);
        }
        temp = calcular_efeito(temp, codigo);
        if (*codigo != SUCESSO)
        {
            trataErro(codigo);
        }
        puts("");
        puts("mapa importada da memória");
        puts("--------------------------------------------");
        puts("");
        imprime_mapa_efeito(temp, codigo);
        if (*codigo != SUCESSO)
        {
            trataErro(codigo);
        }
        puts("");
        puts("----------------------LEGENDA----------------------");
        puts("# -> Efeitos Nefastos");
        puts("(a->z) -> Antenas");
        alerta();
        printf("(a->z) ");
        reset_alerta();
        puts("-> Antenas efetadas por efeitos nefastos");
        puts("");
        puts("-----------------------MENU------------------------");
    }

    puts("1. Inserir Antena");
    puts("2. Remover Antena");
    puts("3. Tabela de Antenas e Efeitos Nefastos");
    puts("4. Reiniciar mapa Importada");
    puts("5. Sair");
};

/**
 * @brief Pede ao utilizador o valor da frequencia e as suas coordenadas,
 * de seguida, insere a antena e guarda a matriz na memória
 *
 */
void menu_inserir_antena(CodigoErro *codigo)
{
    Mapa *temp = NULL;
    temp = ler_mapa(codigo);
    if (*codigo != SUCESSO)
    {
        trataErro(codigo);
    }
    char sinal;
    int x, y;

    system("clear");
    puts("Insira nova antena");
    puts("Nome da frequencia:");
    scanf(" %c", &sinal);
    fflush(stdin);
    puts("Coordenada X da antena:");
    scanf("%d", &x);
    puts("Coordenada Y da antena:");
    scanf("%d", &y);
    fflush(stdin);
    temp->lista_emissores = inserir_emissor(temp->lista_emissores, sinal, x, y, codigo);
    if (*codigo != SUCESSO)
    {
        trataErro(codigo);
    }
    guardar_mapa(temp, codigo);
    if (*codigo != SUCESSO)
    {
        trataErro(codigo);
    }
}

/**
 * @brief Pede ao utilizador as coordenadas da antena,
 * de seguida, remove a antena e guarda a matriz na memória
 *
 */
void menu_remover_antena(CodigoErro *codigo)
{

    Mapa *temp = NULL;
    temp = ler_mapa(codigo);
    if (!temp)
    {
        trataErro(codigo);
    }

    int x, y;

    system("clear");
    puts("Remover antena");
    fflush(stdin);
    puts("Coordenada X da antena:");
    scanf("%d", &x);
    puts("Coordenada Y da antena:");
    scanf("%d", &y);
    fflush(stdin);
    temp->lista_emissores = remover_emissor(temp->lista_emissores, x, y, codigo);

    guardar_mapa(temp, codigo);
}

/**
 * @brief Mostra a tabela de antenas e efeitos nefastos
 *
 */
void listar_antenas_efeitos(CodigoErro *codigo)
{

    Mapa *temp = NULL;
    temp = ler_mapa(codigo);

    temp = calcular_efeito(temp, codigo);

    system("clear");

    if (!temp || !temp->lista_emissores)
    {
        puts("Nenhuma antena ou efeito encontrado.");
        return;
    }

    // Imprimir as antenas
    printf("\n------------ ANTENAS ----------------------------------------\n");
    // Cabeçalho da tabela
    printf("%-15s %-15s %s\n", "Frequencia", "Coordenada X", "Coordenada Y");
    printf("--------------------------------------------------------------\n");
    Emissor *emissor = temp->lista_emissores;
    while (emissor != NULL)
    {
        if (emissor->sinal != '#')
        {
            printf("%-15c %-15d %d\n", emissor->sinal, emissor->x, emissor->y);
        }
        emissor = emissor->next;
    }

    // Imprimir os efeitos
    printf("\n------------ EFEITOS NEFASTOS -------------------------------\n");
    printf("%-15s %s\n", "Coordenada X", "Coordenada Y");
    printf("--------------------------------------------------------------\n");
    emissor = temp->lista_emissores; // Voltar para o início da lista
    while (emissor != NULL)
    {
        if (emissor->sinal == '#')
        {
            printf("%-15d %d\n", emissor->x, emissor->y);
        }
        emissor = emissor->next;
    }
    *codigo = SUCESSO;
};

/**
 * @brief Mostra e controla o menu principal do programa
 *
 */
void menu_principal()
{
    CodigoErro codigo;
    int escolha = 0;
    while (escolha != 5)
    {
        mostrar_menu(&codigo);
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
            menu_inserir_antena(&codigo);
            if (codigo != SUCESSO)
            {
                trataErro(&codigo);
            }
            system("read -p 'Pressione Enter para continuar...' var");
            system("clear");
            break;
        case 2:
            system("clear");
            menu_remover_antena(&codigo);
            if (codigo != SUCESSO)
            {
                trataErro(&codigo);
            }
            system("read -p 'Pressione Enter para continuar...' var");
            system("clear");

            break;

        case 3:
            system("clear");
            listar_antenas_efeitos(&codigo);
            if (codigo != SUCESSO)
            {
                trataErro(&codigo);
            }
            system("read -p 'Pressione Enter para continuar...' var");
            system("clear");

            break;

        case 4:

            system("clear");
            remove("data/data.bin");
            system("read -p 'Pressione Enter para continuar...' var");
            system("clear");

            break;

        case 5:
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