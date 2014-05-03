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
*		3.0		vyc		27/04/2014	Otimiza��o
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
		
		LIS_tppLista listaValoresH ;
					/*Lista de listas de valores horizontais*/
		
		LIS_tppLista listaValoresV ;
					/*Lista de listas de valores verticais*/
		
		int linhas;
					/*Quantidade de linhas do desenho*/

		int colunas;
					/*Quantidade de colunas do desenho*/				

		int hints ;
					/*Armazena a quantidade de hints que o usu�rio pode usar*/

		char nome[50] ;
					/*Nome que identifica o desenho*/

	} DES_tpDesenho ;



/********************* Dados encapsulados no m�dulo *********************/

	static DES_tpDesenho* pDesenho = NULL ; 
				/*Ponteiro para um desenho*/


/************* Prot�tipos das fun��es encapuladas no m�dulo *************/

	static MAT_tpCondRet initMatriz ( MAT_tppMatriz matriz, int linhas, int colunas );
	static LIS_tpCondRet initLista (LIS_tppLista lista, int tam_lista );
	static void zeraListaValores( LIS_tppLista lista_de_listas );
	static void imprimeEstado ( int estado );
	static int obtemEstadoAtualCelula ( int linha, int coluna );
	static int obtemEstadoCorretoCelula ( int linha, int coluna );



/************** C�digo das fun��es exportadas pelo m�dulo ***************/

/************************************************************************
*
*  Fun��o: DES Cria Desenho 
*/

	DES_tpCondRet DES_criaDesenho ( int linhas, int colunas, char* nome ){
		
		MAT_tpCondRet retMat ;	//retorno das fun��es do m�dulo matriz
		LIS_tpCondRet retLis ;	//retorno das fun��es do m�dulo lista
		int i;

		//Se j� existe um desenho
		if ( pDesenho != NULL ){
			return DES_CondRetDesenhoExistente;
		}

	/*Aloca desenho*/
		pDesenho = (DES_tpDesenho*) malloc ( sizeof(DES_tpDesenho) ) ;
		if ( pDesenho == NULL )
			return DES_CondRetFaltouMemoria ;
		
	/*Cria lista de listas horizontais*/
		retLis = LIS_CriarLista ( &pDesenho->listaValoresH, (ExcluirValor) LIS_DestruirLista); 
		if ( retLis == LIS_CondRetFaltouMemoria ){
			free ( pDesenho );
			return DES_CondRetFaltouMemoria ;
		}
		
	/*Cria lista de listas verticais*/
		retLis = LIS_CriarLista ( &pDesenho->listaValoresV, (ExcluirValor) LIS_DestruirLista); 
		if ( retLis == LIS_CondRetFaltouMemoria ){
			LIS_DestruirLista ( pDesenho->listaValoresH );
			free ( pDesenho );
			return DES_CondRetFaltouMemoria ;
		}

	/*Inicializa a lista de listas de valores horizontais*/
		retLis = initLista ( pDesenho->listaValoresH, linhas );
		if ( retLis == LIS_CondRetFaltouMemoria ){
		
			LIS_DestruirLista ( pDesenho->listaValoresH );
			LIS_DestruirLista ( pDesenho->listaValoresV );
			free ( pDesenho );
		}

	/*Inicializa a lista de listas de valores verticais*/
		retLis = initLista ( pDesenho->listaValoresV, colunas );
		if ( retLis == LIS_CondRetFaltouMemoria ){
		
			LIS_DestruirLista ( pDesenho->listaValoresH );
			LIS_DestruirLista ( pDesenho->listaValoresV );
			free ( pDesenho );
		}

	/*Cria a matriz de c�lulas do desenho*/
		retMat = MAT_criaMatriz( &pDesenho->matriz, linhas, colunas, (ExcluirValor) CEL_destroiCelula) ;
		//Se der erro, desaloca todas as estruturas
		if ( retMat == MAT_CondRetFaltouMemoria ){
			
			//Destroi as listas de listas e o desenho
			LIS_DestruirLista ( pDesenho->listaValoresH );
			LIS_DestruirLista ( pDesenho->listaValoresV );
			free (pDesenho);
			
			return DES_CondRetFaltouMemoria;
		}

		//Insere as c�lulas nos elementos da matriz
		retMat = initMatriz ( pDesenho->matriz, linhas, colunas );
		//Se der erro, desaloca todas as estruturas
		if ( retMat == MAT_CondRetFaltouMemoria ){

			//Destroi as listas de listas e o desenho
			LIS_DestruirLista (pDesenho->listaValoresH);
			LIS_DestruirLista (pDesenho->listaValoresV);
			MAT_destroiMatriz ( &pDesenho->matriz );
			free (pDesenho);
			
			return DES_CondRetFaltouMemoria;
		}

		//Atribui o n�mero de linhas e colunas do desenho
		pDesenho->linhas = linhas;
		pDesenho->colunas = colunas;

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
		
		//Destroi as listas de listas
		LIS_DestruirLista ( pDesenho->listaValoresH );
		LIS_DestruirLista ( pDesenho->listaValoresV );

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

		int i, j, k, cont_marcadas = 0 , cont_valores = 0;
		int estado;					//Armazena o estado correto da c�lula
		
		//Ponteiros para os tipos utilizados
		CEL_tppCelula celula = NULL ;
		VAL_tppValor valor = NULL ;
		LIS_tppLista LIS_linha_atual = NULL;
		
		//Condi��es de retorno
		VAL_tpCondRet retVal ;
		LIS_tpCondRet retLis ;
		
		/*Calcula valores horizontais*/
		
		zeraListaValores( pDesenho->listaValoresH );	//Caso os valores j� tenham sido calculados
		LIS_IrInicioLista ( pDesenho->listaValoresH );

		//Para cada linha
		for ( i=0 ; i < pDesenho->linhas ; i++ ){
			
			//Obtem a lista da linha atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresH, (void**)&LIS_linha_atual);
			LIS_IrInicioLista ( LIS_linha_atual );

			//Para cada coluna
			for ( j=0 ; j < pDesenho->colunas ; j++ ){
				
				//Na posi��o (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );
				
				//Obtem a c�lula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
				
				//Obtem o estado correto da c�lula
				CEL_obtemEstadoCorreto ( celula, &estado ) ;
				
				//Se estado for nula
				if ( estado == 0 ){
					return DES_CondRetCelulaNula;
				}

				//Sen�o, se o estado for marcada
				else if ( estado == 1 ){
					
					//N�mero de c�lulas marcadas recebe +1
					cont_marcadas++;

					//Se for a �ltima c�lula da linha
					if ( j == pDesenho->colunas - 1  ){
						
						//Cria um valor
						retVal = VAL_criaValor ( &valor, cont_marcadas );
							
						//Se der erro na aloca��o
						if ( retVal == VAL_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}
							
						//Insere esse valor no final da linha atual
						retLis = LIS_InserirElementoApos ( LIS_linha_atual, (void*)valor );
							
						//Se der erro na aloca��o
						if ( retLis == LIS_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}

						cont_marcadas = 0;	//Zera o contador de c�lulas marcadas
					}
				}

				//Sen�o, se o estado for desmarcada
				else if ( estado == 2 ){
					
					//Se a c�lula anterior estiver marcada
					if ( cont_marcadas > 0 ) {

						//Cria um valor
						retVal = VAL_criaValor ( &valor, cont_marcadas );
							
						//Se der erro na aloca��o
						if ( retVal == VAL_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}
							
						//Insere esse valor no final da linha atual
						retLis = LIS_InserirElementoApos ( LIS_linha_atual, (void*)valor );
							
						//Se der erro na aloca��o
						if ( retLis == LIS_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}

						cont_marcadas = 0;	//Zera o contador de c�lulas marcadas
						cont_valores++;		//Incrementa o contador de valores
					}

					//Se chegou na �ltima c�lula e nenhum valor foi criado
					else if ( (j == pDesenho->colunas -1) && (cont_valores == 0) ){
						return DES_CondRetLinhaSemValor;
					}
				}
			}// end for j
			
			//Avan�a para a lista da pr�xima linha
			LIS_PercorreLista ( pDesenho->listaValoresH, 1);
			cont_valores = 0; //Zera o contador de valores
		}//end for i
				

		/*Calcula valores verticais*/
		
		zeraListaValores( pDesenho->listaValoresV );	//Caso os valores j� tenham sido calculados
		LIS_IrInicioLista ( pDesenho->listaValoresV );

		//Para cada coluna
		for ( j=0 ; j < pDesenho->colunas ; j++ ){
			
			//Obtem a lista da coluna atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresV, (void**)&LIS_linha_atual);
			LIS_IrInicioLista ( LIS_linha_atual );

			//Para cada linha
			for ( i=0 ; i < pDesenho->linhas ; i++ ){
				
				//Na posi��o (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );
				
				//Obtem a c�lula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
				
				//Obtem o estado correto da c�lula
				CEL_obtemEstadoCorreto ( celula, &estado ) ;
				
				//Se estado for nula
				if ( estado == 0 ){
					return DES_CondRetCelulaNula;
				}

				//Sen�o, se estado for marcada
				else if ( estado == 1 ){
					
					//N�mero de c�lulas marcadas recebe +1
					cont_marcadas++;

					//Se for a �ltima c�lula da coluna
					if ( i == pDesenho->linhas - 1  ){
						
						//Cria um valor
						retVal = VAL_criaValor ( &valor, cont_marcadas );
							
						//Se der erro na aloca��o
						if ( retVal == VAL_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}
							
						//Insere esse valor no final da coluna atual
						retLis = LIS_InserirElementoApos ( LIS_linha_atual, (void*)valor );
							
						//Se der erro na aloca��o
						if ( retLis == LIS_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}

						cont_marcadas = 0;	//Zera o contador de c�lulas marcadas
					}
				}

				//Sen�o, se o estado for desmarcada
				else if ( estado == 2 ){
					
					//Se a c�lula anterior estiver marcada
					if ( cont_marcadas > 0 ) {

						//Cria um valor
						retVal = VAL_criaValor ( &valor, cont_marcadas );
							
						//Se der erro na aloca��o
						if ( retVal == VAL_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}
							
						//Insere esse valor no final da coluna atual
						retLis = LIS_InserirElementoApos ( LIS_linha_atual, (void*)valor );
							
						//Se der erro na aloca��o
						if ( retLis == LIS_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}

						cont_marcadas = 0;	//Zera o contador de c�lulas marcadas
						cont_valores++;		//Incrementa o contador de valores
					}

					//Se chegou na �ltima c�lula e nenhum valor foi criado
					else if ( (i == pDesenho->linhas -1) && (cont_valores == 0) ){
						return DES_CondRetColunaSemValor;
					}
				}
			}// end for j

			//Avan�a para a lista da pr�xima coluna
			LIS_PercorreLista ( pDesenho->listaValoresV, 1);
			cont_valores = 0; //Zera o contador de valores
		}//end for i

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Fun��o: DES Confere Solu��o dos Valores
*/

	DES_tpCondRet DES_confereSolucaoValores ( void ){

		int i, j, count_cel = 0;
		int num_celulas, estado_atual, estado_correto;

		VAL_tppValor valor;
		CEL_tppCelula celula;
		LIS_tppLista lista;

		LIS_tpCondRet retLis ;

	/*Confere valores horizontais*/

		LIS_IrInicioLista ( pDesenho->listaValoresH );

		//Para cada linha
		for ( i=0 ; i < pDesenho->linhas ; i++ ){
		
			//Obtem a lista da linha atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresH, (void**)&lista);

			//Vai pro in�cio da lista de valores da linha i
			LIS_IrInicioLista ( lista );

			//Para cada coluna
			for ( j=0 ; j < pDesenho->colunas ; j++ ){

			/*Descobre o n�mero de c�lulas do valor atual*/		

				//Obtem o valor corrente da lista
				LIS_ObterValorCorrente ( lista, (void**)&valor );

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
							retLis = LIS_PercorreLista ( lista, 1 );
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
						retLis = LIS_PercorreLista ( lista, 1 );
						//Se chegou ao fim da lista
						if ( retLis == LIS_CondRetFimLista )
							break;	//Avan�a para a pr�xima linha
					}//end else
				}//end 1� if

			/*Se a c�lula n�o estiver marcada, segue para a pr�xima c�lula*/

			}// end for j

			//Avan�a para a lista da pr�xima linha
			LIS_PercorreLista ( pDesenho->listaValoresH, 1 );

		}// end for i

	/*Confere valores verticais*/

		LIS_IrInicioLista ( pDesenho->listaValoresV );

		//Para cada coluna
		for ( j=0 ; j < pDesenho->colunas ; j++){
		
			//Obtem a lista da linha atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresV, (void**)&lista);

			//Vai pro in�cio da lista de valores da linha i
			LIS_IrInicioLista ( lista );

			//Para cada linha
			for ( i=0 ; i < pDesenho->linhas ; i++ ){

		/*Descobre o n�mero de c�lulas do valor atual*/		

				//Obtem o valor corrente da lista
				LIS_ObterValorCorrente ( lista, (void**)&valor );

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
							retLis = LIS_PercorreLista ( lista, 1 );
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
						retLis = LIS_PercorreLista ( lista, 1 );
						//Se chegou ao fim da lista
						if ( retLis == LIS_CondRetFimLista )
							break;	//Avan�a para a pr�xima linha
					}//end else
				}//end 1� if

		/*Se a c�lula n�o estiver marcada, segue para a pr�xima c�lula*/

			}// end for j

			//Avan�a para a lista da pr�xima coluna
			LIS_PercorreLista ( pDesenho->listaValoresV, 1 );

		}// end for i
		

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Fun��o: DES Salva Desenho
*/

	DES_tpCondRet DES_salvaDesenho (void){
		
		int i, j;
		int estado_atual = -1, estado_correto = -1;
		
		FILE* fpOut;
		VAL_tppValor valor = NULL ;
		CEL_tppCelula celula = NULL ;
		LIS_tppLista lista = NULL ;

		LIS_tpCondRet retLis;

		/*Formata nome do arquivo*/
		char nomeArquivo[54];
		strcpy (nomeArquivo, pDesenho->nome);
		strcat (nomeArquivo, ".txt");

		fpOut = fopen ( nomeArquivo, "wb");
		if ( fpOut == NULL )
			return DES_CondRetErroAberturaArquivo ;

		/*Escreve a dimens�o da matriz*/

		fprintf ( fpOut, "%d x %d\n", pDesenho->linhas, pDesenho->colunas );
		
		/*Escreve a lista de valores horizontal*/
		
		LIS_IrInicioLista ( pDesenho->listaValoresH );

		//Para todas as linhas
		for ( i = 0 ; i < pDesenho->linhas ; i++ ){

			//Identifica a linha
			fprintf( fpOut, "Valores da linha %d ",i+1);

			//Obtem a lista da linha atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresH, (void**)&lista);
			LIS_IrInicioLista ( lista );
			
			//Enquanto n�o chegar ao fim da lista de valores
			do{
				int numCelulas = -1, solucao = -1;

				//Obtem o valor
				LIS_ObterValorCorrente ( lista, (void**)&valor );
				
				//Obtem as informa��es do valor
				VAL_confereSolu��o ( valor, &solucao ) ;
				VAL_obtemNumeroCelulas ( valor, &numCelulas ) ;

				fprintf( fpOut, " (%d, %d) ",solucao, numCelulas );

				//Avan�a a lista pro pr�ximo elemento
				retLis = LIS_PercorreLista ( lista, 1 );
			} while ( retLis != LIS_CondRetFimLista );

			LIS_PercorreLista ( pDesenho->listaValoresH, 1 );
			fprintf( fpOut, "\n", i);	//Pula uma linha
		}
		
		/*Escreve a lista de valores vertical*/
		
		LIS_IrInicioLista ( pDesenho->listaValoresV );

		//Para todas as colunas
		for ( i=0 ; i < pDesenho->colunas ; i++ ){
			
			//Identifica a linha
			fprintf( fpOut, "Valores da coluna %d ",i+1);

			//Obtem a lista da linha atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresV, (void**)&lista);
			LIS_IrInicioLista ( lista );
			
			do{
				int numCelulas = -1, solucao = -1;
				//Obtem o valor
				LIS_ObterValorCorrente ( lista, (void**)&valor);
				
				//Obtem as informa��es do valor
				VAL_confereSolu��o ( valor, &solucao) ;
				VAL_obtemNumeroCelulas (valor, &numCelulas) ;

				fprintf( fpOut, " (%d, %d) ",solucao, numCelulas);

				//Avan�a a lista pro pr�ximo elemento
				retLis = LIS_PercorreLista ( lista, 1 );
			} while ( retLis != LIS_CondRetFimLista );

			LIS_PercorreLista ( pDesenho->listaValoresV, 1);
			fprintf( fpOut, "\n", i);	//Pula uma linha
		}

		/*Escreve as informa��es das c�lulas*/

		fprintf( fpOut, "\nInforma��es das c�lulas:\n");

		//Vai pro in�cio da matriz
		MAT_percorreMatriz ( pDesenho->matriz, 0, 0);
		
		i = j = 0;
		while ( i < pDesenho->linhas ){
			
			//Identifica a linha
			fprintf( fpOut, "Linha %d ", i+1) ;

			while ( j < pDesenho->colunas ){
				
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
		LIS_tppLista lista = NULL ;

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

		LIS_IrInicioLista ( pDesenho->listaValoresH );

		//Para todas as linhas
		for ( i=0 ; i < linhas ; i++ ){
			
			//Obtem o n�mero da linha
			fscanf( fpIn, " Valores da linha %d", &count);
			
			//Obtem a lista da linha atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresH, (void**)&lista);

			//Obtem os dados do valor e o insere na lista correta
			while ( fscanf ( fpIn , " (%d, %d)", &solucao, &numCelulas) == 2 ){

				//Cria valor
				retVal = VAL_criaValor( &valor, numCelulas );
				if ( retVal == VAL_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}

				//Inicializa valor
				VAL_defineSolucao ( valor, solucao );

				//Insere valor na lista da linha atual
				retLis = LIS_InserirElementoApos ( lista, (void*)valor);
				
				//Se der erro na aloca��o
				if ( retLis == LIS_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}
			}
			LIS_PercorreLista ( pDesenho->listaValoresH, 1);
		}

	/*Carrega os valores nas listas verticais*/

		LIS_IrInicioLista ( pDesenho->listaValoresV );

		//Para todas as colunas
		for ( j=0 ; j < colunas ; j++ ){
			
			//Obtem o n�mero da coluna
			fscanf( fpIn, " Valores da coluna %d", &count);

			//Obtem a lista da coluna atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresV, (void**)&lista);

			//Obtem os dados do valor e o insere na lista correta
			while ( fscanf ( fpIn , " (%d, %d)", &solucao, &numCelulas) == 2 ){
				
				//Cria valor
				retVal = VAL_criaValor( &valor, numCelulas );
				if ( retVal == VAL_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}

				//Inicializa valor
				VAL_defineSolucao ( valor, solucao );

				//Insere valor na lista da coluna atual
				retLis = LIS_InserirElementoApos ( lista, (void*)valor);
				
				//Se der erro na aloca��o
				if ( retLis == LIS_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}
			}
			LIS_PercorreLista ( pDesenho->listaValoresV, 1);
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
	
		int i, j;
		int estado_atual, estado_correto;

		CEL_tppCelula celula;

		//Para cada linha
		for ( i=0; i < pDesenho->linhas ; i++ ){
			
			//Para cada coluna
			for ( j=0 ; j < pDesenho->colunas ; j++ ){

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
		
		int i, j;
		int estado_atual, estado_correto;

		CEL_tppCelula celula = NULL;

		//Se n�o possui mais dicas
		if ( pDesenho->hints == 0 ){
			return DES_CondRetSemHints;
		}
		
		//Procura por c�lula a ser pintada
		for ( i=0 ; i < pDesenho->linhas ; i++ ){

			for ( j=0 ; j < pDesenho->colunas ; j++ ){
				
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


/************************************************************************
*
*  Fun��o: DES Imprime Desenho no modo Projeto
*/
	
	DES_tpCondRet DES_imprimeDesenhoProjeto ( void ){
		
		int i,j;
		VAL_tppValor valor = NULL;
		LIS_tppLista lista = NULL;

		LIS_tpCondRet ret = LIS_CondRetFaltouMemoria;
		
	/*Imprime teto*/	
		for ( i=0; i < pDesenho->colunas; i++ ){
			printf(" =====");
		}
		printf(" \n");

	/*Imprime colunas*/

		LIS_IrInicioLista ( pDesenho->listaValoresH );

		//Para cada linha
		for ( i=0; i < pDesenho->linhas; i++ ){
		
			int vezes = 2;	//Flag utilizada para percorrer a mesma linha 2 vezes
			
			do{
				//Para cada coluna
				for ( j=0; j < pDesenho->colunas; j++ ){
					
					int estado = -1;

					//Obtem o estado correto da c�lula (i,j)
					estado = obtemEstadoCorretoCelula ( i,j );

					//Se for a �ltima coluna
					if ( j == pDesenho->colunas - 1 ){
						
						imprimeEstado ( estado );
						printf ("|\n");						
					}
					else
						imprimeEstado ( estado );
				}

				vezes--;

			} while ( vezes > 0 );

	/*Imprime Ch�o*/
			for ( j=0; j < pDesenho->colunas; j++ )
				printf(" =====");
			printf(" \n");
		}//fim for i

		return DES_CondRetOK;
	}//fim fun��o


/************************************************************************
*
*  Fun��o: DES Imprime Desenho no modo Desafio
*/
	
	DES_tpCondRet DES_imprimeDesenhoDesafio ( void ){

		int i,j;
		int listas_vazias = 0;	//contador utilizado na impress�o dos valores verticais
		int num_celulas = -1;
		int vezes = -1;

		VAL_tppValor valor = NULL;
		LIS_tppLista lista = NULL;						

		LIS_tpCondRet ret = LIS_CondRetFaltouMemoria;
		
	/*Imprime teto*/	
		for ( i=0; i < pDesenho->colunas; i++ ){
			printf(" =====");
		}
		printf(" \n");

	/*Imprime colunas*/

		LIS_IrInicioLista ( pDesenho->listaValoresH );

		//Para cada linha
		for ( i=0; i < pDesenho->linhas; i++ ){
		
			vezes = 2;	//Flag utilizada para percorrer a mesma linha 2 vezes

			//Obtem a lista de valores da linha atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresH, (void**)&lista );
			LIS_IrInicioLista ( lista );
			
			do{
				//Para cada coluna
				for ( j=0; j < pDesenho->colunas; j++ ){
					
					int estado = -1;

					//Obtem o estado correto da c�lula (i,j)
					estado = obtemEstadoAtualCelula ( i,j );

					//Se for a �ltima coluna
					if ( j == pDesenho->colunas - 1 ){
						
						imprimeEstado ( estado );
						printf ("|");
						
						//Se for a primeira vez, pula linha. Formata��o para os valores
						if ( vezes == 2 )
							printf ("\n");
						
						//Se for a �ltima vez, imprime os valores horizontais
						else{
							
							//Reseta a vari�vel ret
							ret = LIS_CondRetFaltouMemoria;

							//Enquanto n�o chegar ao fim da lista de valores
							while ( ret != LIS_CondRetFimLista ){

								//Obtem o n�mero de c�lulas do valor
								LIS_ObterValorCorrente ( lista, (void**)&valor );
								VAL_obtemNumeroCelulas ( valor, &num_celulas );

								printf ("%d ", num_celulas); //Imprime n�mero de c�lulas
								ret = LIS_PercorreLista ( lista, 1 );
							}
							printf ("\n");
						}
					}
					else
						imprimeEstado ( estado );
				}

				vezes--;

			} while ( vezes > 0 );

			LIS_PercorreLista ( pDesenho->listaValoresH, 1 );

	/*Imprime Ch�o*/
			for ( j=0; j < pDesenho->colunas; j++ )
				printf(" =====");
			printf(" \n");
		}//fim for i
		
	/*Imprime valores verticais*/
		LIS_IrInicioLista ( pDesenho->listaValoresV );
		vezes = 0;	//Indica quantas vezes todas as listas foram percorridas
		
		do{
			i=0;
			while ( i < pDesenho->colunas ){

				/*Obtem lista de valores da coluna atual*/
				LIS_ObterValorCorrente ( pDesenho->listaValoresV, (void**)&lista );
				LIS_IrInicioLista ( lista );

				ret = LIS_PercorreLista ( lista, vezes );
				
				//Se ainda existem valores n�o impressos na lista atual
				if ( ret == LIS_CondRetOK ){
					
					/*Obtem o n�mero de c�lulas do valor*/
					LIS_ObterValorCorrente ( lista, (void**)&valor );
					VAL_obtemNumeroCelulas ( valor, &num_celulas );

					//Imprime o valor
					printf ("   %d  ", num_celulas);
				}
				
				//Se acabaram os valores
				else{
				
					listas_vazias++;

					//Se todos os valores j� foram impressos
					if ( listas_vazias == pDesenho->colunas ){
					
						vezes = -1;	//Termina a verifica��o
						break;
					}
				}

				//Se chegou na �ltima coluna
				if ( i == pDesenho->colunas - 1 ){
					vezes++;	//As listas foram percorridas mais uma vez
					printf("\n");
				}

				LIS_PercorreLista ( pDesenho->listaValoresV, 1 );
				i++;
			}
		}while ( vezes >= 0 );

		return DES_CondRetOK;
	}



/************* C�digo das fun��es encapuladas no m�dulo *************/

/********************************************************************
*
*  FC Fun��o: DES - Inicializa Matriz
*
********************************************************************/

	static MAT_tpCondRet initMatriz ( MAT_tppMatriz matriz, int linhas, int colunas ){
		
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
					return MAT_CondRetFaltouMemoria;
				//Insere a c�lula no elemento (i,j) da matriz
				MAT_insereDado ( pDesenho->matriz, (void*)cel );
			}
		}
		
		return MAT_CondRetOK;
	}


/********************************************************************
*
*  FC Fun��o: DES - Inicializa Lista de Listas
*
********************************************************************/
	
	static LIS_tpCondRet initLista (LIS_tppLista lista, int tam_lista ){

		int i;
		LIS_tpCondRet ret;

		for ( i=0 ; i < tam_lista ; i++ ){
			
			LIS_tppLista lista_val;

			//Cria lista de valores
			ret = LIS_CriarLista( &lista_val, (ExcluirValor) VAL_destroiValor );
			if ( ret == LIS_CondRetFaltouMemoria )
				return ret;

			//Insere lista de valores na lista de listas
			LIS_InserirElementoApos ( lista, (void*)lista_val );
		}

		return LIS_CondRetOK;
	}


/**************************************************************************
*
*  FC Fun��o: DES - Obtem Estado Atual da C�lula
*
***************************************************************************/

	static int obtemEstadoAtualCelula ( int linha, int coluna ){

		CEL_tppCelula celula = NULL;
		int estado;

		//Obtem a c�lula na posi��o ( linha, coluna)
		MAT_percorreMatriz( pDesenho->matriz, linha, coluna );
		MAT_obterValorCorrente( pDesenho->matriz, (void**)&celula );

		//Obtem estado atual da c�lula
		CEL_obtemEstadoAtual( celula, &estado );

		return estado;
	}


/**************************************************************************
*
*  FC Fun��o: DES - Obtem Estado Correto da C�lula
*
***************************************************************************/

	static int obtemEstadoCorretoCelula ( int linha, int coluna ){

		CEL_tppCelula celula = NULL;
		int estado;

		//Obtem a c�lula na posi��o ( linha, coluna)
		MAT_percorreMatriz( pDesenho->matriz, linha, coluna );
		MAT_obterValorCorrente( pDesenho->matriz, (void**)&celula );

		//Obtem estado atual da c�lula
		CEL_obtemEstadoCorreto( celula, &estado );

		return estado;
	}


/**************************************************************************
*
*  FC Fun��o: DES - Imprime de acordo com o estado
*
***************************************************************************/

	static void imprimeEstado ( int estado ){
	
		switch ( estado ){

			case 0:{				//Nula
				printf("|     ");
				break;
			}
			case 1:{				//Marcada
				printf("|#####");
				break;
			}
			case 2:{				//Desmarcada
				printf("|  x  ");
				break;
			}
		}
	}


/**************************************************************************
*
*  FC Fun��o: DES - Zera a Lista de Listas de Valores
*
***************************************************************************/
	
	static void zeraListaValores( LIS_tppLista lista_de_listas ){
	
		LIS_tppLista lista_de_valores = NULL;
		LIS_tpCondRet ret = LIS_CondRetFaltouMemoria;

		LIS_IrInicioLista ( lista_de_listas );
		
		while ( ret != LIS_CondRetFimLista ){
			
			LIS_ObterValorCorrente ( lista_de_listas, (void**)&lista_de_valores );
			LIS_EsvaziarLista ( lista_de_valores );
			ret = LIS_PercorreLista ( lista_de_listas, 1 );
		}
	}



/************ Fim do m�dulo de implementa��o: M�dulo Desenho ***********/