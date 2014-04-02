/***************************************************************************
*
*	$MCD Módulo de definição: Módulo Célula
*
*	Arquivo gerado:				CELULA.H
*	Letras identificadoras:		CEL
*
*	Nome da base de software:		Exemplo de teste automatizado
*	Arquivo da base de software:	ArcaboucoTeste.lib
*
*	Projeto:	Disciplinas INF 1301
*	Gestor:		Flavio Bevilacqua
*	Autores:	vyc, Victor Yves Crispim
*				sa, Sérgio Argolo
*				ft, Francisco Tacora
*
*	$HA Histórico de evolução:
*	Versão	Autor	Data		Observações
*	1.0		vyc		30/03/2014	Início do desenvolvimento
*
*	$ED Descrição do módulo
*		Este módulo implementa um conjunto de funções para criar e
*		manipular a estrutura célula, elemento básico do jogo Nonogram.
*		Ela armazena o estado da célula de acordo com a entrada fornecida
*		pelo usuário no modo Desafio, que pode ser: marcada, descartada e nulo.
*		Se o estado de uma célula é 1, ela pertence ao desenho.
*		Se o estado de uma célula é 2, ela não pertence ao desenho.
*		Se o estado de uma célula é NULL, o usuário ainda não interagiu
*		com tal célula.
*		A estrutura também armazena o estado correto da célula para
*		averiguar a corretude do desenho no modo Desafio.
*		Na criação, todos os campos são definidos como NULL.
*
***************************************************************************/



/********************* Diretivas de Pré-Processamento *********************/

#ifndef CELULA_ 
#define CELULA_



/******************* Declarações exportadas pelo módulo *******************/

/* Tipo ponteiro para uma célula */

typedef struct CEL_tagCelula* CEL_tppCelula ;



/***********************************************************************
*
*  $TC Tipo de dados: CEL Condicoes de retorno
*
***********************************************************************/

	typedef enum {

			CEL_CondRetOK = 0 ,
			/* Executou corretamente */

			CEL_CondRetFaltouMemoria = 1
			/* Faltou memória ao alocar dados */

	} CEL_tpCondRet ;



/***********************************************************************
*
*	$FC Função:	ARV Cria Célula
*
*	$ED Descrição da função
*		Cria uma nova célula com todos os campos nulos.
*
*	$EP Parâmetros
*		refCelula	  -	Referência para a célula criada
*
*	$FV Valor retornado
*		CEL_CondRetOK
*		CEL_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		refCelula referencia um ponteiro livre para uma nova célula.
*		
*	$AS Assertivas de saída
*		Se OK, refCelula apontará para a célula criada.
*		Caso contrário, refCelula apontará para um ponteiro nulo
*.
***********************************************************************/

	CEL_tpCondRet CEL_criaCelula ( CEL_tppCelula* refCelula );


/***********************************************************************
*
*	$FC Função:	CEL Destroi Célula
*
*	$ED Descrição da função
*		Destrói a célula fornecida.
*		Não modifica o ponteiro passado, deve-se atribur NULL a este
*		após a chamada da função.
*
*	$EP Parâmetros
*		$P pCelula	- Ponteiro para a célula que será destruída.  
*
*	$FV Valor retornado
*		CEL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pCelula aponta para uma célula válida.
*		
*	$AS Assertivas de saída
*		A célula foi liberada corretamente.
*.
***********************************************************************/

	CEL_tpCondRet CEL_destroiCelula ( CEL_tppCelula pCelula );


/***********************************************************************
*
*	$FC Função:	CEL Obtem Estado Atual
*
*	$ED Descrição da função
*		Retorna o estado atual da célula.
*
*	$EP Parâmetros
*		$P	pCelula	-	Ponteiro para a célula cujo estado atual 
*						será consultado.
*			pEstado	-	Ponteiro para a variável que armazenará o estado
*						da célula.
*
*	$FV Valor retornado
*		CEL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pCelula aponta para uma célula válida.
*		
*	$AS Assertivas de saída
*		O conteúdo de pEstado recebe o status atual da célula.
*		A célula não é alterada.
*
***********************************************************************/

	CEL_tpCondRet CEL_obtemEstadoAtual ( CEL_tppCelula pCelula, int* pEstado );


/***********************************************************************
*
*	$FC Função:	CEL Obtem Estado Correto
*
*	$ED Descrição da função
*		Retorna o estado correto da célula.
*
*	$EP Parâmetros
*		$P	pCelula	-	Ponteiro para a célula cuja solução será consultada.  
*			pEstado	-	Ponteiro para a variável que armazenará o estado
*						da célula.
*
*	$FV Valor retornado
*		CEL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pCelula aponta para uma célula válida.
*		
*	$AS Assertivas de saída
*		O conteúdo de pEstado recebe o status correto da célula.
*		A célula não é alterada.
*
***********************************************************************/

	CEL_tpCondRet CEL_obtemEstadoCorreto ( CEL_tppCelula pCelula, int* pEstado );


/***********************************************************************
*
*	$FC Função:	CEL Altera Estado Atual
*
*	$ED Descrição da função
*		Altera o estado atual da célula.
*
*	$EP Parâmetros
*		$P pCelula	- Referência para a célula cujo estado atual 
*					  será alterado. 
*		$P valor	- novo estado da célula.
*
*	$FV Valor retornado
*		CEL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pCelula aponta para uma célula válida.
*		valor é um inteiro entre [1..2] ou NULL.
*		
*	$AS Assertivas de saída
*		A célula apontada por pCelula tem seu estado atual alterado.
*
***********************************************************************/

	CEL_tpCondRet CEL_alteraEstadoAtual ( CEL_tppCelula pCelula , int valor );


/***********************************************************************
*
*	$FC Função:	CEL Altera Estado Correto
*
*	$ED Descrição da função
*		Altera o estado correto da célula.
*
*	$EP Parâmetros
*		$P pCelula	- Ponteiro para a célula cujo estado correto 
*					  será alterado. 
*		$P valor	- novo estado correto da célula.
*
*	$FV Valor retornado
*		CEL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pCelula aponta para uma célula válida.
*		valor é um inteiro entre [1..2] ou NULL. 
*		
*	$AS Assertivas de saída
*		A célula apontada por pCelula tem seu estado correto alterado.
*
***********************************************************************/

	CEL_tpCondRet CEL_alteraEstadoCorreto ( CEL_tppCelula pCelula, int valor );



/**************Fim do módulo de definição: Módulo Célula****************/

#endif