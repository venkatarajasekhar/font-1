/***************************************************************************
*
*	$MCD Módulo de definição:	LIS	Lista genérica duplamente encadeada
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
*				sa, Sérgio Argolo
*				ft, Francisco Tacora
*
*	$HA Histórico de evolução:
*	Versão	Autor	Data		Observações
*	1.0		vyc		30/03/2014	Início do desenvolvimento
*
*	$ED Descrição do módulo
*		Implementa listas genéricas duplamente encadeadas.
*		Podem existir n listas em operação simultaneamente.
*		As listas possuem uma cabeça encapsulando o seu estado.
*
*		Cada lista é homogênea quanto ao tipo dos dados que armazena.
*		Cada elemento da lista referencia o valor que contém.
*
*		Os ponteiros para os dados são copiados para elementos da lista.
*		Não é copiado o valor apontado por estes ponteiros.
*
*		O controle da destruição do valor de um elemento a ser excluído
*		é realizado por uma função fornecida pelo usuário.
*
*		Cada lista referencia uma função que determina como devem ser
*		desalocados os dados referenciados em cada elemento. 
*		Caso essa função seja NULL, os dados não são desalocados.
*
***************************************************************************/



/********************* Diretivas de Pré-Processamento *********************/

#ifndef LISTA_ 
#define LISTA_



/******************* Declarações exportadas pelo módulo *******************/

/* Tipo ponteiro para uma lista */

typedef struct LIS_tagLista* LIS_tppLista ;



/***************************************************************************
*
*	$TC Tipo de dados: LIS Condições de retorno
*
***************************************************************************/

	typedef enum {
	
		LIS_CondRetOK = 0 ,
			/* Concluiu corretamente */
	
		LIS_CondRetListaVazia = 1 ,
			/* A lista não contém elementos */
	
		LIS_CondRetFimLista = 2 ,
			/* Foi atingido o fim de lista */
	
		LIS_CondRetFaltouMemoria = 3
			/* Faltou memória ao tentar criar um elemento de lista */
	
	} LIS_tpCondRet ;

/***************************************************************************
*
*	$FC Função: LIS  Criar lista
*
*	$ED Descrição da função
*		Cria uma lista genérica duplamente encadeada.
*		Os possíveis tipos são desconhecidos a priori.
*		A tipagem é implicita.
*		Não existe identificador de tipo associado à lista.
*
*	$EP Parâmetros
*		refLista	  -	Referência para lista criada
*		ExcluirValor  -	Ponteiro para a função que processa a exclusão 
*						do valor referenciado pelo elemento a ser excluído
*		
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		refLista referencia um ponteiro livre para uma nova lista.
*		O ponteiro para função ExcluirValor deve estar de acordo com
*		a liberação de memória desejada. 
*
*   $AS Assertivas de saída 
*		Se OK, refLista apontará para uma lista criada corretamente
*		Senão, refLista apontará para um ponteiro nulo.
*
***************************************************************************/

LIS_tpCondRet LIS_CriarLista (	LIS_tppLista * refLista, void(*ExcluirValor)(void * pDado) );


/***************************************************************************
*
*	$FC Função: LIS  Obter Número de Elementos
*
*	$ED Descrição da função
*		Retorna por referência o número de elementos contidos na lista.
*
*	$EP Parâmetros
*		pLista	- Ponteiro para a lista que será utilizada
*		refNum	- Referência para retorno do número de elementos da lista
*
*	$FV Valor retornado
*		LIS_CondRetOK
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista válida.
*		refNum deve apontar para um inteiro válido.
* 
*   $AS Assertivas de saída 
*		refNum aponta para um inteiro com o número de elementos da 
*		lista. 
*
***************************************************************************/

LIS_tpCondRet LIS_ObterNumElem ( LIS_tppLista pLista, int * refNum ) ; 


/***************************************************************************
*
*	$FC Função: LIS Destruir lista
*
*	$ED Descrição da função
*		Destrói toda a lista fornecida. 
*		Não modifica o ponteiro passado, deve-se atribur NULL a este
*		após a chamada da função.
*
*	$EP Parâmetros
*		pLista - Ponteiro para a lista que será destruída
*
*	$FV Valor retornado
*		LIS_CondRetOK
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista que existe.
* 
*   $AS Assertivas de saída 
*		A lista passada foi liberada corretamente.
*
***************************************************************************/

LIS_tpCondRet LIS_DestruirLista ( LIS_tppLista pLista ) ;


/***************************************************************************
*
*	$FC Função: LIS Esvaziar lista
*
*	$ED Descrição da função
*		Elimina todos os elementos, sem contudo eliminar a lista.
*
*	$EP Parâmetros
*		pLista - Ponteiro para a lista que será esvaziada
*
*	$FV Valor retornado
*		LIS_CondRetOK
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista válida que deve ser esvaziada.
* 
*   $AS Assertivas de saída 
*		pLista aponta para a mesma lista, porém sem elementos.
*
***************************************************************************/

LIS_tpCondRet LIS_EsvaziarLista ( LIS_tppLista pLista ) ;


/***************************************************************************
*
*	$FC Função: LIS Inserir Elemento Antes
*
*	$ED Descrição da função
*		Insere novo elemento antes do elemento corrente.
*		Caso a lista esteja vazia, insere o primeiro elemento da lista.
*		Altera o corrente para o novo elemento inserido.
*
*	$EP Parâmetros
*		pLista	- Ponteiro para a lista que será utilizada
*		pValor	- Ponteiro para o valor do elemento adicionado
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista válida.
*		pValor contem o valor que será inserido e é diferente de NULL.
* 
*   $AS Assertivas de saída 
*		Se OK, o elemento foi inserido com sucesso e o corrente passa
*		a ser o novo elemento.
*		Senão, o estado original da lista é inalterado.
*
***************************************************************************/

LIS_tpCondRet LIS_InserirElementoAntes ( LIS_tppLista pLista , void * pValor ) ;


/***************************************************************************
*
*	$FC Função: LIS Inserir elemento após
*
*	$ED Descrição da função
*		Insere novo elemento após do elemento corrente.
*		Caso a lista esteja vazia, insere o primeiro elemento da lista.
*		Altera o corrente para o novo elemento inserido.
*
*	$EP Parâmetros
*		pLista	- Ponteiro para a lista que será utilizada
*		pValor	- Ponteiro para o valor do elemento adicionado
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista válida.
*		pValor contem o valor que será inserido e é diferente de NULL.
*
*   $AS Assertivas de saída 
*		Se OK, o elemento foi inserido com sucesso e o corrente passa
*		a ser o novo elemento.
*		Senão, o estado original da lista é inalterado.
*
***************************************************************************/

LIS_tpCondRet LIS_InserirElementoApos ( LIS_tppLista pLista	, void * pValor ) ;


/***************************************************************************
*
*	$FC Função: LIS  Excluir elemento
*
*	$ED Descrição da função
*		Exclui o elemento corrente da lista dada.
*		Se existir o elemento à esquerda do corrente, esse será o novo corrente.
*		Se não existir e existir o elemento à direita, este se tornará corrente.
*		Se este também não existir a lista torna-se vazia.
*
*	$EP Parâmetros
*		pLista	- Ponteiro para a lista na qual deve excluir.
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetListaVazia
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista válida não vazia.
*		O elemento corrente deve ser o elemento que será excluído.
* 
*   $AS Assertivas de saída 
*		Se OK, o elemento corrente foi excluído e as assertivas 
*		estruturais da lista mantêm-se válidas.
*		Senão, o estado original da lista é inalterado.
*
***************************************************************************/

LIS_tpCondRet LIS_ExcluirElemento ( LIS_tppLista pLista ) ;


/***************************************************************************
*
*	$FC Função: LIS Obter Valor Corrente
*
*	$ED Descrição da função
*		Obtem a referência para o valor contido no elemento corrente da lista.
*
*	$EP Parâmetros
*		pLista		- Ponteiro para a lista que será utilizada
*		refValor	- Referência para o valor do corrente
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetListaVazia
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista válida não vazia.
*		refValor é uma referência válida para ponteiro do tipo
*		armazenado.
* 
*   $AS Assertivas de saída 
*		Se OK, refValor referencia o valor armazenado.
*		Senão, refValor é inalterado.
*		Em ambos os casos a lista se mantém inalterada.
*
***************************************************************************/

LIS_tpCondRet LIS_ObterValorCorrente ( LIS_tppLista pLista , void ** refValor ) ;


/***************************************************************************
*
*	$FC Função: LIS  Ir para o Início da Lista
*
*	$ED Descrição da função
*		Torna corrente o primeiro elemento da lista.
*
*	$EP Parâmetros
*		pLista	- Ponteiro para a lista que será utilizada
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetListaVazia
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista válida não vazia.
* 
*   $AS Assertivas de saída 
*		Se OK, o corrente da lista aponta para o primeiro elemento.
*		Senão, o estado original da lista é inalterado.
*
***************************************************************************/

 LIS_tpCondRet LIS_IrInicioLista ( LIS_tppLista pLista ) ;


/***************************************************************************
*
*	$FC Função: LIS Ir para o Final da Lista
*
*	$ED Descrição da função
*		Torna corrente o último elemento da lista.
*
*	$EP Parâmetros
*		pLista - ponteiro para a lista que será utilizada
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetListaVazia
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista válida não vazia.
* 
*   $AS Assertivas de saída 
*		Se OK, o corrente da lista aponta para o último elemento.
*		Senão, o estado original da lista é inalterado.
*
***************************************************************************/

LIS_tpCondRet LIS_IrFinalLista ( LIS_tppLista pLista ) ;


/***************************************************************************
*
*	$FC Função: LIS Percorre Lista
*
*	$ED Descrição da função
*		Anda com o elemento corrente numElem elementos na lista.
*		Se numElem for positivo avança em direção ao final.
*		Se numElem for negativo avança em direção ao início.
*		Se numElem for zero somente verifica se a lista está vazia.
*		Se numElem for maior que o número de movimentos possíveis, a
*		função retorna que alcançou o fim da lista.
*    
*	$EP Parâmetros
*		pLista - ponteiro para a lista que será utilizada
*		numElem - o número de elementos a andar
*
*	$FV Valor retornado
*		LIS_CondRetOK
*		LIS_CondRetListaVazia
*		LIS_CondRetFimLista
*
*   $AE Assertivas de entrada 
*		pLista aponta para a lista válida.
*		numElem deve ser um inteiro definido corretamente de acordo
*		com a descrição da função.
* 
*   $AS Assertivas de saída 
*		Se OK, o elemento corrente será redefinido de acordo com
*		o parâmetro numElem.
*		Se alcançou a fronteira, o corrente será o último ou o primeiro
*		elemento da lista, caso numElem seja positivo ou negativo
*		respectivamente.
*		Senão, a lista está vazia.
*
***************************************************************************/

LIS_tpCondRet LIS_PercorreLista ( LIS_tppLista pLista , int numElem ) ;



/***************Fim do Módulo de Definição: Módulo Lista******************/

#endif
