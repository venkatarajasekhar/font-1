/***************************************************************************
*
*	$MCD M�dulo de implementa��o: M�dulo Valor
*
*	Arquivo gerado:				VALOR.C
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
**************************************************************************/



/********************* Diretivas de pr�-processamento *********************/

#include	<malloc.h>

#define		VALOR_OWN
#include	"valor.h"
#undef		VALOR_OWN

#define NULL 0



/****************** Declara��es encapsuladas pelo m�dulo ******************/

	typedef struct VAL_tagValor {
		
		int resolvido;
		/* Indica se o valor foi resolvido corretamente ou n�o */

		int num_celulas;
		/* Indica o n�mero de c�lulas a que o valor se refere */

	} VAL_tpValor;



/*************** C�digo das fun��es exportadas pelo m�dulo ***************/

/***********************************************************************
*	Fun��o: VAL Cria Valor
*/

	VAL_tpCondRet VAL_criaValor ( VAL_tppValor* refValor, int numCelulas ){
	
		*refValor = (VAL_tpValor*) malloc ( sizeof(VAL_tpValor) );

		if( *refValor == NULL ){
			return VAL_CondRetFaltouMemoria ;
		}

		(*refValor)->resolvido = 0 ;
		(*refValor)->num_celulas = numCelulas ;

		return VAL_CondRetOK ;
	
	}


/***********************************************************************
*	Fun��o: VAL Destroi Valor
*/

	VAL_tpCondRet VAL_destroiValor ( VAL_tppValor pValor ){

		if ( pValor != NULL )
			free(pValor);

		return VAL_CondRetOK;
	}


/***********************************************************************
*	Fun��o: VAL Confere Solu��o
*/

	VAL_tpCondRet VAL_confereSolu��o ( VAL_tppValor pValor, int* pSolucao ){

		*pSolucao = pValor->resolvido;

		return VAL_CondRetOK ;
	}


/***********************************************************************
*	Fun��o: VAL Define Soulu��o
*/

	VAL_tpCondRet VAL_defineSolucao ( VAL_tppValor pValor, int solucao ) {
	
		pValor->resolvido = solucao ;

		return VAL_CondRetOK;
	}


/***********************************************************************
*	Fun��o: VAL Obtem N�mero de C�lulas
*/

	VAL_tpCondRet VAL_obtemNumeroCelulas ( VAL_tppValor pValor, int* refNumCel ){
	
		*refNumCel = pValor->num_celulas ;

		return VAL_CondRetOK;
	}



/************ Fim do m�dulo de implementa��o: M�dulo Valor ************/