/***************************************************************************
*
*	$MCD Módulo de implementação: Módulo Valor
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
*				sa, Sérgio Argolo
*				ft, Francisco Tacora
*
*	$HA Histórico de evolução:
*	Versão	Autor	Data		Observações
*	1.0		vyc		30/03/2014	Início do desenvolvimento
*
**************************************************************************/



/********************* Diretivas de pré-processamento *********************/

#include	<malloc.h>

#define		VALOR_OWN
#include	"valor.h"
#undef		VALOR_OWN

#define NULL 0



/****************** Declarações encapsuladas pelo módulo ******************/

	typedef struct VAL_tagValor {
		
		int resolvido;
		/* Indica se o valor foi resolvido corretamente ou não */

		int num_celulas;
		/* Indica o número de células a que o valor se refere */

	} VAL_tpValor;



/*************** Código das funções exportadas pelo módulo ***************/

/***********************************************************************
*	Função: VAL Cria Valor
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
*	Função: VAL Destroi Valor
*/

	VAL_tpCondRet VAL_destroiValor ( VAL_tppValor pValor ){

		if ( pValor != NULL )
			free(pValor);

		return VAL_CondRetOK;
	}


/***********************************************************************
*	Função: VAL Confere Solução
*/

	VAL_tpCondRet VAL_confereSolução ( VAL_tppValor pValor, int* pSolucao ){

		*pSolucao = pValor->resolvido;

		return VAL_CondRetOK ;
	}


/***********************************************************************
*	Função: VAL Define Soulução
*/

	VAL_tpCondRet VAL_defineSolucao ( VAL_tppValor pValor, int solucao ) {
	
		pValor->resolvido = solucao ;

		return VAL_CondRetOK;
	}


/***********************************************************************
*	Função: VAL Obtem Número de Células
*/

	VAL_tpCondRet VAL_obtemNumeroCelulas ( VAL_tppValor pValor, int* refNumCel ){
	
		*refNumCel = pValor->num_celulas ;

		return VAL_CondRetOK;
	}



/************ Fim do módulo de implementação: Módulo Valor ************/