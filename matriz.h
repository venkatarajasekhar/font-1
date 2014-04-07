/***************************************************************************
*
*	$MCD M�dulo de defini��o: M�dulo Matriz Gen�rica
*
*	Arquivo gerado:				 matriz.h
*	Letras identificadoras:		 MAT
*
*	Nome da base de software:	 Exemplo de teste automatizado
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
*	$ED Descri��o do m�dulo
*		Implementa uma matriz gen�rica.
*		Podem existir n matrizes em opera��o simultaneamente.
*		A matriz est� vazia ap�s sua cria��o.
*		A matriz � homog�nea quanto ao tipo de dado que armazena.
*		Os ponteiros para os dados s�o copiados para elementos da matriz.
*		N�o � copiado o valor apontado por estes ponteiros.
*		O controle da destrui��o do valor de um elemento a ser exclu�do
*		� realizado por uma fun��o fornecida pelo usu�rio.		
*		Cada matriz referencia uma fun��o que determina como devem ser
*		desalocados os dados nela contidos.
*
***************************************************************************/



/********************* Diretivas de Pr�-Processamento *********************/

	#ifndef MATRIZ_ 
	#define MATRIZ_



/******************* Declara��es exportadas pelo m�dulo *******************/
	
	typedef struct MAT_tagMatriz* MAT_tppMatriz ;
				/*Tipo ponteiro para a cabe�a de matriz*/


/***********************************************************************
*
*	$TC Tipo de dados: MAT Condi��es de retorno
*
*	$ED Descri��o do tipo
*		Condi��es de retorno das fun��es da matriz
*
***********************************************************************/

	typedef enum {
		
		MAT_CondRetOK = 0 ,
				//Concluiu corretamente 
		
		MAT_CondRetMatrizVazia = 1 ,
				// A matriz n�o cont�m elementos
		
		MAT_CondRetMatrizNVazia = 2 ,
				// A matriz cont�m elementos

		MAT_CondRetFaltouMemoria = 3
				// Faltou mem�ria ao tentar criar um elemento da matriz

	} MAT_tpCondRet ;


/***********************************************************************
*
*	$FC Fun��o: MAT Criar Matriz
*
*	$ED Descri��o da fun��o
*		Cria a estrutura matriz com o tamanho especificado nos par�metros.
*
*	$EP Par�metros
*		refMatriz	- Refer�ncia para a matriz criada
*		linhas 		- Determina a quantidade de linhas da matriz
*		colunas 	- Determina a quantidade de colunas da matriz
*		ExcluirDado - Ponteiro para a fun��o que processa a exclus�o 
*					  do valor referenciado por um elemento da matriz		
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		refLista referencia um ponteiro livre para a nova matriz
*		O ponteiro para fun��o ExcluirValor deve estar de acordo com
*		a libera��o de mem�ria desejada.
* 
*   $AS Assertivas de sa�da 
*		Se OK, refMatriz aponta para a matriz criada.
*		Do contr�rio, a matriz n�o � criada.
*
***********************************************************************/

	MAT_tpCondRet MAT_criaMatriz ( MAT_tppMatriz* refMatriz, int linhas, int colunas,
												 void (*ExcluirDado) (void* pDado) );


/***********************************************************************
*
*	$FC Fun��o: MAT Destroi Matriz
*
*	$ED Descri��o da fun��o
*		Destroi a matriz, desalocando seus elementos.
*		N�o modifica o ponteiro passado, deve-se atribur NULL a este
*		ap�s a chamada da fun��o.
*
*	$EP Par�metros
*		pMatriz	- Ponteiro para a matriz a ser destruida
*	
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz existente.
* 
*   $AS Assertivas de sa�da 
*		A matriz e seus elementos foram desalocados.
*
***********************************************************************/

	MAT_tpCondRet MAT_destroiMatriz ( MAT_tppMatriz pMatriz );


/***********************************************************************
*
*	$FC Fun��o: MAT Esvazia Matriz
*
*	$ED Descri��o da fun��o
*		Desaloca todos os dados apontados pelos elementos da matriz, que
*		ent�o apontam para NULL.
*	
*	$EP Par�metros
*		pMatriz	- Ponteiro para a matriz a ser esvaziada.
*	
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz n�o vazia.
*		
* 
*   $AS Assertivas de sa�da 
*		A matriz apontada por pMatriz est� vazia.
*
***********************************************************************/

	MAT_tpCondRet MAT_esvaziaMatriz ( MAT_tppMatriz pMatriz );


/***********************************************************************
*
*	$FC Fun��o: MAT Insere Dado
*
*	$ED Descri��o da fun��o
*		Atribui o dado passado para o elemento na 
*		posi��o [linha][coluna] da matriz. Se o elemento
*		j� aponta para um dado, este ser� desalocado.
*
*	$EP Par�metros
*		pMatriz	- Ponteiro para a matriz cujo elemento ser� alterado
*		linha 	- Indica a linha da matriz onde est� o elemento
*		coluna 	- Indica a coluna da matriz onde est� o elemento	
*		pDado	- Ponteiro para o dado a ser apontado pelo elemento
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz v�lida.
*		linha � menor ou igual ao n�mero de linhas da matriz.
*		coluna � menor ou igual ao n�mero de linhas da matriz.
* 		pDado contem o dado que ser� inserido e � diferente de NULL.
*
*   $AS Assertivas de sa�da 
*		O elemento na posi��o [linha][coluna] da matriz aponta para o
*		dado passado.
*
***********************************************************************/

	MAT_tpCondRet MAT_insereDado ( MAT_tppMatriz pMatriz, int linha, int coluna, void* pDado);


/***********************************************************************
*
*	$FC Fun��o: MAT Confere Vazia
*
*	$ED Descri��o da fun��o
*		Confere se a matriz est� vazia.
*	
*	$EP Par�metros
*		pMatriz	- Ponteiro para matriz a ser conferida
*	
*	$FV Valor retornado
*		MAT_tpCondRetMatrizVazia
*		MAT_tpCondRetMatrizNVazia
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz v�lida.
* 
*   $AS Assertivas de sa�da 
*		A matriz n�o � alterada.
*
***********************************************************************/
	
	MAT_tpCondRet MAT_confereVazia ( MAT_tppMatriz pMatriz );


/***********************************************************************
*
*	$FC Fun��o: MAT Obter Linhas
*
*	$ED Descri��o da fun��o
*		Retorna por refer�ncia o n�mero de linhas da matriz.
*		
*	$EP Par�metros
*		pMatriz		- Ponteiro para a matriz
*		refLinhas	- refer�ncia da vari�vel que armazenar� 
*					  o n�mero de linhas
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz v�lida.
*		refLinhas aponta para um inteiro v�lido.
* 
*   $AS Assertivas de sa�da 
*		A matriz n�o � alterada.
*		refNum aponta para um inteiro com o n�mero de linhas da 
*		matriz.
*
***********************************************************************/

	MAT_tpCondRet MAT_obterLinhas ( MAT_tppMatriz pMatriz, int* refLinhas ) ;


/***********************************************************************
*
*	$FC Fun��o: MAT Obter Colunas
*
*	$ED Descri��o da fun��o
*		Retorna por refer�ncia o n�mero de colunas da matriz.
*		
*	$EP Par�metros
*		pMatriz		- Ponteiro para a matriz
*		refColunas	- refer�ncia da vari�vel que armazenar� 
*					  o n�mero de linhas
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		refColunas aponta para um inteiro v�lido.
*		pMatriz aponta para uma matriz v�lida.
* 
*   $AS Assertivas de sa�da 
*		A matriz n�o � alterada.
*		refNum aponta para um inteiro com o n�mero de colunas da 
*		matriz.
*
***********************************************************************/
	
	MAT_tpCondRet MAT_obterColunas ( MAT_tppMatriz pMatriz, int* refLinhas ) ;



/*************Fim do m�dulo de defini��o: M�dulo Valor****************/

#endif

/***********************************************************************
*
*	$FC Fun��o: MAT Obter Dado
*
*	$ED Descri��o da fun��o
*		Retorna por refer�ncia um ponteiro para o dado apontado 
*		pelo elemento [linha][coluna] da matriz.
*		
*	$EP Par�metros
*		linha 	- indica a linha da matriz onde est� o elemento
*		coluna 	- indica a coluna da matriz onde est� o elemento	
*		refDado	- refer�ncia para o dado 
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		linha � menor ou igual ao n�mero de linhas da matriz.
*		coluna � menor ou igual ao n�mero de linhas da matriz.
* 		refDado � do mesmo tipo armazenado na matriz.
*		A matriz existe.
* 
*   $AS Assertivas de sa�da 
*		A matriz n�o � alterada.
*		refDado aponta para o dado contido no elemento [linha][coluna]
*		da matriz.
*
***********************************************************************

	MAT_tpCondRet MAT_obterDado ( int linha, int coluna, void* refDado);*/