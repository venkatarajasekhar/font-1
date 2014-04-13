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
#include <string.h>

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

	static DES_tpDesenho* pDesenho = NULL ; 
				/*Ponteiro para um desenho*/


/************* Protótipos das funções encapuladas no módulo *************/

	static int initMatriz ( MAT_tppMatriz matriz, int linhas, int colunas );
	static void desalocaVetListas (LIS_tppLista* vetListas, int tam_vet );



/************** Código das funções exportadas pelo módulo ***************/

/************************************************************************
*
*  Função: DES Cria Desenho 
*/

	DES_tpCondRet DES_criaDesenho ( int linhas, int colunas, char* nome ){
		
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


/************************************************************************
*
*  Função: DES Modifica Célula
*/

	DES_tpCondRet DES_modificaCelula ( int linha, int coluna, char estado ){
		
		CEL_tpCondRet retCel;
		MAT_tpCondRet retMat;
		CEL_tppCelula celula = NULL;
		
		retMat = MAT_percorreMatriz ( pDesenho->matriz, linha-1, coluna-1 );

		//Se o estado é marcada
		if ( estado == 'm' ){
		
			retCel = CEL_alteraEstadoCorreto ( celula, 1 ) ;
			return DES_CondRetOK ;
		}
		//Se o estado é desmarcada
		else if ( estado == 'd' ){
			
			retCel = CEL_alteraEstadoCorreto ( celula, 2 ) ;
			return DES_CondRetOK ;
		}

		else if ( estado == NULL ){
			
			retCel = CEL_alteraEstadoCorreto ( celula, NULL ) ;
			return DES_CondRetOK ;
		}
		else
			return DES_CondRetEstadoInvalido;
	}


/************************************************************************
*
*  Função: DES Calcula Valores
*/

	DES_tpCondRet DES_calculaValores ( void ){

		int i, j, k, cont_marcadas = 0 ;
		int linhas, colunas ;
		int estado;					//Armazena o estado correto da célula
		
		//Ponteiros para os tipos utilizados
		CEL_tppCelula celula = NULL ;
		VAL_tppValor valor = NULL ;
		
		//Condições de retorno
		VAL_tpCondRet retVal ;
		LIS_tpCondRet retLis ;

		//Obtem as dimensões da matriz
		MAT_obterLinhas ( pDesenho->matriz, &linhas );
		MAT_obterColunas ( pDesenho->matriz, &colunas );
		
		/*Calcula valores horizontais*/
		
		//Para cada linha
		for ( i=0 ; i<linhas ; i++ ){
			
			//Para cada coluna
			for ( j=0 ; j<colunas ; j++ ){
				
				//Na posição (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );
				
				//Obtem a célula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
				
				//Obtem o estado correto da célula
				CEL_obtemEstadoCorreto ( celula, &estado ) ;
				
				//Se estado for marcada
				if ( estado == 1 ){
					
					//Número de células marcadas recebe +1
					cont_marcadas++;
					
					//Verifica quantas células após também estão marcadas
					for ( k=j+1 ; k<colunas ; k++ ){
						
						//Na posição (i,k) da matriz
						MAT_percorreMatriz ( pDesenho->matriz, i, k );
						
						//Obtem a célula
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
						
						//Obtem o estado correto da célula
						CEL_obtemEstadoCorreto ( celula, &estado ) ;
						
						//Se estado for marcada
						if ( estado == 1 ){
						
							//Número de células marcadas recebe +1
							cont_marcadas++;
						}
						
						//Se estado for desmarcada
						else if ( estado == 2 ){
						
							//Cria um valor
							retVal = VAL_criaValor ( &valor, cont_marcadas );
							
							//Se der erro na alocação
							if ( retVal == VAL_CondRetFaltouMemoria ){
								return DES_CondRetFaltouMemoria;
							}
							
							//Senão, insere esse valor no final da linha atual
							retLis = LIS_InserirElementoApos ( pDesenho->listaValoresH[i], &valor );
							
							//Se der erro na alocação
							if ( retLis == LIS_CondRetFaltouMemoria ){
								return DES_CondRetFaltouMemoria;
							}

							cont_marcadas = 0;	//zera o contador
							j = k;				//continua da última coluna visitada
						}

						break; //Sai do loop de verificação
					}
				}
				//Se estado for desmarcada, segue para a próxima coluna
			}
		}

		/*Calcula valores verticais*/
		
		//Para cada coluna
		for ( j=0 ; j<colunas ; j++ ){
			
			//Para cada linha
			for ( i=0 ; i<linhas ; i++ ){
				
				//Na posição (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );
				
				//Obtem a célula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
				
				//Obtem o estado correto da célula
				CEL_obtemEstadoCorreto ( celula, &estado ) ;
				
				//Se estado for marcada
				if ( estado == 1 ){
					
					//Número de células marcadas recebe +1
					cont_marcadas++;
					
					//Verifica quantas células após também estão marcadas
					for ( k=i+1 ; k<linhas ; i++ ){
						
						//Na posição (i,k) da matriz
						MAT_percorreMatriz ( pDesenho->matriz, k, j );

						//Obtem a célula
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
						
						//Obtem o estado correto da célula
						CEL_obtemEstadoCorreto ( celula, &estado ) ;
						
						//Se estado for marcada
						if ( estado == 1 ){
						
							//Número de células marcadas recebe +1
							cont_marcadas++;
						}
						
						//Se estado for desmarcada
						else if ( estado == 2 ){
						
							//Cria um valor
							retVal = VAL_criaValor ( &valor, cont_marcadas );
							
							//Se der erro na alocação
							if ( retVal == VAL_CondRetFaltouMemoria ){
								return DES_CondRetFaltouMemoria;
							}
							
							//Senão, insere esse valor no final da linha atual
							retLis = LIS_InserirElementoApos ( pDesenho->listaValoresH[j], &valor );
							
							//Se der erro na alocação
							if ( retLis == LIS_CondRetFaltouMemoria ){
								return DES_CondRetFaltouMemoria;
							}

							cont_marcadas = 0;	//zera o contador
							i = k;				//continua da última coluna visitada
						}

						break; //Sai do loop de verificação
					}
				}
				//Se estado for desmarcada, segue para a próxima linha
			}
		}

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Função: DES Salva Desenho
*/

	DES_tpCondRet DES_salvaDesenho (void){
		
		int i, linhas, colunas, numCelulas, solucao;
		
		FILE* fpOut;
		VAL_tppValor valor = NULL ;

		LIS_tpCondRet retLis;

		fpOut = fopen ( strcat( pDesenho->nome, ".txt"), "w" );	//Abre o arquivo para escrita
		if ( fpOut == NULL )
			return DES_CondRetErroAberturaArquivo ;

		/*Escreve a dimensão da matriz*/
		
		//Obtem as dimensões da matriz
		MAT_obterLinhas ( pDesenho->matriz, &linhas );
		MAT_obterColunas ( pDesenho->matriz, &colunas );

		fprintf ( fpOut, "%d x %d\n", linhas, colunas );
		
		/*Escreve a lista de valores horizontal*/
		
		//Para todas as linhas
		for ( i = 0 ; i<linhas ; i++ ){
			
			//Vai pro inicio da lista
			LIS_IrInicioLista ( pDesenho->listaValoresH[i] );
			
			do{
				//Obtem o valor
				LIS_ObterValorCorrente ( pDesenho->listaValoresH[i], (void**)&valor);
				
				//Obtem as informações do valor
				VAL_confereSolução ( valor, &solucao) ;
				VAL_obtemNumeroCelulas (valor, &numCelulas) ;

				fprintf( fpOut, " (%d, %d) ",solucao, numCelulas);

				//Avança a lista pro próximo elemento
				retLis = LIS_PercorreLista ( pDesenho->listaValoresH[i], 1);
			} while ( retLis == LIS_CondRetOK );

			fprintf( fpOut, " Valores da linha %d\n", i);
		}
		
		/*Escreve a lista de valores vertical*/
		
		//Para todas as colunas
		for ( i = 0 ; i<colunas ; i++ ){
			
			//Vai pro inicio da lista
			LIS_IrInicioLista ( pDesenho->listaValoresV[i] );
			
			do{
				//Obtem o valor
				LIS_ObterValorCorrente ( pDesenho->listaValoresV[i], (void**)&valor);
				
				//Obtem as informações do valor
				VAL_confereSolução ( valor, &solucao) ;
				VAL_obtemNumeroCelulas (valor, &numCelulas) ;

				fprintf( fpOut, " (%d, %d) ",solucao, numCelulas);

				//Avança a lista pro próximo elemento
				retLis = LIS_PercorreLista ( pDesenho->listaValoresV[i], 1);
			} while ( retLis == LIS_CondRetOK );

			fprintf( fpOut, " Valores da coluna %d\n", i);
		}

		fclose( fpOut );	//Fecha o arquivo

		return DES_CondRetOK;
	}

/************************************************************************
*
*  Função: DES Carrega Desenho
*/



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
		CEL_tppCelula cel = NULL;

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