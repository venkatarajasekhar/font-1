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
*		A posi��o inicial da matriz � (0,0).
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
		
		MAT_CondRetFronteira = 1 ,
				//Movimento que leva para fora da matriz

		MAT_CondRetFaltouMemoria = 2
				//Faltou mem�ria ao tentar criar um elemento da matriz

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
*	$FC Fun��o: MAT Percorre Matriz
*
*	$ED Descri��o da fun��o
*		Anda com o elemento corrente para a posi��o linha x coluna.
*
*	$EP Par�metros
*		pMatriz	- Ponteiro para a matriz
*		linha	- Inteiro que indica a linha
*		coluna	- Inteiro que indica a coluna
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*		MAT_tpCondRetFronteira
*
*   $AE Assertivas de entrada
*		pMatriz aponta para uma matriz v�lida.
*		linha e coluna s�o menores ou iguais as dimens�es
*		da matriz.
*
*   $AS Assertivas de sa�da 
*		Se Ok, o elemento corrente da matriz � o elemento na posi��o
*		linha x coluna.
*		Sen�o, a matriz n�o � alterada.
*
***********************************************************************/
	
	MAT_tpCondRet MAT_percorreMatriz ( MAT_tppMatriz pMatriz, int linha, int coluna );


/***********************************************************************
*
*	$FC Fun��o: MAT Insere Dado
*
*	$ED Descri��o da fun��o
*		Atribui o dado passado para o elemento corrente da matriz. 
*		Se o elemento j� aponta para um dado, este ser� desalocado.
*
*	$EP Par�metros
*		pMatriz	- Ponteiro para a matriz cujo elemento ser� alterado	
*		pDado	- Ponteiro para o dado a ser apontado pelo elemento
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz v�lida.
* 		pDado contem o dado que ser� inserido e � diferente de NULL.
*
*   $AS Assertivas de sa�da 
*		O elemento na posi��o corrente da matriz aponta para o
*		dado passado.
*
***********************************************************************/

	MAT_tpCondRet MAT_insereDado ( MAT_tppMatriz pMatriz, void* pDado);


/***********************************************************************
*
*	$FC Fun��o: MAT Obter Valor Corrente
*
*	$ED Descri��o da fun��o
*		Retorna por refer�ncia um ponteiro para o dado apontado 
*		pelo elemento corrente da matriz.
*		
*	$EP Par�metros
*		pMatriz	- Ponteiro para a matriz.	
*		refDado	- Refer�ncia para o dado.
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz v�lida.
* 		refDado � do mesmo tipo armazenado na matriz.
* 
*   $AS Assertivas de sa�da 
*		A matriz n�o � alterada.
*		refDado aponta para o dado contido no elemento corrente
*		da matriz.
*
***********************************************************************/

	MAT_tpCondRet MAT_obterValorCorrente ( MAT_tppMatriz pMatriz, void** refDado);
	

/***********************************************************************
*
*	$FC Fun��o: MAT Obter Linhas
*
*	$ED Descri��o da fun��o
*		Informa a quantidade de linhas da matriz.
*		
*	$EP Par�metros
*		pMatriz	- Ponteiro para a matriz.	
*		pLinhas	- Ponteiro para o inteiro que receber�
*				  a quantidade de linhas.	
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz v�lida.
* 		pLinhas aponta para um inteiro.
* 
*   $AS Assertivas de sa�da 
*		A matriz n�o � alterada.
*		O conte�do pLinhas recebe n�mero
*		de linhas da matriz.
*
***********************************************************************/

	MAT_tpCondRet MAT_obterLinhas ( MAT_tppMatriz pMatriz, int* pLinhas );


/***********************************************************************
*
*	$FC Fun��o: MAT Obter Colunas
*
*	$ED Descri��o da fun��o
*		Informa a quantidade de colunas da matriz.
*		
*	$EP Par�metros
*		pMatriz		- Ponteiro para a matriz.	
*		pColunas	- Ponteiro para o inteiro que receber�
*					  a quantidade de colunas.	
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz v�lida.
* 		pColunas aponta para um inteiro.
* 
*   $AS Assertivas de sa�da 
*		A matriz n�o � alterada.
*		O conte�do pColunas recebe n�mero
*		de colunas da matriz.
*
***********************************************************************/

	MAT_tpCondRet MAT_obterColunas ( MAT_tppMatriz pMatriz, int* pColunas );


/***********************************************************************
*
*	$FC Fun��o: MAT Reseta Matriz
*
*	$ED Descri��o da fun��o
*		Desaloca todos os dados apontados pelos elementos da matriz, que
*		ent�o apontam para NULL.
*	
*	$EP Par�metros
*		pMatriz	- Ponteiro para a matriz a ser resetada.
*	
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz � um ponteiro para uma matriz v�lida.
*		Os elementos da matriz apontam para dados.
* 
*   $AS Assertivas de sa�da 
*		Os elementos da matriz apontada por pMatriz 
*		apontam para NULL.
*		O ponteiro para o elemento corrente aponta
*		para o elemento inicial.
*
***********************************************************************/

	MAT_tpCondRet MAT_resetaMatriz ( MAT_tppMatriz pMatriz );
	


/*************Fim do m�dulo de defini��o: M�dulo Valor****************/

#endif