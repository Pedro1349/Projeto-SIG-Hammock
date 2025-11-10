#include <stdio.h>
#include <stdlib.h>
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

    while (fread(prod, sizeof(Produto), 1, arquivo)) {
        if (prod->status == True) {
            printf("\nID: %d", prod->id);
            printf("\nModelo: %s", prod->modelo_rede);
            printf("\nValor: %.2f", prod->valor_rede);
            printf("\nTipo: %s", prod->tipo_rede);
            printf("\nCor: %s", prod->cor_rede);
            printf("\n---------------------------------------------------");
            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("\nNenhum produto ativo encontrado.\n");

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

    while (fread(prod, sizeof(Produto), 1, arquivo)) {
        if (prod->status == False) {
            printf("\nID: %d", prod->id);
            printf("\nModelo: %s", prod->modelo_rede);
            printf("\nValor: %.2f", prod->valor_rede);
            printf("\nTipo: %s", prod->tipo_rede);
            printf("\nCor: %s", prod->cor_rede);
            printf("\n---------------------------------------------------");
            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("\nNenhum produto inativo encontrado.\n");

    fclose(arquivo);
    free(prod);
    printf("\nPressione ENTER para continuar...");
    getchar();
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

void listar_clientes(void) {
    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));
    int arquivo_vazio = True;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Listar Clientes                   ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    arquivo = fopen("database/clientes.dat", "rb");

    if (arquivo == NULL) {
        arquivo = fopen("database/clientes.dat", "wb");
        fclose(arquivo);
        arquivo = fopen("database/clientes.dat", "rb");
    }

    while (fread(cli, sizeof(Cliente), 1, arquivo)){
        if (cli->status == True){
            printf("\n\n-------------------- Cliente %d --------------------", cli->id);
            printf("\nID do Cliente: %d", cli->id);
            printf("\nNome do Cliente: %s", cli->nome);
            printf("\nCPF do Cliente: %s", cli->cpf);
            printf("\nEmail do Cliente: %s", cli->email);
            printf("\nTelefone do Cliente: %s", cli->telefone);
            getchar();
            arquivo_vazio = False;
        }
    }
    fclose(arquivo);
    free(cli);
        
    if (arquivo_vazio == True) {
        printf("Não tem nenhum cliente cadastrado...");
        getchar();
    }

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

    while (fread(cli, sizeof(Cliente), 1, arquivo)) {
        if (cli->status == True) {
            printf("\n\n-------------------- Cliente %d --------------------", cli->id);
            printf("\nID do Cliente: %d", cli->id);
            printf("\nNome do Cliente: %s", cli->nome);
            printf("\nCPF do Cliente: %s", cli->cpf);
            printf("\nEmail do Cliente: %s", cli->email);
            printf("\nTelefone do Cliente: %s", cli->telefone);
            printf("\n---------------------------------------------------");
            encontrados++;
        }
    }

    if (encontrados == 0) {
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

    while (fread(cli, sizeof(Cliente), 1, arquivo)) {
        if (cli->status == False) {
            printf("\n\n-------------------- Cliente %d --------------------", cli->id);
            printf("\nID do Cliente: %d", cli->id);
            printf("\nNome do Cliente: %s", cli->nome);
            printf("\nCPF do Cliente: %s", cli->cpf);
            printf("\nEmail do Cliente: %s", cli->email);
            printf("\nTelefone do Cliente: %s", cli->telefone);
            printf("\n---------------------------------------------------");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum cliente inativo encontrado.\n");
    }

    fclose(arquivo);
    free(cli);

    printf("\n\nPressione ENTER para continuar...");
    getchar();
}


void listar_funcionarios(void) {
    Funcionarios* func;
    func = (Funcionarios*) malloc(sizeof(Funcionarios));
    int arquivo_vazio = True;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Listar Funcionários               ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    arquivo = fopen("database/funcionarios.dat", "rb");

    if (arquivo == NULL) {
        arquivo = fopen("database/funcionarios.dat", "wb");
        fclose(arquivo);
        arquivo = fopen("database/funcionarios.dat", "rb");
    }

    while (fread(func, sizeof(Funcionarios), 1, arquivo)){
        if (func->status == True){
            printf("\n\n------------------ Funcionário %d ------------------", func->id);
            printf("\nID do Funcionário: %d", func->id);
            printf("\nNome do Funcionário: %s", func->nome);
            printf("\nCPF do Funcionário: %s", func->cpf);
            printf("\nEmail do Funcionário: %s", func->email);
            printf("\nTelefone do Funcionário: %s", func->telefone);
            getchar();
            arquivo_vazio = False;
        }
    }
    fclose(arquivo);
    free(func);
  
    if (arquivo_vazio == True) {
        printf("Não tem nenhum funcionário cadastrado...");
        getchar();
    }
    
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

    while (fread(func, sizeof(Funcionarios), 1, arquivo)) {
        if (func->status == True) {
            printf("\n\n------------------ Funcionário %d ------------------", func->id);
            printf("\nID do Funcionário: %d", func->id);
            printf("\nNome: %s", func->nome);
            printf("\nCPF: %s", func->cpf);
            printf("\nEmail: %s", func->email);
            printf("\nTelefone: %s", func->telefone);
            printf("\n---------------------------------------------------");
            encontrados++;
        }
    }

    if (encontrados == 0) {
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

    while (fread(func, sizeof(Funcionarios), 1, arquivo)) {
        if (func->status == False) {
            printf("\n\n------------------ Funcionário %d ------------------", func->id);
            printf("\nID do Funcionário: %d", func->id);
            printf("\nNome: %s", func->nome);
            printf("\nCPF: %s", func->cpf);
            printf("\nEmail: %s", func->email);
            printf("\nTelefone: %s", func->telefone);
            printf("\n---------------------------------------------------");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum funcionário inativo encontrado.\n");
    }

    fclose(arquivo);
    free(func);

    printf("\n\nPressione ENTER para continuar...");
    getchar();
}


void listar_produto(void) {
    Produto* prod;
    prod = (Produto*) malloc(sizeof(Produto));
    int arquivo_vazio = True;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Listar Produtos                   ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    arquivo = fopen("database/produtos.dat", "rb");

    if (arquivo == NULL) {
        arquivo = fopen("database/produtos.dat", "wb");
        fclose(arquivo);
        arquivo = fopen("database/produtos.dat", "rb");
    }

    while (fread(prod, sizeof(Produto), 1, arquivo)){
        if (prod->status == True){
            printf("\n\n------------------------ Produto %d ------------------------", prod->id);
            printf("\nID do Produto: %d", prod->id);
            printf("\nModelo do Produto: %s", prod->modelo_rede);
            printf("\nValor do Produto: %f", prod->valor_rede);
            printf("\nTipo do Produto: %s", prod->tipo_rede);
            printf("\nCor do Produto: %s", prod->cor_rede);
            getchar();
            arquivo_vazio = False;
        }
    }
    fclose(arquivo);
    free(prod);
            
    if (arquivo_vazio == True) {
        printf("Não tem nenhum produto cadastrado...");
        getchar();
    }
    
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

    while (fread(pedido, sizeof(Pedido), 1, arquivo)) {
        if (pedido->status == True) {
            printf("\n\n---------------------- Pedido %d ----------------------", pedido->id_pedido);
            printf("\nID do Pedido: %d", pedido->id_pedido);
            printf("\nID do Cliente: %d", pedido->id_cliente);
            printf("\nID do Produto: %d", pedido->id_produto);
            printf("\nID do Funcionário: %d", pedido->id_funcionario);
            printf("\nPreço do Pedido: %.2f", pedido->preco);
            printf("\nData do Pedido: %s", pedido->data);
            printf("\n---------------------------------------------------");
            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("\nNenhum pedido ativo encontrado.\n");

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

    while (fread(pedido, sizeof(Pedido), 1, arquivo)) {
        if (pedido->status == False) {
            printf("\n\n---------------------- Pedido %d ----------------------", pedido->id_pedido);
            printf("\nID do Pedido: %d", pedido->id_pedido);
            printf("\nID do Cliente: %d", pedido->id_cliente);
            printf("\nID do Produto: %d", pedido->id_produto);
            printf("\nID do Funcionário: %d", pedido->id_funcionario);
            printf("\nPreço do Pedido: %.2f", pedido->preco);
            printf("\nData do Pedido: %s", pedido->data);
            printf("\n---------------------------------------------------");
            encontrados++;
        }
    }

    if (encontrados == 0)
        printf("\nNenhum pedido inativo encontrado.\n");

    fclose(arquivo);
    free(pedido);
    printf("\nPressione ENTER para continuar...");
    getchar();
}


void listar_pedidos(void) {
    Pedido* pedido;
    pedido = (Pedido*) malloc(sizeof(Pedido));
    int arquivo_vazio = True;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Listar Pedidos                    ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    arquivo = fopen("database/pedidos.dat", "rb");

    if (arquivo == NULL) {
        arquivo = fopen("database/pedidos.dat", "wb");
        fclose(arquivo);
        arquivo = fopen("database/pedidos.dat", "rb");
    }

    while (fread(pedido, sizeof(Pedido), 1, arquivo)){
        if (pedido->status == True)
        {
            printf("\n\n------------------------ Pedido %d ------------------------", pedido->id_pedido);
            printf("\nID do Pedido: %d", pedido->id_pedido);
            printf("\nID do Cliente: %d", pedido->id_cliente);
            printf("\nID do Produto: %d", pedido->id_produto);
            printf("\nID do Funcionario: %d", pedido->id_funcionario);
            printf("\nPreco do Pedido: %f", pedido->preco);
            printf("\nData do Pedido: %s", pedido->data);
            getchar();
            arquivo_vazio = False;
        }
    }
    fclose(arquivo);
    free(pedido);
            
    if (arquivo_vazio == True) {
        printf("Não tem nenhum pedido cadastrado...");
        getchar();
    }
    
}