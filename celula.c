/***************************************************************************
*
*	$MCD M�dulo de implementa��o: M�dulo C�lula
*
*	Arquivo gerado:              CELULA.C
*	Letras identificadoras:      CEL
*
*	Nome da base de software:    Exemplo de teste automatizado
*	Arquivo da base de software: ArcaboucoTeste.lib
*
*	Projeto: Disciplinas INF 1301
*	Gestor:  Flavio Bevilacqua
*	Autores: vyc - Victor Yves Crispim
*			 sa - S�rgio Argolo
*			 ft - Francisco Tacora
*
*	$HA Hist�rico de evolu��o:
*		Vers�o	Autor	Data		Observa��es
*		1.0		vyc		30/03/2014	In�cio do desenvolvimento
*		2.0		sa		29/04/2014	Revis�o das fun��es do m�dulo
*		3.0		sa		03/05/2014	Revis�o das fun��es do m�dulo
*
***************************************************************************/


/********************* Diretivas de pr�-processamento *********************/

#include	<malloc.h>

#define		CELULA_OWN
#include	"celula.h"
#undef		CELULA_OWN

#define NULL 0



/****************** Declara��es encapsuladas pelo m�dulo ******************/

/***************************************************************************
*
*	$TC Tipo de dados: CEL Tipo C�lula
*
*	$ED Descri��o do tipo
*		Define uma c�lula, que armazena seu estado atual definido pelo
*		usu�rio no modo Desafio e armazena a seu estado correto, definido
*		pelo usu�rio no modo Projeto.
*
***************************************************************************/
	
	typedef struct CEL_tagCelula {
		
		int estado_atual;
		/* Indica o estado atual da c�lula */

		int estado_correto;
		/* Indica o estado correto da c�lula */

	} CEL_tpCelula;



/*************** C�digo das fun��es exportadas pelo m�dulo ***************/

/***********************************************************************
*	Fun��o: CEL Cria C�lula
*/
		
	CEL_tpCondRet CEL_criaCelula ( CEL_tppCelula* refCelula ){
		
		*refCelula = (CEL_tpCelula*)malloc(sizeof(CEL_tpCelula));

		if ( *refCelula == NULL )
			return CEL_CondRetFaltouMemoria ;

		(*refCelula)->estado_atual = NULL;
		(*refCelula)->estado_correto = NULL;

		return CEL_CondRetOK ;
	}


/***********************************************************************
* Fun��o: CEL Destroi C�lula
*/

	CEL_tpCondRet CEL_destroiCelula ( CEL_tppCelula pCelula ){
		
		if ( pCelula == NULL )
			return CEL_CondRetCelulaInexistente; 
		
		free(pCelula);

		return CEL_CondRetOK;
	}


/***********************************************************************
*	Fun��o:	CEL Obtem Estado Atual
*/

	CEL_tpCondRet CEL_obtemEstadoAtual ( CEL_tppCelula pCelula, int* pEstado ){
		
		if ( pCelula == NULL ) 
			return CEL_CondRetCelulaInexistente ;

		*pEstado = pCelula->estado_atual ;

		return CEL_CondRetOK ;
	}


/***********************************************************************
*	Fun��o:	CEL Obtem Estado Correto
*/

	CEL_tpCondRet CEL_obtemEstadoCorreto ( CEL_tppCelula pCelula, int* pEstado){
			
		if ( pCelula == NULL ) 
			return CEL_CondRetCelulaInexistente ;

		*pEstado = pCelula->estado_correto ;

		return CEL_CondRetOK ;
	
	}


/***********************************************************************
*	Fun��o:	CEL Altera Estado Atual
*/

	CEL_tpCondRet CEL_alteraEstadoAtual ( CEL_tppCelula pCelula , int valor ){
		
		if ( pCelula == NULL ) 
			return CEL_CondRetCelulaInexistente ;

		if ( valor < 0 || valor > 2 )
			return CEL_CondRetEstadoInvalido;

		pCelula->estado_atual = valor;

		return CEL_CondRetOK;
	}


/***********************************************************************
*	Fun��o:	CEL Altera Estado Correto
*/

	CEL_tpCondRet CEL_alteraEstadoCorreto ( CEL_tppCelula pCelula, int valor ){
		
		if ( pCelula == NULL ) 
			return CEL_CondRetCelulaInexistente ;

		if ( valor < 0 || valor > 2 )
			return CEL_CondRetEstadoInvalido;

		pCelula->estado_correto = valor;

		return CEL_CondRetOK;
	}


/************* Fim do m�dulo de implementa��o: M�dulo C�lula *************/