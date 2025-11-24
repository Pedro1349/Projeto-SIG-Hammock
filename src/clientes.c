#include <stdio.h>
#include <stdlib.h>
#include <string.h> //usar o "strcmp"
#include <unistd.h>
#include <ctype.h>
#include "../include/utilidades.h"
#include "../include/clientes.h"
#include <locale.h>

FILE * arquivo_cliente; //Apontador do arquivo

#define MAX_CLIENTES 100

void modulo_clientes(void){
    char opcao;

    do {
        opcao = tela_de_clientes();
        switch(opcao){
            case '1':   cadastrar_clientes();
                        break;
            case '2':   exibir_clientes();
                        break;
            case '3':   alterar_cliente();
                        break;
            case '4':   excluir_cliente();
                        break;
            case '5':   perma_excluir_cliente();
                        break;
            case '6':   restaurar_cliente();
                        break;

        }
    } while (opcao != '0');
}

char tela_de_clientes(void){

    char op_cliente;
    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Módulo De Clientes                ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║                                                 ║\n");
    printf("║ 1 - Cadastrar Cliente                           ║\n");
    printf("║ 2 - Exibir Clientes                             ║\n");
    printf("║ 3 - Editar Cliente                              ║\n");
    printf("║ 4 - Excluir Cliente                             ║\n");
    printf("║ 5 - Excluir Permanentemente Cliente             ║\n");
    printf("║ 6 - Restaurar Cliente                           ║\n");
    printf("║                                                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║ 0 - Voltar                                      ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op_cliente);
    return op_cliente;
}

void cadastrar_clientes(void){
    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));
    limpar_buffer();

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Cadastrar Clientes                ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    receber_dados_cliente(cli);
    
    arquivo_cliente = fopen("database/clientes.dat", "ab"); //Cria o arquivo
    if (arquivo_cliente == NULL) {
        printf("\nO arquivo nao foi criado.");
        getchar();
    }
    else{
        //Escreve o novo cliente no arquivo
        fwrite(cli, sizeof(Cliente), 1, arquivo_cliente);
        fclose(arquivo_cliente);
        free(cli);
        printf("\nCliente cadastrado com sucesso!");
        printf("\nPressione ENTER para continuar.");
    }
    getchar();  // Apenas para pausar antes de sair
}

void exibir_clientes(void){
    int id_procurar = 0;
    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));

    system("clear || cls");
    limpar_buffer();
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Pequisar Clientes                 ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do cliente que deseja buscar: ");
    scanf(" %d", &id_procurar);

    arquivo_cliente = fopen("database/clientes.dat", "rb");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_cliente == NULL) {
        arquivo_cliente = fopen("database/clientes.dat", "wb");
        fclose(arquivo_cliente);
        arquivo_cliente = fopen("database/clientes.dat", "rb");
    }

    while (fread(cli, sizeof(Cliente), 1, arquivo_cliente)){
        if (cli->id == id_procurar && cli->status == True){
            printf("\nID do Cliente: %d", cli->id);
            printf("\nNome do Cliente: %s", cli->nome);
            printf("\nCPF do Cliente: %s", cli->cpf);
            printf("\nEmail do Cliente: %s", cli->email);
            printf("\nTelefone do Cliente: %s", cli->telefone);

            fclose(arquivo_cliente);
            free(cli);
            limpar_buffer();
            getchar();
            return;
        }
        
    }
    fclose(arquivo_cliente);
    free(cli);
    limpar_buffer();
    printf("\nNenhum cliente com esse id foi encontrado.");
    getchar();
}

void alterar_cliente(void){
    int id_procurar = 0;
    char opc_alterar;
    char opc_confirmar;
    int cli_alterado = False;
    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                Alterar Clientes                 ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do cliente que deseja alterar: ");
    scanf(" %d", &id_procurar);
    limpar_buffer();

    arquivo_cliente = fopen("database/clientes.dat", "r+b");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_cliente == NULL) {
        arquivo_cliente = fopen("database/clientes.dat", "wb");
        fclose(arquivo_cliente);
        arquivo_cliente = fopen("database/clientes.dat", "r+b");
    }

    while (fread(cli, sizeof(Cliente), 1, arquivo_cliente) && cli_alterado == False){
        if (cli->id == id_procurar && cli->status == True) {
            do {
                system("clear || cls");
                printf("\nO que deseja alterar desse cliente (Digite 1,2,3 OU 4)? ");
                printf("\n1 - nome");
                printf("\n2 - cpf");
                printf("\n3 - email");
                printf("\n4 - telefone\n");
                scanf("%c", &opc_alterar);
                limpar_buffer();
            } while(opc_alterar != '1' && opc_alterar != '2' && opc_alterar != '3' && opc_alterar != '4');

            alterar_campo_cliente(cli, opc_alterar);

            printf("\nDeseja alterar algum outro campo? (s/n)\n");
            scanf("%c", &opc_confirmar);
            limpar_buffer();
            fseek(arquivo_cliente, (-1)*sizeof(Cliente), SEEK_CUR);
            fwrite(cli, sizeof(Cliente), 1, arquivo_cliente);
            
            if (opc_confirmar == 's' || opc_confirmar == 'S'){
                fseek(arquivo_cliente, (-1)*sizeof(Cliente), SEEK_CUR);     
            } else {
                cli_alterado = True;
            }
        }
    }
    if (cli_alterado == False) {
        printf("\nCliente com o ID %d não foi encontrado...", id_procurar);
        getchar();
    }
    fclose(arquivo_cliente);
    free(cli);
}

void excluir_cliente(void){
    int id_procurar = 0;
    int excluido = False;
    char opc_confirmar;
    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                Excluir Clientes                 ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do cliente que deseja excluir: ");
    scanf(" %d", &id_procurar);
    limpar_buffer();

    arquivo_cliente = fopen("database/clientes.dat", "r+b");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_cliente == NULL) {
        arquivo_cliente = fopen("database/clientes.dat", "wb");
        fclose(arquivo_cliente);
        arquivo_cliente = fopen("database/clientes.dat", "r+b");
    }

    while (fread(cli, sizeof(Cliente), 1, arquivo_cliente) && (excluido == False)){
        if (cli->id == id_procurar && cli->status == True){
            system("clear || cls");
            printf("\n\n------------------------ Cliente ------------------------");
            printf("\nID do cliente: %d", cli->id);
            printf("\nNome do cliente: %s", cli->nome);
            printf("\nCPF do cliente: %s", cli->cpf);
            printf("\nEmail do cliente: %s", cli->email);
            printf("\nTelefone do cliente: %s", cli->telefone);
            printf("\n\nCliente de ID %d foi encontrado.\nTem certeza que deseja exclui-lo? (s/n)", id_procurar);
            scanf("%c", &opc_confirmar);
            limpar_buffer();

            if (opc_confirmar == 's' || opc_confirmar == 'S') {
                cli->status = 0;

                excluido = True;
                fseek(arquivo_cliente, (-1)*sizeof(Cliente), SEEK_CUR);
                fwrite(cli, sizeof(Cliente), 1, arquivo_cliente);
                printf("\nCliente com o ID %d excluido com sucesso!", id_procurar);   
            } else {
                printf("\nExclusão cancelada.");
                excluido = True;
            }
        }
                 
    }
    if (excluido == False) {
        printf("\nNão existe nenhum cliente com o ID %d cadastrado...", id_procurar);
    }
    fclose(arquivo_cliente);
    free(cli);
    getchar();
}

void restaurar_cliente(void) {
    int id_procurar = 0;
    int restaurado = False;
    char opc_confirmar;
    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                Restaurar Clientes               ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do cliente que deseja reativar: ");
    scanf(" %d", &id_procurar);
    limpar_buffer();

    arquivo_cliente = fopen("database/clientes.dat", "r+b");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_cliente == NULL) {
        arquivo_cliente = fopen("database/clientes.dat", "wb");
        fclose(arquivo_cliente);
        arquivo_cliente = fopen("database/clientes.dat", "r+b");
    }

    while (fread(cli, sizeof(Cliente), 1, arquivo_cliente) && (restaurado == False)){
        if (cli->id == id_procurar && cli->status == False){
            system("clear || cls");
            printf("\n\n------------------------ Cliente ------------------------");
            printf("\nID do cliente: %d", cli->id);
            printf("\nNome do cliente: %s", cli->nome);
            printf("\nCPF do cliente: %s", cli->cpf);
            printf("\nEmail do cliente: %s", cli->email);
            printf("\nTelefone do cliente: %s", cli->telefone);
            printf("\n\nCliente de ID %d foi encontrado.\nTem certeza que deseja restaura-lo? (s/n)", id_procurar);
            scanf("%c", &opc_confirmar);
            limpar_buffer();

            if (opc_confirmar == 's' || opc_confirmar == 'S') {
                cli->status = 1;

                restaurado = True;
                fseek(arquivo_cliente, (-1)*sizeof(Cliente), SEEK_CUR);
                fwrite(cli, sizeof(Cliente), 1, arquivo_cliente);
                printf("\nCliente com o ID %d restaurado com sucesso!", id_procurar);   
            } else {
                printf("\nRestauração cancelada.");
                restaurado = True;
            }
        }
                 
    }
    if (restaurado == False) {
        printf("\nNão existe nenhum cliente desativado com o ID %d...", id_procurar);
    }
    fclose(arquivo_cliente);
    free(cli);
    getchar();
}

void perma_excluir_cliente(void) {
    int id_procurar = 0;
    int excluido = False;
    char opc_confirmar;
    char opc_escolha;
    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));
    FILE * arquivo_novo;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║        Excluir Permanentemente Clientes         ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Deseja excluir um cliente específico ou todos os clientes inativos?");
    printf("\n1 - Um cliente específico\n2 - Todos os clientes inativos\n");
    scanf(" %c", &opc_escolha);
    limpar_buffer();

    arquivo_cliente = fopen("database/clientes.dat", "rb");
    arquivo_novo = fopen("database/clientes_novo.dat", "wb");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_cliente == NULL) {
        arquivo_cliente = fopen("database/clientes.dat", "wb");
        fclose(arquivo_cliente);
        arquivo_cliente = fopen("database/clientes.dat", "rb");
    }

    if (opc_escolha == '1') {
        printf("Digite o ID do cliente que deseja excluir permanentemente: ");
        scanf(" %d", &id_procurar);
        limpar_buffer();

        while (fread(cli, sizeof(Cliente), 1, arquivo_cliente)){
            if (cli->id == id_procurar && cli->status == False){
                system("clear || cls");
                printf("\n\n------------------------ Cliente ------------------------");
                printf("\nID do cliente: %d", cli->id);
                printf("\nNome do cliente: %s", cli->nome);
                printf("\nCPF do cliente: %s", cli->cpf);
                printf("\nEmail do cliente: %s", cli->email);
                printf("\nTelefone do cliente: %s", cli->telefone);
                printf("\n\nCliente de ID %d foi encontrado.\nTem certeza que deseja exclui-lo permanentemente? (s/n)", id_procurar);
                scanf("%c", &opc_confirmar);
                limpar_buffer();

                if (opc_confirmar == 's' || opc_confirmar == 'S') {
                    printf("\nCliente com o ID %d excluido com sucesso!", id_procurar);
                    getchar();
                    excluido = True;
                } else {
                    fwrite(cli, sizeof(Cliente), 1, arquivo_novo);
                    printf("\nExclusão cancelada.");
                    getchar();
                    excluido = True;
                }
            } else {
                fwrite(cli, sizeof(Cliente), 1, arquivo_novo);
            }
                    
        }
        if (excluido == False) {
            printf("\nNão existe nenhum cliente inativo com o ID %d...", id_procurar);
            getchar();
        }
    }
    else if (opc_escolha == '2') {
        while (fread(cli, sizeof(Cliente), 1, arquivo_cliente)) {
            if (cli->status == True){
                fwrite(cli, sizeof(Cliente), 1, arquivo_novo);
            }     
        }
        printf("Todos os clientes inativos foram deletados permanentemente.");
        getchar();
    }
    else {
        printf("Opção inválida.");
        getchar();
    }
    fclose(arquivo_cliente);
    fclose(arquivo_novo);
    free(cli);
    remove("database/clientes.dat");
    rename("database/clientes_novo.dat", "database/clientes.dat");
}

int verificar_id_cliente(char *valor) {
    int id;
    if (valor == NULL || strlen(valor) == 0) {
        printf("\nDigite o id.");
        getchar();
        return 0;
    }

    for (int i = 0; valor[i] != '\0'; i++) {
        if (!isdigit((unsigned char)valor[i])) {
            printf("\nDigite apenas numeros (0-9).");
            getchar();
            return 0;
        }
    }

    id = atoi(valor);

    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));

    arquivo_cliente = fopen("database/clientes.dat", "rb");

    if (arquivo_cliente == NULL) {
        arquivo_cliente = fopen("database/clientes.dat", "wb");
        fclose(arquivo_cliente);
        arquivo_cliente = fopen("database/clientes.dat", "rb");
    }

    while (fread(cli, sizeof(Cliente), 1, arquivo_cliente)){
        if (cli->status == True){
            if (cli->id == id) {
                fclose(arquivo_cliente);
                free(cli);
                return 1;
            }
        }
    }
    fclose(arquivo_cliente);
    free(cli);
    printf("\nUm cliente com o ID %d não existe", id);
    getchar();
    return 0;
}

void receber_dados_cliente(Cliente* cli) {
    char cpf[30];
    char email[51];
    char nome[51];
    char telefone[12];

    do {
        printf("Digite o nome do cliente: ");
        scanf("%[^\n]", nome);
        limpar_buffer();
    } while (validar_nome(nome) == 0);
    memcpy(cli->nome, nome, sizeof(cli->nome));

    do {
        printf("Digite o CPF do cliente: ");
        scanf("%[^\n]", cpf);
        limpar_buffer();   
    }
    while (validar_cpf(cpf) == 0);
    memcpy(cli->cpf, cpf, sizeof(cli->cpf));

    do {
        printf("Digite o email do cliente: ");
        scanf("%[^\n]", email);
        limpar_buffer();
    }
    while (validar_email(email) == 0);
    memcpy(cli->email, email, sizeof(cli->email));

    do {
        printf("Digite o telefone do cliente: ");
        scanf("%[^\n]", telefone);
        limpar_buffer();
    } while(validar_telefone(telefone) == 0);
    memcpy(cli->telefone, telefone, sizeof(cli->telefone));

    arquivo_cliente = fopen("database/clientes.dat", "rb");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_cliente == NULL) {
        arquivo_cliente = fopen("database/clientes.dat", "wb");
        fclose(arquivo_cliente);
        arquivo_cliente = fopen("database/clientes.dat", "rb");
    }

    cli->id = gerar_id(arquivo_cliente, 1);

    fclose(arquivo_cliente);
    cli->status = True;
}

void alterar_campo_cliente(Cliente* cli, char opc_alterar) {
    char cpf[30];
    char email[51];
    char nome[51];
    char telefone[12];

    switch (opc_alterar){
        case '1':
            do {
                printf("Digite o nome do cliente: ");
                scanf("%[^\n]", nome);
                limpar_buffer();
            } while (validar_nome(nome) == 0);
            memcpy(cli->nome, nome, sizeof(cli->nome));
            break;
        case  '2':
            do {
                printf("Digite o CPF do cliente: ");
                scanf("%[^\n]", cpf);
                limpar_buffer();   
            }
            while (validar_cpf(cpf) == 0);
            memcpy(cli->cpf, cpf, sizeof(cli->cpf));
            break;
        case  '3':
            do {
                printf("Digite o email do cliente: ");
                scanf("%[^\n]", email);
                limpar_buffer();
            }
            while (validar_email(email) == 0);
            memcpy(cli->email, email, sizeof(cli->email));
            break;
        case  '4':
            do {
                printf("Digite o telefone do cliente: ");
                scanf("%[^\n]", telefone);
                limpar_buffer();
            } while(validar_telefone(telefone) == 0);
            memcpy(cli->telefone, telefone, sizeof(cli->telefone));
            break;
        default:
            break;
    }
    system("clear || cls");
    printf("\nCliente com o ID %d alterado com sucesso!", cli->id);
    printf("\n\n------------------------ Cliente Alterado ------------------------");
    printf("\nID do cliente: %d", cli->id);
    printf("\nNome do cliente: %s", cli->nome);
    printf("\nCPF do cliente: %s", cli->cpf);
    printf("\nEmail do cliente: %s", cli->email);
    printf("\nTelefone do cliente: %s", cli->telefone);
    getchar();
}

char* procurar_nome_cliente(int id) {
    Cliente* cli;
    cli = (Cliente*) malloc(sizeof(Cliente));

    arquivo_cliente = fopen("database/clientes.dat", "rb");

    while(fread(cli, sizeof(Cliente), 1, arquivo_cliente)) {
        if (cli->id == id)  {
            return cli->nome;
        }
    }
    return NULL;
}