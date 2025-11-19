typedef struct pedido Pedido;

struct pedido {
    int id_pedido;
    int id_cliente;
    int id_produto;
    int id_funcionario;
    float preco;
    char data[26];
    int status;
};

char tela_de_pedidos(void);
void cadastrar_pedidos(void);
void exibir_pedidos(void);
void excluir_pedido(void);
void restaurar_pedido(void);
void perma_excluir_pedido(void);
void modulo_pedidos(void);
int verificar_criacao_pedidos(void);
void receber_dados_pedido(Pedido*);
void adicionar_outro_produto(Pedido*);
void alterar_campo_pedido(Pedido*, char);