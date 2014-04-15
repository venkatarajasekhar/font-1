/***************************************************************************
*
*	$MCD M�dulo de defini��o:	LIS	Lista gen�rica duplamente encadeada
*
*	Arquivo gerado:				LISTA.H
*	Letras identificadoras:		LIS
*
*	Nome da base de software:		Exemplo de teste automatizado
*	Arquivo da base de software:	ArcaboucoTeste.lib
*
*	Projeto:	Disciplinas INF 1301
*	Gestor:		Flavio Bevilacqua
*	Autores:	vyc, Victor Yves Crispim
*				sa, S�rgio Argolo
*				ft, Francisco Tacora
*
*	$HA Hist�rico de evolu��o:
*	Vers�o	Autor	Data		Observa��es
*	1.0		vyc		30/03/2014	In�cio do desenvolvimento
*
*	$ED Descri��o do m�dulo
*		Implementa listas gen�ricas duplamente encadeadas.
*		Podem existir n listas em opera��o simultaneamente.
*		As listas possuem uma cabe�a encapsulando o seu estado.
*
*		Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*		Cada elemento da lista referencia o valor que cont�m.
*
*		Os ponteiros para os dados s�o copiados para elementos da lista.
*		N�o � copiado o valor apontado por estes ponteiros.
*
*		O controle da destrui��o do valor de um elemento a ser exclu�do
*		� realizado por uma fun��o fornecida pelo usu�rio.
*
*		Cada lista referencia uma fun��o que determina como devem ser
*		desalocados os dados referenciados em cada elemento. 
*		Caso essa fun��o seja NULL, os dados n�o s�o desalocados.
*
***************************************************************************/



/********************* Diretivas de Pr�-Processamento *********************/

#ifndef LISTA_ 
#define LISTA_



/******************* Declara��es exportadas pelo m�dulo *******************/

/* Tipo ponteiro para uma lista */

typedef struct LIS_tagLista* LIS_tppLista ;



/***************************************************************************
*
*	$TC Tipo de dados: LIS Condi��es de retorno
*
***************************************************************************/

	typedef enum {
	
		LIS_CondRetOK = 0 ,
			/* Concluiu corretamente */
	
		LIS_CondRetListaVazia = 1 ,
			/* A lista n�o cont�m elementos */
	
		LIS_CondRetFimLista = 2 ,
			/* Foi atingido o fim de lista */
	
		LIS_CondRetFaltouMemoria = 3
			/* Faltou mem�ria ao tentar criar um elemento de lista */
	
	} LIS_tpCondRet ;

/***************************************************************************
*
*	$FC Fun��o: LIS  Criar lista
*
*	$ED Descri��o da fun��o
*		Cria uma lista gen�rica duplamente encadeada.
*		Os poss�veis tipos s�o desconhecidos a priori.
*		A tipagem � implicita.
*		N�o existe identificador de tipo associado � lista.
*
*	$EP Par�metros
*		refLista	  -	Refer�ncia para lista criada
*		ExcluirValor  -	Ponteiro para a fun��o que processa a exclus�o 
*						do valor referenciado pelo elemento a ser exclu�do
*		
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		refLista referencia um ponteiro livre para uma nova lista.
*		O ponteiro para fun��o ExcluirValor deve estar de acordo com
*		a libera��o de mem�ria desejada. 
*
*   $AS Assertivas de sa�da 
*		Se OK, refLista apontar� para uma lista criada corretamente
*		Sen�o, refLista apontar� para um ponteiro nulo.
*
***************************************************************************/

LIS_tpCondRet LIS_CriarLista (	LIS_tppLista * refLista, void(*ExcluirValor)(void * pDado) );


/***************************************************************************
*
*	$FC Fun��o: LIS  Obter N�mero de Elementos
*
*	$ED Descri��o da fun��o
*		Retorna por refer�ncia o n�mero de elementos contidos na lista.
*
*	$EP Par�metros
*		pLista	- Ponteiro para a lista que ser� utilizada
*		refNum	- Refer�ncia para retorno do n�mero de elementos da lista
*
*	$FV Valor retornado
*		LIS_CondRetOK
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista v�lida.
*		refNum deve apontar para um inteiro v�lido.
* 
*   $AS Assertivas de sa�da 
*		refNum aponta para um inteiro com o n�mero de elementos da 
*		lista. 
*
***************************************************************************/

LIS_tpCondRet LIS_ObterNumElem ( LIS_tppLista pLista, int * refNum ) ; 


/***************************************************************************
*
*	$FC Fun��o: LIS Destruir lista
*
*	$ED Descri��o da fun��o
*		Destr�i toda a lista fornecida. 
*		N�o modifica o ponteiro passado, deve-se atribur NULL a este
*		ap�s a chamada da fun��o.
*
*	$EP Par�metros
*		pLista - Ponteiro para a lista que ser� destru�da
*
*	$FV Valor retornado
*		LIS_CondRetOK
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista que existe.
* 
*   $AS Assertivas de sa�da 
*		A lista passada foi liberada corretamente.
*
***************************************************************************/

LIS_tpCondRet LIS_DestruirLista ( LIS_tppLista pLista ) ;


/***************************************************************************
*
*	$FC Fun��o: LIS Esvaziar lista
*
*	$ED Descri��o da fun��o
*		Elimina todos os elementos, sem contudo eliminar a lista.
*
*	$EP Par�metros
*		pLista - Ponteiro para a lista que ser� esvaziada
*
*	$FV Valor retornado
*		LIS_CondRetOK
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista v�lida que deve ser esvaziada.
* 
*   $AS Assertivas de sa�da 
*		pLista aponta para a mesma lista, por�m sem elementos.
*
***************************************************************************/

LIS_tpCondRet LIS_EsvaziarLista ( LIS_tppLista pLista ) ;


/***************************************************************************
*
*	$FC Fun��o: LIS Inserir Elemento Antes
*
*	$ED Descri��o da fun��o
*		Insere novo elemento antes do elemento corrente.
*		Caso a lista esteja vazia, insere o primeiro elemento da lista.
*		Altera o corrente para o novo elemento inserido.
*
*	$EP Par�metros
*		pLista	- Ponteiro para a lista que ser� utilizada
*		pValor	- Ponteiro para o valor do elemento adicionado
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista v�lida.
*		pValor contem o valor que ser� inserido e � diferente de NULL.
* 
*   $AS Assertivas de sa�da 
*		Se OK, o elemento foi inserido com sucesso e o corrente passa
*		a ser o novo elemento.
*		Sen�o, o estado original da lista � inalterado.
*
***************************************************************************/

LIS_tpCondRet LIS_InserirElementoAntes ( LIS_tppLista pLista , void * pValor ) ;


/***************************************************************************
*
*	$FC Fun��o: LIS Inserir elemento ap�s
*
*	$ED Descri��o da fun��o
*		Insere novo elemento ap�s do elemento corrente.
*		Caso a lista esteja vazia, insere o primeiro elemento da lista.
*		Altera o corrente para o novo elemento inserido.
*
*	$EP Par�metros
*		pLista	- Ponteiro para a lista que ser� utilizada
*		pValor	- Ponteiro para o valor do elemento adicionado
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista v�lida.
*		pValor contem o valor que ser� inserido e � diferente de NULL.
*
*   $AS Assertivas de sa�da 
*		Se OK, o elemento foi inserido com sucesso e o corrente passa
*		a ser o novo elemento.
*		Sen�o, o estado original da lista � inalterado.
*
***************************************************************************/

LIS_tpCondRet LIS_InserirElementoApos ( LIS_tppLista pLista	, void * pValor ) ;


/***************************************************************************
*
*	$FC Fun��o: LIS  Excluir elemento
*
*	$ED Descri��o da fun��o
*		Exclui o elemento corrente da lista dada.
*		Se existir o elemento � esquerda do corrente, esse ser� o novo corrente.
*		Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*		Se este tamb�m n�o existir a lista torna-se vazia.
*
*	$EP Par�metros
*		pLista	- Ponteiro para a lista na qual deve excluir.
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetListaVazia
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista v�lida n�o vazia.
*		O elemento corrente deve ser o elemento que ser� exclu�do.
* 
*   $AS Assertivas de sa�da 
*		Se OK, o elemento corrente foi exclu�do e as assertivas 
*		estruturais da lista mant�m-se v�lidas.
*		Sen�o, o estado original da lista � inalterado.
*
***************************************************************************/

LIS_tpCondRet LIS_ExcluirElemento ( LIS_tppLista pLista ) ;


/***************************************************************************
*
*	$FC Fun��o: LIS Obter Valor Corrente
*
*	$ED Descri��o da fun��o
*		Obtem a refer�ncia para o valor contido no elemento corrente da lista.
*
*	$EP Par�metros
*		pLista		- Ponteiro para a lista que ser� utilizada
*		refValor	- Refer�ncia para o valor do corrente
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetListaVazia
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista v�lida n�o vazia.
*		refValor � uma refer�ncia v�lida para ponteiro do tipo
*		armazenado.
* 
*   $AS Assertivas de sa�da 
*		Se OK, refValor referencia o valor armazenado.
*		Sen�o, refValor � inalterado.
*		Em ambos os casos a lista se mant�m inalterada.
*
***************************************************************************/

LIS_tpCondRet LIS_ObterValorCorrente ( LIS_tppLista pLista , void ** refValor ) ;


/***************************************************************************
*
*	$FC Fun��o: LIS  Ir para o In�cio da Lista
*
*	$ED Descri��o da fun��o
*		Torna corrente o primeiro elemento da lista.
*
*	$EP Par�metros
*		pLista	- Ponteiro para a lista que ser� utilizada
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetListaVazia
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista v�lida n�o vazia.
* 
*   $AS Assertivas de sa�da 
*		Se OK, o corrente da lista aponta para o primeiro elemento.
*		Sen�o, o estado original da lista � inalterado.
*
***************************************************************************/

 LIS_tpCondRet LIS_IrInicioLista ( LIS_tppLista pLista ) ;


/***************************************************************************
*
*	$FC Fun��o: LIS Ir para o Final da Lista
*
*	$ED Descri��o da fun��o
*		Torna corrente o �ltimo elemento da lista.
*
*	$EP Par�metros
*		pLista - ponteiro para a lista que ser� utilizada
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetListaVazia
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista v�lida n�o vazia.
* 
*   $AS Assertivas de sa�da 
*		Se OK, o corrente da lista aponta para o �ltimo elemento.
*		Sen�o, o estado original da lista � inalterado.
*
***************************************************************************/

LIS_tpCondRet LIS_IrFinalLista ( LIS_tppLista pLista ) ;


/***************************************************************************
*
*	$FC Fun��o: LIS Percorre Lista
*
*	$ED Descri��o da fun��o
*		Anda com o elemento corrente numElem elementos na lista.
*		Se numElem for positivo avan�a em dire��o ao final.
*		Se numElem for negativo avan�a em dire��o ao in�cio.
*		Se numElem for zero somente verifica se a lista est� vazia.
*		Se numElem for maior que o n�mero de movimentos poss�veis, a
*		fun��o retorna que alcan�ou o fim da lista.
*    
*	$EP Par�metros
*		pLista - ponteiro para a lista que ser� utilizada
*		numElem - o n�mero de elementos a andar
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetListaVazia
*		LIS_CondRetFimLista
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista v�lida.
*		numElem deve ser um inteiro definido corretamente de acordo
*		com a descri��o da fun��o.
* 
*   $AS Assertivas de sa�da 
*		Se OK, o elemento corrente ser� redefinido de acordo com
*		o par�metro numElem.
*		Se alcan�ou a fronteira, o corrente ser� o �ltimo ou o primeiro
*		elemento da lista, caso numElem seja positivo ou negativo
*		respectivamente.
*		Sen�o, a lista est� vazia.
*
***************************************************************************/

LIS_tpCondRet LIS_PercorreLista ( LIS_tppLista pLista , int numElem ) ;



/***************Fim do M�dulo de Defini��o: M�dulo Lista******************/

#endif
