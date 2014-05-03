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
*		2.0		vyc		14/04/2014	Correções
*		3.0		vyc		27/04/2014	Otimização
*
***************************************************************************/


/********************* Diretivas de Pré-Processamento *********************/

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
		
		LIS_tppLista listaValoresH ;
					/*Lista de listas de valores horizontais*/
		
		LIS_tppLista listaValoresV ;
					/*Lista de listas de valores verticais*/
		
		int linhas;
					/*Quantidade de linhas do desenho*/

		int colunas;
					/*Quantidade de colunas do desenho*/				

		int hints ;
					/*Armazena a quantidade de hints que o usuário pode usar*/

		char nome[50] ;
					/*Nome que identifica o desenho*/

	} DES_tpDesenho ;



/********************* Dados encapsulados no módulo *********************/

	static DES_tpDesenho* pDesenho = NULL ; 
				/*Ponteiro para um desenho*/


/************* Protótipos das funções encapuladas no módulo *************/

	static MAT_tpCondRet initMatriz ( MAT_tppMatriz matriz, int linhas, int colunas );
	static LIS_tpCondRet initLista (LIS_tppLista lista, int tam_lista );
	static void zeraListaValores( LIS_tppLista lista_de_listas );
	static void imprimeEstado ( int estado );
	static int obtemEstadoAtualCelula ( int linha, int coluna );
	static int obtemEstadoCorretoCelula ( int linha, int coluna );



/************** Código das funções exportadas pelo módulo ***************/

/************************************************************************
*
*  Função: DES Cria Desenho 
*/

	DES_tpCondRet DES_criaDesenho ( int linhas, int colunas, char* nome ){
		
		MAT_tpCondRet retMat ;	//retorno das funções do módulo matriz
		LIS_tpCondRet retLis ;	//retorno das funções do módulo lista
		int i;

		//Se já existe um desenho
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

	/*Cria a matriz de células do desenho*/
		retMat = MAT_criaMatriz( &pDesenho->matriz, linhas, colunas, (ExcluirValor) CEL_destroiCelula) ;
		//Se der erro, desaloca todas as estruturas
		if ( retMat == MAT_CondRetFaltouMemoria ){
			
			//Destroi as listas de listas e o desenho
			LIS_DestruirLista ( pDesenho->listaValoresH );
			LIS_DestruirLista ( pDesenho->listaValoresV );
			free (pDesenho);
			
			return DES_CondRetFaltouMemoria;
		}

		//Insere as células nos elementos da matriz
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

		//Atribui o número de linhas e colunas do desenho
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
*  Função: DES Destroi Desenho
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
*  Função: DES Modifica Célula Correto
*/

	DES_tpCondRet DES_modificaCelulaCorreto ( int linha, int coluna, char estado ){
		
		CEL_tppCelula celula = NULL;
		
		/* Obtem a célula da posição (linha,coluna) */
		MAT_percorreMatriz ( pDesenho->matriz, linha-1, coluna-1 );
		MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

		//Se o estado é marcada
		if ( estado == 'm' ){
		
			CEL_alteraEstadoCorreto ( celula, 1 ) ;
			return DES_CondRetOK ;
		}
		//Se o estado é desmarcada
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
*  Função: DES Modifica Célula Atual
*/

	DES_tpCondRet DES_modificaCelulaAtual ( int linha, int coluna, char estado){
	
		CEL_tppCelula celula = NULL;
		
		/* Obtem a célula da posição (linha,coluna) */
		MAT_percorreMatriz ( pDesenho->matriz, linha-1, coluna-1 );
		MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

		//Se o estado é marcada
		if ( estado == 'm' ){
		
			CEL_alteraEstadoAtual ( celula, 1 ) ;
			return DES_CondRetOK ;
		}
		//Se o estado é desmarcada
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
*  Função: DES Calcula Valores
*/

	DES_tpCondRet DES_calculaValores ( void ){

		int i, j, k, cont_marcadas = 0 , cont_valores = 0;
		int estado;					//Armazena o estado correto da célula
		
		//Ponteiros para os tipos utilizados
		CEL_tppCelula celula = NULL ;
		VAL_tppValor valor = NULL ;
		LIS_tppLista LIS_linha_atual = NULL;
		
		//Condições de retorno
		VAL_tpCondRet retVal ;
		LIS_tpCondRet retLis ;
		
		/*Calcula valores horizontais*/
		
		zeraListaValores( pDesenho->listaValoresH );	//Caso os valores já tenham sido calculados
		LIS_IrInicioLista ( pDesenho->listaValoresH );

		//Para cada linha
		for ( i=0 ; i < pDesenho->linhas ; i++ ){
			
			//Obtem a lista da linha atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresH, (void**)&LIS_linha_atual);
			LIS_IrInicioLista ( LIS_linha_atual );

			//Para cada coluna
			for ( j=0 ; j < pDesenho->colunas ; j++ ){
				
				//Na posição (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );
				
				//Obtem a célula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
				
				//Obtem o estado correto da célula
				CEL_obtemEstadoCorreto ( celula, &estado ) ;
				
				//Se estado for nula
				if ( estado == 0 ){
					return DES_CondRetCelulaNula;
				}

				//Senão, se o estado for marcada
				else if ( estado == 1 ){
					
					//Número de células marcadas recebe +1
					cont_marcadas++;

					//Se for a última célula da linha
					if ( j == pDesenho->colunas - 1  ){
						
						//Cria um valor
						retVal = VAL_criaValor ( &valor, cont_marcadas );
							
						//Se der erro na alocação
						if ( retVal == VAL_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}
							
						//Insere esse valor no final da linha atual
						retLis = LIS_InserirElementoApos ( LIS_linha_atual, (void*)valor );
							
						//Se der erro na alocação
						if ( retLis == LIS_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}

						cont_marcadas = 0;	//Zera o contador de células marcadas
					}
				}

				//Senão, se o estado for desmarcada
				else if ( estado == 2 ){
					
					//Se a célula anterior estiver marcada
					if ( cont_marcadas > 0 ) {

						//Cria um valor
						retVal = VAL_criaValor ( &valor, cont_marcadas );
							
						//Se der erro na alocação
						if ( retVal == VAL_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}
							
						//Insere esse valor no final da linha atual
						retLis = LIS_InserirElementoApos ( LIS_linha_atual, (void*)valor );
							
						//Se der erro na alocação
						if ( retLis == LIS_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}

						cont_marcadas = 0;	//Zera o contador de células marcadas
						cont_valores++;		//Incrementa o contador de valores
					}

					//Se chegou na última célula e nenhum valor foi criado
					else if ( (j == pDesenho->colunas -1) && (cont_valores == 0) ){
						return DES_CondRetLinhaSemValor;
					}
				}
			}// end for j
			
			//Avança para a lista da próxima linha
			LIS_PercorreLista ( pDesenho->listaValoresH, 1);
			cont_valores = 0; //Zera o contador de valores
		}//end for i
				

		/*Calcula valores verticais*/
		
		zeraListaValores( pDesenho->listaValoresV );	//Caso os valores já tenham sido calculados
		LIS_IrInicioLista ( pDesenho->listaValoresV );

		//Para cada coluna
		for ( j=0 ; j < pDesenho->colunas ; j++ ){
			
			//Obtem a lista da coluna atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresV, (void**)&LIS_linha_atual);
			LIS_IrInicioLista ( LIS_linha_atual );

			//Para cada linha
			for ( i=0 ; i < pDesenho->linhas ; i++ ){
				
				//Na posição (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );
				
				//Obtem a célula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
				
				//Obtem o estado correto da célula
				CEL_obtemEstadoCorreto ( celula, &estado ) ;
				
				//Se estado for nula
				if ( estado == 0 ){
					return DES_CondRetCelulaNula;
				}

				//Senão, se estado for marcada
				else if ( estado == 1 ){
					
					//Número de células marcadas recebe +1
					cont_marcadas++;

					//Se for a última célula da coluna
					if ( i == pDesenho->linhas - 1  ){
						
						//Cria um valor
						retVal = VAL_criaValor ( &valor, cont_marcadas );
							
						//Se der erro na alocação
						if ( retVal == VAL_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}
							
						//Insere esse valor no final da coluna atual
						retLis = LIS_InserirElementoApos ( LIS_linha_atual, (void*)valor );
							
						//Se der erro na alocação
						if ( retLis == LIS_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}

						cont_marcadas = 0;	//Zera o contador de células marcadas
					}
				}

				//Senão, se o estado for desmarcada
				else if ( estado == 2 ){
					
					//Se a célula anterior estiver marcada
					if ( cont_marcadas > 0 ) {

						//Cria um valor
						retVal = VAL_criaValor ( &valor, cont_marcadas );
							
						//Se der erro na alocação
						if ( retVal == VAL_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}
							
						//Insere esse valor no final da coluna atual
						retLis = LIS_InserirElementoApos ( LIS_linha_atual, (void*)valor );
							
						//Se der erro na alocação
						if ( retLis == LIS_CondRetFaltouMemoria ){
							return DES_CondRetFaltouMemoria;
						}

						cont_marcadas = 0;	//Zera o contador de células marcadas
						cont_valores++;		//Incrementa o contador de valores
					}

					//Se chegou na última célula e nenhum valor foi criado
					else if ( (i == pDesenho->linhas -1) && (cont_valores == 0) ){
						return DES_CondRetColunaSemValor;
					}
				}
			}// end for j

			//Avança para a lista da próxima coluna
			LIS_PercorreLista ( pDesenho->listaValoresV, 1);
			cont_valores = 0; //Zera o contador de valores
		}//end for i

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Função: DES Confere Solução dos Valores
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

			//Vai pro início da lista de valores da linha i
			LIS_IrInicioLista ( lista );

			//Para cada coluna
			for ( j=0 ; j < pDesenho->colunas ; j++ ){

			/*Descobre o número de células do valor atual*/		

				//Obtem o valor corrente da lista
				LIS_ObterValorCorrente ( lista, (void**)&valor );

				//Obtem o número de células desse valor
				VAL_obtemNumeroCelulas ( valor, &num_celulas );
		
			/*Obtem os estados da celula*/
				
				//Vai pra posição (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );

				//Obtem a célula da posição (i,j)
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );

				//Obtem os estados da célula
				CEL_obtemEstadoAtual ( celula, &estado_atual );
				CEL_obtemEstadoCorreto ( celula, &estado_correto );

			/*Se a célula estiver marcada*/
				if ( estado_atual == 1 ){
					
					//Se ela estiver marcada corretamente
					if ( estado_atual == estado_correto ){
						//Contador de células marcadas +1
						count_cel++;
						//Se o valor já foi resolvido
						if ( count_cel == num_celulas ){
							//Marca o valor como resolvido
							VAL_defineSolucao (valor, 1);
							//Zera contador
							count_cel = 0;
							//Avança para o próximo valor da lista
							retLis = LIS_PercorreLista ( lista, 1 );
							//Se chegou ao fim da lista
							if ( retLis == LIS_CondRetFimLista )
								break;	//Avança para a próxima linha
						}
					}
					//Se ela não estiver marcada corretamente
					else{

						//Marca o valor como não resolvido
						VAL_defineSolucao (valor, 0);
						//Zera contador
						count_cel = 0;
						//Avança para o próximo valor da lista
						retLis = LIS_PercorreLista ( lista, 1 );
						//Se chegou ao fim da lista
						if ( retLis == LIS_CondRetFimLista )
							break;	//Avança para a próxima linha
					}//end else
				}//end 1º if

			/*Se a célula não estiver marcada, segue para a próxima célula*/

			}// end for j

			//Avança para a lista da próxima linha
			LIS_PercorreLista ( pDesenho->listaValoresH, 1 );

		}// end for i

	/*Confere valores verticais*/

		LIS_IrInicioLista ( pDesenho->listaValoresV );

		//Para cada coluna
		for ( j=0 ; j < pDesenho->colunas ; j++){
		
			//Obtem a lista da linha atual
			LIS_ObterValorCorrente ( pDesenho->listaValoresV, (void**)&lista);

			//Vai pro início da lista de valores da linha i
			LIS_IrInicioLista ( lista );

			//Para cada linha
			for ( i=0 ; i < pDesenho->linhas ; i++ ){

		/*Descobre o número de células do valor atual*/		

				//Obtem o valor corrente da lista
				LIS_ObterValorCorrente ( lista, (void**)&valor );

				//Obtem o número de células desse valor
				VAL_obtemNumeroCelulas ( valor, &num_celulas );
		
		/*Obtem os estados da celula*/
				
				//Vai pra posição (i,j) da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j );

				//Obtem a célula da posição (i,j)
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );

				//Obtem os estados da célula
				CEL_obtemEstadoAtual ( celula, &estado_atual );
				CEL_obtemEstadoCorreto ( celula, &estado_correto );

		/*Se a célula estiver marcada*/
				if ( estado_atual == 1 ){
					
					//Se ela estiver marcada corretamente
					if ( estado_atual == estado_correto ){
						//Contador de células marcadas +1
						count_cel++;
						//Se o valor já foi resolvido
						if ( count_cel == num_celulas ){
							//Marca o valor como resolvido
							VAL_defineSolucao (valor, 1);
							//Zera contador
							count_cel = 0;
							//Avança para o próximo valor da lista
							retLis = LIS_PercorreLista ( lista, 1 );
							//Se chegou ao fim da lista
							if ( retLis == LIS_CondRetFimLista )
								break;	//Avança para a próxima linha
						}
					}
					//Se ela não estiver marcada corretamente
					else{

						//Marca o valor como não resolvido
						VAL_defineSolucao (valor, 0);
						//Zera contador
						count_cel = 0;
						//Avança para o próximo valor da lista
						retLis = LIS_PercorreLista ( lista, 1 );
						//Se chegou ao fim da lista
						if ( retLis == LIS_CondRetFimLista )
							break;	//Avança para a próxima linha
					}//end else
				}//end 1º if

		/*Se a célula não estiver marcada, segue para a próxima célula*/

			}// end for j

			//Avança para a lista da próxima coluna
			LIS_PercorreLista ( pDesenho->listaValoresV, 1 );

		}// end for i
		

		return DES_CondRetOK;
	}


/************************************************************************
*
*  Função: DES Salva Desenho
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

		/*Escreve a dimensão da matriz*/

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
			
			//Enquanto não chegar ao fim da lista de valores
			do{
				int numCelulas = -1, solucao = -1;

				//Obtem o valor
				LIS_ObterValorCorrente ( lista, (void**)&valor );
				
				//Obtem as informações do valor
				VAL_confereSolução ( valor, &solucao ) ;
				VAL_obtemNumeroCelulas ( valor, &numCelulas ) ;

				fprintf( fpOut, " (%d, %d) ",solucao, numCelulas );

				//Avança a lista pro próximo elemento
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
				
				//Obtem as informações do valor
				VAL_confereSolução ( valor, &solucao) ;
				VAL_obtemNumeroCelulas (valor, &numCelulas) ;

				fprintf( fpOut, " (%d, %d) ",solucao, numCelulas);

				//Avança a lista pro próximo elemento
				retLis = LIS_PercorreLista ( lista, 1 );
			} while ( retLis != LIS_CondRetFimLista );

			LIS_PercorreLista ( pDesenho->listaValoresV, 1);
			fprintf( fpOut, "\n", i);	//Pula uma linha
		}

		/*Escreve as informações das células*/

		fprintf( fpOut, "\nInformações das células:\n");

		//Vai pro início da matriz
		MAT_percorreMatriz ( pDesenho->matriz, 0, 0);
		
		i = j = 0;
		while ( i < pDesenho->linhas ){
			
			//Identifica a linha
			fprintf( fpOut, "Linha %d ", i+1) ;

			while ( j < pDesenho->colunas ){
				
				//Obtem a célula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

				//Obtem as informações da célula
				CEL_obtemEstadoCorreto ( celula, &estado_correto );
				CEL_obtemEstadoAtual ( celula, &estado_atual );

				fprintf( fpOut, " (%d, %d) ", estado_atual, estado_correto );

				j++;
				//Avança para o próximo elemento da matriz
				MAT_percorreMatriz ( pDesenho->matriz, i, j);
			}

			j=0;
			i++;
			//Avança para o próximo elemento da matriz
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
*  Função: DES Carrega Desenho
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

		//Se já existe um desenho aberto
		if ( pDesenho != NULL ){
			//Destroi desenho atual
			DES_destroiDesenho();
		}

		//Lê dimensões da matriz
		fscanf( fpIn, " %d x %d", &linhas, &colunas);

		//Cria um novo desenho
		DES_criaDesenho ( linhas, colunas, nome_desenho);
		

	/*Carrega os valores nas listas horizontais*/

		LIS_IrInicioLista ( pDesenho->listaValoresH );

		//Para todas as linhas
		for ( i=0 ; i < linhas ; i++ ){
			
			//Obtem o número da linha
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
				
				//Se der erro na alocação
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
			
			//Obtem o número da coluna
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
				
				//Se der erro na alocação
				if ( retLis == LIS_CondRetFaltouMemoria ){
					return DES_CondRetFaltouMemoria;
				}
			}
			LIS_PercorreLista ( pDesenho->listaValoresV, 1);
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

					case 1:{
						CEL_tppCelula celula;

						//Obtem a célula
						MAT_percorreMatriz ( pDesenho->matriz, i, j );
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

						//Altera estado atual
						CEL_alteraEstadoAtual ( celula, 1 );
						break;
					}
					case 2:{
						CEL_tppCelula celula;

						//Obtem a célula
						MAT_percorreMatriz ( pDesenho->matriz, i, j );
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

						//Altera estado atual
						CEL_alteraEstadoAtual ( celula, 2 );
						break;
					}
					case 0:{
						CEL_tppCelula celula;

						//Obtem a célula
						MAT_percorreMatriz ( pDesenho->matriz, i, j );
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

						//Altera estado atual
						CEL_alteraEstadoAtual ( celula, 0 );
						break;
					}
				}

				//Modifica o estado correto da célula (i,j)
				switch ( estado_correto ){

					case 1:{
						CEL_tppCelula celula;

						//Obtem a célula
						MAT_percorreMatriz ( pDesenho->matriz, i, j );
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

						//Altera estado correto
						CEL_alteraEstadoCorreto ( celula, 1 );
						break;
					}
					case 2:{
						CEL_tppCelula celula;

						//Obtem a célula
						MAT_percorreMatriz ( pDesenho->matriz, i, j );
						MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula);

						//Altera estado correto
						CEL_alteraEstadoCorreto ( celula, 2 );
						break;
					}
					case 0:{
						CEL_tppCelula celula;

						//Obtem a célula
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
*  Função: DES Confere Conclusão do Desenho
*/

	DES_tpCondRet DES_confereConclusaoDesenho ( void ){
	
		int i, j;
		int estado_atual, estado_correto;

		CEL_tppCelula celula;

		//Para cada linha
		for ( i=0; i < pDesenho->linhas ; i++ ){
			
			//Para cada coluna
			for ( j=0 ; j < pDesenho->colunas ; j++ ){

		/*Obter os estados da célula (i,j)*/

				MAT_percorreMatriz ( pDesenho->matriz, i, j );

				//Obtem a célula
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );

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


/************************************************************************
*
*  Função: DES Usa Dica
*/

	DES_tpCondRet DES_usaDica( void ){
		
		int i, j;
		int estado_atual, estado_correto;

		CEL_tppCelula celula = NULL;

		//Se não possui mais dicas
		if ( pDesenho->hints == 0 ){
			return DES_CondRetSemHints;
		}
		
		//Procura por célula a ser pintada
		for ( i=0 ; i < pDesenho->linhas ; i++ ){

			for ( j=0 ; j < pDesenho->colunas ; j++ ){
				
				/*Obter celula na posição (i,j)*/
				MAT_percorreMatriz ( pDesenho->matriz, i, j);
				MAT_obterValorCorrente ( pDesenho->matriz, (void**)&celula );
				
				/*Obter informações da célula*/
				CEL_obtemEstadoAtual ( celula, &estado_atual );
				CEL_obtemEstadoCorreto ( celula, &estado_correto );

				//Se a celula não está marcada corretamente
				if ( (estado_atual != estado_correto) && (estado_correto == 1) ){

					//Marca a célula
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
*  Função: DES Imprime Desenho no modo Projeto
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

					//Obtem o estado correto da célula (i,j)
					estado = obtemEstadoCorretoCelula ( i,j );

					//Se for a última coluna
					if ( j == pDesenho->colunas - 1 ){
						
						imprimeEstado ( estado );
						printf ("|\n");						
					}
					else
						imprimeEstado ( estado );
				}

				vezes--;

			} while ( vezes > 0 );

	/*Imprime Chão*/
			for ( j=0; j < pDesenho->colunas; j++ )
				printf(" =====");
			printf(" \n");
		}//fim for i

		return DES_CondRetOK;
	}//fim função


/************************************************************************
*
*  Função: DES Imprime Desenho no modo Desafio
*/
	
	DES_tpCondRet DES_imprimeDesenhoDesafio ( void ){

		int i,j;
		int listas_vazias = 0;	//contador utilizado na impressão dos valores verticais
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

					//Obtem o estado correto da célula (i,j)
					estado = obtemEstadoAtualCelula ( i,j );

					//Se for a última coluna
					if ( j == pDesenho->colunas - 1 ){
						
						imprimeEstado ( estado );
						printf ("|");
						
						//Se for a primeira vez, pula linha. Formatação para os valores
						if ( vezes == 2 )
							printf ("\n");
						
						//Se for a última vez, imprime os valores horizontais
						else{
							
							//Reseta a variável ret
							ret = LIS_CondRetFaltouMemoria;

							//Enquanto não chegar ao fim da lista de valores
							while ( ret != LIS_CondRetFimLista ){

								//Obtem o número de células do valor
								LIS_ObterValorCorrente ( lista, (void**)&valor );
								VAL_obtemNumeroCelulas ( valor, &num_celulas );

								printf ("%d ", num_celulas); //Imprime número de células
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

	/*Imprime Chão*/
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
				
				//Se ainda existem valores não impressos na lista atual
				if ( ret == LIS_CondRetOK ){
					
					/*Obtem o número de células do valor*/
					LIS_ObterValorCorrente ( lista, (void**)&valor );
					VAL_obtemNumeroCelulas ( valor, &num_celulas );

					//Imprime o valor
					printf ("   %d  ", num_celulas);
				}
				
				//Se acabaram os valores
				else{
				
					listas_vazias++;

					//Se todos os valores já foram impressos
					if ( listas_vazias == pDesenho->colunas ){
					
						vezes = -1;	//Termina a verificação
						break;
					}
				}

				//Se chegou na última coluna
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



/************* Código das funções encapuladas no módulo *************/

/********************************************************************
*
*  FC Função: DES - Inicializa Matriz
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
				//Cria a célula
				retCel = CEL_criaCelula ( &cel );
				if ( retCel == CEL_CondRetFaltouMemoria )
					return MAT_CondRetFaltouMemoria;
				//Insere a célula no elemento (i,j) da matriz
				MAT_insereDado ( pDesenho->matriz, (void*)cel );
			}
		}
		
		return MAT_CondRetOK;
	}


/********************************************************************
*
*  FC Função: DES - Inicializa Lista de Listas
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
*  FC Função: DES - Obtem Estado Atual da Célula
*
***************************************************************************/

	static int obtemEstadoAtualCelula ( int linha, int coluna ){

		CEL_tppCelula celula = NULL;
		int estado;

		//Obtem a célula na posição ( linha, coluna)
		MAT_percorreMatriz( pDesenho->matriz, linha, coluna );
		MAT_obterValorCorrente( pDesenho->matriz, (void**)&celula );

		//Obtem estado atual da célula
		CEL_obtemEstadoAtual( celula, &estado );

		return estado;
	}


/**************************************************************************
*
*  FC Função: DES - Obtem Estado Correto da Célula
*
***************************************************************************/

	static int obtemEstadoCorretoCelula ( int linha, int coluna ){

		CEL_tppCelula celula = NULL;
		int estado;

		//Obtem a célula na posição ( linha, coluna)
		MAT_percorreMatriz( pDesenho->matriz, linha, coluna );
		MAT_obterValorCorrente( pDesenho->matriz, (void**)&celula );

		//Obtem estado atual da célula
		CEL_obtemEstadoCorreto( celula, &estado );

		return estado;
	}


/**************************************************************************
*
*  FC Função: DES - Imprime de acordo com o estado
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
*  FC Função: DES - Zera a Lista de Listas de Valores
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



/************ Fim do módulo de implementação: Módulo Desenho ***********/