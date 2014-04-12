/***************************************************************************
*
*	$MCD M�dulo de defini��o: M�dulo Valor
*
*	Arquivo gerado:				VALOR.H
*	Letras identificadoras:		VAL
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
*		manipular a estrutura valor.
*		O valor indica o n�mero de c�lulas sequenciais que devem ser 
*		marcadas em determinada linha ou coluna para se descobrir 
*		o desenho oculto no jogo Nonogram.
*		Se a solu��o do valor for 1, ele foi resolvido corretamente.
*		Se a solu��o do valor for 0, ele n�o foi resolvido corretamente.
*		Na cria��o, o n�mero de c�lulas do valor � NULL.
*
***************************************************************************/


/********************* Diretivas de Pr�-Processamento *********************/

#ifndef VALOR_ 
#define VALOR_



/******************* Declara��es exportadas pelo m�dulo *******************/

/* Tipo refer�ncia para um valor */

typedef struct VAL_tagValor* VAL_tppValor ;



/***********************************************************************
*
*  $TC Tipo de dados: VAL Condicoes de retorno
*
***********************************************************************/

	typedef enum {

			VAL_CondRetOK = 0 ,
			/* Executou corretamente */
			
			VAL_CondRetFaltouMemoria = 1
			/* Faltou mem�ria ao alocar dados */

	} VAL_tpCondRet ;



/***********************************************************************
*
*	$FC Fun��o:	VAL Cria Valor
*
*	$ED Descri��o da fun��o
*		Cria um novo valor.
*
*	$EP Par�metros
*		refValor	-	Refer�ncia para o valor criado.
*		numCelulas	-	Inteiro representando o n�mero de c�lulas
*						a que o valor se refere.
*		
*	$FV Valor retornado
*		VAL_tpCondRetOK
*		VAL_tpCondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		refValor referencia um ponteiro livre para um novo valor.
*		numCelulas � um inteiro maior que 0.
*		
*	$AS Assertivas de sa�da
*		Se OK, refValor apontar� para o valor criado.
*		Caso contr�rio, refValor apontar� para um ponteiro nulo.
*
***********************************************************************/

	VAL_tpCondRet VAL_criaValor ( VAL_tppValor* refValor, int numCelulas ) ;


/***********************************************************************
*
*	$FC Fun��o:	VAL Destroi Valor
*
*	$ED Descri��o da fun��o
*		Destroi um valor.
*		N�o modifica o ponteiro passado, deve-se atribur NULL a este
*		ap�s a chamada da fun��o.
*
*	$EP Par�metros
*		$P pValor - Ponteiro para o valor a ser destru�do.
*
*	$FV Valor retornado
*		VAL_tpCondRetOK;
*
*   $AE Assertivas de entrada 
*		pValor aponta para um valor v�lido.
*		
*	$AS Assertivas de sa�da
*		O valor foi liberado corretamente.
*.
***********************************************************************/

	VAL_tpCondRet VAL_destroiValor ( VAL_tppValor pValor ) ;


/***********************************************************************
*
*	$FC Fun��o:	VAL Confere Solu��o
*
*	$ED Descri��o da fun��o
*		Confere se o valor est� resolvido corretamente ou n�o.
*
*	$EP Par�metros
*		$P	pValor		-	Ponteiro para o valor a ser consultado.
*			pSolucao	-	Ponteiro para a vari�vel que vai armazenar
*							a solu��o do valor.
*
*	$FV Valor retornado
*		VAL_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pValor aponta para um valor v�lido.
*		pSolucao � um ponteiro para inteiro v�lido.
*		
*	$AS Assertivas de sa�da
*		O conte�do de pSolucao recebe a solu��o do valor.
*		O valor n�o � alterado.
*
***********************************************************************/

	VAL_tpCondRet VAL_confereSolu��o ( VAL_tppValor pValor, int* pSolucao ) ;


/***********************************************************************
*
*	$FC Fun��o:	VAL Define Solu��o
*
*	$ED Descri��o da fun��o
*		Define se o valor est� resolvido ou n�o.
*
*	$EP Par�metros
*		$P	pValor	- Ponteiro para o valor a ser alterado.
*			solucao	- Valor correspondente a solu��o desejada.
*
*	$FV Valor retornado
*		VAL_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pValor aponta para um valor v�lido.
*		solucao � um inteiro de valor 1 ou 0.
*		
*	$AS Assertivas de sa�da
*		O valor tem a sua solu��o alterada.
*
***********************************************************************/

	VAL_tpCondRet VAL_defineSolucao ( VAL_tppValor pValor, int solucao ) ;



/***********************************************************************
*
*	$FC Fun��o:	VAL Obtem N�mero de C�lulas
*
*	$ED Descri��o da fun��o
*		Retorna por refer�ncia o n�mero de c�lulas a que o valor se refere.
*
*	$EP Par�metros
*		$P pValor	-	Ponteiro para o valor a ser consultado.
*		$P pNumCel	-	Ponteiro para a vari�vel que armazenar� o n�mero
*						de c�lulas.
*
*	$FV Valor retornado
*		VAL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pValor aponta para um valor v�lido.
*		
*	$AS Assertivas de sa�da
*		O conte�do de pNumCel recebe o n�mero de c�lulas do valor.
*		O valor n�o � alterado.
*
***********************************************************************/

	int VAL_obtemNumeroCelulas ( VAL_tppValor pValor, int* pNumCel ) ;



/*************Fim do m�dulo de defini��o: M�dulo Valor****************/

#endif