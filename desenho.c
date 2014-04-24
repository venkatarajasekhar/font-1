/***************************************************************************
*
*	$MCI M�dulo de implementa��o: M�dulo Desenho
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
*	$HA Hist�rico de evolu��o:
*		Vers�o	Autor	Data		Observa��es
*		1.0		vyc		11/04/2014	In�cio do Desenvolvimento
*		2.0		vyc		14/04/2014	Corre��es
*
***************************************************************************/


/********************* Diretivas de Pr�-Processamento *********************/

#include	<malloc.h>
#include	<stdio.h>
#include	<string.h>

#include	"celula.h"
#include	"valor.h"
#include	"lista.h"
#include	"matriz.h"

#define		DESENHO_OWN
#include	"desenho.h"
#undef		DESENHO_OWN



/****************** Declara��es encapsuladas pelo m�dulo *******************/

/*************************************************************************
*
*	$TC Tipo de dados: DES Descritor de um desenho
*
*	$ED Descri��o do tipo
*		Cont�m todos os dados do desenho
*
*************************************************************************/

	typedef struct DES_tagDesenho{
		
		MAT_tppMatriz matriz;
					/*Ponteiro para a matriz*/
		
		LIS_tppLista* listaValoresH ;
					/*Vetor de listas de valores horizontais*/
		
		LIS_tppLista* listaValoresV ;
					/*Vetor de listas de valores verticais*/

		int hints ;
					/*Armazena a quantidade de hints que o usu�rio pode usar*/

		char nome[50] ;
					/*Nome que identifica o desenho*/

	} DES_tpDesenho ;



/********************* Dados encapsulados no m�dulo *********************/

	static DES_tpDesenho* pDesenho = NULL ; 
				/*Ponteiro para um desenho*/


/************* Prot�tipos das fun��es encapuladas no m�dulo *************/

	static int initMatriz ( MAT_tppMatriz matriz, int linhas, int colunas );
	static void desalocaVetListas (LIS_tppLista* vetListas, int tam_vet );



/************** C�digo das fun��es exportadas pelo m�dulo ***************/

/************************************************************************
*
*  Fun��o: DES Cria Desenho 
*/

	DES_tpCondRet DES_criaDesenho ( int linhas, int colunas, char* nome ){
		
		MAT_tpCondRet retMat ;	//retorno das fun��es do m�dulo matriz
		LIS_tpCondRet retLis ;	//retorno das fun��es do m�dulo lista
		int retInitMat ;		//retorno da fun��o auxiliar initMatriz
		int i;

		//Se j� existe um desenho
		if ( pDesenho != NULL ){
			return DES_CondRetDesenhoExistente;
		}

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
			retLis = LIS_CriarLista ( &(pDesenho->listaValoresH[i]), (ExcluirValor) VAL_destroiValor ) ;
			//Se a aloca��o de uma lista deu errado
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
			retLis = LIS_CriarLista ( &(pDesenho->listaValoresV[i]), (ExcluirValor) VAL_destroiValor ) ;
			//Se a aloca��o de uma lista deu errado
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

		//Cria a matriz de c�lulas do desenho
		retMat = MAT_criaMatriz( &(pDesenho->matriz), linhas, colunas, (ExcluirValor) CEL_destroiCelula) ;
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

		//Insere as c�lulas nos elementos da matriz
		retInitMat = initMatriz ( pDesenho->matriz, linhas, colunas );
		//Se der erro, desaloca todas as estruturas
		if ( retInitMat != 0 ){

			//Desaloca as listas dos vetores de listas de valores
			desalocaVetListas ( pDesenho->listaValoresH, linhas) ;
			desalocaVetListas ( pDesenho->listaValoresV, colunas) ;
			
			//Libera os vetores de listas, a matriz e o desenho
			free (pDesenho->listaValoresH);
			free (pDesenho->listaValoresV);
			MAT_destroiMatriz ( &pDesenho->matriz );
			free (pDesenho);
			
			return DES_CondRetFaltouMemoria;
		}

		//Atribui o nome do desenho
		strcpy (pDesenho->nome, nome) ;

		//Atribui a quantidade de hints
		pDesenho->hints = 10;

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Fun��o: DES Destroi Desenho
*/

	DES_tpCondRet DES_destroiDesenho( void ){
		
		int linhas, colunas;

		//Obtem as dimens�es do desenho
		MAT_obterLinhas ( pDesenho->matriz, &linhas );
		MAT_obterColunas ( pDesenho->matriz, &colunas );

		//Desaloca as listas dos vetores de listas de valores
		desalocaVetListas ( pDesenho->listaValoresH, linhas );
		desalocaVetListas ( pDesenho->listaValoresV, colunas );

		//Libera os vetores de listas
		free (pDesenho->listaValoresV);
		free (pDesenho->listaValoresH);

		//Destroi matriz
		MAT_destroiMatriz ( &pDesenho->matriz );
		
		//Libera o desenho
		free (pDesenho);

		pDesenho = NULL;

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Fun��o: DES Modifica C�lula Correto
*/

	DES_tpCondRet DES_modificaCelulaCorreto ( int linha, int coluna, char estado ){
		
		CEL_tppCelula celula = NULL;
		
		/* Obtem a c�lula da posi��o (linha,coluna) */
		MAT_percorreMatriz ( pDesenho->matriz, linha-1, coluna-1 );
		MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

		//Se o estado � marcada
		if ( estado == 'm' ){
		
			CEL_alteraEstadoCorreto ( celula, 1 ) ;
			return DES_CondRetOK ;
		}
		//Se o estado � desmarcada
		else if ( estado == 'd' ){
			
			CEL_alteraEstadoCorreto ( celula, 2 ) ;
			return DES_CondRetOK ;
		}

		else if ( estado == 'n' ){
			
			CEL_alteraEstadoCorreto ( celula, 0 ) ;
			return DES_CondRetOK ;
		}
		else
			return DES_CondRetEstadoInvalido;
	}


/************************************************************************
*
*  Fun��o: DES Modifica C�lula Atual
*/

	DES_tpCondRet DES_modificaCelulaAtual ( int linha, int coluna, char estado){
	
		CEL_tppCelula celula = NULL;
		
		/* Obtem a c�lula da posi��o (linha,coluna) */
		MAT_percorreMatriz ( pDesenho->matriz, linha-1, coluna-1 );
		MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

		//Se o estado � marcada
		if ( estado == 'm' ){
		
			CEL_alteraEstadoAtual ( celula, 1 ) ;
			return DES_CondRetOK ;
		}
		//Se o estado � desmarcada
		else if ( estado == 'd' ){
			
			CEL_alteraEstadoAtual ( celula, 2 ) ;
			return DES_CondRetOK ;
		}

		else if ( estado == 'n' ){
			
			CEL_alteraEstadoAtual ( celula, 0 ) ;
			return DES_CondRetOK ;
		}
		else
			return DES_CondRetEstadoInvalido;
	}


/************************************************************************
*
*  Fun��o: DES Calcula Valores
*/

	DES_tpCondRet DES_calculaValores ( void ){

		int i, j, k, cont_marcadas = 0 ;
		int linhas, colunas ;
		int estado;					//Armazena o estado correto da c�lula
		
		//Ponteiros para os tipos utilizados
		CEL_tppCelula celula = NULL ;
		VAL_tppValor valor = NULL ;
		
		//Condi��es de retorno
		VAL_tpCondRet retVal ;
		LIS_tpCondRet retLis ;

		//Obtem as dimens�es da matriz
		MAT_obterLinhas ( pDesenho->matriz, &linhas );
		MAT_obterColunas ( pDesenho->matriz, &colunas );
		
		/*Calcula valores horizontais*/
		
		//Para cada linha
		for ( i=0 ; i<linhas ; i++ ){
			
			//Para cada coluna
			for ( j=0 ; j<colunas ; j++ ){
				
				//Na posi��o (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );
				
				//Obtem a c�lula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
				
				//Obtem o estado correto da c�lula
				CEL_obtemEstadoCorreto ( celula, &estado ) ;
				
				//Se estado for marcada
				if ( estado == 1 ){
					
					//N�mero de c�lulas marcadas recebe +1
					cont_marcadas++;
				}

				else if ( (estado == 2) && (cont_marcadas > 0) ){
					
					//Cria um valor
					retVal = VAL_criaValor ( &valor, cont_marcadas );
							
					//Se der erro na aloca��o
					if ( retVal == VAL_CondRetFaltouMemoria ){
						return DES_CondRetFaltouMemoria;
					}
							
					//Sen�o, insere esse valor no final da linha atual
					retLis = LIS_InserirElementoApos ( pDesenho->listaValoresH[i], (void*)valor );
							
					//Se der erro na aloca��o
					if ( retLis == LIS_CondRetFaltouMemoria ){
						return DES_CondRetFaltouMemoria;
					}

					cont_marcadas = 0;	//zera o contador
				}//end else

				//Se a �ltima c�lula da linha estiver marcada
				if ( (j == colunas-1) && (cont_marcadas > 0)){
				
					//Cria um valor
					retVal = VAL_criaValor ( &valor, cont_marcadas );
							
					//Se der erro na aloca��o
					if ( retVal == VAL_CondRetFaltouMemoria ){
						return DES_CondRetFaltouMemoria;
					}
							
					//Sen�o, insere esse valor no final da linha atual
					retLis = LIS_InserirElementoApos ( pDesenho->listaValoresH[i], (void*)valor );
							
					//Se der erro na aloca��o
					if ( retLis == LIS_CondRetFaltouMemoria ){
						return DES_CondRetFaltouMemoria;
					}

					cont_marcadas = 0;	//zera o contador
				}
			}// end for j
		}//end for i
				

		/*Calcula valores verticais*/

		//Para cada coluna
		for ( j=0 ; j<colunas ; j++ ){
			
			//Para cada linhas
			for ( i=0 ; i<linhas ; i++ ){
				
				//Na posi��o (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );
				
				//Obtem a c�lula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
				
				//Obtem o estado correto da c�lula
				CEL_obtemEstadoCorreto ( celula, &estado ) ;
				
				//Se estado for marcada
				if ( estado == 1 ){
					
					//N�mero de c�lulas marcadas recebe +1
					cont_marcadas++;
				}

				else if ( (estado == 2) && (cont_marcadas > 0) ){
					
					//Cria um valor
					retVal = VAL_criaValor ( &valor, cont_marcadas );
							
					//Se der erro na aloca��o
					if ( retVal == VAL_CondRetFaltouMemoria ){
						return DES_CondRetFaltouMemoria;
					}
							
					//Sen�o, insere esse valor no final da linha atual
					retLis = LIS_InserirElementoApos ( pDesenho->listaValoresV[j], (void*)valor );
							
					//Se der erro na aloca��o
					if ( retLis == LIS_CondRetFaltouMemoria ){
						return DES_CondRetFaltouMemoria;
					}

					cont_marcadas = 0;	//zera o contador
				}//end else

				//Se a �ltima c�lula da coluna estiver marcada
				if ( (i == linhas-1) && (cont_marcadas > 0) ){
				
					//Cria um valor
					retVal = VAL_criaValor ( &valor, cont_marcadas );
							
					//Se der erro na aloca��o
					if ( retVal == VAL_CondRetFaltouMemoria ){
						return DES_CondRetFaltouMemoria;
					}
							
					//Sen�o, insere esse valor no final da linha atual
					retLis = LIS_InserirElementoApos ( pDesenho->listaValoresV[j], (void*)valor );
							
					//Se der erro na aloca��o
					if ( retLis == LIS_CondRetFaltouMemoria ){
						return DES_CondRetFaltouMemoria;
					}

					cont_marcadas = 0;	//zera o contador
				}//end else
			}// end for j
		}//end for i

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Fun��o: DES Confere Solu��o dos Valores
*/

	DES_tpCondRet DES_confereSolucaoValores ( void ){

		int i, j, linhas, colunas, count_cel = 0;
		int num_celulas, estado_atual, estado_correto;

		VAL_tppValor valor;
		CEL_tppCelula celula;

		LIS_tpCondRet retLis ;

		//Obtem as dimens�es da matriz
		MAT_obterLinhas ( pDesenho->matriz, &linhas );
		MAT_obterColunas ( pDesenho->matriz, &colunas );

	/*Confere valores horizontais*/

		//Para cada linha
		for ( i=0 ; i<linhas ; i++ ){
		
			//Vai pro in�cio da lista de valores da linha i
			LIS_IrInicioLista ( pDesenho->listaValoresH[i] );

			//Para cada coluna
			for ( j=0 ; j<colunas ; j++ ){

			/*Descobre o n�mero de c�lulas do valor atual*/		

				//Obtem o valor corrente da lista
				LIS_ObterValorCorrente ( pDesenho->listaValoresH[i], (void**)&valor );

				//Obtem o n�mero de c�lulas desse valor
				VAL_obtemNumeroCelulas ( valor, &num_celulas );
		
			/*Obtem os estados da celula*/
				
				//Vai pra posi��o (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );

				//Obtem a c�lula da posi��o (i,j)
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );

				//Obtem os estados da c�lula
				CEL_obtemEstadoAtual ( celula, &estado_atual );
				CEL_obtemEstadoCorreto ( celula, &estado_correto );

			/*Se a c�lula estiver marcada*/
				if ( estado_atual == 1 ){
					
					//Se ela estiver marcada corretamente
					if ( estado_atual == estado_correto ){
						//Contador de c�lulas marcadas +1
						count_cel++;
						//Se o valor j� foi resolvido
						if ( count_cel == num_celulas ){
							//Marca o valor como resolvido
							VAL_defineSolucao (valor, 1);
							//Zera contador
							count_cel = 0;
							//Avan�a para o pr�ximo valor da lista
							retLis = LIS_PercorreLista ( pDesenho->listaValoresH[i], 1);
							//Se chegou ao fim da lista
							if ( retLis == LIS_CondRetFimLista )
								break;	//Avan�a para a pr�xima linha
						}
					}
					//Se ela n�o estiver marcada corretamente
					else{

						//Marca o valor como n�o resolvido
						VAL_defineSolucao (valor, 0);
						//Zera contador
						count_cel = 0;
						//Avan�a para o pr�ximo valor da lista
						retLis = LIS_PercorreLista ( pDesenho->listaValoresH[i], 1);
						//Se chegou ao fim da lista
						if ( retLis == LIS_CondRetFimLista )
							break;	//Avan�a para a pr�xima linha
					}//end else
				}//end 1� if

			/*Se a c�lula n�o estiver marcada, segue para a pr�xima c�lula*/

			}// end for j
		}// end for i

	/*Confere valores verticais*/

		//Para cada coluna
		for ( j=0 ; j<colunas ; j++){
		
			//Vai pro in�cio da lista de valores da linha i
			LIS_IrInicioLista ( pDesenho->listaValoresV[j] );

			//Para cada linha
			for ( i=0 ; i<linhas ; i++ ){

		/*Descobre o n�mero de c�lulas do valor atual*/		

				//Obtem o valor corrente da lista
				LIS_ObterValorCorrente ( pDesenho->listaValoresV[j], (void**)&valor );

				//Obtem o n�mero de c�lulas desse valor
				VAL_obtemNumeroCelulas ( valor, &num_celulas );
		
		/*Obtem os estados da celula*/
				
				//Vai pra posi��o (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );

				//Obtem a c�lula da posi��o (i,j)
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );

				//Obtem os estados da c�lula
				CEL_obtemEstadoAtual ( celula, &estado_atual );
				CEL_obtemEstadoCorreto ( celula, &estado_correto );

		/*Se a c�lula estiver marcada*/
				if ( estado_atual == 1 ){
					
					//Se ela estiver marcada corretamente
					if ( estado_atual == estado_correto ){
						//Contador de c�lulas marcadas +1
						count_cel++;
						//Se o valor j� foi resolvido
						if ( count_cel == num_celulas ){
							//Marca o valor como resolvido
							VAL_defineSolucao (valor, 1);
							//Zera contador
							count_cel = 0;
							//Avan�a para o pr�ximo valor da lista
							retLis = LIS_PercorreLista ( pDesenho->listaValoresV[j], 1);
							//Se chegou ao fim da lista
							if ( retLis == LIS_CondRetFimLista )
								break;	//Avan�a para a pr�xima linha
						}
					}
					//Se ela n�o estiver marcada corretamente
					else{

						//Marca o valor como n�o resolvido
						VAL_defineSolucao (valor, 0);
						//Zera contador
						count_cel = 0;
						//Avan�a para o pr�ximo valor da lista
						retLis = LIS_PercorreLista ( pDesenho->listaValoresV[j], 1);
						//Se chegou ao fim da lista
						if ( retLis == LIS_CondRetFimLista )
							break;	//Avan�a para a pr�xima linha
					}//end else
				}//end 1� if

		/*Se a c�lula n�o estiver marcada, segue para a pr�xima c�lula*/

			}// end for j
		}// end for i
		

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Fun��o: DES Salva Desenho
*/

	DES_tpCondRet DES_salvaDesenho (void){
		
		int i, j, linhas, colunas;
		int estado_atual = -1, estado_correto = -1;
		
		FILE* fpOut;
		VAL_tppValor valor = NULL ;
		CEL_tppCelula celula = NULL ;

		LIS_tpCondRet retLis;

		/*Formata nome do arquivo*/
		char nomeArquivo[54];
		strcpy (nomeArquivo, pDesenho->nome);
		strcat (nomeArquivo, ".txt");

		fpOut = fopen ( nomeArquivo, "wb");
		if ( fpOut == NULL )
			return DES_CondRetErroAberturaArquivo ;

		/*Escreve a dimens�o da matriz*/
		
		//Obtem as dimens�es da matriz
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
				int numCelulas = -1, solucao = -1;
				//Obtem o valor
				LIS_ObterValorCorrente ( pDesenho->listaValoresH[i], (void**)&valor);
				
				//Obtem as informa��es do valor
				VAL_confereSolu��o ( valor, &solucao) ;
				VAL_obtemNumeroCelulas (valor, &numCelulas) ;

				fprintf( fpOut, " (%d, %d) ",solucao, numCelulas);

				//Avan�a a lista pro pr�ximo elemento
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
				int numCelulas = -1, solucao = -1;
				//Obtem o valor
				LIS_ObterValorCorrente ( pDesenho->listaValoresV[i], (void**)&valor);
				
				//Obtem as informa��es do valor
				VAL_confereSolu��o ( valor, &solucao) ;
				VAL_obtemNumeroCelulas (valor, &numCelulas) ;

				fprintf( fpOut, " (%d, %d) ",solucao, numCelulas);

				//Avan�a a lista pro pr�ximo elemento
				retLis = LIS_PercorreLista ( pDesenho->listaValoresV[i], 1);
			} while ( retLis == LIS_CondRetOK );

			fprintf( fpOut, "\n", i);	//Pula uma linha
		}

		/*Escreve as informa��es das c�lulas*/

		fprintf( fpOut, "\nInforma��es das c�lulas:\n");

		//Vai pro in�cio da matriz
		MAT_percorreMatriz ( pDesenho->matriz, 0, 0);
		
		i = j = 0;
		while ( i<linhas ){
			
			//Identifica a linha
			fprintf( fpOut, "Linha %d ", i+1) ;

			while ( j<colunas ){
				
				//Obtem a c�lula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

				//Obtem as informa��es da c�lula
				CEL_obtemEstadoCorreto ( celula, &estado_correto );
				CEL_obtemEstadoAtual ( celula, &estado_atual );

				fprintf( fpOut, " (%d, %d) ", estado_atual, estado_correto );

				j++;
				//Avan�a para o pr�ximo elemento da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j);
			}

			j=0;
			i++;
			//Avan�a para o pr�ximo elemento da matriz
			MAT_percorreMatriz ( pDesenho->matriz, i, j);
			
			fprintf( fpOut, "\n", i);	//Pula uma linha
		}

		/*Escreve a quantidade de hints*/
		fprintf( fpOut, "Hints: %d\n", pDesenho->hints );
		
		fclose( fpOut );	//Fecha o arquivo

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Fun��o: DES Carrega Desenho
*/

	DES_tpCondRet DES_carregaDesenho ( char* nome_desenho ){
	
		int i, j, count, linhas, colunas;
		int estado_atual, estado_correto, numCelulas, solucao;
		
		FILE* fpIn;
		VAL_tppValor valor = NULL ;

		VAL_tpCondRet retVal;
		LIS_tpCondRet retLis;

		/*Formata nome do arquivo*/
		char nomeArquivo[54];
		strcpy (nomeArquivo, nome_desenho);
		strcat (nomeArquivo, ".txt");

		//Abre o arquivo
		fpIn = fopen ( nomeArquivo , "rb") ;		
		if ( fpIn == NULL )
			return DES_CondRetErroAberturaArquivo ;

		//Se j� existe um desenho aberto
		if ( pDesenho != NULL ){
			//Destroi desenho atual
			DES_destroiDesenho();
		}

		//L� dimens�es da matriz
		fscanf( fpIn, " %d x %d", &linhas, &colunas);

		//Cria um novo desenho
		DES_criaDesenho ( linhas, colunas, nome_desenho);
		

		/*Carrega os valores nas listas horizontais*/

		//Para todas as linhas
		for ( i=0 ; i < linhas ; i++ ){
			
			//Obtem o n�mero da linha
			fscanf( fpIn, " Valores da linha %d", &count);

			//Obtem os dados do valor e o insere na lista correta
			while ( fscanf ( fpIn , " (%d, %d)", &solucao, &numCelulas) == 2 ){

				//Cria valor
				retVal = VAL_criaValor( &valor, numCelulas );
				if ( retVal == VAL_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}

				//Inicializa valor
				VAL_defineSolucao ( valor, solucao );

				//Insere valor na lista correta
				retLis = LIS_InserirElementoApos ( pDesenho->listaValoresH[i], (void*)&valor);
				if ( retLis == LIS_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}
			}
		}

		/*Carrega os valores nas listas verticais*/

		//Para todas as colunas
		for ( j=0 ; j < colunas ; j++ ){
			
			//Obtem o n�mero da coluna
			fscanf( fpIn, " Valores da coluna %d", &count);

			//Obtem os dados do valor e o insere na lista correta
			while ( fscanf ( fpIn , " (%d, %d)", &solucao, &numCelulas) == 2 ){
				
				//Cria valor
				retVal = VAL_criaValor( &valor, numCelulas );
				if ( retVal == VAL_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}

				//Inicializa valor
				VAL_defineSolucao ( valor, solucao );

				//Insere valor na lista correta
				retLis = LIS_InserirElementoApos ( pDesenho->listaValoresV[j], (void*)&valor);
				if ( retLis == LIS_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}
			}
		}

		/*Insere as informa��es das c�lulas*/

		fscanf( fpIn, " Informa��es das c�lulas:" );

		//Para cada linha
		for ( i=0 ; i<linhas ; i++ ){
			
			//Obtem o n�mero da linha
			fscanf( fpIn, " Linha %d", &count );

			//Para cada coluna
			for ( j=0 ; j<colunas ; j++ ){

				//Obtem os dados da c�lula
				fscanf ( fpIn , " (%d, %d)", &estado_atual, &estado_correto) ;

				//Modifica o estado atual da c�lula (i,j)	
				switch ( estado_atual ){

					case 1:{
						CEL_tppCelula celula;

						//Obtem a c�lula
						MAT_percorreMatriz ( pDesenho->matriz, i, j );
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

						//Altera estado atual
						CEL_alteraEstadoAtual ( celula, 1 );
						break;
					}
					case 2:{
						CEL_tppCelula celula;

						//Obtem a c�lula
						MAT_percorreMatriz ( pDesenho->matriz, i, j );
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

						//Altera estado atual
						CEL_alteraEstadoAtual ( celula, 2 );
						break;
					}
					case 0:{
						CEL_tppCelula celula;

						//Obtem a c�lula
						MAT_percorreMatriz ( pDesenho->matriz, i, j );
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

						//Altera estado atual
						CEL_alteraEstadoAtual ( celula, 0 );
						break;
					}
				}

				//Modifica o estado correto da c�lula (i,j)
				switch ( estado_correto ){

					case 1:{
						CEL_tppCelula celula;

						//Obtem a c�lula
						MAT_percorreMatriz ( pDesenho->matriz, i, j );
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

						//Altera estado correto
						CEL_alteraEstadoCorreto ( celula, 1 );
						break;
					}
					case 2:{
						CEL_tppCelula celula;

						//Obtem a c�lula
						MAT_percorreMatriz ( pDesenho->matriz, i, j );
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

						//Altera estado correto
						CEL_alteraEstadoCorreto ( celula, 2 );
						break;
					}
					case 0:{
						CEL_tppCelula celula;

						//Obtem a c�lula
						MAT_percorreMatriz ( pDesenho->matriz, i, j );
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

						//Altera estado correto
						CEL_alteraEstadoCorreto ( celula, 0 );
						break;
					}
				}
				
			}//end for j
		}//end for i

		/*Insere a quantidade de hints*/
		fscanf ( fpIn, " Hints: %d", &(pDesenho->hints) );

		fclose ( fpIn );

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Fun��o: DES Confere Conclus�o do Desenho
*/

	DES_tpCondRet DES_confereConclusaoDesenho ( void ){
	
		int i, j, linhas, colunas;
		int estado_atual, estado_correto;

		CEL_tppCelula celula;

		//Obtem as dimens�es da matriz
		MAT_obterLinhas ( pDesenho->matriz, &linhas );
		MAT_obterColunas ( pDesenho->matriz, &colunas );

		//Para cada linha
		for ( i=0; i<linhas ; i++ ){
			
			//Para cada coluna
			for ( j=0 ; j<colunas ; j++ ){

		/*Obter os estados da c�lula (i,j)*/

				MAT_percorreMatriz ( pDesenho->matriz, i, j );

				//Obtem a c�lula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );

				//Obtem os estados
				CEL_obtemEstadoAtual ( celula, &estado_atual) ;
				CEL_obtemEstadoCorreto ( celula, &estado_correto);

				//Se a c�lula est� incorreta
				if ( estado_atual != estado_correto ){
					
					return DES_CondRetDesenhoIncorreto;
				}

				//Se a c�lula est� correta, segue para a pr�xima
			}
		}

		return DES_CondRetDesenhoCorreto;
	}


/************************************************************************
*
*  Fun��o: DES Usa Dica
*/

	DES_tpCondRet DES_usaDica( void ){
		
		int i, j, linhas, colunas;
		int estado_atual, estado_correto;

		CEL_tppCelula celula = NULL;

		//Se n�o possui mais dicas
		if ( pDesenho->hints == 0 ){
			return DES_CondRetSemHints;
		}
		
		//Obtem as dimens�es da matriz
		MAT_obterLinhas ( pDesenho->matriz, &linhas );
		MAT_obterColunas ( pDesenho->matriz, &colunas );
		
		//Procura por c�lula a ser pintada
		for ( i=0 ; i <linhas ; i++ ){

			for ( j=0 ; j<colunas ; j++ ){
				
				/*Obter celula na posi��o (i,j)*/
				MAT_percorreMatriz ( pDesenho->matriz, i, j);
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
				
				/*Obter informa��es da c�lula*/
				CEL_obtemEstadoAtual ( celula, &estado_atual );
				CEL_obtemEstadoCorreto ( celula, &estado_correto );

				//Se a celula n�o est� marcada corretamente
				if ( (estado_atual != estado_correto) && (estado_correto == 1) ){

					//Marca a c�lula
					CEL_alteraEstadoAtual ( celula, 1 );
					//Decrementa as dicas
					(pDesenho->hints)--;
					
					return DES_CondRetOK;
				}
			}
		} 

		return DES_CondRetDesenhoCorreto;
	}



/************* C�digo das fun��es encapuladas no m�dulo *************/

/********************************************************************
*
*  FC Fun��o: DES - Inicializa Matriz
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
				MAT_percorreMatriz ( pDesenho->matriz, i, j );
				//Cria a c�lula
				retCel = CEL_criaCelula ( &cel );
				if ( retCel == CEL_CondRetFaltouMemoria )
					return -1;
				//Insere a c�lula no elemento (i,j) da matriz
				MAT_insereDado ( pDesenho->matriz, (void*)cel );
			}
		}
		
		return 0;
	}


/********************************************************************
*
*  FC Fun��o: DES - Desaloca Vetor de Listas
*
********************************************************************/
	
	static void desalocaVetListas (LIS_tppLista* vetListas, int tam_vet ){
		
		int i;

		for ( i=0 ; i < tam_vet ; i++ )
			LIS_DestruirLista ( vetListas[i] );
	}



/************ Fim do m�dulo de implementa��o: M�dulo Desenho ***********/