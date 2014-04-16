/***************************************************************************
*	$MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*	Arquivo gerado:              LISTA.c
*	Letras identificadoras:      LIS
*
*	Nome da base de software:    Exemplo de teste automatizado
*	Arquivo da base de software: ArcaboucoTeste.lib
*
*	Projeto:	Disciplinas INF1301
*	Gestor:		Flavio Bevilacqua
*	Autores:	vyc, Victor Yves Crispim
*				sa, Sérgio Argolo
*				ft, Francisco Tacora
*
*	$HA Histórico de evolução:
*	Versão	Autor	Data		Observações
*	1.0		vyc		30/03/2014	Início do desenvolvimento
*
***************************************************************************/



/********************* Diretivas de pré-processamento *********************/
#include <malloc.h>

#define	LISTA_OWN
#include "lista.h"
#undef LISTA_OWN

#define NULL 0


/******************* Declarações Encapsuladas no Módulo *******************/

/***************************************************************************
*
*	$TC Tipo de dados: LIS Elemento da lista
*
*	$ED Descrição do tipo
*		Elemento da lista, que armazena um ponteiro para o sucessor, 
*		antecessor e um valor ponteiro para void.
*
***************************************************************************/

	typedef struct LIS_tagElemLista {

		void * pValor ;
			/* Ponteiro para o valor contido no elemento */
	
		struct LIS_tagElemLista * pAnt ;
			/* Ponteiro para o elemento predecessor */
	
		struct LIS_tagElemLista * pProx ;
			/* Ponteiro para o elemento sucessor */

	} LIS_tpElemLista ;


/***************************************************************************
*
*	$TC Tipo de dados: LIS Descritor da cabeça de lista
*
*	$ED Descrição do tipo
*		Contem todos os dados de uma lista específica.
*
***************************************************************************/

	typedef struct LIS_tagLista {
	
		struct LIS_tagElemLista * pOrigemLista ;
			/* Ponteiro para a origem da lista */
	
		struct LIS_tagElemLista * pFimLista ;
			/* Ponteiro para o final da lista */
	
		struct LIS_tagElemLista * pElemCorr ;
			/* Ponteiro para o elemento corrente da lista */
	
		unsigned int numElem ;
			/* Número de elementos da lista */
	
		void (*ExcluirValor)(void * pValor) ;
			/* Ponteiro para a função de destruição do valor contido em um elemento */
	
	} LIS_tpLista ;



/*********** Protótipos das Funções Encapsuladas Pelo Módulo ************/

static void LIS_LiberarElemento ( LIS_tppLista pLista , LIS_tpElemLista * pElem ) ;

static LIS_tpElemLista * LIS_CriarElemento ( LIS_tppLista pLista , void * pValor ) ;

static void LIS_LimparCabeca ( LIS_tppLista pLista ) ;



/************* Código das Funções Exportadas Pelo Módulo **************/

/***************************************************************************
*
*  Função: LIS  Criar lista
*/

	LIS_tpCondRet LIS_CriarLista ( LIS_tppLista * refLista , void(*ExcluirValor)(void * pDado) )
	{
		*refLista = (LIS_tpLista*)malloc(sizeof(LIS_tpLista));
	
		if ( *refLista == NULL )
			return LIS_CondRetFaltouMemoria ;
	
		LIS_LimparCabeca (*refLista) ;

		(*refLista)->ExcluirValor = ExcluirValor;

		return LIS_CondRetOK ;
	}


/***************************************************************************
*
*  Função: LIS  Obter Número de Elementos
*/

	LIS_tpCondRet LIS_ObterNumElem ( LIS_tppLista pLista, int * refNum ) 
	{ 

		*refNum = pLista->numElem; 

		return LIS_CondRetOK; 

	}


/***************************************************************************
*
*  Função: LIS  Destruir lista
*/

	LIS_tpCondRet LIS_DestruirLista ( LIS_tppLista pLista )
	{

		if ( pLista != NULL )
		{
			LIS_EsvaziarLista ( pLista );
			free ( pLista );
		}
	
		return LIS_CondRetOK;

	}


/***************************************************************************
*
*  Função: LIS  Esvaziar lista
*/

	LIS_tpCondRet LIS_EsvaziarLista ( LIS_tppLista pLista )
	{

		while ( pLista->pOrigemLista != NULL ) 
		{
			pLista->pElemCorr = pLista->pOrigemLista;
			pLista->pOrigemLista = pLista->pOrigemLista->pProx;
			LIS_LiberarElemento (pLista, pLista->pElemCorr);
		}

		LIS_LimparCabeca (pLista);

		return LIS_CondRetOK; 
	}


/***************************************************************************
*
*  Função: LIS  Inserir Elemento Antes
*/

	LIS_tpCondRet LIS_InserirElementoAntes ( LIS_tppLista pLista , void * pValor )
	{
		// Criar elemento a inserir antes
		LIS_tpElemLista * pElem = LIS_CriarElemento (pLista, pValor);

		if ( pElem == NULL )
			return LIS_CondRetFaltouMemoria ;

		// Encadear o elemento antes do elemento corrente
		if ( pLista->pElemCorr == NULL ) 
		{
			pLista->pOrigemLista = pElem;
			pLista->pFimLista = pElem;
		} 
		
		else 
		{
			if ( pLista->pElemCorr->pAnt != NULL ) 
			{
				pElem->pAnt = pLista->pElemCorr->pAnt;
				pLista->pElemCorr->pAnt->pProx = pElem;
			} 

			else 
			{
				pLista->pOrigemLista = pElem;
			}

			pElem->pProx = pLista->pElemCorr;
			pLista->pElemCorr->pAnt = pElem;
		}

		pLista->pElemCorr = pElem ;

		return LIS_CondRetOK ;
	}


/***************************************************************************
*
*  Função: LIS  Inserir Elemento Após
*/

	LIS_tpCondRet LIS_InserirElementoApos ( LIS_tppLista pLista	, void * pValor ) {
		
		/* Criar elemento a inserir após */
		LIS_tpElemLista * pElem ;
		pElem = LIS_CriarElemento( pLista , pValor ) ;

		if ( pElem == NULL )
			return LIS_CondRetFaltouMemoria ;

			/* Encadear o elemento após o elemento */
		if ( pLista->pElemCorr == NULL ) 
		{
			pLista->pOrigemLista = pElem ;
			pLista->pFimLista = pElem ;
		} 	

		else 
		{
			if ( pLista->pElemCorr->pProx != NULL ) {
				pElem->pProx  = pLista->pElemCorr->pProx ;
				pLista->pElemCorr->pProx->pAnt = pElem ;
			} 
			else {
				pLista->pFimLista = pElem ;
			}
			pElem->pAnt = pLista->pElemCorr ;
			pLista->pElemCorr->pProx = pElem ;
		}   

		pLista->pElemCorr = pElem ;         
	
		return LIS_CondRetOK ;
	}


/***************************************************************************
*
*  Função: LIS  Excluir elemento
*/

LIS_tpCondRet LIS_ExcluirElemento ( LIS_tppLista pLista )
{
	LIS_tpElemLista * pElem ;

	if ( pLista->pElemCorr == NULL )
		return LIS_CondRetListaVazia;

	pElem = pLista->pElemCorr ;

	// Desencadeia à esquerda
	if ( pElem->pAnt != NULL ) 
	{
		pElem->pAnt->pProx   = pElem->pProx ;
		pLista->pElemCorr    = pElem->pAnt ;
	} 
	else 
	{
		pLista->pElemCorr    = pElem->pProx ;
		pLista->pOrigemLista = pLista->pElemCorr ;
	}

	// Desencadeia à direita 
	if ( pElem->pProx != NULL )
		pElem->pProx->pAnt = pElem->pAnt ;
	else
		pLista->pFimLista = pElem->pAnt ;

	LIS_LiberarElemento (pLista, pElem);

	return LIS_CondRetOK ;
}


/***************************************************************************
*
*  Função: LIS Obter Valor Corrente
*/

LIS_tpCondRet LIS_ObterValorCorrente ( LIS_tppLista pLista , void ** refValor )
{
	
	if ( pLista->pElemCorr == NULL )
		return LIS_CondRetListaVazia ;
    
	*refValor = pLista->pElemCorr->pValor;

	return  LIS_CondRetOK ;

}


/***************************************************************************
*
*  Função: LIS Ir para o Início da Lista
*/

	 LIS_tpCondRet LIS_IrInicioLista ( LIS_tppLista pLista )
	{

		if ( pLista->pElemCorr == NULL )
			return LIS_CondRetListaVazia ;

		pLista->pElemCorr = pLista->pOrigemLista ;

		return LIS_CondRetOK ;

	}


/***************************************************************************
*
*  Função: LIS  Ir para o Final da Lista
*/

	LIS_tpCondRet LIS_IrFinalLista ( LIS_tppLista pLista )
	{

		if ( pLista->pElemCorr == NULL )
			return LIS_CondRetListaVazia ;

		pLista->pElemCorr = pLista->pFimLista ;
	
		return LIS_CondRetOK ;

	}


/***************************************************************************
*
*  Função: LIS Percorre Lista
*/

	LIS_tpCondRet LIS_PercorreLista ( LIS_tppLista pLista , int numElem )
	{
		int i = -1 ;
		LIS_tpElemLista * pElem = NULL;

		// Caso lista vazia
		if ( pLista->pElemCorr == NULL )
			return LIS_CondRetListaVazia ;

		// Caso numElem == 0
		if ( numElem == 0 )
			return LIS_CondRetOK ;

		pElem = pLista->pElemCorr ;

		// Tratar avançar para frente
		if ( numElem > 0 ) 
		{
			for ( i = numElem ; i > 0 ; i-- ) 
			{
				if ( pElem == NULL ) break;
				pElem = pElem->pProx ;
			}

			// Caso alcance a fronteira
			if ( pElem == NULL ) 
			{
				pLista->pElemCorr = pLista->pFimLista ;
				return LIS_CondRetFimLista ;
			} 
		}

		// Tratar avançar para trás
		else
		{
			for( i = numElem ; i < 0 ; i++ ) 
			{
				if ( pElem == NULL ) break ;
				pElem = pElem->pAnt ;
			}

			// Caso alcance a fronteira
			if ( pElem == NULL ) 
			{
				pLista->pElemCorr = pLista->pOrigemLista ;
				return LIS_CondRetFimLista ;
			}
		}

		pLista->pElemCorr = pElem ;
		return LIS_CondRetOK ;
	}



/************** Código das Funções Encapsuladas pelo Módulo *****************/


/***************************************************************************
*
*	$FC Função: LIS - Liberar elemento da lista
*
*	$ED Descrição da função
*		Elimina os espaços apontados pelo valor do elemento e o próprio elemento.
*
***************************************************************************/

	static void LIS_LiberarElemento ( LIS_tppLista pLista , LIS_tpElemLista * pElem )
	{
		if ( pLista->ExcluirValor != NULL && pElem->pValor != NULL )
			 pLista->ExcluirValor (pElem->pValor) ;

		free (pElem) ;

		pLista->numElem-- ;

	}


/***************************************************************************
*
*  $FC Função: LIS - Criar o elemento
*
***************************************************************************/

	static LIS_tpElemLista * LIS_CriarElemento ( LIS_tppLista pLista , void * pValor )
	{

		LIS_tpElemLista * pElem = NULL;

		pElem = (LIS_tpElemLista*)malloc(sizeof(LIS_tpElemLista)) ;

		if ( pElem == NULL )
			return NULL;

		pElem->pValor = pValor;
		pElem->pAnt = pElem->pProx = NULL;

		pLista->numElem ++;

		return pElem;

	}


/***************************************************************************
*
*	$FC Função: LIS - Limpar a cabeça da lista
*
***************************************************************************/

	static void LIS_LimparCabeca ( LIS_tppLista pLista )
	{
		pLista->pOrigemLista = NULL ;
		pLista->pFimLista = NULL	;
		pLista->pElemCorr = NULL	;
		pLista->numElem   = 0		;

	}


/*************** Fim do Módulo de Definição: Módulo Lista ****************/