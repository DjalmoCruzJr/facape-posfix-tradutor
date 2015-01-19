/* importa��o de bibliotecas basicas */ 
#include <conio.h>
#include <stdio.h>

/* importa��o da biblioteca que implementa o tradutor */ 
#include "posfix-tradutor.h"


/* Defini��o dos prorotipos das fun��es auxiliares */
void cabecalho(void);

/* Fun��o Principal */
int main(int argc, char *argv[]) {

    cabecalho(); 	/* exibe um cabe�alho com informa��es do projeto */
                    
    traduzir();	    /* Fun��o do tradutor que inicia o processo */
                    /* de tradu��o;                             */
    
	finalizar();    /* Fun��o do tradutor que finaliza o processo   */
                    /* de tradu��o fechando os arquivos utilizados; */
    
    aguardar(CONTINUE);
	return 0;
}

/* Implementa��o das fun��es auxiliares */
void cabecalho(void) {     
     printf("\n\tAutarquia Educacional do Vale do Sao Francisco - AEVSF");
     printf("\n\tFaculdade de Ciencias Aplicadas e Sociais de Petrolina - FACAPE");
     printf("\n\tCurso de Ciencia da Computacao");
     printf("\n\tDisciplina: COMPILADORES\t\tSemestre: 2014.2");
     printf("\n\tProf. SERGIO FAUSTINO RIBEIRO");    
     printf("\n\tEquipe:");     
     printf("\n\t\tANDERSON;");
     printf("\n\t\tDJALMO;");     
     printf("\n\t\tESDRAS;");
     printf("\n\t\tLUIZ MARIO;");
     printf("\n\n\tDescricao:");
     printf("\n\t\tO projeto consiste na criacao de uma biblioteca C que");
     printf("\n\t\timplementa um tradutor simples capaz de reconhecer");
     printf("\n\t\talgumas expressoes na forma infixa e as traduzir para");
     printf("\n\t\ta forma pos-fixa, obedecendo a expecificacao abaixo:\n");
     printf("\n\t\tCMD   --> ID    =  EXPR");
     printf("\n\t\tEXPR  --> EXPR  +  TERMO");
     printf("\n\t\tTERMO --> TERMO *  FATOR");
     printf("\n\t\tFATOR --> ID\t\t[a-z | A-Z]");
     printf("\n\t\t\t| NUM\t\t[0...9]");
     printf("\n\t\t\t| (EXPR)");
     printf("\n\t\t\t| -FATOR");
     aguardar(CONTINUE);
}


