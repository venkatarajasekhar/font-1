/***************************************************************************
*
*	$MCD Módulo de definição: Módulo Desenho
*
*	Arquivo gerado:				desenho.h
*	Letras identificadoras:		DES
*
*	Nome da base de software:		Exemplo de teste automatizado
*	Arquivo da base de software:	ArcaboucoTeste.lib
*
*	Projeto:	Disciplinas INF 1301
*	Gestor:		Flavio Bevilacqua
*	Autores:	vyc, Victor Yves Crispim
*				sa, Sérgio Argolo	
*				ft, Francisco Tacora
*
*	$HA Histórico de evolução:
*	Versão	Autor	Data		Observações
*	1.0		vyc		11/04/2014	Início do desenvolvimento
*
*	$ED Descrição do módulo
*		Este é o módulo responsável pela criação e manipulação
*		do desenho no jogo Nonogram.
*		Só existe um desenho em execução por modo de jogo.
*		Um desenho pode ser salvo a qualquer momento
*		e carregado posteriormente.
*
***************************************************************************/


/********************* Diretivas de Pré-Processamento *********************/

#ifndef DESENHO_ 
#define DESENHO_



/****************** Declarações exportadas pelo módulo *******************/




/*************************************************************************
*
*  $TC Tipo de dados: DES Condicoes de retorno
*
*************************************************************************/

	typedef enum {

			DES_CondRetOK = 0 ,
			/* Executou corretamente */
			
			DES_CondRetFaltouMemoria = 1
			/* Faltou memória ao alocar dados */

	} DES_tpCondRet ;



/***********************************************************************
*
*	$FC Função:	
*
*	$ED Descrição da função
*		
*
*	$EP Parâmetros
*		
*
*	$FV Valor retornado
*		
*
*   $AE Assertivas de entrada 
*		
*		
*	$AS Assertivas de saída
*
**********************************************************************/




/************Fim do módulo de definição: Módulo Desenho***************/

#endif