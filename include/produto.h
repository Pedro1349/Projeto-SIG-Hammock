typedef struct  produto Produto;

struct produto{
    int id;
    char modelo_rede[51];
    float valor_rede;
    char tipo_rede[51]; 
    char cor_rede [51];
    int status;
};




char tela_de_produto(void);
void cadastrar_produto(void);
void exibir_produto(void);
void alterar_produto(void);
void excluir_produto(void);
void restaurar_produto(void);
void perma_excluir_produto(void);
void modulo_produto(void);
int verificar_id_produto(char*);
float verificar_valor_produto(int);
void receber_dados_produto(Produto*);
void alterar_campo_produto(Produto*, char);
Produto* pesquisar_produto_ID(int);
char* procurar_nome_produto(int);