/***************************************************************************
*
*	$MCD Módulo de definição: Módulo Valor
*
*	Arquivo gerado:				VALOR.H
*	Letras identificadoras:		VAL
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
*		manipular a estrutura valor.
*		O valor indica o número de células sequenciais que devem ser 
*		marcadas em determinada linha ou coluna para se descobrir 
*		o desenho oculto no jogo Nonogram.
*		Se a solução do valor for 1, ele foi resolvido corretamente.
*		Se a solução do valor for 0, ele não foi resolvido corretamente.
*		Na criação, o número de células do valor é NULL.
*
***************************************************************************/


/********************* Diretivas de Pré-Processamento *********************/

#ifndef VALOR_ 
#define VALOR_



/******************* Declarações exportadas pelo módulo *******************/

/* Tipo referência para um valor */

typedef struct VAL_tagValor* VAL_tppValor ;



/***********************************************************************
*
*  $TC Tipo de dados: VAL Condicoes de retorno
*
***********************************************************************/

	typedef enum {

			VAL_CondRetOK = 0 ,
			/* Executou corretamente */
			
			VAL_CondRetFaltouMemoria = 1
			/* Faltou memória ao alocar dados */

	} VAL_tpCondRet ;



/***********************************************************************
*
*	$FC Função:	VAL Cria Valor
*
*	$ED Descrição da função
*		Cria um novo valor.
*
*	$EP Parâmetros
*		refValor	-	Referência para o valor criado.
*		numCelulas	-	Inteiro representando o número de células
*						a que o valor se refere.
*		
*	$FV Valor retornado
*		VAL_tpCondRetOK
*		VAL_tpCondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		refValor referencia um ponteiro livre para um novo valor.
*		numCelulas é um inteiro maior que 0.
*		
*	$AS Assertivas de saída
*		Se OK, refValor apontará para o valor criado.
*		Caso contrário, refValor apontará para um ponteiro nulo.
*
***********************************************************************/

	VAL_tpCondRet VAL_criaValor ( VAL_tppValor* refValor, int numCelulas ) ;


/***********************************************************************
*
*	$FC Função:	VAL Destroi Valor
*
*	$ED Descrição da função
*		Destroi um valor.
*		Não modifica o ponteiro passado, deve-se atribur NULL a este
*		após a chamada da função.
*
*	$EP Parâmetros
*		$P pValor - Ponteiro para o valor a ser destruído.
*
*	$FV Valor retornado
*		VAL_tpCondRetOK;
*
*   $AE Assertivas de entrada 
*		pValor aponta para um valor válido.
*		
*	$AS Assertivas de saída
*		O valor foi liberado corretamente.
*.
***********************************************************************/

	VAL_tpCondRet VAL_destroiValor ( VAL_tppValor pValor ) ;


/***********************************************************************
*
*	$FC Função:	VAL Confere Solução
*
*	$ED Descrição da função
*		Confere se o valor está resolvido corretamente ou não.
*
*	$EP Parâmetros
*		$P	pValor		-	Ponteiro para o valor a ser consultado.
*			pSolucao	-	Ponteiro para a variável que vai armazenar
*							a solução do valor.
*
*	$FV Valor retornado
*		VAL_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pValor aponta para um valor válido.
*		pSolucao é um ponteiro para inteiro válido.
*		
*	$AS Assertivas de saída
*		O conteúdo de pSolucao recebe a solução do valor.
*		O valor não é alterado.
*
***********************************************************************/

	VAL_tpCondRet VAL_confereSolução ( VAL_tppValor pValor, int* pSolucao ) ;


/***********************************************************************
*
*	$FC Função:	VAL Define Solução
*
*	$ED Descrição da função
*		Define se o valor está resolvido ou não.
*
*	$EP Parâmetros
*		$P	pValor	- Ponteiro para o valor a ser alterado.
*			solucao	- Valor correspondente a solução desejada.
*
*	$FV Valor retornado
*		VAL_tpCondRetOK
*
*   $AE Assertivas de entrada 
*		pValor aponta para um valor válido.
*		solucao é um inteiro de valor 1 ou 0.
*		
*	$AS Assertivas de saída
*		O valor tem a sua solução alterada.
*
***********************************************************************/

	VAL_tpCondRet VAL_defineSolucao ( VAL_tppValor pValor, int solucao ) ;



/***********************************************************************
*
*	$FC Função:	VAL Obtem Número de Células
*
*	$ED Descrição da função
*		Retorna por referência o número de células a que o valor se refere.
*
*	$EP Parâmetros
*		$P pValor	-	Ponteiro para o valor a ser consultado.
*		$P pNumCel	-	Ponteiro para a variável que armazenará o número
*						de células.
*
*	$FV Valor retornado
*		VAL_CondRetOK
*
*   $AE Assertivas de entrada 
*		pValor aponta para um valor válido.
*		
*	$AS Assertivas de saída
*		O conteúdo de pNumCel recebe o número de células do valor.
*		O valor não é alterado.
*
***********************************************************************/

	int VAL_obtemNumeroCelulas ( VAL_tppValor pValor, int* pNumCel ) ;



/*************Fim do módulo de definição: Módulo Valor****************/

#endif