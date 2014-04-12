/***************************************************************************
*
*	$MCI Módulo de implementação: Módulo Desenho
*
*	Arquivo gerado:				 desenho.c
*	Letras identificadoras:		 DES
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
*	$HA Histórico de evolução:
*		Versão	Autor	Data		Observações
*		1.0		vyc		11/04/2014	Início do Desenvolvimento
*
***************************************************************************/


/********************* Diretivas de Pré-Processamento *********************/

#include "desenho.h"
#include "celula.h"
#include "valor.h"
#include "lista.h"
#include "matriz.h"

#include <malloc.h>
#include <stdio.h>
#define NULL 0

/****************** Declarações encapsuladas pelo módulo *******************/

/*************************************************************************
*
*	$TC Tipo de dados: DES Descritor de um desenho
*
*	$ED Descrição do tipo
*		Contém todos os dados do desenho
*
*************************************************************************/

	typedef struct DES_tagDesenho{
		
		MAT_tppMatriz matriz;
					/*Ponteiro para a matriz*/
		LIS_tppLista* listaValoresH ;
					/*Vetor de listas de valores horizontais*/
		LIS_tppLista* listaValoresV ;
					/*Vetor de listas de valores verticais*/
		VAL_tpCondRet (*destroiValor) (VAL_tppValor valor) ;
					/*Ponteiro para a função de de exclusão de valores*/
		CEL_tpCondRet (*destroiCelula) (CEL_tppCelula celula) ;
					/*Ponteiro para a função de de exclusão de células*/
		char* nome ;
					/*Nome que identifica o desenho*/

	} DES_tpDesenho ;



/********************* Dados encapsulados no módulo *********************/

	static DES_tpDesenho* pDesenho ; 
				/*Ponteiro para um desenho*/


/************* Protótipos das funções encapuladas no módulo *************/

	static int initMatriz ( MAT_tppMatriz matriz, int linhas, int colunas );
	static void desalocaVetListas (LIS_tppLista* vetListas, int tam_vet );



/************** Código das funções exportadas pelo módulo ***************/

/************************************************************************
*
*  Função: DES Cria Desenho 
*/

	DES_tpCondRet criaDesenho ( int linhas, int colunas, char* nome ){
		
		MAT_tpCondRet retMat ;	//retorno das funções do módulo matriz
		LIS_tpCondRet retLis ;	//retorno das funções do módulo lista
		int retInitMat ;		//retorno da função auxiliar initMatriz
		int i, j;

		//Aloca desenho
		pDesenho = (DES_tpDesenho*) malloc ( sizeof(DES_tpDesenho) ) ;
		if ( pDesenho == NULL )
			return DES_CondRetFaltouMemoria ;
		
		//Aloca vetor de listas horizontais 
		pDesenho->listaValoresH = (LIS_tppLista*) malloc ( sizeof(LIS_tppLista) * linhas ) ;
		if ( pDesenho->listaValoresH == NULL ){
			free ( pDesenho );
			return DES_CondRetFaltouMemoria ;
		}
		
		//Aloca vetor de listas verticais
		pDesenho->listaValoresV = (LIS_tppLista*) malloc ( sizeof(LIS_tppLista) * colunas ) ;
		if ( pDesenho->listaValoresV == NULL){
			free ( pDesenho->listaValoresH );
			free ( pDesenho );
			return DES_CondRetFaltouMemoria ;
		}

		//Aloca as listas do vetor de listas de valores horizontais
		for ( i=0 ; i < linhas ; i++ ){
			//Cria a lista de valores da linha i
			retLis = LIS_CriarLista ( &pDesenho->listaValoresH[i], (ExcluirValor) pDesenho->destroiValor ) ;
			//Se a alocação de uma lista deu errado
			if ( retLis == LIS_CondRetFaltouMemoria ){
				
				//Desaloca as listas alocadas previamente
				desalocaVetListas ( pDesenho->listaValoresH, i-1 );

				//Libera os vetores de listas e o desenho
				free ( pDesenho->listaValoresH );
				free ( pDesenho->listaValoresV );
				free (pDesenho);

				return DES_CondRetFaltouMemoria;
			}
		}

		//Aloca as listas do vetor de listas de valores verticais
		for ( i=0 ; i < colunas ; i++ ){
			//Cria a lista de valores da coluna i
			retLis = LIS_CriarLista ( &pDesenho->listaValoresV[i], (ExcluirValor) pDesenho->destroiValor ) ;
			//Se a alocação de uma lista deu errado
			if ( retLis == LIS_CondRetFaltouMemoria ){			
				
				//Desaloca as listas alocadas previamente
				desalocaVetListas ( pDesenho->listaValoresV, i-1 );
				//Desaloca as listas do vetor de listas de valores horizontais
				desalocaVetListas ( pDesenho->listaValoresH, linhas);

				//Libera os vetores de listas e o desenho
				free (pDesenho->listaValoresV);
				free (pDesenho->listaValoresH);
				free (pDesenho);
			
				return DES_CondRetFaltouMemoria;
			}
		}

		//Cria a matriz de células do desenho
		retMat = MAT_criaMatriz( &pDesenho->matriz, linhas, colunas, (ExcluirValor) pDesenho->destroiCelula) ;
		//Se der erro, desaloca todas as estruturas
		if ( retMat == MAT_CondRetFaltouMemoria ){

			//Desaloca as listas dos vetores de listas de valores
			desalocaVetListas ( pDesenho->listaValoresH, linhas) ;
			desalocaVetListas ( pDesenho->listaValoresV, colunas) ;
			
			//Libera os vetores de listas e o desenho
			free (pDesenho->listaValoresH);
			free (pDesenho->listaValoresV);
			free (pDesenho);
			
			return DES_CondRetFaltouMemoria;
		}

		//Insere as células nos elementos da matriz
		retInitMat = initMatriz ( pDesenho->matriz, linhas, colunas );
		//Se der erro, desaloca todas as estruturas
		if ( retInitMat != 0 ){

			//Desaloca as listas dos vetores de listas de valores
			desalocaVetListas ( pDesenho->listaValoresH, linhas) ;
			desalocaVetListas ( pDesenho->listaValoresV, colunas) ;
			
			//Libera os vetores de listas, a matriz e o desenho
			free (pDesenho->listaValoresH);
			free (pDesenho->listaValoresV);
			retMat = MAT_destroiMatriz ( pDesenho->matriz );
			free (pDesenho);
			
			return DES_CondRetFaltouMemoria;
		}

		//Atribui o nome do desenho
		pDesenho->nome = nome ;

		return DES_CondRetOK;
	}



/************* Código das funções encapuladas no módulo *************/

/********************************************************************
*
*  FC Função: DES - Inicializa Matriz
*
********************************************************************/

	static int initMatriz ( MAT_tppMatriz matriz, int linhas, int colunas ){
		
		int i, j;
		CEL_tpCondRet retCel;
		MAT_tpCondRet retMat;
		CEL_tppCelula cel;

		for ( i=0 ; i < linhas ; i++ ){
			
			for ( j=0 ; j < colunas ; j++ ){
				//Vai pro elemento (i,j) da matriz
				retMat = MAT_percorreMatriz ( pDesenho->matriz, i, j );
				//Cria a célula
				retCel = CEL_criaCelula ( &cel );
				if ( retCel == CEL_CondRetFaltouMemoria )
					return -1;
				//Insere a célula no elemento (i,j) da matriz
				retMat = MAT_insereDado ( pDesenho->matriz, cel );
			}
		}
		
		return 0;
	}


/********************************************************************
*
*  FC Função: DES - Desaloca Vetor de Listas
*
********************************************************************/
	
	static void desalocaVetListas (LIS_tppLista* vetListas, int tam_vet ){
		
		int i;
		LIS_tpCondRet ret;

		for ( i=0 ; i < tam_vet ; i++ )
			ret = LIS_DestruirLista ( vetListas[i] );
	}



/************ Fim do módulo de implementação: Módulo Desenho ***********/