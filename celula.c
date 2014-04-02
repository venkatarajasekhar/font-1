/***************************************************************************
*
*	$MCD Módulo de implementação: Módulo Célula
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
*			 sa - Sérgio Argolo
*			 ft - Francisco Tacora
*
*	$HA Histórico de evolução:
*		Versão	Autor	Data		Observações
*		1.0		vyc		30/03/2014	Início do desenvolvimento
*
***************************************************************************/


/********************* Diretivas de pré-processamento *********************/

#include	"celula.h"
#include	<malloc.h>
#define NULL 0



/****************** Declarações encapsuladas pelo módulo ******************/

/***************************************************************************
*
*	$TC Tipo de dados: CEL Tipo Célula
*
*	$ED Descrição do tipo
*		Define uma célula, que armazena seu estado atual definido pelo
*		usuário no modo Desafio e armazena a seu estado correto, definido
*		pelo usuário no modo Projeto.
*
***************************************************************************/
	
	typedef struct CEL_tagCelula {
		
		int estado_atual;
		/* Indica o estado atual da célula */

		int estado_correto;
		/* Indica o estado correto da célula */

	} CEL_tpCelula;



/*************** Código das funções exportadas pelo módulo ***************/

/***********************************************************************
*	Função: CEL Cria Célula
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
* Função: CEL Destroi Célula
*/

	CEL_tpCondRet CEL_destroiCelula ( CEL_tppCelula pCelula ){
		
		if ( pCelula != NULL )
			free(pCelula);

		return CEL_CondRetOK;
	}


/***********************************************************************
*	Função:	CEL Obtem Estado Atual
*/

	CEL_tpCondRet CEL_obtemEstadoAtual ( CEL_tppCelula pCelula, int* pEstado ){
		
		*pEstado = pCelula->estado_atual ;

		return CEL_CondRetOK ;
	}


/***********************************************************************
*	Função:	CEL Obtem Estado Correto
*/

	CEL_tpCondRet CEL_obtemEstadoCorreto ( CEL_tppCelula pCelula, int* pEstado){
			
		*pEstado = pCelula->estado_correto ;

		return CEL_CondRetOK ;
	
	}


/***********************************************************************
*	Função:	CEL Altera Estado Atual
*/

	CEL_tpCondRet CEL_alteraEstadoAtual ( CEL_tppCelula* pCelula , int valor ){
		
		pCelula->estado_atual = valor;

		return CEL_CondRetOK;
	}


/***********************************************************************
*	Função:	CEL Altera Estado Correto
*/

	CEL_tpCondRet CEL_alteraestadoCorreto ( CEL_tppCelula* pCelula, int valor ){
		
		pCelula->estado_atual = valor;

		return CEL_CondRetOK;
	}


/************* Fim do módulo de implementação: Módulo Célula *************/