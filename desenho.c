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
		int i;

		//Se já existe um desenho
		if ( pDesenho != NULL )
			return DES_CondRetDesenhoExistente;

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
*  Função: DES Destroi Desenho
*/

	DES_tpCondRet DES_destroiDesenho( void ){
		
		int linhas, colunas;

		//Obtem as dimensões do desenho
		MAT_obterLinhas ( pDesenho->matriz, &linhas );
		MAT_obterColunas ( pDesenho->matriz, &colunas );

		//Destroi matriz
		MAT_destroiMatriz ( pDesenho->matriz );

		//Desaloca as listas dos vetores de listas de valores
		desalocaVetListas ( pDesenho->listaValoresH, linhas );
		desalocaVetListas ( pDesenho->listaValoresV, colunas );

		//Libera os vetores de listas e o desenho
		free (pDesenho->listaValoresV);
		free (pDesenho->listaValoresH);
		free (pDesenho);

		pDesenho = NULL;

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Função: DES Modifica Célula Correto
*/

	DES_tpCondRet DES_modificaCelulaCorreto ( int linha, int coluna, char estado ){
		
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
*  Função: DES Modifica Célula Atual
*/

	DES_tpCondRet DES_modificaCelulaAtual ( int linha, int coluna, char estado){
	
		CEL_tpCondRet retCel;
		MAT_tpCondRet retMat;
		CEL_tppCelula celula = NULL;
		
		retMat = MAT_percorreMatriz ( pDesenho->matriz, linha-1, coluna-1 );

		//Se o estado é marcada
		if ( estado == 'm' ){
		
			retCel = CEL_alteraEstadoAtual ( celula, 1 ) ;
			return DES_CondRetOK ;
		}
		//Se o estado é desmarcada
		else if ( estado == 'd' ){
			
			retCel = CEL_alteraEstadoAtual ( celula, 2 ) ;
			return DES_CondRetOK ;
		}

		else if ( estado == NULL ){
			
			retCel = CEL_alteraEstadoAtual ( celula, NULL ) ;
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
				
				//Se existir uma célula nula, os valores não podem ser computados corretamente
				else if ( estado == NULL ){
					return DES_CondRetCelulaNula;
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
*  Função: DES Confere Solução dos Valores
*/

	DES_tpCondRet DES_confereSolucaoValores ( void ){

		int i, j, linhas, colunas, count_cel = 0;
		int num_celulas, estado_atual, estado_correto;

		VAL_tppValor valor;
		CEL_tppCelula celula;

		LIS_tpCondRet retLis ;

		//Obtem as dimensões da matriz
		MAT_obterLinhas ( pDesenho->matriz, &linhas );
		MAT_obterColunas ( pDesenho->matriz, &colunas );

	/*Confere valores horizontais*/

		//Para cada linha
		for ( i=0 ; i<linhas ; i++ ){
		
			//Vai pro início da lista de valores da linha i
			LIS_IrInicioLista ( pDesenho->listaValoresH[i] );

		/*Descobre o número de células do valor atual (nova linha)*/

			//Obtem o valor corrente da lista
			LIS_ObterValorCorrente ( pDesenho->listaValoresH[i], (void**)&valor );

			//Obtem o número de células desse valor
			VAL_obtemNumeroCelulas ( valor, &num_celulas );

			//Para cada coluna
			for ( j=0 ; j<colunas ; j++ ){

		/*Descobre o número de células do valor atual (valor incorreto)*/		

				//Obtem o valor corrente da lista
				LIS_ObterValorCorrente ( pDesenho->listaValoresH[i], (void**)&valor );

				//Obtem o número de células desse valor
				VAL_obtemNumeroCelulas ( valor, &num_celulas );
		
		/*Obtem os estados da celula*/
				
				//Vai pra posição (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );

				//Obtem a célula da posição (i,j)
				MAT_obterValorCorrente ( pDesenho->matriz, &celula );

				//Obtem os estados da célula
				CEL_obtemEstadoAtual ( celula, &estado_atual );
				CEL_obtemEstadoCorreto ( celula, &estado_correto );

				/*Se a célula estiver marcada*/
				if ( estado_atual == 1 ){
					
					//Se ela estiver marcada corretamente
					if ( estado_atual == estado_correto ){
						
						//Contador de células marcadas +1
						count_cel++;
					}

					//Se não estiver marcada corretamente
					
					//Marca o valor atual como não resolvido
					VAL_defineSolucao ( valor, 0 );
			
					//Zera contador
					count_cel = 0;

					//Avança pro próximo valor
					retLis = LIS_PercorreLista ( pDesenho->listaValoresH[i], 1);
					//Se chegou ao fim da lista de valores dessa linha
					if ( retLis == LIS_CondRetFimLista ){
						break;		//Segue para a próxima linha
					}
				}

				/*Se a célula não estiver marcada*/
				else if ( estado_atual == 2 ){

					//Se quantidade de células marcadas é igual a do valor
					if ( count_cel == num_celulas ){
						
						//Define o valor como resolvido
						VAL_defineSolucao ( valor, 1 );

						//Zera contador
						count_cel = 0 ;

						//Avança pro próximo valor
						retLis = LIS_PercorreLista ( pDesenho->listaValoresH[i], 1);
						//Se chegou ao fim da lista de valores dessa linha
						if ( retLis == LIS_CondRetFimLista ){
							break;		//Segue para a próxima linha
						}
					}
					//Se count_cell != num_celulas, segue para a próxima célula
				}
			}
		}

	/*Confere valores verticais*/

		//Para cada coluna
		for ( j=0 ; j<colunas ; j++ ){
		
			//Vai pro início da lista de valores da linha i
			LIS_IrInicioLista ( pDesenho->listaValoresV[j] );

		/*Descobre o número de células do valor atual (nova coluna)*/

			//Obtem o valor corrente da lista
			LIS_ObterValorCorrente ( pDesenho->listaValoresV[j], (void**)&valor );

			//Obtem o número de células desse valor
			VAL_obtemNumeroCelulas ( valor, &num_celulas );

			//Para cada linha
			for ( i=0 ; i<linhas ; i++ ){

		/*Descobre o número de células do valor atual (valor incorreto)*/		

				//Obtem o valor corrente da lista
				LIS_ObterValorCorrente ( pDesenho->listaValoresH[j], (void**)&valor );

				//Obtem o número de células desse valor
				VAL_obtemNumeroCelulas ( valor, &num_celulas );
		
		/*Obtem os estados da celula*/
				
				//Vai pra posição (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );

				//Obtem a célula da posição (i,j)
				MAT_obterValorCorrente ( pDesenho->matriz, &celula );

				//Obtem os estados da célula
				CEL_obtemEstadoAtual ( celula, &estado_atual );
				CEL_obtemEstadoCorreto ( celula, &estado_correto );

				/*Se a célula estiver marcada*/
				if ( estado_atual == 1 ){
					
					//Se ela estiver marcada corretamente
					if ( estado_atual == estado_correto ){
						
						//Contador de células marcadas +1
						count_cel++;
					}

					//Se não estiver marcada corretamente
					
					//Marca o valor atual como não resolvido
					VAL_defineSolucao ( valor, 0 );

					//Zera contador
					count_cel = 0;

					//Avança pro próximo valor
					retLis = LIS_PercorreLista ( pDesenho->listaValoresV[j], 1);
					
					//Se chegou ao fim da lista de valores dessa linha
					if ( retLis == LIS_CondRetFimLista ){
						break;		//Segue para a próxima linha
					}
				}

				/*Se a célula não estiver marcada*/
				else if ( estado_atual == 2 ){

					//Se quantidade de células marcadas é igual a do valor
					if ( count_cel == num_celulas ){
						
						//Define o valor como resolvido
						VAL_defineSolucao ( valor, 1 );

						//Zera contador
						count_cel = 0 ;

						//Avança pro próximo valor
						retLis = LIS_PercorreLista ( pDesenho->listaValoresV[j], 1);
						//Se chegou ao fim da lista de valores dessa linha
						if ( retLis == LIS_CondRetFimLista ){
							break;		//Segue para a próxima linha
						}
					}
					//Se count_cell != num_celulas, segue para a próxima célula
				}
			}
		}

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Função: DES Salva Desenho
*/

	DES_tpCondRet DES_salvaDesenho (void){
		
		int i, j, linhas, colunas;
		int numCelulas, solucao, estado_atual, estado_correto;
		
		FILE* fpOut;
		VAL_tppValor valor = NULL ;
		CEL_tppCelula celula = NULL ;

		LIS_tpCondRet retLis;
		MAT_tpCondRet retMat;

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
			
			//Identifica a linha
			fprintf( fpOut, "Valores da linha %d ",i+1);

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

			fprintf( fpOut, "\n", i);	//Pula uma linha
		}
		
		/*Escreve a lista de valores vertical*/
		
		//Para todas as colunas
		for ( i = 0 ; i<colunas ; i++ ){
			
			//Identifica a linha
			fprintf( fpOut, "Valores da coluna %d ",i+1);

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

			fprintf( fpOut, "\n", i);	//Pula uma linha
		}

		/*Escreve as informações das células*/

		fprintf( fpOut, "\nInformações das células:\n");

		for ( i=0 ; i<linhas; i++ ){
			
			//Identifica a linha
			fprintf( fpOut, "Linha %d ", i+1) ;

			//Vai pro início da matriz
			MAT_percorreMatriz ( pDesenho->matriz, 0, 0);

			for ( j=0 ; j<colunas ; j++ ){
				
				//Obtem a célula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

				//Obtem as informações da célula
				CEL_obtemEstadoCorreto ( celula, &estado_correto );
				CEL_obtemEstadoAtual ( celula, &estado_atual );

				fprintf( fpOut, " (%d, %d) ", estado_atual, estado_correto );

				//Avança para o próximo elemento da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j);
			}

			fprintf( fpOut, "\n", i);	//Pula uma linha
		}
		
		fclose( fpOut );	//Fecha o arquivo

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Função: DES Carrega Desenho
*/

	DES_tpCondRet DES_carregaDesenho ( char* nome_desenho ){
	
		int i, j, count, linhas, colunas;
		int estado_atual, estado_correto, numCelulas, solucao;
		
		FILE* fpIn;
		VAL_tppValor valor = NULL ;

		VAL_tpCondRet retVal;
		LIS_tpCondRet retLis;

		//Abre o arquivo
		fpIn = fopen ( strcat(nome_desenho,".txt") , "r") ;		
		if ( fpIn == NULL )
			return DES_CondRetErroAberturaArquivo ;

		//Lê dimensões da matriz
		fscanf( fpIn, " %d x %d", &linhas, &colunas);

		//Se já existe um desenho aberto
		if ( pDesenho != NULL ){
			//Destroi desenho atual
			DES_destroiDesenho();
		}

		//Cria um novo desenho
		DES_criaDesenho ( linhas, colunas, nome_desenho);

		/*Carrega os valores nas listas horizontais*/

		//Para todas as linhas
		for ( i=1 ; i <= linhas ; i++ ){
			
			//Obtem o número da linha
			fscanf( fpIn, "Valores da linha %d", &count);

			//Obtem os dados do valor e o insere na lista correta
			while ( fscanf ( fpIn , " (%d, %d)", &solucao, &numCelulas) == 2 ){
				
				//Cria valor
				retVal = VAL_criaValor( &valor, numCelulas );
				if ( retVal == VAL_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}

				//Insere valor na lista correta
				retLis = LIS_InserirElementoApos ( pDesenho->listaValoresH[i], &valor);
				if ( retLis == LIS_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}
			}
		}

		/*Carrega os valores nas listas verticais*/

		//Para todas as colunas
		for ( i=1 ; i <= colunas ; i++ ){
			
			//Obtem o número da coluna
			fscanf( fpIn, "Valores da coluna %d", &count);

			//Obtem os dados do valor e o insere na lista correta
			while ( fscanf ( fpIn , " (%d, %d)", &solucao, &numCelulas) == 2 ){
				
				//Cria valor
				retVal = VAL_criaValor( &valor, numCelulas );
				if ( retVal == VAL_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}

				//Insere valor na lista correta
				retLis = LIS_InserirElementoApos ( pDesenho->listaValoresV[i], &valor);
				if ( retLis == LIS_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}
			}
		}

		/*Insere as informações das células*/

		fscanf( fpIn, " Informações das células:" );

		//Para cada linha
		for ( i=0 ; i<linhas ; i++ ){
			
			//Obtem o número da linha
			fscanf( fpIn, " Linha %d", &count );

			//Para cada coluna
			for ( j=0 ; j<colunas ; j++ ){
				
				//Obtem os dados da célula
				fscanf ( fpIn , " (%d, %d)", &estado_atual, &estado_correto) ;

				//Modifica o estado atual da célula (i,j)
				switch ( estado_atual ){

					case 1:
						DES_modificaCelulaAtual (i, j, 'm');
					case 2:
						DES_modificaCelulaAtual (i, j, 'd');
					default:
						DES_modificaCelulaAtual (i, j, NULL);
				}

				//Modifica o estado correto da célula (i,j)
				switch ( estado_correto ){

					case 1:
						DES_modificaCelulaCorreto (i, j, 'm');
					case 2:
						DES_modificaCelulaCorreto (i, j, 'd');
					default:
						DES_modificaCelulaCorreto (i, j, NULL);
				}
				
			}
		}

		fclose ( fpIn );

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Função: DES Confere Conclusão do Desenho
*/

	DES_tpCondRet DES_confereConclusaoDesenho ( void ){
	
		int i, j, linhas, colunas;
		int estado_atual, estado_correto;

		CEL_tppCelula celula;

		//Obtem as dimensões da matriz
		MAT_obterLinhas ( pDesenho->matriz, &linhas );
		MAT_obterColunas ( pDesenho->matriz, &colunas );

		//Para cada linha
		for ( i=0; i<linhas ; i++ ){
			
			//Para cada coluna
			for ( j=0 ; j<colunas ; j++ ){

		/*Obter os estados da célula (i,j)*/

				//Obtem a célula
				MAT_obterValorCorrente ( pDesenho->matriz, &celula );

				//Obtem os estados
				CEL_obtemEstadoAtual ( celula, &estado_atual) ;
				CEL_obtemEstadoCorreto ( celula, &estado_correto);

				//Se a célula está incorreta
				if ( estado_atual != estado_correto ){
					
					return DES_CondRetDesenhoIncorreto;
				}

				//Se a célula está correta, segue para a próxima
			}
		}

		return DES_CondRetDesenhoCorreto;
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