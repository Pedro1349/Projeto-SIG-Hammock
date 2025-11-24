typedef struct funcionarios Funcionarios;

struct funcionarios {
    int id;
    char nome[51];
    char cpf[30];
    char email[51];
    char telefone[12];
    int status;
};



char tela_de_funcionarios(void);
void cadastrar_funcionarios(void);
void exibir_funcionarios(void);
void alterar_funcionarios(void);
void excluir_funcionarios(void);
void restaurar_funcionarios(void);
void perma_excluir_funcionario(void);
void modulo_funcionarios(void);
int verificar_id_funcionario(char*);
void receber_dados_funcionario(Funcionarios*);
void alterar_campo_funcionario(Funcionarios*, char);
char* procurar_nome_funcionario(int id);