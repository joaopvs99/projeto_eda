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

int memoria_esta_vazia()
{
    FILE *f = fopen("./bin/data.bin", "rb");
    if (!f)
    {
        return -1; // Retorna -1 para indicar erro ao abrir o ficheiro
    }

    fseek(f, 0, SEEK_END);   // Move para o final do ficheiro
    long tamanho = ftell(f); // Obtém a posição atual, que indica o tamanho

    fclose(f);

    return tamanho == 0;
}
void mostrar_menu()
{
    Matriz *temp = NULL;

    // se o ficheiro bin não existir ou estive vazio, importar matriz do ficheira txt
    if (memoria_esta_vazia())
    {
        temp = importar_matriz("import/mapa.txt");
        temp = calcular_efeito(temp);
        puts("");
        puts("Matriz importada do ficheiro texto fornecido");
        puts("--------------------------------------------");
        puts("");
        imprime_matriz_efeito(temp);
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
    else // se o ficheiro bin existir, ler matriz apartir do ficheiro bin
    {
        temp = ler_matriz();
        temp = calcular_efeito(temp);
        puts("");
        puts("Matriz importada da memória");
        puts("--------------------------------------------");
        puts("");
        imprime_matriz_efeito(temp);
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
    puts("4. Reiniciar Matriz Importada");
    puts("5. Sair");
};

void menu_inserir_antena()
{
    Matriz *temp = NULL;
    temp = ler_matriz();
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
    temp->lista_emissores = inserir_emissor(temp->lista_emissores, sinal, x, y);
    guardar_matriz(temp);
}

void menu_remover_antena()
{
    Matriz *temp = NULL;
    temp = ler_matriz();
    int x, y;

    system("clear");
    puts("Remover antena");
    fflush(stdin);
    puts("Coordenada X da antena:");
    scanf("%d", &x);
    puts("Coordenada Y da antena:");
    scanf("%d", &y);
    fflush(stdin);
    temp->lista_emissores = remover_emissor(temp->lista_emissores, x, y);
    guardar_matriz(temp);
}

void listar_antenas_efeitos()
{
    Matriz *temp = NULL;
    temp = ler_matriz();
    temp = calcular_efeito(temp);
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
};

void menu_principal()
{
    int escolha = 0;
    while (escolha != 5)
    {
        mostrar_menu();
        scanf("%d", &escolha);
        fflush(stdin);
        switch (escolha)
        {
        case 1:
            system("clear");
            menu_inserir_antena();
            system("read -p 'Pressione Enter para continuar...' var");
            system("clear");
            break;
        case 2:
            system("clear");
            menu_remover_antena();
            system("read -p 'Pressione Enter para continuar...' var");
            system("clear");

            break;

        case 3:
            system("clear");
            listar_antenas_efeitos();
            system("read -p 'Pressione Enter para continuar...' var");
            system("clear");

            break;

        case 4:

            system("clear");
            remove("./bin/data.bin");
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