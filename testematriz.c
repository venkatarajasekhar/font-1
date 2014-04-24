/***************************************************************************
*	$MCI M�dulo de implementa��o: TLIS Teste espec�fico para m�dulo Matriz
*
*	Arquivo gerado:              testmatriz.c
*	Letras identificadoras:      TMAT
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
*		1.0		vyc		15/04/2014	In�cio do desenvolvimento
*
*	$ED Descri��o do m�dulo
*		Este m�dulo cont�m as fun��es espec�ficas para o teste do
*		m�dulo matriz. Podem ser criadas at� 10 matrizes, indexadas
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
#include	"celula.h"
#include	"matriz.h"

#define MAX_STRING 100
#define MAX_VET_MAT 10

static MAT_tppMatriz vtMatriz [MAX_VET_MAT] ;

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define		RESET_CMD			"=resetteste"
#define		CRIAR_MAT_CMD		"=cria"
#define		DESTRUIR_MAT_CMD	"=destroi"
#define		PERCORRE_MAT_CMD	"=percorre"
#define		INSERE_CMD			"=insere"
#define		OBTER_VAL_CMD		"=obtervalor"
#define		OBTER_LINHAS_CMD	"=obterlinhas"
#define		OBTER_COLUNAS_CMD	"=obtercolunas"
#define		RESETA_MAT_CMD		"=reseta"



/**************  Prot�tipo das fun��es encapsuladas no m�dulo  **************/

	static int ValidarIdMat ( int idMat ) ;



/**************  C�digo das fun��es exportadas pelo m�dulo  **************/

/**************************************************************************
*
*	$FC Fun��o: TLIS Efetuar opera��es de teste espec�ficas para matriz
*
*	$ED Descri��o da fun��o
*		Efetua os diversos comandos de teste espec�ficos para o m�dulo
*		matriz sendo testado.
*
*	$EP Par�metros
*		ComandoTeste - String contendo o comando
*		
*		Comandos dispon�veis:
*		
*		=resetteste
*		=cria					idMat			CondRetEsp		linha	coluna
*		=destroi				idMat			CondRetEsp
*		=percorre				idMat			CondRetEsp		linha	coluna
*		=insere					idMat			CondRetEsp		stringDado
*		=obtervalor				idMat			CondRetEsp		stringDado
*		=obterlinhas			idMat			CondRetEsp		numEsperado
*		=obtercolunas			idMat			CondRetEsp		numEsperado
*		=reseta					idMat			CondRetEsp		
*
*************************************************************************/

	TST_tpCondRet TST_EfetuarComando ( char * ComandoTeste ) {

		int numLidos = -1 ,		//N�mero de par�metros lidos
			idMat	= -1  ,		//�ndice do vetor de matrizes

			linha	= -1  ,
			coluna	= -1  ,
			numEsperado = -1,
			numObtido = -1	;
			

		MAT_tpCondRet	CondRetObtida, CondRetEsperada;

		char stringDado	[MAX_STRING];	//String passada pelo usu�rio
		char* pString ;


		
		/* Efetuar reset de teste de matriz */
		if ( strcmp (ComandoTeste , RESET_CMD) == 0 ) {

			int i ;
			for( i = 0 ; i < MAX_VET_MAT ; i++ ){
				vtMatriz[ i ] = NULL ;
			}

			return TST_CondRetOK ;
		} /* Fim Efetuar reset de teste de matriz */


		/* Testar MAT_criaMatriz */
		else if ( strcmp (ComandoTeste , CRIAR_MAT_CMD) == 0 ){

			numLidos = LER_LerParametros ("iiii", &idMat, &CondRetEsperada, &linha, &coluna);

			if ( (numLidos != 4) || (!ValidarIdMat (idMat)) )
				return TST_CondRetParm ;
		
			CondRetObtida = MAT_criaMatriz ( &vtMatriz[idMat], linha, coluna, (void(*)(void*)) CEL_destroiCelula);	
		
			return TST_CompararInt ( CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao criar matriz");
		}//Fim Testar MAT_criaMatriz


		/* Testar MAT_destroiMatriz */
		else if ( strcmp (ComandoTeste , DESTRUIR_MAT_CMD) == 0) {

			numLidos = LER_LerParametros ("ii", &idMat, &CondRetEsperada) ;

			if ( (numLidos != 2) || (!ValidarIdMat (idMat)) )
				return TST_CondRetParm ;

			CondRetObtida = MAT_destroiMatriz ( &vtMatriz [idMat] ) ;

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao destruir matriz.") ;
		} //Fim Testar MAT_destroiMatriz


		/* Testar MAT_percorreMatriz */
		else if ( strcmp (ComandoTeste, PERCORRE_MAT_CMD) == 0 ){
		
			numLidos = LER_LerParametros ( "iiii", &idMat, &CondRetEsperada, &linha, &coluna );

			if ( numLidos != 4 || ( !ValidarIdMat (idMat) ) )
				return TST_CondRetParm ;

			CondRetObtida = MAT_percorreMatriz ( vtMatriz [idMat], linha, coluna );

			return TST_CompararInt ( CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompativel ao percorrer a matriz" );
		}// Fim Testar MAT_percorreMatriz


		/* Testar MAT_insereDado */
		else if ( strcmp (ComandoTeste , INSERE_CMD) == 0) {

			numLidos = LER_LerParametros ("iis", &idMat, &CondRetEsperada, stringDado) ;

			if ( (numLidos != 3) || (!ValidarIdMat (idMat)) )
				return TST_CondRetParm ;

			pString = (char*) malloc (strlen (stringDado) + 1) ;
		
			if ( pString == NULL )
				   return TST_CondRetMemoria ;

			strcpy (pString, stringDado) ;

			CondRetObtida = MAT_insereDado ( vtMatriz [idMat], pString ) ;

			if ( CondRetObtida != MAT_CondRetOK )
				free (pString) ;

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao inserir dado.") ;
		} //Fim Testar MAT_insereDado


		/* Testar MAT_obterValorCorrente */
		else if ( strcmp (ComandoTeste , OBTER_VAL_CMD) == 0) {

			numLidos = LER_LerParametros ("iis", &idMat, &CondRetEsperada, stringDado) ;

			if ( (numLidos != 3) || (!ValidarIdMat (idMat)) )
				return TST_CondRetParm ;

			CondRetObtida = MAT_obterValorCorrente ( vtMatriz [idMat] , (void**)&pString ) ;

			if ( CondRetObtida != MAT_CondRetOK )
				return TST_CompararInt (CondRetEsperada, CondRetObtida, 
										"Condi��o de retorno incompativel ao obter valor corrente.") ;  

			return TST_CompararString ( stringDado , pString , "Valor do elemento errado." ) ;
		} //Fim ativa: Testar LIS_ObterValor

		
		/* Testar MAT_obterLinhas */
		else if ( strcmp (ComandoTeste , OBTER_LINHAS_CMD) == 0) {

			numLidos = LER_LerParametros ("iii", &idMat, &CondRetEsperada,&numEsperado) ;
	
			if ( (numLidos != 3) || (!ValidarIdMat (idMat)) )
				return TST_CondRetParm ;

			CondRetObtida = MAT_obterLinhas ( vtMatriz [idMat], &numObtido ) ;

			if ( CondRetObtida != MAT_CondRetOK ){
				return TST_CompararInt (CondRetEsperada, CondRetObtida, 
								"Condi��o de retorno incompat�vel ao obter linhas.") ;
			}

			return	TST_CompararInt (numEsperado, numObtido,
									"O n�mero de linhas esperado � diferente do obtido");
		} //Fim Testar MAT_obterLinhas


		/* Testar MAT_obterColunas */
		else if ( strcmp (ComandoTeste , OBTER_COLUNAS_CMD) == 0) {

			numLidos = LER_LerParametros ("iii", &idMat, &CondRetEsperada,&numEsperado) ;
	
			if ( (numLidos != 3) || (!ValidarIdMat (idMat)) )
				return TST_CondRetParm ;

			CondRetObtida = MAT_obterColunas ( vtMatriz [idMat], &numObtido ) ;

			if ( CondRetObtida != MAT_CondRetOK ){
				return TST_CompararInt (CondRetEsperada, CondRetObtida, 
								"Condi��o de retorno incompat�vel ao obter colunas.") ;
			}

			return	TST_CompararInt (numEsperado, numObtido,
									"O n�mero de colunas esperado � diferente do obtido");
		} //Fim Testar MAT_obterLinhas
		
		
		/* Testar MAT_resetaMatriz */
		else if ( strcmp (ComandoTeste , RESETA_MAT_CMD) == 0) {

			numLidos = LER_LerParametros ("ii", &idMat, &CondRetEsperada) ;

			if ( (numLidos != 2) || (!ValidarIdMat (idMat)) )
				return TST_CondRetParm ;

			CondRetObtida = MAT_resetaMatriz ( vtMatriz [idMat] ) ;

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao resetar matriz" );
		} //Fim Testar MAT_resetaMatriz


		return TST_CondRetNaoConhec ;
	}



/*************** C�digo das fun��es encapsuladas no m�dulo ***************/

/**************************************************************************
*
*  $FC Fun��o: TLIS Validar indice de lista
*
**************************************************************************/

int ValidarIdMat ( int idMat ) {

      return ( idMat >=0 && idMat < MAX_VET_MAT );
}



/*** Fim do M�dulo de Implementa��o: Teste Espec�fico para M�dulo Matriz****/