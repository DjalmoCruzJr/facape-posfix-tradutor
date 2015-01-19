/*----------------------------------------------------*/
/*-----------DEFINICAO DE CONTANTES GLOBAIS-----------*/  
/*----------------------------------------------------*/
#define NONE 		    -1

#define TABULACAO 	    '\t'
#define QUEBRA_LINHA    '\n'
#define ESPACO_BRANCO   ' '
#define PONTO_E_VIRGULA ';'
#define ABRE_PAR        '('
#define FECHA_PAR       ')'

#define ID 			    0
#define NUM 		    1

#define ADD			    '+'
#define SUB 		    '-'
#define MUL 		    '*'
#define DIV			    '/'
#define ATR 		    '='

#define TOKEN           int
#define LEXEMA          char*
#define ATRIBUTO        char

#define MENSAGEM        char*
#define OPCAO           int
#define CAMINHO         char*
#define ISOPERADOR      isalnum
#define VAZIO           ""

#define MAX_LEXEMA      32
#define MAX_TOKENS      100

#define SAIDA           0
#define CONTINUE        1
/*----------------------------------------------------*/
/*-----------------------FIM--------------------------*/
/*----------------------------------------------------*/



/*----------------------------------------------------*/
/*----------DEFINICAO DE TIPOS E ESTRUTURAS-----------*/
/*----------------------------------------------------*/
typedef struct Token {
        TOKEN token;
        LEXEMA lexema[MAX_LEXEMA];
        ATRIBUTO atributo;
}Token;

typedef struct TabelaDeSimbolos {
    Token   simbolos[MAX_TOKENS];
    int     qtdTokens;    
    int 	qtdIds;
    int 	qtdNums;
}TabelaDeSimbolos;
/*----------------------------------------------------*/
/*-----------------------FIM--------------------------*/
/*----------------------------------------------------*/



/*----------------------------------------------------*/
/*----------DEFINICAO DE PROTOTIPOS DE FUNCOES--------*/  
/*----------------------------------------------------*/
void inicializar(void);
void carregarArquivo(CAMINHO c);
void finalizar(void);

Token analiseLexica(void);
void inserir(Token t);
int buscar(Token t);

void traduzir(void);
void cmd();
void expr(void);
void R1(void);
void termo(void);
void R2(void);
void fator(void);
void reconhecer(TOKEN t);

void imprimir(TOKEN t);

void erro(MENSAGEM m);

void aguardar(OPCAO opcao);
/*----------------------------------------------------*/
/*-----------------------FIM--------------------------*/
/*----------------------------------------------------*/
