/***************************************************************************
*
*	$MCI M�dulo de implementa��o: M�dulo Matriz Gen�rica
*
*	Arquivo gerado:              MAT
*
*	Nome da base de software:    Exemplo de teste automatizado
*	Arquivo da base de software: ArcaboucoTeste.lib
*
*	Projeto: Disciplinas INF1301
*	Gestor:  Flavio Bevilacqua
*	Autores:	vyc, Victor Yves Crispim
*				sa, Sergio Argolo
*				ft, Francisco Tacora
*
*	$HA Hist�rico de evolu��o:
*		Vers�o	Autor	Data		Observa��es
*		1.0		vyc		05/04/2014	In�cio do Desenvolvimento
*
***************************************************************************/



/********************* Diretivas de Pr�-Processamento *********************/

#include "matriz.h"
#include <malloc.h>
#define NULL 0



/***************** Declara��es encapsuladas pelo m�dulo ******************/


/**************************************************************************
*
*	$TC Tipo de dados: MAT Descritor da Cabe�a de matriz
*
*	$ED Descri��o do tipo
*		Contem todos os dados da matriz.
*
**************************************************************************/

	struct MAT_tagMatriz{

		void* m ;
				/*Ponteiro para a matriz*/
		void (*ExcluirDado) (void* pDado) ;
				/*Ponteiro para a fun��o de destrui��o do valor 
				contido em um elemento*/
		int linhas;
				/*indica o n�mero de linhas da matriz*/
		int colunas;
				/*indica o n�mero de colunas da matriz*/

	};


/************* C�digo das fun��es exportadas pelo m�dulo **************/

/***********************************************************************
*
*  Fun��o: MAT Cria Matriz
*/

	MAT_tpCondRet MAT_criaMatriz ( MAT_tppMatriz* refMatriz, int linhas, int colunas,
												 void (*ExcluirDado) (void* pDado) ){

		*refMatriz = (MAT_tagMatriz*) malloc (sizeof ( struct MAT_tagMatriz) );  //aloca espa�o para a cabe�a da matriz
		(*refMatriz)->m = (void*) malloc (sizeof ( linhas * colunas ) + 4 ); //aloca espa�o para a matriz em si

		if ( *refMatriz == NULL ){

			return MAT_CondRetFaltouMemoria ;

		}

		//inicializa a cabe�a da matriz
		(*refMatriz)->linhas = linhas ;
		(*refMatriz)->colunas = colunas ;
		(*refMatriz)->ExcluirDado = ExcluirDado ;

		return MAT_CondRetOK ;
	}


/***********************************************************************
*
*  Fun��o: MAT Destroi Matriz
*/

	MAT_tpCondRet MAT_destroiMatriz ( MAT_tppMatriz pMatriz ){

		int i , j ;
		
		if ( MAT_confereVazia (pMatriz) == MAT_CondRetMatrizNVazia ){
			
			for( i=0, j=0; i < pMatriz->linhas, j < pMatriz->colunas; i++, j++ ){
			
				pMatriz->ExcluirDado( pMatriz->m[i][j] );
			}

			free ( pMatriz->m );
			free ( pMatriz ) ;
		}

		else {

			free ( pMatriz->m ) ;
			free ( pMatriz ) ;
		} 
		
		return MAT_CondRetOK ;
	}


/***********************************************************************
*
*  Fun��o: MAT Esvazia Matriz
*/

	MAT_tpCondRet MAT_esvaziaMatriz ( MAT_tppMatriz pMatriz ){

		int i , j ;
		
		for ( i=0, j=0; i < pMatriz->linhas, j < pMatriz->colunas; i++, j++ ){
			
				pMatriz->ExcluirDado ( pMatriz->m[i][j] ) );
		}

		return MAT_CondRetOK ;
	}


/***********************************************************************
*
*  Fun��o: MAT Insere Dado
*/

	MAT_tpCondRet MAT_insereDado ( MAT_tppMatriz pMatriz, int linha, int coluna, void* pDado){

		pMatriz->m[linha][coluna] = pDado ;
	}


/***********************************************************************
*
*  Fun��o: MAT Confere Vazia
*/

	MAT_tpCondRet MAT_confereVazia ( MAT_tppMatriz pMatriz ){

		int i, j ;

		for ( i=0, j=0; i < pMatriz->linhas, j < pMatriz->colunas; i++, j++ ){

			if ( pMatriz->m[i][j] != NULL )
				return MAT_CondRetMatrizNVazia ;
		} 

		return MAT_CondRetMatrizVazia ;
	}


/***********************************************************************
*
*  Fun��o: MAT Obter Linhas
*/

	MAT_tpCondRet MAT_obterLinhas ( MAT_tppMatriz pMatriz, int* refLinhas ){

		*refLinhas = pMatriz->linhas ;

		return MAT_CondRetOK ;
	}


/***********************************************************************
*
*  Fun��o: MAT Obter Colunas
*/
	MAT_tpCondRet MAT_obterColunas ( MAT_tppMatriz pMatriz, int* refLinhas ){

		*refLinhas = pMatriz->colunas;

		return MAT_CondRetOK ;
	}