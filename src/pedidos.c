#include <stdio.h>
#include <stdlib.h>
#include <string.h> //usar o "strcmp"
#include <unistd.h>
#include "../include/utilidades.h"
#include "../include/pedidos.h"
#include "../include/clientes.h"
#include "../include/produto.h"
#include "../include/funcionarios.h"
#include <time.h>
#include <locale.h>

FILE * arquivo_pedido; //Apontador do arquivo

void modulo_pedidos(void){
    char opcao;

    do {
        opcao = tela_de_pedidos();
        switch(opcao){
            case '1':   cadastrar_pedidos();
                        break;
            case '2':   exibir_pedidos();
                        break;
            case '3':   excluir_pedido();
                        break;
            case '4':   perma_excluir_pedido();
                        break;
            case '5':   restaurar_pedido();
                        break;

        }
    } while (opcao != '0');
}

char tela_de_pedidos(void){

    char op_pedido;
    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Módulo De Pedidos                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║                                                 ║\n");
    printf("║ 1 - Cadastrar Pedido                            ║\n");
    printf("║ 2 - Exibir Pedido                               ║\n");
    printf("║ 3 - Excluir Pedido                              ║\n");
    printf("║ 4 - Excluir permanentemente Pedido              ║\n");
    printf("║ 5 - Restaurar Pedido                            ║\n");
    printf("║                                                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║ 0 - Voltar                                      ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op_pedido);
    return op_pedido;
}

void cadastrar_pedidos(void){
    if (verificar_criacao_pedidos() == 1) {
        limpar_buffer();
        Pedido* pedido;
        pedido = (Pedido*) malloc(sizeof(Pedido));
        char add_produto;

        system("clear || cls");
        printf("╔═════════════════════════════════════════════════╗\n");
        printf("║               Cadastrar Pedidos                 ║\n");
        printf("╚═════════════════════════════════════════════════╝\n");
        receber_dados_pedido(pedido);
        
        arquivo_pedido = fopen("database/pedidos.dat", "ab"); //Cria o arquivo
        if (arquivo_pedido == NULL) {
            printf("\nO arquivo nao foi criado.");
            getchar();
        }
        else{
            //Escreve o novo pedido no arquivo
            fwrite(pedido, sizeof(Pedido), 1, arquivo_pedido);

            do {
                system("clear || cls");
                printf("Deseja adicionar outro produto a esse pedido?\n1 - SIM\n2 - NÃO\n");
                scanf("%c", &add_produto);
                limpar_buffer();
                if (add_produto == '1') {
                    adicionar_outro_produto(pedido);
                    fwrite(pedido, sizeof(Pedido), 1, arquivo_pedido);
                    printf("Novo produto foi adicionado ao pedido.");
                    getchar();
                }
            } while (add_produto != '2');

            fclose(arquivo_pedido);
            printf("\nPedido de numero %d cadastrado com sucesso!", pedido->id_pedido);
            printf("\nPressione ENTER para continuar.");
            free(pedido);
        }
        getchar();
    }
}

void exibir_pedidos(void){
    int id_procurar = 0;
    Pedido* pedido;
    pedido = (Pedido*) malloc(sizeof(Pedido));

    Pedido* pedido_exibir;
    pedido_exibir = (Pedido*) malloc(sizeof(Pedido));

    char id_produtos[50] = "";
    float total_preco = 0;

    system("clear || cls");
    limpar_buffer();
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Pequisar Pedidos                  ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do pedido que deseja buscar: ");
    scanf(" %d", &id_procurar);

    arquivo_pedido = fopen("database/pedidos.dat", "rb");

    if (arquivo_pedido == NULL) {
        arquivo_pedido = fopen("database/pedidos.dat", "wb");
        fclose(arquivo_pedido);
        arquivo_pedido = fopen("database/pedidos.dat", "rb");
    }

    // Obtendo as informações do pedido
    int auxi = 0;
    char temp[20];
    while (fread(pedido, sizeof(Pedido), 1, arquivo_pedido)){
        if (pedido->id_pedido == id_procurar && pedido->status == True){
            sprintf(temp, "%d,", pedido->id_produto);
            strcat(id_produtos, temp);

            total_preco += pedido->preco;
            pedido_exibir = pedido;

            auxi++;
        }
    }

    // Exibindo o pedido
    if (total_preco != 0) {
        printf("\nID do Pedido: %d", pedido_exibir->id_pedido);
        printf("\nID do Cliente: %d", pedido_exibir->id_cliente);
        printf("\nID dos Produtos: %s", id_produtos);
        printf("\nID do Funcionario: %d", pedido_exibir->id_funcionario);
        printf("\nPreco do Pedido: %f", total_preco);
        printf("\nData do Pedido: %s", pedido_exibir->data);

        limpar_buffer();
        getchar();
        fclose(arquivo_pedido);
        free(pedido);
        return;
    }
    fclose(arquivo_pedido);
    free(pedido);
    limpar_buffer();
    printf("\nNenhum pedido com o ID %d foi encontrado.", id_procurar);
    getchar();
}

void excluir_pedido(void){
    int id_procurar = 0;
    Pedido* pedido;
    pedido = (Pedido*) malloc(sizeof(Pedido));
    int pedido_excluido = False;
    int pedido_encontrado = False;
    char opc_confirmar = 'N';

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                Excluir Pedidos                  ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do pedido que deseja excluir: ");
    scanf(" %d", &id_procurar);
    limpar_buffer();

    arquivo_pedido = fopen("database/pedidos.dat", "r+b");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_pedido == NULL) {
        arquivo_pedido = fopen("database/pedidos.dat", "wb");
        fclose(arquivo_pedido);
        arquivo_pedido = fopen("database/pedidos.dat", "r+b");
    }

    while (fread(pedido, sizeof(Pedido), 1, arquivo_pedido)){
        if (pedido->id_pedido == id_procurar && pedido->status == True){
            if (pedido_encontrado == False) {
                system("clear || cls");
                printf("\n\n------------------------ Pedido ------------------------");
                printf("\nID do pedido: %d", pedido->id_pedido);
                printf("\nID do cliente: %d", pedido->id_cliente);
                printf("\nID do produto: %d", pedido->id_produto);
                printf("\nID do funcionario: %d", pedido->id_funcionario);
                printf("\nPreco do pedido: %f", pedido->preco);
                printf("\nData do pedido: %s", pedido->data);
                printf("\n\nPedido de ID %d foi encontrado.\nTem certeza que deseja exclui-lo? (s/n)", id_procurar);
                scanf("%c", &opc_confirmar);
                limpar_buffer();

                if (opc_confirmar == 's' || opc_confirmar == 'S') {
                    pedido->status = 0;
                    pedido_excluido = True;
                    pedido_encontrado = True;
                    fseek(arquivo_pedido, (-1)*sizeof(Pedido), SEEK_CUR);
                    fwrite(pedido, sizeof(Pedido), 1, arquivo_pedido);
                    printf("\nPedido com o ID %d excluido com sucesso!", id_procurar);   
                } else {
                    printf("\nExclusão cancelada.");
                    pedido_encontrado = True;
                }
            }
            else if (pedido_excluido == True) { // serve para restaurar as outras instâncias do pedido
                pedido->status = 0;
                fseek(arquivo_pedido, (-1)*sizeof(Pedido), SEEK_CUR);
                fwrite(pedido, sizeof(Pedido), 1, arquivo_pedido);
            }
        }
        
    }
    if (pedido_encontrado == False) {
        printf("\nNão existe nenhum pedido com o ID %d cadastrado...", id_procurar);
    }
    fclose(arquivo_pedido);
    free(pedido);
    getchar();
}

void restaurar_pedido(void){
    int id_procurar = 0;
    Pedido* pedido;
    pedido = (Pedido*) malloc(sizeof(Pedido));
    int pedido_restaurado = False;
    int pedido_encontrado = False;
    char opc_confirmar = 'N';

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                Restaurar Pedidos                ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do pedido que deseja restaurar: ");
    scanf(" %d", &id_procurar);
    limpar_buffer();

    arquivo_pedido = fopen("database/pedidos.dat", "r+b");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_pedido == NULL) {
        arquivo_pedido = fopen("database/pedidos.dat", "wb");
        fclose(arquivo_pedido);
        arquivo_pedido = fopen("database/pedidos.dat", "r+b");
    }

    while (fread(pedido, sizeof(Pedido), 1, arquivo_pedido)){
        if (pedido->id_pedido == id_procurar && pedido->status == False){
            if (pedido_encontrado == False) {
                system("clear || cls");
                printf("\n\n------------------------ Pedido ------------------------");
                printf("\nID do pedido: %d", pedido->id_pedido);
                printf("\nID do cliente: %d", pedido->id_cliente);
                printf("\nID do produto: %d", pedido->id_produto);
                printf("\nID do funcionario: %d", pedido->id_funcionario);
                printf("\nPreco do pedido: %f", pedido->preco);
                printf("\nData do pedido: %s", pedido->data);
                printf("\n\nPedido de ID %d foi encontrado.\nTem certeza que deseja reativa-lo? (s/n)", id_procurar);
                scanf("%c", &opc_confirmar);
                limpar_buffer();

                if (opc_confirmar == 's' || opc_confirmar == 'S') {
                    pedido->status = 1;
                    pedido_restaurado = True;
                    pedido_encontrado = True;
                    fseek(arquivo_pedido, (-1)*sizeof(Pedido), SEEK_CUR);
                    fwrite(pedido, sizeof(Pedido), 1, arquivo_pedido);
                    printf("\nPedido com o ID %d reativado com sucesso!", id_procurar);   
                } else {
                    printf("\nRestauração cancelada.");
                    pedido_encontrado = True;
                }
            }
            else if (pedido_restaurado == True) { // serve para restaurar as outras instâncias do pedido
                pedido->status = 1;
                fseek(arquivo_pedido, (-1)*sizeof(Pedido), SEEK_CUR);
                fwrite(pedido, sizeof(Pedido), 1, arquivo_pedido);
            }
        }
        
    }
    if (pedido_encontrado == False) {
        printf("\nNão existe nenhum pedido desativado com o ID %d...", id_procurar);
    }
    fclose(arquivo_pedido);
    free(pedido);
    getchar();
}

void perma_excluir_pedido(void) {
    int id_procurar = 0;
    int excluido = False;
    int pedido_encontrado = False;
    char opc_confirmar;
    char opc_escolha;
    Pedido* pedido;
    pedido = (Pedido*) malloc(sizeof(Pedido));
    FILE * arquivo_novo;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║        Excluir Permanentemente Pedidos          ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Deseja excluir um pedido específico ou todos os pedidos inativos?");
    printf("\n1 - Um pedido específico\n2 - Todos os pedidos inativos\n");
    scanf(" %c", &opc_escolha);
    limpar_buffer();

    arquivo_pedido = fopen("database/pedidos.dat", "rb");
    arquivo_novo = fopen("database/pedidos_novo.dat", "wb");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_pedido == NULL) {
        arquivo_pedido = fopen("database/pedidos.dat", "wb");
        fclose(arquivo_pedido);
        arquivo_pedido = fopen("database/pedidos.dat", "rb");
    }

    if (opc_escolha == '1') {
        printf("Digite o ID do pedido que deseja excluir permanentemente: ");
        scanf(" %d", &id_procurar);
        limpar_buffer();

        while (fread(pedido, sizeof(Pedido), 1, arquivo_pedido)){
            if (pedido->id_pedido == id_procurar && pedido->status == False){
                if (pedido_encontrado == False) {
                    system("clear || cls");
                    printf("\n\n------------------------ Pedido ------------------------");
                    printf("\nID do pedido: %d", pedido->id_pedido);
                    printf("\nID do cliente: %d", pedido->id_cliente);
                    printf("\nID do produto: %d", pedido->id_produto);
                    printf("\nID do funcionario: %d", pedido->id_funcionario);
                    printf("\nPreco do pedido: %f", pedido->preco);
                    printf("\nData do pedido: %s", pedido->data);
                    printf("\n\nPedido de ID %d foi encontrado.\nTem certeza que deseja exclui-lo permanentemente? (s/n)", id_procurar);
                    scanf("%c", &opc_confirmar);
                    limpar_buffer();

                    if (opc_confirmar == 's' || opc_confirmar == 'S') {
                        printf("\nPedido com o ID %d excluido com sucesso!", id_procurar);
                        getchar();
                        excluido = True;
                        pedido_encontrado = True;
                    } else {
                        fwrite(pedido, sizeof(Pedido), 1, arquivo_novo);
                        printf("\nExclusão cancelada.");
                        getchar();
                        pedido_encontrado = True;
                        excluido = True;
                    }
                } else if (excluido == True) { // Serve para excluir as outras instâncias de pedido sem perguntar novamente ao cliente

                }
            } else {
                fwrite(pedido, sizeof(Pedido), 1, arquivo_novo);
            }
                    
        }
        if (pedido_encontrado == False) {
            printf("\nNão existe nenhum pedido inativo com o ID %d...", id_procurar);
            getchar();
        }
    }
    else if (opc_escolha == '2') {
        while (fread(pedido, sizeof(Pedido), 1, arquivo_pedido)) {
            if (pedido->status == True){
                fwrite(pedido, sizeof(Pedido), 1, arquivo_novo);
            }     
        }
        printf("Todos os pedidos inativos foram deletados permanentemente.");
        getchar();
    }
    else {
        printf("Opção inválida.");
        getchar();
    }
    fclose(arquivo_pedido);
    fclose(arquivo_novo);
    free(pedido);
    remove("database/pedidos.dat");
    rename("database/pedidos_novo.dat", "database/pedidos.dat");
}

int verificar_criacao_pedidos(void) {
    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));

    int arquivo_vazio = True;

    FILE * arquivo_cliente = fopen("database/clientes.dat", "rb");
    if (arquivo_cliente == NULL) {
        arquivo_cliente = fopen("database/clientes.dat", "wb");
        fclose(arquivo_cliente);
        arquivo_cliente = fopen("database/clientes.dat", "rb");
    }

    while (fread(cli, sizeof(Cliente), 1, arquivo_cliente)){
        if (cli->status == True){
            arquivo_vazio = False;
        }
    }
    fclose(arquivo_cliente);
    free(cli);
        
    if (arquivo_vazio == True) {
        system("clear || cls");
        printf("\nNão tem nenhum cliente cadastrado, então não é possível criar o pedido...");
        getchar();
        getchar();
        return 0;
    }
    arquivo_vazio = True;
    Funcionarios* func;
    func = (Funcionarios*) malloc(sizeof(Funcionarios));

    FILE * arquivo_funcionario = fopen("database/funcionarios.dat", "rb");
    if (arquivo_funcionario == NULL) {
        arquivo_funcionario = fopen("database/funcionarios.dat", "wb");
        fclose(arquivo_funcionario);
        arquivo_funcionario = fopen("database/funcionarios.dat", "rb");
    }

    while (fread(func, sizeof(Funcionarios), 1, arquivo_funcionario)){
        if (func->status == True){
            arquivo_vazio = False;
        }
    }
    fclose(arquivo_funcionario);
    free(func);
            
    if (arquivo_vazio == True) {
        system("clear || cls");
        printf("\nNão tem nenhum funcionário cadastrado, então não é possível criar o pedido...");
        getchar();
        getchar();
        return 0;
    }
    arquivo_vazio = True;
    Produto* prod;
    prod = (Produto*) malloc(sizeof(Produto));

    FILE * arquivo_produto = fopen("database/produtos.dat", "rb");
    if (arquivo_produto == NULL) {
        arquivo_produto = fopen("database/produtos.dat", "wb");
        fclose(arquivo_produto);
        arquivo_produto = fopen("database/produtos.dat", "rb");
    }

    while (fread(prod, sizeof(Produto), 1, arquivo_produto)){
        if (prod->status == True){
            arquivo_vazio = False;
        }
    }
    fclose(arquivo_produto);
    free(prod);
            
    if (arquivo_vazio == True) {
        system("clear || cls");
        printf("\nNão tem nenhum produto cadastrado, então não é possível criar o pedido...");
        getchar();
        getchar();
        return 0;
    }

    return 1;

}

void receber_dados_pedido(Pedido* pedido) {
    char id[20];

    do {
        printf("Digite o ID do cliente que fez o pedido: ");
        scanf("%[^\n]", id);
        limpar_buffer();
    }
    while (verificar_id_cliente(id) == 0);
    pedido->id_cliente = atoi(id);

    do {
        printf("Digite o ID do funcionario que fez o pedido: ");
        scanf("%[^\n]", id);
        limpar_buffer();
    }
    while (verificar_id_funcionario(id) == 0);
    pedido->id_funcionario = atoi(id);

    do {
        printf("Digite o ID do produto que compõe o pedido: ");
        scanf("%[^\n]", id);
        limpar_buffer();
    }
    while (verificar_id_produto(id) == 0);
    pedido->id_produto = atoi(id);

    pedido->preco = verificar_valor_produto(atoi(id));

    time_t agora;
    struct tm *info_data;
    time(&agora);
    info_data = localtime(&agora);
    strftime(pedido->data, sizeof(pedido->data), "%d/%m/%Y", info_data);

    arquivo_pedido = fopen("database/pedidos.dat", "rb");

    if (arquivo_pedido == NULL) {
        arquivo_pedido = fopen("database/pedidos.dat", "wb");
        fclose(arquivo_pedido);
        arquivo_pedido = fopen("database/pedidos.dat", "rb");
    }

    pedido->id_pedido = gerar_id(arquivo_pedido, 4);
    pedido->status = True;

    fclose(arquivo_pedido);
}

void adicionar_outro_produto(Pedido *pedido) {
    char id[20];
    do {
        printf("Digite o ID do outro produto que compõe o pedido: ");
        scanf("%[^\n]", id);
        limpar_buffer();
    } while (verificar_id_produto(id) == 0);

    pedido->id_produto = atoi(id);
    pedido->preco = verificar_valor_produto(atoi(id));
}

void alterar_campo_pedido(Pedido *pedido, char opc_alterar) {
    char id[20] = "";
    char data[26] = "";
    char valor[20];
    switch (opc_alterar){
        case '1':
            do {
                printf("Digite o ID do cliente que fez o pedido: ");
                scanf("%[^\n]", id);
                limpar_buffer();
            }
            while (verificar_id_cliente(id) == 0);
            pedido->id_cliente = atoi(id);
            break;
        case  '2':
            do {
                printf("Digite o ID do produto que fez o pedido: ");
                scanf("%[^\n]", id);
                limpar_buffer();
            }
            while (verificar_id_produto(id) == 0);
            pedido->id_produto = atoi(id);
            break;
        case  '3':
            do {
                printf("Digite o ID do funcionario que fez o pedido: ");
                scanf("%[^\n]", id);
                limpar_buffer();
            }
            while (verificar_id_funcionario(id) == 0);
            pedido->id_funcionario = atoi(id);
            break;
        case  '4':
            do {
                printf("Digite o novo valor do pedido: ");
                scanf("%[^\n]", valor);
                limpar_buffer();
            } while(validar_valor(valor) == 0);
            pedido->preco = atof(valor);
            break;
        case '5':
            do {
                printf("\nDigite a nova data: ");
                scanf("%[^\n]", data);
                limpar_buffer();
            } while (validar_data(data) == 0);
            memcpy(pedido->data, data, sizeof(pedido->data));
            break;                            
        default:
            break;
    }
    system("clear || cls");
    printf("\nPedido com o ID %d alterado com sucesso!", pedido->id_pedido);
    printf("\n\n------------------------ Pedido Alterado ------------------------");
    printf("\nID do pedido: %d", pedido->id_pedido);
    printf("\nID do cliente: %d", pedido->id_cliente);
    printf("\nID do produto: %d", pedido->id_produto);
    printf("\nID do funcionario: %d", pedido->id_funcionario);
    printf("\nPreco do pedido: %f", pedido->preco);
    printf("\nData do pedido: %s", pedido->data);
    getchar();
}

//adicionar função que adiciona um produto a um pedido existente
//