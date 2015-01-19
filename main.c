/* importação de bibliotecas basicas */ 
#include <conio.h>
#include <stdio.h>

/* importação da biblioteca que implementa o tradutor */ 
#include "posfix-tradutor.h"


/* Definição dos prorotipos das funções auxiliares */
void cabecalho(void);

/* Função Principal */
int main(int argc, char *argv[]) {

    cabecalho(); 	/* exibe um cabeçalho com informações do projeto */
                    
    traduzir();	    /* Função do tradutor que inicia o processo */
                    /* de tradução;                             */
    
	finalizar();    /* Função do tradutor que finaliza o processo   */
                    /* de tradução fechando os arquivos utilizados; */
    
    aguardar(CONTINUE);
	return 0;
}

/* Implementação das funções auxiliares */
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


