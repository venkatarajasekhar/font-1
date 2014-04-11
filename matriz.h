/***************************************************************************
*
*	$MCD Módulo de definição: Módulo Matriz Genérica
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
*	$HA Histórico de evolução:
*		Versão	Autor	Data		Observações
*		1.0		vyc		05/04/2014	Início do Desenvolvimento
*
*	$ED Descrição do módulo
*		Implementa uma matriz genérica.
*		Podem existir n matrizes em operação simultaneamente.
*		A matriz está vazia após sua criação.
*		A matriz é homogênea quanto ao tipo de dado que armazena.
*		Os ponteiros para os dados são copiados para elementos da matriz.
*		Não é copiado o valor apontado por estes ponteiros.
*		O controle da destruição do valor de um elemento a ser excluído
*		é realizado por uma função fornecida pelo usuário.		
*		Cada matriz referencia uma função que determina como devem ser
*		desalocados os dados nela contidos.
*
***************************************************************************/



/********************* Diretivas de Pré-Processamento *********************/

	#ifndef MATRIZ_ 
	#define MATRIZ_



/******************* Declarações exportadas pelo módulo *******************/
	
	typedef struct MAT_tagMatriz* MAT_tppMatriz ;
				/*Tipo ponteiro para a cabeça de matriz*/


/***********************************************************************
*
*	$TC Tipo de dados: MAT Condições de retorno
*
*	$ED Descrição do tipo
*		Condições de retorno das funções da matriz
*
***********************************************************************/

	typedef enum {
		
		MAT_CondRetOK = 0 ,
				//Concluiu corretamente 
		
		MAT_CondRetFronteira = 1 ,
				//Movimento que leva para fora da matriz

		MAT_CondRetFaltouMemoria = 2
				//Faltou memória ao tentar criar um elemento da matriz

	} MAT_tpCondRet ;


/***********************************************************************
*
*	$FC Função: MAT Criar Matriz
*
*	$ED Descrição da função
*		Cria a estrutura matriz com o tamanho especificado nos parâmetros.
*
*	$EP Parâmetros
*		refMatriz	- Referência para a matriz criada
*		linhas 		- Determina a quantidade de linhas da matriz
*		colunas 	- Determina a quantidade de colunas da matriz
*		ExcluirDado - Ponteiro para a função que processa a exclusão 
*					  do valor referenciado por um elemento da matriz		
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		refLista referencia um ponteiro livre para a nova matriz
*		O ponteiro para função ExcluirValor deve estar de acordo com
*		a liberação de memória desejada.
* 
*   $AS Assertivas de saída 
*		Se OK, refMatriz aponta para a matriz criada.
*		Do contrário, a matriz não é criada.
*
***********************************************************************/

	MAT_tpCondRet MAT_criaMatriz ( MAT_tppMatriz* refMatriz, int linhas, int colunas,
												 void (*ExcluirDado) (void* pDado) );


/***********************************************************************
*
*	$FC Função: MAT Destroi Matriz
*
*	$ED Descrição da função
*		Destroi a matriz, desalocando seus elementos.
*		Não modifica o ponteiro passado, deve-se atribur NULL a este
*		após a chamada da função.
*
*	$EP Parâmetros
*		pMatriz	- Ponteiro para a matriz a ser destruida
*	
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz existente.
* 
*   $AS Assertivas de saída 
*		A matriz e seus elementos foram desalocados.
*
***********************************************************************/

	MAT_tpCondRet MAT_destroiMatriz ( MAT_tppMatriz pMatriz );


/***********************************************************************
*
*	$FC Função: MAT Percorre Matriz
*
*	$ED Descrição da função
*		Anda com o elemento corrente na direção escolhida.
*		As direções são Cima, Baixo, Esquerda e Direita.
*
*	$EP Parâmetros
*		pMatriz	-	Ponteiro para a matriz
*		direcao	-	Inteiro representando a direção do movimento. 
*					0 = Cima, 1 = Direta, 2 = Baixo, 3 = Esquerda.
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*		MAT_tpCondRetFronteira
*
*   $AE Assertivas de entrada
*		pMatriz aponta para uma matriz válida.
*		direcao varia entre [0,3].
*
*   $AS Assertivas de saída 
*		O elemento corrente da matriz é o elemento apontado
*		pelo corrente anterior na direção indicada.
*
***********************************************************************/
	
	MAT_tpCondRet MAT_percorreMatriz ( MAT_tppMatriz pMatriz, int direcao );


/***********************************************************************
*
*	$FC Função: MAT Insere Dado
*
*	$ED Descrição da função
*		Atribui o dado passado para o elemento corrente da matriz. 
*		Se o elemento já aponta para um dado, este será desalocado.
*
*	$EP Parâmetros
*		pMatriz	- Ponteiro para a matriz cujo elemento será alterado	
*		pDado	- Ponteiro para o dado a ser apontado pelo elemento
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz válida.
* 		pDado contem o dado que será inserido e é diferente de NULL.
*
*   $AS Assertivas de saída 
*		O elemento na posição corrente da matriz aponta para o
*		dado passado.
*
***********************************************************************/

	MAT_tpCondRet MAT_insereDado ( MAT_tppMatriz pMatriz, void* pDado);


/***********************************************************************
*
*	$FC Função: MAT Obter Valor Corrente
*
*	$ED Descrição da função
*		Retorna por referência um ponteiro para o dado apontado 
*		pelo elemento corrente da matriz.
*		
*	$EP Parâmetros
*		pMatriz	- Ponteiro para a matriz.	
*		refDado	- Referência para o dado.
*
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz aponta para uma matriz válida.
* 		refDado é do mesmo tipo armazenado na matriz.
* 
*   $AS Assertivas de saída 
*		A matriz não é alterada.
*		refDado aponta para o dado contido no elemento corrente
*		da matriz.
*
***********************************************************************/

	MAT_tpCondRet MAT_obterValorCorrente ( MAT_tppMatriz pMatriz, void** refDado);
	

/***********************************************************************
*
*	$FC Função: MAT Reseta Matriz
*
*	$ED Descrição da função
*		Desaloca todos os dados apontados pelos elementos da matriz, que
*		então apontam para NULL.
*	
*	$EP Parâmetros
*		pMatriz	- Ponteiro para a matriz a ser resetada.
*	
*	$FV Valor retornado
*		MAT_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pMatriz é um ponteiro para uma matriz válida.
*		Os elementos da matriz apontam para dados.
* 
*   $AS Assertivas de saída 
*		Os elementos da matriz apontada por pMatriz 
*		apontam para NULL.
*		O ponteiro para o elemento corrente aponta
*		para o elemento inicial.
*
***********************************************************************/

	MAT_tpCondRet MAT_resetaMatriz ( MAT_tppMatriz pMatriz );
	


/*************Fim do módulo de definição: Módulo Valor****************/

#endif