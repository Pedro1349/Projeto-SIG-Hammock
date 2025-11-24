typedef struct cliente Cliente;

struct cliente {
    int id;
    char nome[51];
    char cpf[30];
    char email[51];
    char telefone[12];
    int status;
};

char tela_de_clientes(void);
void cadastrar_clientes(void);
void exibir_clientes(void);
void alterar_cliente(void);
void excluir_cliente(void);
void restaurar_cliente(void);
void perma_excluir_cliente(void);
void modulo_clientes(void);
int verificar_id_cliente(char*);
void receber_dados_cliente(Cliente*);
void alterar_campo_cliente(Cliente*, char);
char* procurar_nome_cliente(int);
