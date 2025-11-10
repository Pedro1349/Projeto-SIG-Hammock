#include <stdio.h>
#include <stdlib.h>

char tela_de_equipe(void);

void modulo_equipe(void) {
    char opcao;
    do {
        opcao = tela_de_equipe();
        switch(opcao) {
            case '0':   
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                getchar();
        }
    } while (opcao != '0');
}

char tela_de_equipe(void) {
    char op_equipe;
    system("clear || cls");
    printf("╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           SOBRE O PROJETO                             ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════╣\n");
    printf("║   Este projeto foi desenvolvido pelos alunos:                         ║\n");
    printf("║      Daniel Mariz                                                     ║\n");
    printf("║       GitHub: danielmarrizz7                                          ║\n");
    printf("║      Gabriel Victor                                                   ║\n");
    printf("║       GitHub: GabrielVictor7                                          ║\n");
    printf("║      Pedro Lucas                                                      ║\n");
    printf("║       GitHub: Pedro1349                                               ║\n");
    printf("║      Leonardo Breno                                                   ║\n");
    printf("║       GitHub: leonardobreno                                           ║\n");
    printf("║                                                                       ║\n");
    printf("║   Com a supervisão do Gerente                                         ║\n");
    printf("║      Flavius Gorgonio                                                 ║\n");
    printf("║       Github: FlaviusGorgonio                                         ║\n");
    printf("║                                                                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Digite 0 para voltar à tela inicial: ");
    scanf(" %c", &op_equipe);
    return op_equipe;
}