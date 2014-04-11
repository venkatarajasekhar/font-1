/***************************************************************************
*
*	$MCD M�dulo de defini��o: M�dulo Desenho
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
*				sa, S�rgio Argolo	
*				ft, Francisco Tacora
*
*	$HA Hist�rico de evolu��o:
*	Vers�o	Autor	Data		Observa��es
*	1.0		vyc		11/04/2014	In�cio do desenvolvimento
*
*	$ED Descri��o do m�dulo
*		Este � o m�dulo respons�vel pela cria��o e manipula��o
*		do desenho no jogo Nonogram.
*		S� existe um desenho em execu��o por modo de jogo.
*		Um desenho pode ser salvo a qualquer momento
*		e carregado posteriormente.
*
***************************************************************************/


/********************* Diretivas de Pr�-Processamento *********************/

#ifndef DESENHO_ 
#define DESENHO_



/****************** Declara��es exportadas pelo m�dulo *******************/




/*************************************************************************
*
*  $TC Tipo de dados: DES Condicoes de retorno
*
*************************************************************************/

	typedef enum {

			DES_CondRetOK = 0 ,
			/* Executou corretamente */
			
			DES_CondRetFaltouMemoria = 1
			/* Faltou mem�ria ao alocar dados */

	} DES_tpCondRet ;



/***********************************************************************
*
*	$FC Fun��o:	
*
*	$ED Descri��o da fun��o
*		
*
*	$EP Par�metros
*		
*
*	$FV Valor retornado
*		
*
*   $AE Assertivas de entrada 
*		
*		
*	$AS Assertivas de sa�da
*
**********************************************************************/




/************Fim do m�dulo de defini��o: M�dulo Desenho***************/

#endif