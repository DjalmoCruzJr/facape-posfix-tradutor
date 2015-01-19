#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "posfix-tradutor.h"

/*----------------------------------------------------*/
/*---------------DEFINICAO DE VARIAVEIS---------------*/
/*----------------------------------------------------*/
FILE    *arquivoDeEntrada;
FILE    *arquivoDeSaida;
CAMINHO caminhoArquivo;

TabelaDeSimbolos tabelaSimbolos;

Token   lookahead;

Token   abrePar;
Token   fechaPar;
Token   pontoVirgula;

int     contadorDeLinha;
int     contadorDeColuna;
/*----------------------------------------------------*/
/*-----------------------FIM--------------------------*/
/*----------------------------------------------------*/



/*----------------------------------------------------*/
/*-------------IMPLEMENTACAO DAS FUNCOES--------------*/
/*----------------------------------------------------*/
void inicializar(void) {	
	carregarArquivo("entrada.txt");

	lookahead.token          = NONE;
	lookahead.atributo       = ESPACO_BRANCO;
	strcpy(lookahead.lexema, VAZIO);
	tabelaSimbolos.qtdTokens = 0;
	tabelaSimbolos.qtdIds    = 0;
	tabelaSimbolos.qtdNums   = 0;
	contadorDeLinha          = 1;
	contadorDeColuna         = 0;
}

void carregarArquivo(CAMINHO c) {
	printf("\nCarregando o arquivo de entrada...");	
	arquivoDeEntrada = fopen("entrada.txt", "r");
	if(arquivoDeEntrada == NULL) {
		printf("\nERRO AO TENTAR ABRIR O ARQUIVO DE ENTRADA!");
        printf("\ncrie o arquivo 'entrada.txt' no diretorio do programa!");
		aguardar(SAIDA);
	}
	printf("\nArquivo carregado com sucesso!");
	
	printf("\n\nCarregando o arquivo de saida...");	
	arquivoDeSaida= fopen("SAIDA.txt", "a+");
	if(arquivoDeSaida == NULL) {
		printf("\nERRO AO TENTAR ARBIR O ARQUIVO DE SAIDA!");
		aguardar(SAIDA);
	}	
	printf("\nArquivo carregado com sucesso!");
	aguardar(CONTINUE);
}

void finalizar(void) {
    fclose(arquivoDeEntrada);     
    fclose(arquivoDeSaida);
    
    printf("\nO arquivo 'SAIDA.txt' contendo os resultados da traducao");
    printf("\nfoi gerado no mesmo diretorio do programa. VERIFIQUE!");
    aguardar(SAIDA);
}
/*----------------------------------------------------*/
Token analiseLexica(void) {
    Token t;
    int   p;    
    char  c;
    for(;;) {
    	c = getc(arquivoDeEntrada);
	    contadorDeColuna++;
	    if(c == EOF)
	         erro("ERRO! O ARQUIVO CHEGOU AO FINAL.");
	    else if(c == ESPACO_BRANCO || c == TABULACAO)
	         continue;
	    else if(c == QUEBRA_LINHA) {
	    	 c = getc(arquivoDeEntrada);
	    	 contadorDeLinha++;
	    }else if(isdigit(c)) {
	         t.token    = NUM;
	         t.atributo = c;
	         strcpy(t.lexema, VAZIO);
	    } else if(isalpha(c)) { /* eh um ID (identificador de variavel) */
	         t.token    = ID;
	         t.atributo = tabelaSimbolos.qtdIds+1;             
	         p = 0;
	         while(isalnum(c)) {
	            t.lexema[p] = c;
	            c  = getc(arquivoDeEntrada);
	            p++;
	            if(p >= MAX_LEXEMA)
	                 erro("ERRO! TAMANHO DO LEXEMA NAO SUPORTADO!");
	         }   
			 ungetc(c, arquivoDeEntrada);
	    } else { /* eh um operador */
	    	t.token    = c;
	    	t.atributo = ESPACO_BRANCO; 
	    	strcpy(t.lexema, VAZIO);
	    }		            
	    inserir(t);         
	    return t;
	}
}

void inserir(Token t) {
    tabelaSimbolos.qtdTokens++;
    if(t.token == ID)  tabelaSimbolos.qtdIds++;
    if(t.token == NUM) tabelaSimbolos.qtdNums++;
    tabelaSimbolos.simbolos[tabelaSimbolos.qtdTokens].token = t.token;
    tabelaSimbolos.simbolos[tabelaSimbolos.qtdTokens].atributo = t.atributo;
    strcpy(tabelaSimbolos.simbolos[tabelaSimbolos.qtdTokens].lexema, t.lexema);
}

int buscar(Token t) {
    int i;
    for(i = 0; i <= tabelaSimbolos.qtdTokens; i++) {
        if((tabelaSimbolos.simbolos[i].token == t.token) &&
           (tabelaSimbolos.simbolos[i].atributo == t.atributo) &&
           (strcmp(tabelaSimbolos.simbolos[i].lexema, t.lexema) == 0)
          ) return i;           
    }
    return NONE;  
}
/*----------------------------------------------------*/
void traduzir(void) {
     inicializar();     
     lookahead = analiseLexica();     
     cmd();
     finalizar();
}

void cmd() {
    imprimir(ID);
	reconhecer(ID);    
    reconhecer(ATR);
    expr();
    imprimir(ATR);
}

void expr(void) {
	termo();
	R1();
}

void R1() {
	if(lookahead.token == ADD) {
		reconhecer(ADD);
		termo();
		imprimir(ADD);
		R1();
	}
}

void termo(void) {
	fator();
	R2();
}

void R2() {
	if(lookahead.token == MUL) {
		reconhecer(MUL);
		fator();
		imprimir(MUL);
		R2();
	}
}

void fator(void) {
	if(lookahead.token == ID) {
		   imprimir(ID);
		   reconhecer(ID);		   
	} else if(lookahead.token == NUM) {
		   imprimir(NUM);
		   reconhecer(NUM);		   
	} else if(lookahead.token ==  ABRE_PAR) {
		   reconhecer(ABRE_PAR);
		   expr();
		   reconhecer(FECHA_PAR);
	} else if(lookahead.token == SUB) {
		   reconhecer(SUB);
		   fator();
		   imprimir(SUB);
	} else erro("OCORREU UM ERRO DE SINTAXE!\n");
}

void reconhecer(TOKEN t) {
     if(lookahead.token == t) 
         lookahead = analiseLexica();
     else 
         erro("OCORREU UM ERRO DE SINTAXE!\n");
}
/*----------------------------------------------------*/
void imprimir(TOKEN t) {
     int p;
     switch(t) {
          case ADD:
          case SUB:
          case MUL:
          case DIV:
          case ATR:
               fprintf(arquivoDeSaida, "%c", t);
               printf("%c", t);
               break;  
          case NUM:                
               fprintf(arquivoDeSaida, "%c", lookahead.atributo);
               printf("%c", lookahead.atributo);
               break;  
          case ID:
               fprintf(arquivoDeSaida, "%s", lookahead.lexema);
               printf("%s", lookahead.lexema);
               break;
          default: 
               erro("OCORREU UM ERRO DE SINTAXE!");
     }
}
/*----------------------------------------------------*/
void erro(MENSAGEM m) {
    fprintf(arquivoDeSaida, "\n[LINHA %d, COLUNA %d]: %s\n", contadorDeLinha, contadorDeColuna, m);
    printf("\n[LINHA %d, COLUNA %d]: %s\n", contadorDeLinha, contadorDeColuna, m);
    aguardar(SAIDA);
}
/*----------------------------------------------------*/
void aguardar(int opcao){
     if(opcao) {
         printf("\n\nPressione qualquer tecla para continuar...\n\n");     
         getch();
     }else {
         printf("\n\nPressione qualquer tecla para finalizar...\n\n");          
         getch();
         exit(1);
     }
     
}
/*----------------------------------------------------*/
/*-----------------------FIM--------------------------*/
/*----------------------------------------------------*/
