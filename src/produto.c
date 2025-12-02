#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "../include/utilidades.h"
#include "../include/produto.h"
#include <locale.h>


FILE * arquivo_produto;

void modulo_produto(void){
    char opcao;
    
    do {
        opcao = tela_de_produto();
        switch(opcao){
            case '1':   cadastrar_produto();
                        break;
            case '2':   exibir_produto();
                        break;
            case '3':   alterar_produto();
                        break;
            case '4':   excluir_produto();
                        break;
            case '5':   perma_excluir_produto();
                        break;
            case '6':   restaurar_produto();
                        break;

        }
    } while (opcao != '0');
}


char tela_de_produto(void){

    char op_produtos;
    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║              Módulo De Produtos                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║                                                 ║\n");
    printf("║ 1 - Cadastrar Produto                           ║\n");
    printf("║ 2 - Exibir Produto                              ║\n");
    printf("║ 3 - Editar Produto                              ║\n");
    printf("║ 4 - Excluir Produto                             ║\n");
    printf("║ 5 - Excluir Permanentemente Produto             ║\n");
    printf("║ 6 - Restaurar Produto                           ║\n");
    printf("║                                                 ║\n");
    printf("╠═════════════════════════════════════════════════╣\n");
    printf("║ 0 - Para voltar à tela inicial                  ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Selecione uma opção: ");
    scanf(" %c", &op_produtos);
    return op_produtos;
}

void cadastrar_produto(){
    Produto* prod;
    prod = (Produto*)malloc(sizeof(Produto));

    limpar_buffer();
    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                Cadastrar Produto                ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    receber_dados_produto(prod);

    arquivo_produto = fopen("database/produtos.dat", "ab");
    if (arquivo_produto == NULL){
        printf("\nO arquivo não foi criado.");
        getchar();
    }
    else
    {
        //escreve o novo produto no arquivo
        fwrite(prod, sizeof(Produto), 1, arquivo_produto);
        fclose(arquivo_produto);
        free(prod);
        printf("\nProduto cadastrado com sucesso!");
        printf("\nPressione ENTER para continuar.");
    }
    getchar();
}

void exibir_produto(void){
    int id_procurar = 0;
    Produto* prod;
    prod = (Produto*)malloc(sizeof(Produto));
    
    system("clear || cls");
    limpar_buffer();
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║               Pequisar Produto                  ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do Produto que deseja buscar: ");
    scanf(" %d", &id_procurar);

    arquivo_produto = fopen("database/produtos.dat", "rb");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_produto == NULL) {
        arquivo_produto = fopen("database/produtos.dat", "wb");
        fclose(arquivo_produto);
        arquivo_produto = fopen("database/produtos.dat", "rb");
    }

    while (fread(prod, sizeof(Produto), 1, arquivo_produto)){
        if (prod->id == id_procurar && prod->status == True)
        {
            printf("\nID do Produto: %d", prod->id);
            printf("\nModelo do Produto: %s", prod->modelo_rede);
            printf("\nValor do Produto: %f", prod->valor_rede);
            printf("\nTipo do Produto: %s", prod->tipo_rede);
            printf("\nCor do Produto: %s", prod->cor_rede);

            fclose(arquivo_produto);
            free(prod);
            limpar_buffer();
            getchar();
            return;
            
        }
    }
    fclose(arquivo_produto);
    
    limpar_buffer();
    printf("\nNenhuma rede com esse id foi encontrado.");
    getchar();
    
}

void alterar_produto(void){
    int id_procurar = 0;
    char opc_alterar;
    char opc_confirmar;
    int prod_alterado = False;
    Produto* prod;
    prod = (Produto*) malloc(sizeof(Produto));


    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                Alterar Produto                  ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do produto que deseja alterar: ");
    scanf(" %d", &id_procurar);
    limpar_buffer();

    arquivo_produto = fopen("database/produtos.dat", "r+b");

    if (arquivo_produto == NULL) {
        arquivo_produto = fopen("database/produtos.dat", "wb");
        fclose(arquivo_produto);
        arquivo_produto = fopen("database/produtos.dat", "r+b");
    }
    while (fread(prod, sizeof(Produto), 1, arquivo_produto) && prod_alterado == False){

        if (prod->id == id_procurar && prod->status == True){
            do {
                system("clear || cls");
                printf("\nO que deseja alterar desse Produto (Digite 1,2,3 OU 4)?");
                printf("\n1 - modelo");
                printf("\n2 - valor");
                printf("\n3 - tipo");
                printf("\n4 - cor\n");
                scanf("%c", &opc_alterar);
                limpar_buffer();
            } while (opc_alterar != '1' && opc_alterar != '2' && opc_alterar != '3' && opc_alterar != '4');

            alterar_campo_produto(prod, opc_alterar);

            printf("\nDeseja alterar algum outro campo? (s/n)\n");
            scanf("%c", &opc_confirmar);
            limpar_buffer();
            fseek(arquivo_produto, (-1)*sizeof(Produto), SEEK_CUR);
            fwrite(prod, sizeof(Produto), 1, arquivo_produto);

            if (opc_confirmar == 's' || opc_confirmar == 'S'){
                fseek(arquivo_produto, (-1)*sizeof(Produto), SEEK_CUR);     
            } else {
                prod_alterado = True;
            }
        }
    }
    if (prod_alterado == False) {
        printf("\nProduto com o ID %d não foi encontrado...", id_procurar);
        getchar();
    }
    fclose(arquivo_produto);
    free(prod);
}

void excluir_produto(void){
    int id_procurar = 0;
    int excluido = False;
    char opc_confirmar;
    Produto* prod;
    prod = (Produto*) malloc(sizeof(Produto));

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                 Excluir Produtos                ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do Produto que deseja excluir: ");
    scanf(" %d", &id_procurar);
    limpar_buffer();

    arquivo_produto = fopen("database/produtos.dat", "r+b");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_produto == NULL) {
        arquivo_produto = fopen("database/produtos.dat", "wb");
        fclose(arquivo_produto);
        arquivo_produto = fopen("database/produtos.dat", "r+b");
    }

    while (fread(prod, sizeof(Produto), 1, arquivo_produto) && (excluido == False)){
        if (prod->id == id_procurar && prod->status == True){
            system("clear || cls");
            printf("\n\n------------------------ Produto ------------------------");
            printf("\nID do Produto: %d", prod->id);
            printf("\nModelo do Produto: %s", prod->modelo_rede);
            printf("\nValor do Produto: %f", prod->valor_rede);
            printf("\nTipo do Produto: %s", prod->tipo_rede);
            printf("\nCor do Produto: %s", prod->cor_rede);
            printf("\n\nProduto de ID %d foi encontrado.\nTem certeza que deseja exclui-lo? (s/n)", id_procurar);
            scanf("%c", &opc_confirmar);
            limpar_buffer();

            if (opc_confirmar == 's' || opc_confirmar == 'S') {
                prod->status = 0;
                excluido = True;
                fseek(arquivo_produto, (-1)*sizeof(Produto), SEEK_CUR);
                fwrite(prod, sizeof(Produto), 1, arquivo_produto);
                printf("\nProduto com o ID %d excluido com sucesso!", id_procurar);
            } else {
                printf("\nExclusão cancelada.");
                excluido = True;
            }
        }
                 
        
    }
    if (excluido == False) {
        printf("\nNão existe nenhum Produto com o ID %d cadastrado...", id_procurar);
    }
    fclose(arquivo_produto);
    free(prod);
    getchar();
}

void restaurar_produto(void){
    int id_procurar = 0;
    int restaurado = False;
    char opc_confirmar;
    Produto* prod;
    prod = (Produto*) malloc(sizeof(Produto));

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║                 Restaurar Produtos              ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Digite o ID do Produto que deseja restaurar: ");
    scanf(" %d", &id_procurar);
    limpar_buffer();

    arquivo_produto = fopen("database/produtos.dat", "r+b");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_produto == NULL) {
        arquivo_produto = fopen("database/produtos.dat", "wb");
        fclose(arquivo_produto);
        arquivo_produto = fopen("database/produtos.dat", "r+b");
    }

    while (fread(prod, sizeof(Produto), 1, arquivo_produto) && (restaurado == False)){
        if (prod->id == id_procurar && prod->status == False){
            system("clear || cls");
            printf("\n\n------------------------ Produto ------------------------");
            printf("\nID do Produto: %d", prod->id);
            printf("\nModelo do Produto: %s", prod->modelo_rede);
            printf("\nValor do Produto: %f", prod->valor_rede);
            printf("\nTipo do Produto: %s", prod->tipo_rede);
            printf("\nCor do Produto: %s", prod->cor_rede);
            printf("\n\nProduto de ID %d foi encontrado.\nTem certeza que deseja reativa-lo? (s/n)", id_procurar);
            scanf("%c", &opc_confirmar);
            limpar_buffer();

            if (opc_confirmar == 's' || opc_confirmar == 'S') {
                prod->status = 1;
                restaurado = True;
                fseek(arquivo_produto, (-1)*sizeof(Produto), SEEK_CUR);
                fwrite(prod, sizeof(Produto), 1, arquivo_produto);
                printf("\nProduto com o ID %d restaurado com sucesso!", id_procurar);
            } else {
                printf("\nRestauração cancelada.");
                restaurado = True;
            }
        }
                 
        
    }
    if (restaurado == False) {
        printf("\nNão existe nenhum produto desativado com o ID %d...", id_procurar);
    }
    fclose(arquivo_produto);
    free(prod);
    getchar();
}

void perma_excluir_produto(void) {
    int id_procurar = 0;
    int excluido = False;
    char opc_confirmar;
    char opc_escolha;
    Produto* prod;
    prod = (Produto*) malloc(sizeof(Produto));
    FILE * arquivo_novo;

    system("clear || cls");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║        Excluir Produtos Permanentemente         ║\n");
    printf("╚═════════════════════════════════════════════════╝\n");
    printf("Deseja excluir um produto específico ou todos os produtos inativos?");
    printf("\n1 - Um produto específico\n2 - Todos os produtos inativos\n");
    scanf(" %c", &opc_escolha);
    limpar_buffer();

    arquivo_produto = fopen("database/produtos.dat", "rb");
    arquivo_novo = fopen("database/produtos_novo.dat", "wb");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_produto == NULL) {
        arquivo_produto = fopen("database/produtos.dat", "wb");
        fclose(arquivo_produto);
        arquivo_produto = fopen("database/produtos.dat", "rb");
    }

    if (opc_escolha == '1') {
        printf("Digite o ID do produto que deseja excluir permanentemente: ");
        scanf(" %d", &id_procurar);
        limpar_buffer();

        while (fread(prod, sizeof(Produto), 1, arquivo_produto)){
            if (prod->id == id_procurar && prod->status == False){
                system("clear || cls");
                printf("\n\n------------------------ Produto ------------------------");
                printf("\nID do Produto: %d", prod->id);
                printf("\nModelo do Produto: %s", prod->modelo_rede);
                printf("\nValor do Produto: %f", prod->valor_rede);
                printf("\nTipo do Produto: %s", prod->tipo_rede);
                printf("\nCor do Produto: %s", prod->cor_rede);
                printf("\n\nProduto de ID %d foi encontrado.\nTem certeza que deseja exclui-lo permanentemente? (s/n)", id_procurar);
                scanf("%c", &opc_confirmar);
                limpar_buffer();

                if (opc_confirmar == 's' || opc_confirmar == 'S') {
                    printf("\nProduto com o ID %d excluido com sucesso!", id_procurar);
                    getchar();
                    excluido = True;
                } else {
                    fwrite(prod, sizeof(Produto), 1, arquivo_novo);
                    printf("\nExclusão cancelada.");
                    getchar();
                    excluido = True;
                }
            } else {
                fwrite(prod, sizeof(Produto), 1, arquivo_novo);
            }
                    
        }
        if (excluido == False) {
            printf("\nNão existe nenhum produto inativo com o ID %d...", id_procurar);
            getchar();
        }
    }
    else if (opc_escolha == '2') {
        while (fread(prod, sizeof(Produto), 1, arquivo_produto)) {
            if (prod->status == True){
                fwrite(prod, sizeof(Produto), 1, arquivo_novo);
            }     
        }
        printf("Todos os produtos inativos foram deletados permanentemente.");
        getchar();
    }
    else {
        printf("Opção inválida.");
        getchar();
    }
    fclose(arquivo_produto);
    fclose(arquivo_novo);
    free(prod);
    remove("database/produtos.dat");
    rename("database/produtos_novo.dat", "database/produtos.dat");
}

int verificar_id_produto(char *valor) {
    
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
    
    Produto* prod;
    prod = (Produto*) malloc(sizeof(Produto));
    arquivo_produto = fopen("database/produtos.dat", "rb");

    if (arquivo_produto == NULL) {
        arquivo_produto = fopen("database/produtos.dat", "wb");
        fclose(arquivo_produto);
        arquivo_produto = fopen("database/produtos.dat", "rb");
    }

    while (fread(prod, sizeof(Produto), 1, arquivo_produto)){
        if (prod->status == True){
            if (prod->id == id) {
                fclose(arquivo_produto);
                free(prod);
                return 1;
            }
        }
    }
    fclose(arquivo_produto);
    free(prod);
    printf("\nUm produto com o ID %d não existe", id);
    getchar();
    return 0;
}

float verificar_valor_produto(int id) {
    Produto* prod;
    prod = (Produto*) malloc(sizeof(Produto));
    arquivo_produto = fopen("database/produtos.dat", "rb");
    float valor = 0;

    if (arquivo_produto == NULL) {
        arquivo_produto = fopen("database/produtos.dat", "wb");
        fclose(arquivo_produto);
        arquivo_produto = fopen("database/produtos.dat", "rb");
    }

    while (fread(prod, sizeof(Produto), 1, arquivo_produto)){
        if (prod->status == True){
            if (prod->id == id) {
                valor = prod->valor_rede;
            }
        }
    }   
    fclose(arquivo_produto);
    free(prod);
    return valor;
}

void receber_dados_produto(Produto *prod) {
    char valor[20];
    char cor[51];
    char modelo[51];
    char tipo[51];

    do {
        printf("Digite o modelo da rede: ");
        scanf("%[^\n]", modelo);
        limpar_buffer();
    } while(validar_nome(modelo) == 0);
    memcpy(prod->modelo_rede, modelo, sizeof(prod->modelo_rede));

    do {
        printf("Digite o valor da rede: ");
        scanf("%[^\n]", valor);
        limpar_buffer();
    } while(validar_valor(valor) == 0);
    // atof serve para converter string em float
    prod->valor_rede = atof(valor);

    do {
        printf("Digite o tipo da rede: ");
        scanf("%[^\n]", tipo);
        limpar_buffer();
    } while (validar_nome(tipo) == 0);
    memcpy(prod->tipo_rede, tipo, sizeof(prod->tipo_rede));

    do {
        printf("Digite a cor da rede: ");
        scanf("%[^\n]", cor);
        limpar_buffer();
    } while(validar_nome(cor) == 0);
    memcpy(prod->cor_rede, cor, sizeof(prod->cor_rede));

    arquivo_produto = fopen("database/produtos.dat", "rb");

    //testa se o arquivo existe, se não existe, cria o arquivo
    if (arquivo_produto == NULL) {
        arquivo_produto = fopen("database/produtos.dat", "wb");
        fclose(arquivo_produto);
        arquivo_produto = fopen("database/produtos.dat", "rb");
    }

    prod->id = gerar_id(arquivo_produto, 2);

    fclose(arquivo_produto);
    prod->status = True;
    prod->prox = NULL;
}

void alterar_campo_produto(Produto *prod, char opc_alterar) {
    char valor[20];
    char cor[51];
    char modelo[51];
    char tipo[51];

    switch (opc_alterar){
        case '1':
            do {
                printf("Digite o modelo da rede: ");
                scanf("%[^\n]", modelo);
                limpar_buffer();
            } while(validar_nome(modelo) == 0);
            memcpy(prod->modelo_rede, modelo, sizeof(prod->modelo_rede));
            break;
        case  '2':
            do {
                printf("Digite o novo valor da rede: ");
                scanf("%[^\n]", valor);
                limpar_buffer();
            } while(validar_valor(valor) == 0);
            // atof serve para converter string em float
            prod->valor_rede = atof(valor);
            limpar_buffer();
            break;
        case  '3':
            do {
                printf("Digite o tipo da rede: ");
                scanf("%[^\n]", tipo);
                limpar_buffer();
            } while (validar_nome(tipo) == 0);
            memcpy(prod->tipo_rede, tipo, sizeof(prod->tipo_rede));
            break;
        case  '4':
            do {
                printf("Digite a cor da rede: ");
                scanf("%[^\n]", cor);
                limpar_buffer();
            } while(validar_nome(cor) == 0);
            memcpy(prod->cor_rede, cor, sizeof(prod->cor_rede));
            break;
        default:
            break;
    }
    system("clear || cls");
    printf("\nProduto com o ID %d alterado com sucesso!", prod->id);
    printf("\n\n------------------------ Produto Alterado ------------------------");
    printf("\nID do Produto: %d", prod->id);
    printf("\nModelo do Produto: %s", prod->modelo_rede);
    printf("\nValor do Produto: %f", prod->valor_rede);
    printf("\nTipo do Produto: %s", prod->tipo_rede);
    printf("\nCor do Produto: %s", prod->cor_rede);
    getchar();
}

Produto* pesquisar_produto_ID(int id) {
    Produto* prod;
    prod = (Produto*) malloc(sizeof(Produto));
    arquivo_produto = fopen("database/produtos.dat", "rb");

    while(fread(prod, sizeof(Produto), 1, arquivo_produto)) {
        if (id == prod->id) {
            fclose(arquivo_produto);
            return prod;
        }
    }
    fclose(arquivo_produto);

    prod->id = -1;
    return prod;
}

char* procurar_nome_produto(int id) {
    Produto prod;

    FILE* fp = fopen("database/produtos.dat", "rb");

    if (!fp) return NULL;

    while(fread(&prod, sizeof(Produto), 1, fp)) {
        if (prod.id == id)  {
            fclose(fp);
            char* nome = malloc(strlen(prod.modelo_rede) + 1);
            strcpy(nome, prod.modelo_rede);
            return nome;
        }
    }
    fclose(fp);
    return NULL;
}