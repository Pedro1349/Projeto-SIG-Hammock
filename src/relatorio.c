#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/relatorio.h"
#include "../include/utilidades.h"
#include "../include/clientes.h"
#include "../include/funcionarios.h"
#include "../include/produto.h"
#include "../include/pedidos.h"

FILE * arquivo;

void modulo_relatorio(void) {
    char opcao;

    do {
        opcao = tela_relatorio();
        switch(opcao) {
            case '1':   
                navegacao_relatorios_clientes();
                break;
            case '2':   
                navegacao_relatorios_funcionarios();
                break;
            case '3':   
                navegacao_relatorios_produtos();
                break;
            case '4':   
                navegacao_relatorios_pedidos();
                break;              
        }
    } while (opcao != '0');
}

void navegacao_relatorios_clientes(void) {
    char opcao;

    do {
        opcao = tela_relatorio_clientes();
        switch(opcao) {
            case '1':   
                listar_clientes_ativos();
                break;
            case '2':   
                listar_clientes_inativos();
                break;
            case '3':
                filtrar_clientes_nome();
                break;
           
        }
    } while (opcao != '0');
}


void navegacao_relatorios_funcionarios(void) {
    char opcao;

    do {
        opcao = tela_relatorio_funcionarios();
        switch(opcao) {
            case '1':   
                listar_funcionarios_ativos();
                break;
            case '2':   
                listar_funcionarios_inativos();
                break;
            case '3':
                filtrar_funcionarios_nome();
                break;           
        }
    } while (opcao != '0');
}


void navegacao_relatorios_produtos(void) {
    char opcao;

    do {
        opcao = tela_relatorio_produtos();
        switch(opcao) {
            case '1':   
                listar_produtos_ativos();
                break;
            case '2':   
                listar_pedidos_inativos();
                break;      
            case '3':
                filtrar_produtos_preco();
                break;       
        }
    } while (opcao != '0');
}

void navegacao_relatorios_pedidos(void) {
    char opcao;

    do {
        opcao = tela_relatorio_pedidos();
        switch(opcao) {
            case '1':   
                listar_pedidos_ativos();
                break;
            case '2':   
                listar_pedidos_inativos();
                break;  
            case '3':
                filtrar_pedidos_data();
                break;     
        }
    } while (opcao != '0');
}

char tela_relatorio(void){
    char op_relat;
    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                  Relatorio Geral                ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║ 1 - Relatório geral de Clientes                 ║\n");
    printf("║ 2 - Relatório geral de Funcionários             ║\n");
    printf("║ 3 - Relatório geral de Produtos                 ║\n");
    printf("║ 4 - Relatório geral de Pedidos                  ║\n");
    printf("║                                                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║ 0 - Voltar                                      ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op_relat);
    limpar_buffer();
    return op_relat;
}

char tela_relatorio_clientes(void){

    char op_cliente;
    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Relatório De Clientes             ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║                                                 ║\n");
    printf("║ 1 - Listar clientes ativos                      ║\n");
    printf("║ 2 - Listar clientes inativos                    ║\n");
    printf("║ 3 - Filtrar clientes por nome                   ║\n");
    printf("║                                                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║ 0 - Voltar                                      ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op_cliente);
    limpar_buffer();
    return op_cliente;
}

char tela_relatorio_funcionarios(void){

    char op_func;
    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║            Relatório De Funcionários            ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║                                                 ║\n");
    printf("║ 1 - Listar funcionários ativos                  ║\n");
    printf("║ 2 - Listar funcionários inativos                ║\n");
    printf("║ 3 - Listar funcionarios por nome                ║\n");
    printf("║                                                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║ 0 - Voltar                                      ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op_func);
    limpar_buffer();
    return op_func;
}

char tela_relatorio_produtos(void){

    char op_produto;
    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║            Relatório De Produtos                ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║                                                 ║\n");
    printf("║ 1 - Listar produtos ativos                      ║\n");
    printf("║ 2 - Listar produtos inativos                    ║\n");
    printf("║ 3 - Filtrar produtos por preço                  ║\n");
    printf("║                                                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║ 0 - Voltar                                      ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op_produto);
    limpar_buffer();
    return op_produto;
}

char tela_relatorio_pedidos(void){

    char op_pedido;
    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║            Relatório De Pedidos                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║                                                 ║\n");
    printf("║ 1 - Listar pedidos ativos                       ║\n");
    printf("║ 2 - Listar pedidos inativos                     ║\n");
    printf("║ 3 - Filtrar pedidos por período                 ║\n");
    printf("║                                                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║ 0 - Voltar                                      ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op_pedido);
    limpar_buffer();
    return op_pedido;
}

// ============================================================
// LISTAR CLIENTES ATIVOS
// ============================================================
void listar_clientes_ativos(void) {
    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));
    int encontrados = 0;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║              Clientes Ativos                    ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/clientes.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum cliente encontrado (arquivo inexistente).\n");
        getchar();
        free(cli);
        return;
    }

    printf("| %-5s | %-20s | %-14s | %-25s | %-12s |\n", "ID", "NOME", "CPF", "EMAIL", "TELEFONE");
    while (fread(cli, sizeof(Cliente), 1, arquivo)) {
        if (cli->status == True) {
            printf("| %-5d | %-20.20s | %-14.14s | %-25.25s | %-12.12s |\n", cli->id, cli->nome, cli->cpf, cli->email, cli->telefone);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        system("clear || cls");
        printf("\nNenhum cliente ativo encontrado.\n");
    }

    fclose(arquivo);
    free(cli);

    printf("\n\nPressione ENTER para continuar...");
    getchar();
}


// ============================================================
// LISTAR CLIENTES INATIVOS
// ============================================================
void listar_clientes_inativos(void) {
    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));
    int encontrados = 0;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║              Clientes Inativos                  ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/clientes.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum cliente encontrado (arquivo inexistente).\n");
        getchar();
        free(cli);
        return;
    }

    printf("| %-5s | %-20s | %-14s | %-25s | %-12s |\n", "ID", "NOME", "CPF", "EMAIL", "TELEFONE");
    while (fread(cli, sizeof(Cliente), 1, arquivo)) {
        if (cli->status == False) {
            printf("| %-5d | %-20.20s | %-14.14s | %-25.25s | %-12.12s |\n", cli->id, cli->nome, cli->cpf, cli->email, cli->telefone);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        system("clear || cls");
        printf("\nNenhum cliente inativo encontrado.\n");
    }

    fclose(arquivo);
    free(cli);

    printf("\n\nPressione ENTER para continuar...");
    getchar();
}

// ============================================================
// FILTRAR CLIENTES POR NOME
// ============================================================
void filtrar_clientes_nome(void) {
    Cliente* cli = (Cliente*) malloc(sizeof(Cliente));
    char nome_busca[51];
    char nome_cliente_lower[51];
    char nome_busca_lower[51];
    int cliente_encontrado = 1;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║            Filtrar Clientes por Nome            ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/clientes.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum cliente encontrado (arquivo inexistente).\n");
        getchar();
        free(cli);
        return;
    }

    printf("Digite parte do nome do cliente: ");
    scanf("%50[^\n]", nome_busca);
    limpar_buffer();

    // converter busca para minúsculas
    for (int i = 0; nome_busca[i]; i++)
        nome_busca_lower[i] = tolower(nome_busca[i]);
    nome_busca_lower[strlen(nome_busca)] = '\0';

    system("clear || cls");

    printf("| %-5s | %-20s | %-14s | %-25s | %-12s |\n", "ID", "NOME", "CPF", "EMAIL", "TELEFONE");
    while (fread(cli, sizeof(Cliente), 1, arquivo)) {
        // Ignorar clientes inativos
        if (cli->status == False)
            continue;

        // converter nome para minúsculas
        for (int i = 0; cli->nome[i]; i++)
            nome_cliente_lower[i] = tolower(cli->nome[i]);
        nome_cliente_lower[strlen(cli->nome)] = '\0';

        // procurar substring
        if (strstr(nome_cliente_lower, nome_busca_lower)) {
            printf("| %-5d | %-20.20s | %-14.14s | %-25.25s | %-12.12s |\n", cli->id, cli->nome, cli->cpf, cli->email, cli->telefone);
            cliente_encontrado++;
        }
    }
    if (cliente_encontrado <= 1) {
        system("clear || cls");
        printf("Nenhum cliente com essa parte do nome foi encontrado.");
    }

    getchar();
    fclose(arquivo);
    free(cli);
}


// ============================================================
// LISTAR FUNCIONÁRIOS ATIVOS
// ============================================================
void listar_funcionarios_ativos(void) {
    Funcionarios* func;
    func = (Funcionarios*) malloc(sizeof(Funcionarios));
    int encontrados = 0;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║            Funcionários Ativos                  ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/funcionarios.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum funcionário encontrado (arquivo inexistente).\n");
        getchar();
        free(func);
        return;
    }

    printf("| %-5s | %-20s | %-14s | %-25s | %-12s |\n", "ID", "NOME", "CPF", "EMAIL", "TELEFONE");

    while (fread(func, sizeof(Funcionarios), 1, arquivo)) {
        if (func->status == True) {
            printf("| %-5d | %-20.20s | %-14.14s | %-25.25s | %-12.12s |\n", func->id, func->nome, func->cpf, func->email, func->telefone);
                encontrados++;
        }
    }

    if (encontrados == 0) {
        system("clear || cls");
        printf("\nNenhum funcionário ativo encontrado.\n");
    }

    fclose(arquivo);
    free(func);

    printf("\n\nPressione ENTER para continuar...");
    getchar();
}


// ============================================================
// LISTAR FUNCIONÁRIOS INATIVOS
// ============================================================
void listar_funcionarios_inativos(void) {
    Funcionarios* func;
    func = (Funcionarios*) malloc(sizeof(Funcionarios));
    int encontrados = 0;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║            Funcionários Inativos                ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/funcionarios.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum funcionário encontrado (arquivo inexistente).\n");
        getchar();
        free(func);
        return;
    }

    printf("| %-5s | %-20s | %-14s | %-25s | %-12s |\n", "ID", "NOME", "CPF", "EMAIL", "TELEFONE");

    while (fread(func, sizeof(Funcionarios), 1, arquivo)) {
        if (func->status == False) {
            printf("| %-5d | %-20.20s | %-14.14s | %-25.25s | %-12.12s |\n", func->id, func->nome, func->cpf, func->email, func->telefone);
                encontrados++;
        }
    }

    if (encontrados == 0) {
        system("clear || cls");
        printf("\nNenhum funcionário inativo encontrado.\n");
    }

    fclose(arquivo);
    free(func);

    printf("\n\nPressione ENTER para continuar...");
    getchar();
}

// ============================================================
// FILTRAR FUNCIONÁRIOS POR NOME
// ============================================================
void filtrar_funcionarios_nome(void) {
    Funcionarios* func = (Funcionarios*) malloc(sizeof(Funcionarios));
    char nome_busca[51];
    char nome_func_lower[51];
    char nome_busca_lower[51];
    int funcionario_encontrado = 1;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║         Filtrar Funcionários por Nome           ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/funcionarios.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum funcionário encontrado (arquivo inexistente).\n");
        getchar();
        free(func);
        return;
    }

    printf("Digite parte do nome do funcionário: ");
    scanf("%50[^\n]", nome_busca);
    limpar_buffer();

    // converter busca para minúsculas
    for (int i = 0; nome_busca[i]; i++)
        nome_busca_lower[i] = tolower(nome_busca[i]);
    nome_busca_lower[strlen(nome_busca)] = '\0';

    system("clear || cls");

    printf("| %-5s | %-20s | %-14s | %-25s | %-12s |\n", "ID", "NOME", "CPF", "EMAIL", "TELEFONE");
    while (fread(func, sizeof(Funcionarios), 1, arquivo)) {

        if (func->status == False)
            continue;

        for (int i = 0; func->nome[i]; i++)
            nome_func_lower[i] = tolower(func->nome[i]);
        nome_func_lower[strlen(func->nome)] = '\0';

        if (strstr(nome_func_lower, nome_busca_lower)) {
            printf("| %-5d | %-20.20s | %-14.14s | %-25.25s | %-12.12s |\n", func->id, func->nome, func->cpf, func->email, func->telefone);
            funcionario_encontrado++;
        }
    }
    if (funcionario_encontrado <= 1) {
        system("clear || cls");
        printf("Nenhum funcionário com essa parte do nome foi encontrado.");
    }

    getchar();

    fclose(arquivo);
    free(func);
}


// LISTAR PRODUTOS ATIVOS
void listar_produtos_ativos(void) {
    Produto* prod = (Produto*) malloc(sizeof(Produto));
    int encontrados = 0;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                Produtos Ativos                  ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/produtos.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum produto encontrado (arquivo inexistente).\n");
        getchar();
        free(prod);
        return;
    }

    printf("| %-5s | %-20s | %-10s | %-20s | %-15s |\n", "ID", "MODELO", "VALOR", "TIPO", "COR");

    while (fread(prod, sizeof(Produto), 1, arquivo)) {
        if (prod->status == True) {
            printf("| %-5d | %-20.20s | %-10.2f | %-20.20s | %-15.15s |\n", prod->id, prod->modelo_rede, prod->valor_rede, prod->tipo_rede, prod->cor_rede);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        system("clear || cls");
        printf("\nNenhum produto ativo encontrado.\n");
    }

    fclose(arquivo);
    free(prod);
    printf("\nPressione ENTER para continuar...");
    getchar();
}

// LISTAR PRODUTOS INATIVOS
void listar_produtos_inativos(void) {
    Produto* prod = (Produto*) malloc(sizeof(Produto));
    int encontrados = 0;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Produtos Inativos                 ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/produtos.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum produto encontrado (arquivo inexistente).\n");
        getchar();
        free(prod);
        return;
    }

    printf("| %-5s | %-20s | %-10s | %-20s | %-15s |\n", "ID", "MODELO", "VALOR", "TIPO", "COR");

    while (fread(prod, sizeof(Produto), 1, arquivo)) {
        if (prod->status == False) {
            printf("| %-5d | %-20.20s | %-10.2f | %-20.20s | %-15.15s |\n", prod->id, prod->modelo_rede, prod->valor_rede, prod->tipo_rede, prod->cor_rede);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        system("clear || cls");
        printf("\nNenhum produto inativo encontrado.\n");
    }

    fclose(arquivo);
    free(prod);
    printf("\nPressione ENTER para continuar...");
    getchar();
}

//filtrar produtos por preço

void filtrar_produtos_preco(void) {
    Produto* prod = (Produto*) malloc(sizeof(Produto));
    char valor_minimo [20];
    char valor_maximo [20];
    float preco_minimo;
    float preco_maximo;
    int prod_encontrado = 1;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║          Filtrar Produtos por Preço             ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/produtos.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum produto encontrado (arquivo inexistente).\n");
        getchar();
        free(prod);
        return;
    }

    do {
        printf("Digite o preco mínimo do produto: ");
        scanf("%[^\n]", valor_minimo);
        limpar_buffer();

    } while (validar_valor(valor_minimo) == 0);
    preco_minimo = atof(valor_minimo);

    do {
        printf("\nAgora, digite o preco máximo do produto: ");
        scanf("%[^\n]", valor_maximo);
        limpar_buffer();

    } while (validar_valor(valor_maximo) == 0);
    preco_maximo = atof(valor_maximo);

    system("clear || cls");

    printf("| %-5s | %-20s | %-10s | %-20s | %-15s |\n", "ID", "MODELO", "VALOR", "TIPO", "COR");
    while (fread(prod, sizeof(Produto), 1, arquivo)) {
        if (prod->valor_rede >= preco_minimo && prod->valor_rede <= preco_maximo) {
            printf("| %-5d | %-20.20s | %-10.2f | %-20.20s | %-15.15s |\n", prod->id, prod->modelo_rede, prod->valor_rede, prod->tipo_rede, prod->cor_rede);
            prod_encontrado ++;
        }
    }
    if (prod_encontrado <= 1) {
        system("clear || cls");
        printf("Nenhum produto foi encontrado nessa faixa de preço.");
    }

    getchar();

    fclose(arquivo);
    free(prod);
}

// ============================================================
// LISTAR PEDIDOS ATIVOS
// ============================================================
void listar_pedidos_ativos(void) {
    Pedido* pedido;
    pedido = (Pedido*) malloc(sizeof(Pedido));
    int encontrados = 0;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                 Pedidos Ativos                  ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/pedidos.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum pedido encontrado (arquivo inexistente).\n");
        getchar();
        free(pedido);
        return;
    }

    printf("| %-10s | %-10s | %-10s | %-15s | %-10s | %-26s |\n", "ID PEDIDO", "ID CLIENTE", "ID PRODUTO", "ID FUNCIONARIO", "PRECO", "DATA");

    while (fread(pedido, sizeof(Pedido), 1, arquivo)) {
        if (pedido->status == True) {
            printf("| %-10d | %-10d | %-10d | %-15d | %-10.2f | %-26.26s |\n", pedido->id_pedido, pedido->id_cliente, pedido->id_produto, pedido->id_funcionario, pedido->preco, pedido->data);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        system("clear || cls");
        printf("\nNenhum pedido ativo encontrado.\n");
    }

    fclose(arquivo);
    free(pedido);
    printf("\nPressione ENTER para continuar...");
    getchar();
}

// ============================================================
// LISTAR PEDIDOS INATIVOS
// ============================================================
void listar_pedidos_inativos(void) {
    Pedido* pedido;
    pedido = (Pedido*) malloc(sizeof(Pedido));
    int encontrados = 0;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                 Pedidos Inativos                ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/pedidos.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum pedido encontrado (arquivo inexistente).\n");
        getchar();
        free(pedido);
        return;
    }

    printf("| %-10s | %-10s | %-10s | %-15s | %-10s | %-26s |\n", "ID PEDIDO", "ID CLIENTE", "ID PRODUTO", "ID FUNCIONARIO", "PRECO", "DATA");
    while (fread(pedido, sizeof(Pedido), 1, arquivo)) {
        if (pedido->status == False) {
            printf("| %-10d | %-10d | %-10d | %-15d | %-10.2f | %-26.26s |\n", pedido->id_pedido, pedido->id_cliente, pedido->id_produto, pedido->id_funcionario, pedido->preco, pedido->data);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        system("clear || cls");
        printf("\nNenhum pedido inativo encontrado.\n");
    }

    fclose(arquivo);
    free(pedido);
    printf("\nPressione ENTER para continuar...");
    getchar();
}

//filtrar pedidos por data

void filtrar_pedidos_data(void) {
    Pedido* pedido;
    pedido = (Pedido*) malloc(sizeof(Pedido));
    int pedido_encontrado = 1;

    char data_minima [26];
    char *dia_minimo;
    char *mes_minimo;
    char *ano_minimo;
    int data_minima_int = 0;

    char data_maxima [26];
    char *dia_maximo;
    char *mes_maximo;
    char *ano_maximo;
    int data_maxima_int = 0;

    char *dia_pedido;
    char *mes_pedido;
    char *ano_pedido;
    int data_pedido_int = 0;

    char data_copia [26];


    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║           Filtrar Pedidos por período           ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");

    arquivo = fopen("database/pedidos.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum pedido encontrado (arquivo inexistente).\n");
        getchar();
        free(pedido);
        return;
    }

    do {
        printf("\nDigite a data mínima do pedido: ");
        scanf("%[^\n]", data_minima);
        limpar_buffer();
    } while (validar_data(data_minima) == 0);

    dia_minimo = strtok(data_minima, "/");
    mes_minimo = strtok(NULL, "/");
    ano_minimo = strtok(NULL, "/");
    data_minima_int = atoi(ano_minimo) * 10000 + atoi(mes_minimo) * 100 + atoi(dia_minimo);

    

    do {
        printf("\nAgora, digite a data máxima do pedido: ");
        scanf("%[^\n]", data_maxima);
        limpar_buffer();
    } while (validar_data(data_maxima) == 0);

    dia_maximo = strtok(data_maxima, "/");
    mes_maximo = strtok(NULL, "/");
    ano_maximo = strtok(NULL, "/");
    data_maxima_int = atoi(ano_maximo) * 10000 + atoi(mes_maximo) * 100 + atoi(dia_maximo);


    system("clear || cls");

    printf("| %-10s | %-10s | %-10s | %-15s | %-10s | %-26s |\n", "ID PEDIDO", "ID CLIENTE", "ID PRODUTO", "ID FUNCIONARIO", "PRECO", "DATA");
    while (fread(pedido, sizeof(Pedido), 1, arquivo)) {
        strcpy(data_copia, pedido->data);
        dia_pedido = strtok(data_copia, "/");
        mes_pedido = strtok(NULL, "/");
        ano_pedido = strtok(NULL, "/");
        data_pedido_int = atoi(ano_pedido) * 10000 + atoi(mes_pedido) * 100 + atoi(dia_pedido);


        if (data_pedido_int >= data_minima_int && data_pedido_int <= data_maxima_int) {
            printf("| %-10d | %-10d | %-10d | %-15d | %-10.2f | %-26.26s |\n", pedido->id_pedido, pedido->id_cliente, pedido->id_produto, pedido->id_funcionario, pedido->preco, pedido->data);
            pedido_encontrado ++;
        }
    }
    if (pedido_encontrado <= 1) {
        system("clear || cls");
        printf("Nennhum pedido foi encontrado nesse período.");
    }

    getchar();

    fclose(arquivo);
    free(pedido);
}