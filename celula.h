/***************************************************************************
*
*	$MCD M�dulo de defini��o: M�dulo C�lula
*
*	Arquivo gerado:				CELULA.H
*	Letras identificadoras:		CEL
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
*	1.0		vyc		30/03/2014	In�cio do desenvolvimento
*
*	$ED Descri��o do m�dulo
*		Este m�dulo implementa um conjunto de fun��es para criar e
*		manipular a estrutura c�lula, elemento b�sico do jogo Nonogram.
*		Ela armazena o estado da c�lula de acordo com a entrada fornecida
*		pelo usu�rio no modo Desafio, que pode ser: marcada, descartada e nulo.
*		Se o estado de uma c�lula � 1, ela pertence ao desenho.
*		Se o estado de uma c�lula � 2, ela n�o pertence ao desenho.
*		Se o estado de uma c�lula � NULL, o usu�rio ainda n�o interagiu
*		com tal c�lula.
*		A estrutura tamb�m armazena o estado correto da c�lula para
*		averiguar a corretude do desenho no modo Desafio.
*		Na cria��o, todos os campos s�o definidos como NULL.
*
***************************************************************************/



/********************* Diretivas de Pr�-Processamento *********************/

#ifndef CELULA_ 
#define CELULA_



/******************* Declara��es exportadas pelo m�dulo *******************/

/* Tipo ponteiro para uma c�lula */

typedef struct CEL_tagCelula* CEL_tppCelula ;



/***********************************************************************
*
*  $TC Tipo de dados: CEL Condicoes de retorno
*
***********************************************************************/

	typedef enum {

			CEL_CondRetOK = 0 ,
			/* Executou corretamente */

			CEL_CondRetFaltouMemoria = 1
			/* Faltou mem�ria ao alocar dados */

	} CEL_tpCondRet ;



/***********************************************************************
*
*	$FC Fun��o:	ARV Cria C�lula
*
*	$ED Descri��o da fun��o
*		Cria uma nova c�lula com todos os campos nulos.
*
*	$EP Par�metros
*		refCelula	  -	Refer�ncia para a c�lula criada
*
*	$FV Valor retornado
*		CEL_CondRetOK
*		CEL_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		refCelula referencia um ponteiro livre para uma nova c�lula.
*		
*	$AS Assertivas de sa�da
*		Se OK, refCelula apontar� para a c�lula criada.
*		Caso contr�rio, refCelula apontar� para um ponteiro nulo
*.
***********************************************************************/

	CEL_tpCondRet CEL_criaCelula ( CEL_tppCelula* refCelula );


/***********************************************************************
*
*	$FC Fun��o:	CEL Destroi C�lula
*
*	$ED Descri��o da fun��o
*		Destr�i a c�lula fornecida.
*		N�o modifica o ponteiro passado, deve-se atribur NULL a este
*		ap�s a chamada da fun��o.
*
*	$EP Par�metros
*		$P pCelula	- Ponteiro para a c�lula que ser� destru�da.  
*
*	$FV Valor retornado
*		CEL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pCelula aponta para uma c�lula v�lida.
*		
*	$AS Assertivas de sa�da
*		A c�lula foi liberada corretamente.
*.
***********************************************************************/

	CEL_tpCondRet CEL_destroiCelula ( CEL_tppCelula pCelula );


/***********************************************************************
*
*	$FC Fun��o:	CEL Obtem Estado Atual
*
*	$ED Descri��o da fun��o
*		Retorna o estado atual da c�lula.
*
*	$EP Par�metros
*		$P	pCelula	-	Ponteiro para a c�lula cujo estado atual 
*						ser� consultado.
*			pEstado	-	Ponteiro para a vari�vel que armazenar� o estado
*						da c�lula.
*
*	$FV Valor retornado
*		CEL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pCelula aponta para uma c�lula v�lida.
*		
*	$AS Assertivas de sa�da
*		O conte�do de pEstado recebe o status atual da c�lula.
*		A c�lula n�o � alterada.
*
***********************************************************************/

	CEL_tpCondRet CEL_obtemEstadoAtual ( CEL_tppCelula pCelula, int* pEstado );


/***********************************************************************
*
*	$FC Fun��o:	CEL Obtem Estado Correto
*
*	$ED Descri��o da fun��o
*		Retorna o estado correto da c�lula.
*
*	$EP Par�metros
*		$P	pCelula	-	Ponteiro para a c�lula cuja solu��o ser� consultada.  
*			pEstado	-	Ponteiro para a vari�vel que armazenar� o estado
*						da c�lula.
*
*	$FV Valor retornado
*		CEL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pCelula aponta para uma c�lula v�lida.
*		
*	$AS Assertivas de sa�da
*		O conte�do de pEstado recebe o status correto da c�lula.
*		A c�lula n�o � alterada.
*
***********************************************************************/

	CEL_tpCondRet CEL_obtemEstadoCorreto ( CEL_tppCelula pCelula, int* pEstado );


/***********************************************************************
*
*	$FC Fun��o:	CEL Altera Estado Atual
*
*	$ED Descri��o da fun��o
*		Altera o estado atual da c�lula.
*
*	$EP Par�metros
*		$P pCelula	- Refer�ncia para a c�lula cujo estado atual 
*					  ser� alterado. 
*		$P valor	- novo estado da c�lula.
*
*	$FV Valor retornado
*		CEL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pCelula aponta para uma c�lula v�lida.
*		valor � um inteiro entre [1..2] ou NULL.
*		
*	$AS Assertivas de sa�da
*		A c�lula apontada por pCelula tem seu estado atual alterado.
*
***********************************************************************/

	CEL_tpCondRet CEL_alteraEstadoAtual ( CEL_tppCelula pCelula , int valor );


/***********************************************************************
*
*	$FC Fun��o:	CEL Altera Estado Correto
*
*	$ED Descri��o da fun��o
*		Altera o estado correto da c�lula.
*
*	$EP Par�metros
*		$P pCelula	- Ponteiro para a c�lula cujo estado correto 
*					  ser� alterado. 
*		$P valor	- novo estado correto da c�lula.
*
*	$FV Valor retornado
*		CEL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pCelula aponta para uma c�lula v�lida.
*		valor � um inteiro entre [1..2] ou NULL. 
*		
*	$AS Assertivas de sa�da
*		A c�lula apontada por pCelula tem seu estado correto alterado.
*
***********************************************************************/

	CEL_tpCondRet CEL_alteraEstadoCorreto ( CEL_tppCelula pCelula, int valor );



/**************Fim do m�dulo de defini��o: M�dulo C�lula****************/

#endif