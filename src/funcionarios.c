#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "../include/utilidades.h"
#include "../include/funcionarios.h"
#include <locale.h>


FILE * arquivo_funcionario; //Apontador para o arquivo

void modulo_funcionarios(void) {
    char opcao;

    do {
        opcao = tela_de_funcionarios();
        switch(opcao) {
            case '1':   cadastrar_funcionarios();
                        break;
            case '2': 	exibir_funcionarios();
                        break;
            case '3': 	alterar_funcionarios();
                        break;
            case '4': 	excluir_funcionarios();
                        break;
            case '5': 	perma_excluir_funcionario();
                        break;
            case '6': 	restaurar_funcionarios();
                        break;
        } 		
    } while (opcao != '0');
}

char tela_de_funcionarios(void){

    char op_funcionario;
    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Módulo De Funcionarios            ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║                                                 ║\n");
    printf("║ 1 - Cadastrar Funcionario                       ║\n");
    printf("║ 2 - Exibir Funcionario                          ║\n");
    printf("║ 3 - Editar Funcionario                          ║\n");
    printf("║ 4 - Excluir Funcionario                         ║\n");
    printf("║ 5 - Excluir Permanentemente Funcionario         ║\n");
    printf("║ 6 - Restaurar Funcionario                       ║\n");
    printf("║                                                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║ 0 - Voltar                                      ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op_funcionario);
    return op_funcionario;
}

void cadastrar_funcionarios(void){
    Funcionarios* func;
    func = (Funcionarios*) malloc(sizeof(Funcionarios));
    limpar_buffer();

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║              Cadastrar Funcionários             ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    receber_dados_funcionario(func);

    arquivo_funcionario = fopen("database/funcionarios.dat", "ab"); //Cria o arquivo
    if (arquivo_funcionario == NULL){
        printf("\nO arquivo não foi criado.");
        getchar();
    }
    else{
        //escreve o novo funcionário no arquivo
        fwrite(func, sizeof(Funcionarios), 1, arquivo_funcionario);
        fclose(arquivo_funcionario);
        free(func);
        printf("\nFuncionário cadastrado com sucesso!");
        printf("\nPressione ENTER para continuar.");
    }
    getchar();
}

void exibir_funcionarios(void){
    int id_procurar = 0;
    Funcionarios* func;
    func = (Funcionarios*)malloc(sizeof(Funcionarios));
    
    system("clear || cls");
    limpar_buffer();
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Pesquisar Funcionários            ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o id do Funcionário que deseja buscar: ");
    scanf(" %d", &id_procurar);

    arquivo_funcionario = fopen("database/funcionarios.dat", "rb");

    if (arquivo_funcionario == NULL) {
        arquivo_funcionario = fopen("database/funcionarios.dat", "wb");
        fclose(arquivo_funcionario);
        arquivo_funcionario = fopen("database/funcionarios.dat", "rb");
    }

    while (fread(func, sizeof(Funcionarios), 1, arquivo_funcionario)){
        if (func->id == id_procurar && func->status == True)
        {
            printf("\nID do Funcionário: %d", func->id);
            printf("\nNome do Funcionário: %s", func->nome);
            printf("\nCPF do Funcionário: %s", func->cpf);
            printf("\nEmail do Funcionário: %s", func->email);
            printf("\nTelefone do Funcionário: %s", func->telefone);

            fclose(arquivo_funcionario);
            free(func);
            limpar_buffer();
            getchar();
            return;
            
        }
    }

    fclose(arquivo_funcionario);
    
    limpar_buffer();
    printf("\nNenhum funcionário com esse id foi encontrado.");
    getchar();
    
}

void alterar_funcionarios(void){
    int id_procurar = 0;
    char opc_alterar;
    char opc_confirmar;
    int func_alterado = False;
    Funcionarios* func;
    func = (Funcionarios*) malloc(sizeof(Funcionarios));

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                Alterar Funcionários             ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do Funcionário que deseja alterar: ");
    scanf(" %d", &id_procurar);
    limpar_buffer();

    arquivo_funcionario = fopen("database/funcionarios.dat", "r+b");

    if (arquivo_funcionario == NULL) {
        arquivo_funcionario = fopen("database/funcionarios.dat", "wb");
        fclose(arquivo_funcionario);
        arquivo_funcionario = fopen("database/funcionarios.dat", "r+b");
    }

    while (fread(func, sizeof(Funcionarios), 1, arquivo_funcionario) && func_alterado == False){
        if (func->id == id_procurar && func->status == True){
            do {
                system("clear || cls");
                printf("\nO que deseja alterar desse Funcionário (Digite 1,2,3 OU 4)?");
                printf("\n1 - nome");
                printf("\n2 - cpf");
                printf("\n3 - email");
                printf("\n4 - telefone\n");
                scanf("%c", &opc_alterar);
                limpar_buffer();
            } while (opc_alterar != '1' && opc_alterar != '2' && opc_alterar != '3' && opc_alterar != '4');

            alterar_campo_funcionario(func, opc_alterar);

            printf("\nDeseja alterar algum outro campo? (s/n)\n");
            scanf("%c", &opc_confirmar);
            limpar_buffer();
            fseek(arquivo_funcionario, (-1)*sizeof(Funcionarios), SEEK_CUR);
            fwrite(func, sizeof(Funcionarios), 1, arquivo_funcionario);

            if (opc_confirmar == 's' || opc_confirmar == 'S'){
                fseek(arquivo_funcionario, (-1)*sizeof(Funcionarios), SEEK_CUR);     
            } else {
                func_alterado = True;
            }
        }
    }
    if (func_alterado == False) {
        printf("\nFuncionário com o ID %d não foi encontrado...", id_procurar);
        getchar();
    }
    fclose(arquivo_funcionario);
    free(func);
}

void excluir_funcionarios(void){
    int id_procurar = 0;
    int excluido = False;
    char opc_confirmar;
    Funcionarios* func;
    func = (Funcionarios*) malloc(sizeof(Funcionarios));

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║              Excluir Funcionários               ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do Funcionário que deseja excluir: ");
    scanf(" %d", &id_procurar);
    limpar_buffer();

    arquivo_funcionario = fopen("database/funcionarios.dat", "r+b");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_funcionario == NULL) {
        arquivo_funcionario = fopen("database/funcionarios.dat", "wb");
        fclose(arquivo_funcionario);
        arquivo_funcionario = fopen("database/funcionarios.dat", "r+b");
    }

    while (fread(func, sizeof(Funcionarios), 1, arquivo_funcionario) && (excluido == False)){
        if (func->id == id_procurar && func->status == True){
            system("clear || cls");
            printf("\n\n------------------------ Funcionário ------------------------");
            printf("\nID do Funcionário: %d", func->id);
            printf("\nNome do Funcionário: %s", func->nome);
            printf("\nCPF do Funcionário: %s", func->cpf);
            printf("\nEmail do Funcionário: %s", func->email);
            printf("\nTelefone do Funcionário: %s", func->telefone);
            printf("\n\nFuncionário de ID %d foi encontrado.\nTem certeza que deseja exclui-lo? (s/n)", id_procurar);
            scanf("%c", &opc_confirmar);
            limpar_buffer();

            if (opc_confirmar == 's' || opc_confirmar == 'S') {
                func->status = 0;
                excluido = True;

                fseek(arquivo_funcionario, (-1)*sizeof(Funcionarios), SEEK_CUR);
                fwrite(func, sizeof(Funcionarios), 1, arquivo_funcionario);
                printf("\nFuncionário com o ID %d excluido com sucesso!", id_procurar);  
            } else {
                printf("\nExclusão cancelada.");
                excluido = True;
            }
        }               
    }
    if (excluido == False) {
        printf("\nNão existe nenhum Funcionário com o ID %d cadastrado...", id_procurar);
    }
    fclose(arquivo_funcionario);
    free(func);
    getchar();
}

void restaurar_funcionarios(void){
    int id_procurar = 0;
    int restaurado = False;
    char opc_confirmar;
    Funcionarios* func;
    func = (Funcionarios*) malloc(sizeof(Funcionarios));

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║              Restaurar Funcionários             ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do Funcionário que deseja reativar: ");
    scanf(" %d", &id_procurar);
    limpar_buffer();

    arquivo_funcionario = fopen("database/funcionarios.dat", "r+b");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_funcionario == NULL) {
        arquivo_funcionario = fopen("database/funcionarios.dat", "wb");
        fclose(arquivo_funcionario);
        arquivo_funcionario = fopen("database/funcionarios.dat", "r+b");
    }

    while (fread(func, sizeof(Funcionarios), 1, arquivo_funcionario) && (restaurado == False)){
        if (func->id == id_procurar && func->status == False){
            system("clear || cls");
            printf("\n\n------------------------ Funcionário ------------------------");
            printf("\nID do Funcionário: %d", func->id);
            printf("\nNome do Funcionário: %s", func->nome);
            printf("\nCPF do Funcionário: %s", func->cpf);
            printf("\nEmail do Funcionário: %s", func->email);
            printf("\nTelefone do Funcionário: %s", func->telefone);
            printf("\n\nFuncionário de ID %d foi encontrado.\nTem certeza que deseja reativa-lo? (s/n)", id_procurar);
            scanf("%c", &opc_confirmar);
            limpar_buffer();

            if (opc_confirmar == 's' || opc_confirmar == 'S') {
                func->status = 1;
                restaurado = True;

                fseek(arquivo_funcionario, (-1)*sizeof(Funcionarios), SEEK_CUR);
                fwrite(func, sizeof(Funcionarios), 1, arquivo_funcionario);
                printf("\nFuncionário com o ID %d restaurado com sucesso!", id_procurar);  
            } else {
                printf("\nRestauração cancelada.");
                restaurado = True;
            }
        }               
    }
    if (restaurado == False) {
        printf("\nNão existe nenhum Funcionário desativado com o ID %d...", id_procurar);
    }
    fclose(arquivo_funcionario);
    free(func);
    getchar();
}

void perma_excluir_funcionario(void) {
    int id_procurar = 0;
    int excluido = False;
    char opc_confirmar;
    char opc_escolha;
    Funcionarios* func;
    func = (Funcionarios*) malloc(sizeof(Funcionarios));
    FILE * arquivo_novo;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║      Excluir Funcionários Permanentemente       ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Deseja excluir um funcionário específico ou todos os funcionários inativos?");
    printf("\n1 - Um funcionário específico\n2 - Todos os funcionários inativos\n");
    scanf(" %c", &opc_escolha);
    limpar_buffer();

    arquivo_funcionario = fopen("database/funcionarios.dat", "rb");
    arquivo_novo = fopen("database/funcionarios_novo.dat", "wb");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_funcionario == NULL) {
        arquivo_funcionario = fopen("database/funcionarios.dat", "wb");
        fclose(arquivo_funcionario);
        arquivo_funcionario = fopen("database/funcionarios.dat", "rb");
    }

    if (opc_escolha == '1') {
        printf("Digite o ID do funcionário que deseja excluir permanentemente: ");
        scanf(" %d", &id_procurar);
        limpar_buffer();

        while (fread(func, sizeof(Funcionarios), 1, arquivo_funcionario)){
            if (func->id == id_procurar && func->status == False){
                system("clear || cls");
                printf("\n\n------------------------ Funcionário ------------------------");
                printf("\nID do Funcionário: %d", func->id);
                printf("\nNome do Funcionário: %s", func->nome);
                printf("\nCPF do Funcionário: %s", func->cpf);
                printf("\nEmail do Funcionário: %s", func->email);
                printf("\nTelefone do Funcionário: %s", func->telefone);
                printf("\n\nFuncionário de ID %d foi encontrado.\nTem certeza que deseja exclui-lo permanentemente? (s/n)", id_procurar);
                scanf("%c", &opc_confirmar);
                limpar_buffer();

                if (opc_confirmar == 's' || opc_confirmar == 'S') {
                    printf("\nFuncionário com o ID %d excluido com sucesso!", id_procurar);
                    getchar();
                    excluido = True;
                } else {
                    fwrite(func, sizeof(Funcionarios), 1, arquivo_novo);
                    printf("\nExclusão cancelada.");
                    getchar();
                    excluido = True;
                }
            } else {
                fwrite(func, sizeof(Funcionarios), 1, arquivo_novo);
            }
                    
        }
        if (excluido == False) {
            printf("\nNão existe nenhum Funcionário inativo com o ID %d...", id_procurar);
            getchar();
        }
    }
    else if (opc_escolha == '2') {
        while (fread(func, sizeof(Funcionarios), 1, arquivo_funcionario)) {
            if (func->status == True){
                fwrite(func, sizeof(Funcionarios), 1, arquivo_novo);
            }     
        }
        printf("Todos os Funcionários inativos foram deletados permanentemente.");
        getchar();
    }
    else {
        printf("Opção inválida.");
        getchar();
    }
    fclose(arquivo_funcionario);
    fclose(arquivo_novo);
    free(func);
    remove("database/funcionarios.dat");
    rename("database/funcionarios_novo.dat", "database/funcionarios.dat");
}

int verificar_id_funcionario(char *valor) {

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
    
    Funcionarios* func;
    func = (Funcionarios*) malloc(sizeof(Funcionarios));
    arquivo_funcionario = fopen("database/funcionarios.dat", "rb");

    if (arquivo_funcionario == NULL) {
        arquivo_funcionario = fopen("database/funcionarios.dat", "wb");
        fclose(arquivo_funcionario);
        arquivo_funcionario = fopen("database/funcionarios.dat", "rb");
    }

    while (fread(func, sizeof(Funcionarios), 1, arquivo_funcionario)){
        if (func->status == True){
            if (func->id == id) {
                fclose(arquivo_funcionario);
                free(func);
                return 1;
            }
        }
    }
    fclose(arquivo_funcionario);
    free(func);
    printf("\nUm funcionario com o ID %d não existe", id);
    getchar();
    return 0;
}

void receber_dados_funcionario(Funcionarios *func) {
    char cpf[30];
    char email[51];
    char nome[51];
    char telefone[12];

    do {
        printf("Digite o nome do funcionario: ");
        scanf("%[^\n]", nome);
        limpar_buffer();
    } while(validar_nome(nome) == 0);
    memcpy(func->nome, nome, sizeof(func->nome));

    do {
        printf("Digite o CPF do funcionario: ");
        scanf("%[^\n]", cpf);
        limpar_buffer();
    }
    while (validar_cpf(cpf) == 0);
    memcpy(func->cpf, cpf, sizeof(func->cpf));

    do {
        printf("Digite o email do funcionario: ");
        scanf("%[^\n]", email);
        limpar_buffer();
    }
    while (validar_email(email) == 0);
    memcpy(func->email, email, sizeof(func->email));

    do {
        printf("Digite o telefone do funcionario: ");
        scanf("%[^\n]", telefone);
        limpar_buffer();
    } while (validar_telefone(telefone) == 0);
    memcpy(func->telefone, telefone, sizeof(func->telefone));
    
    arquivo_funcionario = fopen("database/funcionarios.dat", "rb");
    
    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_funcionario == NULL) {
        arquivo_funcionario = fopen("database/funcionarios.dat", "wb");
        fclose(arquivo_funcionario);
        arquivo_funcionario = fopen("database/funcionarios.dat", "rb");
    }

    func->id = gerar_id(arquivo_funcionario, 3);
    fclose(arquivo_funcionario);
    func->status = True;
}

void alterar_campo_funcionario(Funcionarios *func, char opc_alterar) {
    char cpf[30];
    char email[51];
    char nome[51];
    char telefone[12];

    switch (opc_alterar){
        case '1':
            do {
                printf("Digite o nome do funcionario: ");
                scanf("%[^\n]", nome);
                limpar_buffer();
            } while(validar_nome(nome) == 0);
            memcpy(func->nome, nome, sizeof(func->nome));
            break;
        case  '2':
            do {
                printf("Digite o CPF do funcionario: ");
                scanf("%[^\n]", cpf);
                limpar_buffer();
            }
            while (validar_cpf(cpf) == 0);
            memcpy(func->cpf, cpf, sizeof(func->cpf));
            break;
        case  '3':
            do {
                printf("Digite o email do funcionario: ");
                scanf("%[^\n]", email);
                limpar_buffer();
            }
            while (validar_email(email) == 0);
            memcpy(func->email, email, sizeof(func->email));
            break;
        case  '4':
            do {
                printf("Digite o telefone do funcionario: ");
                scanf("%[^\n]", telefone);
                limpar_buffer();
            } while (validar_telefone(telefone) == 0);
            memcpy(func->telefone, telefone, sizeof(func->telefone));
            break;
        default:
            break;
    }
    system("clear || cls");
    printf("\nFuncionário com o ID %d alterado com sucesso!", func->id);
    printf("\n\n------------------------ Funcionário Alterado ------------------------");
    printf("\nID do Funcionário: %d", func->id);
    printf("\nNome do Funcionário: %s", func->nome);
    printf("\nCPF do Funcionário: %s", func->cpf);
    printf("\nEmail do Funcionário: %s", func->email);
    printf("\nTelefone do Funcionário: %s", func->telefone);
    getchar();
}

char* procurar_nome_funcionario(int id) {
    Funcionarios* func;
    func = (Funcionarios*) malloc(sizeof(Funcionarios));

    arquivo_funcionario = fopen("database/funcionarios.dat", "rb");

    while(fread(func, sizeof(Funcionarios), 1, arquivo_funcionario)) {
        if (func->id == id)  {
            return func->nome;
        }
    }
    return NULL;
}