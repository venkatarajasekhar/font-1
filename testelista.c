/***************************************************************************
*	$MCI M�dulo de implementa��o: TLIS Teste espec�fico para m�dulo Lista
*
*	Arquivo gerado:              testlista.c
*	Letras identificadoras:      TLIS
*
*	Nome da base de software:    Exemplo de teste automatizado
*	Arquivo da base de software: ArcaboucoTeste.lib
*
*	Projeto: Disciplinas INF 1301
*	Gestor:  Flavio Bevilacqua
*	Autores:	vyc, Victor Yves Crispim
*				sa, S�rgio Argolo
*				ft, Francisco Tacora
*
*	$HA Hist�rico de evolu��o:
*		Vers�o	Autor	Data		Observa��es
*		1.0		vyc		14/04/2014	In�cio do desenvolvimento
*		2.0		sa		01/05/2014	Revis�o dos testes
*		3.0		sa		05/05/2014	Revis�o dos testes
*		4.0		sa		08/05/2014	Revis�o dos testes	
*
*	$ED Descri��o do m�dulo
*		Este m�dulo cont�m as fun��es espec�ficas para o teste do
*		m�dulo lista. Podem ser criadas at� 10 listas, indexadas
*		em um vetor de 0 a 9. S� ser�o testados valores do tipo string.
*
***************************************************************************/



/********************* Diretivas de pr�-processamento *********************/

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>

#include    "TST_ESPC.H"
#include    "GENERICO.H" 
#include    "LERPARM.H"
#include	"lista.h"

#define MAX_STRING 100
#define MAX_VET_LIS 10

static LIS_tppLista vtListas [MAX_VET_LIS] ;

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define		RESET_LIS_CMD		"=resetteste"
#define     CRIAR_LIS_CMD		"=criar"
#define     OBTER_NUM_ELEM_CMD  "=obternumelem"
#define		DESTRUIR_LIS_CMD	"=destruir"
#define     ESVAZIAR_LIS_CMD	"=esvaziar"
#define     INS_ELEM_ANTES_CMD  "=inselemantes"
#define     INS_ELEM_APOS_CMD	"=inselemapos"
#define     EXCLUIR_ELEM_CMD	"=excluirelem"
#define     OBTER_VAL_CMD		"=obtervalor"
#define     INI_LIS_CMD			"=irinicio"
#define     FIM_LIS_CMD		    "=irfinal"
#define		PERCORRE_LIS_CMD	"=percorre"



/**************  Prot�tipo das fun��es encapsuladas no m�dulo  **************/

	static int ValidarIdLista ( int idLista ) ;



/**************  C�digo das fun��es exportadas pelo m�dulo  **************/

/**************************************************************************
*
*	$FC Fun��o: TLIS Efetuar opera��es de teste espec�ficas para lista
*
*	$ED Descri��o da fun��o
*		Efetua os diversos comandos de teste espec�ficos para o m�dulo
*		lista sendo testado.
*
*	$EP Par�metros
*		ComandoTeste - String contendo o comando
*		
*		Comandos dispon�veis:
*		
*		=resetteste
*		=criar					idLista			CondRetEsp
*		=obternumelem			idLista			CondRetEsp		intDado
*		=destruir				idLista			CondRetEsp
*		=esvaziar				idLista			CondRetEsp
*		=inselemantes			idLista			CondRetEsp		stringDado
*		=inselemapos			idLista			CondRetEsp		stringDado
*		=excluirelem			idLista			CondRetEsp
*		=obtervalor				idLista			CondRetEsp		stringDado
*		=irinicio				idLista			CondRetEsp
*		=irfinal				idLista			CondRetEsp
*		=percorre				idLista			CondRetEsp		numElem
*
*************************************************************************/

	TST_tpCondRet TST_EfetuarComando ( char * ComandoTeste ) {

		int numLidos = -1 ,		//N�mero de par�metros lidos
			idLista	= -1  ,		//�ndice do vetor de listas
			numElem = -1  ,		//Par�metro da fun��o LIS_PercorreLista

			numElemListaObtido		,	//Retorno da fun��o LIS_ObterNumElem
			numElemListaEsperado	;	//Par�metro da fun��o LIS_ObterNumElem passada
										//pelo usu�rio


		LIS_tpCondRet	CondRetObtida, CondRetEsperada;

		char stringDado	[MAX_STRING];	//String passada pelo usu�rio
		char* pString ;


		
		/* Efetuar reset de teste de lista */
		if ( strcmp (ComandoTeste , RESET_LIS_CMD) == 0 ) {

			int i ;
			for( i = 0 ; i < MAX_VET_LIS ; i++ )
				vtListas[ i ] = NULL ;

			return TST_CondRetOK ;
		} /* Fim Efetuar reset de teste de lista */


		/* Testar LIS_CriarLista */
		else if ( strcmp (ComandoTeste , CRIAR_LIS_CMD) == 0 ){

			numLidos = LER_LerParametros ("ii", &idLista, &CondRetEsperada);

			if ( (numLidos != 2) || (!ValidarIdLista (idLista)) )
				return TST_CondRetParm ;
		
			CondRetObtida = LIS_CriarLista ( &vtListas[idLista], NULL );	
		
			return TST_CompararInt ( CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao criar lista");
		}//Fim Testar LIS_CriarLista


		/* Testar LIS_ObterNumElem */
		else if ( strcmp (ComandoTeste, OBTER_NUM_ELEM_CMD) == 0 ){
		
			numLidos = LER_LerParametros ("iii", &idLista, &CondRetEsperada, &numElemListaEsperado) ;
		
			if ( (numLidos != 3) || (!ValidarIdLista (idLista)) )
				return TST_CondRetParm ;
		
			CondRetObtida = LIS_ObterNumElem ( vtListas [idLista], &numElemListaObtido ) ;
		
			if ( CondRetObtida != LIS_CondRetOK ){
				return TST_CompararInt (CondRetEsperada, CondRetObtida,
										"Condi��o de retorno incompat�vel ao obter n�mero de elementos");
			}

			return TST_CompararInt ( numElemListaObtido, numElemListaEsperado, 
									"N�mero de elementos est� incorreto" );
		}//Fim Testar LIS_ObterNumElem


		/* Testar LIS_DestruirLista */
		else if ( strcmp (ComandoTeste , DESTRUIR_LIS_CMD) == 0) {

			numLidos = LER_LerParametros ("ii", &idLista, &CondRetEsperada) ;

			if ( (numLidos != 2) || (!ValidarIdLista (idLista)) )
				return TST_CondRetParm ;

			CondRetObtida = LIS_DestruirLista ( vtListas [idLista] ) ;
			vtListas[idLista] = NULL ;

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao destruir lista.") ;
		} //Fim Testar LIS_DestruirLista


		/* Testar LIS_EsvaziarLista */
		else if ( strcmp (ComandoTeste , ESVAZIAR_LIS_CMD) == 0) {

			numLidos = LER_LerParametros ("ii", &idLista, &CondRetEsperada) ;
	
			if ( (numLidos != 2) || (!ValidarIdLista (idLista)) )
				return TST_CondRetParm ;

			CondRetObtida = LIS_EsvaziarLista ( vtListas [idLista] ) ;

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao esvaziar lista.") ;
		} //Fim Testar LIS_EsvaziarLista


		/* Testar LIS_InserirElementoAntes */
		else if ( strcmp (ComandoTeste , INS_ELEM_ANTES_CMD) == 0) {

			numLidos = LER_LerParametros ("iis", &idLista, &CondRetEsperada, stringDado) ;

			if ( (numLidos != 3) || (!ValidarIdLista (idLista)) )
				return TST_CondRetParm ;

			pString = (char*) malloc (strlen (stringDado) + 1) ;
		
			if ( pString == NULL )
				   return TST_CondRetMemoria ;

			strcpy (pString, stringDado) ;

			CondRetObtida = LIS_InserirElementoAntes ( vtListas [idLista], pString ) ;

			if ( CondRetObtida != LIS_CondRetOK )
				free (pString) ;

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao inserir elemento antes.") ;
		} //Fim Testar LIS_InserirElementoAntes
	

		/* Testar LIS_InserirElementoApos */
		else if ( strcmp (ComandoTeste , INS_ELEM_APOS_CMD) == 0) {

			numLidos = LER_LerParametros ("iis", &idLista, &CondRetEsperada, stringDado) ;

			if ( (numLidos != 3) || (!ValidarIdLista (idLista)) )
				return TST_CondRetParm ;

			pString = (char*) malloc (strlen (stringDado) + 1) ;
		
			if ( pString == NULL )
				   return TST_CondRetMemoria ;

			strcpy (pString, stringDado) ;

			CondRetObtida = LIS_InserirElementoApos ( vtListas [idLista], pString ) ;
		
			if ( CondRetObtida != LIS_CondRetOK )
				free (pString) ; 

			return TST_CompararInt (CondRetEsperada, CondRetObtida,
									"Condi��o de retorno incompat�vel ao inserir elemento ap�s.") ;
		} //Fim ativa: Testar LIS_InserirElementoApos


		/* Testar LIS_ExcluirElemento */
		else if ( strcmp (ComandoTeste , EXCLUIR_ELEM_CMD) == 0) {

			numLidos = LER_LerParametros ("ii", &idLista, &CondRetEsperada) ;

			if ( (numLidos != 2) || (!ValidarIdLista (idLista)) )
				return TST_CondRetParm ;

			CondRetObtida = LIS_ExcluirElemento ( vtListas [idLista] ) ;

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao excluir elemento" );
		} //Fim ativa: Testar LIS_ExcluirElemento


		/* Testar LIS_ObterValorCorrente */
		else if ( strcmp (ComandoTeste , OBTER_VAL_CMD) == 0) {

			numLidos = LER_LerParametros ("iis", &idLista, &CondRetEsperada, stringDado) ;

			if ( (numLidos != 3) || (!ValidarIdLista (idLista)) )
				return TST_CondRetParm ;

			CondRetObtida = LIS_ObterValorCorrente ( vtListas [idLista] , (void**)&pString ) ;

			if ( CondRetObtida != LIS_CondRetOK )
				return TST_CompararInt (CondRetEsperada, CondRetObtida, 
										"Condi��o de retorno incompativel ao obter valor corrente.") ;  

			return TST_CompararString ( stringDado , pString , "Valor do elemento errado." ) ;
		} //Fim ativa: Testar LIS_ObterValor


		/* Testar LIS_IrInicioLista */
		else if ( strcmp (ComandoTeste , INI_LIS_CMD) == 0) {

			numLidos = LER_LerParametros ("ii", &idLista, &CondRetEsperada) ;

			if ( (numLidos != 2) || (!ValidarIdLista (idLista)) )
				return TST_CondRetParm ;

			CondRetObtida = LIS_IrInicioLista ( vtListas [idLista] ) ;

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
				"Condi��o de retorno incompativel ao ir para in�cio da lista" );
		} //Fim Testar LIS_IrInicioLista


		/* Testar LIS_IrFinalLista */
		else if ( strcmp (ComandoTeste, FIM_LIS_CMD) == 0) {
		
			numLidos = LER_LerParametros ("ii", &idLista, &CondRetEsperada) ;

			if ( (numLidos != 2) || (!ValidarIdLista (idLista)) )
				return TST_CondRetParm ;

			CondRetObtida = LIS_IrFinalLista ( vtListas [idLista] ) ;

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompativel ao ir para final da lista" );
		}/* Fim Testar LIS_IrFinalLista */


		/* Testar LIS_PercorreLista */
		else if ( strcmp (ComandoTeste, PERCORRE_LIS_CMD) == 0 ){
		
			numLidos = LER_LerParametros ( "iii", &idLista, &CondRetEsperada, &numElem );

			if ( numLidos != 3 || ( !ValidarIdLista (idLista) ) )
				return TST_CondRetParm ;

			CondRetObtida = LIS_PercorreLista ( vtListas [idLista], numElem );

			return TST_CompararInt ( CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompativel ao percorrer a lista" );
		}// Fim Testar LIS_PercorreLista

		return TST_CondRetNaoConhec ;
	}



/*************** C�digo das fun��es encapsuladas no m�dulo ***************/

/**************************************************************************
*
*  $FC Fun��o: TLIS Validar indice de lista
*
**************************************************************************/

int ValidarIdLista ( int idLista ) {

      return ( idLista >=0 && idLista < MAX_VET_LIS );
}



/*** Fim do M�dulo de Implementa��o: Teste Espec�fico para M�dulo Lista****/