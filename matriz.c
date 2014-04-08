/***************************************************************************
*
*	$MCI Módulo de implementação: Módulo Matriz Genérica
*
*	Arquivo gerado:				 matriz.c
*	Letras identificadoras:		 MAT
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
*		1.0		vyc		05/04/2014	Início do Desenvolvimento
*
***************************************************************************/



/********************* Diretivas de Pré-Processamento *********************/

#include "matriz.h"
#include <malloc.h>
#define NULL 0



/***************** Declarações encapsuladas pelo módulo ******************/

/*************************************************************************
*
*	$TC Tipo de dados: MAT Elemento da matriz
*
*	$ED Descrição do tipo
*		Elemento da matriz, que armazena 4 ponteiros para seus vizinhos, 
*		e um ponteiro para void.
*
*************************************************************************/

	typedef struct MAT_tagElemMatriz{

		struct MAT_tagElemMatriz* pCima ;
					/*Ponteiro para o vizinho de cima*/
		struct MAT_tagElemMatriz* pBaixo ;
					/*Ponteiro para o vizinho de baixo*/
		struct MAT_tagElemMatriz* pEsq	;
					/*Ponteiro para o vizinho a esquerda*/
		struct MAT_tagElemMatriz* pDir	;
					/*Ponteiro para o vizinho a direita*/
		void* pDado ;
					/*Ponteiro para o dado apontado pelo elemento*/

	} MAT_tpElemMatriz ;


/**************************************************************************
*
*	$TC Tipo de dados: MAT Descritor da Cabeça de matriz
*
*	$ED Descrição do tipo
*		Contem todos os dados da matriz.
*
**************************************************************************/

	typedef struct MAT_tagMatriz{

		struct MAT_tagElemMatriz* pElemInicial ;
				/*Ponteiro para o elemento inicial*/
		struct MAT_tagElemMatriz* pElemCorrente ;
				/*Ponteiro para o elemento corrente*/
		void (*ExcluirDado) (void* pDado) ;
				/*Ponteiro para a função de destruição do valor 
				contido em um elemento*/
		int linhas;
				/*indica o número de linhas da matriz*/
		int colunas;
				/*indica o número de colunas da matriz*/

	} MAT_tpMatriz;


/************* Código das funções exportadas pelo módulo **************/

/***********************************************************************
*
*  Função: MAT Cria Matriz
*/

	MAT_tpCondRet MAT_criaMatriz ( MAT_tppMatriz* refMatriz, int linhas, int colunas,
												 void (*ExcluirDado) (void* pDado) ){
		
		MAT_tpElemMatriz** vetAux ; //vetor auxiliar para armazenar os elementos
		int i, j ;

		//Aloca a cabeça da matriz
		*refMatriz = (MAT_tpMatriz*) malloc ( sizeof ( MAT_tpMatriz ) ) ;
		
		if ( *refMatriz == NULL )
			return MAT_CondRetFaltouMemoria;

		//Alocação do vetor auxiliar
		vetAux = (MAT_tpElemMatriz **) malloc 
							( sizeof ( MAT_tpElemMatriz*) * linhas * colunas );
		if ( vetAux == NULL ) {
			free ( *refMatriz );
			return MAT_CondRetFaltouMemoria;
		}
	
		/* Alocação dos elementos */
		for (i=0; i < linhas*colunas; i++) {
			vetAux[i] = (MAT_tpElemMatriz *) malloc ( sizeof(MAT_tpElemMatriz) );
			if ( vetAux[i] == NULL ) { 
				
				for (j=0; j<i; j++) { // Libera tudo que tinha sido alocado
					free(vetAux[j]);
				}
				
				free(*refMatriz);
				
				return MAT_CondRetFaltouMemoria;
			}

			vetAux[i]->pDado = NULL; // Zera os ponteiros para lista
		}

		/* Ligar os ponteiros dos elementos */
		for (i=0; i < linhas; i++) {

			for (j=0; j < colunas; j++) {
					/*Inicializa pValor*/
				vetAux[i*linhas + j]->pDado = NULL;

					/* Cima */
				vetAux[i*linhas + j]->pCima = (i > 0) ? 
					vetAux[(i-1)*linhas + j] : NULL;

					/* Direita */
				vetAux[i*linhas + j]->pDir = (j < colunas-1) ? 
					vetAux[i*linhas + (j+1)] : NULL;

					/* Baixo */
				vetAux[i*linhas + j]->pBaixo = (i < linhas-1) ? 
					vetAux[(i+1)*linhas + j] : NULL;

					/* Esquerda */
				vetAux[i*linhas + j]->pEsq = (j > 0) ? 
					vetAux[i*linhas + (j-1)] : NULL;
			}
		}

		//Inicializa a cabeça da matriz
		(**refMatriz).pElemInicial = (**refMatriz).pElemCorrente = vetAux[0];
		(**refMatriz).colunas = colunas ;
		(**refMatriz).linhas = linhas ;
		(**refMatriz).ExcluirDado = ExcluirDado ;

		free ( vetAux ) ;

		return MAT_CondRetOK ;
	}


/***********************************************************************
*
*  Função: MAT Destroi Matriz
*/


/***********************************************************************
*
*	Função: MAT Andar corrente
*/


/***********************************************************************
*
*  Função: MAT Insere Dado
*/

	
/***********************************************************************
*
*	Função: MAT Obter Valor Corrente
*/


/***********************************************************************
*
*	Função: MAT Remove Valor Corrente
*/


/***********************************************************************
*
*  Função: MAT Reseta Matriz (esvazia)
*/


/********** Fim do módulo de implementação: Módulo matriz **********/