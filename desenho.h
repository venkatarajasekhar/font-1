/***************************************************************************
*
*	$MCD M�dulo de defini��o: M�dulo Desenho
*
*	Arquivo gerado:				desenho.h
*	Letras identificadoras:		DES
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
*	1.0		vyc		11/04/2014	In�cio do desenvolvimento
*
*	$ED Descri��o do m�dulo
*		Este � o m�dulo respons�vel pela cria��o e manipula��o
*		do desenho no jogo Nonogram.
*		S� existe um desenho em execu��o de cada vez.
*		Cada desenho possui 10 hints.
*		Um desenho pode ser salvo a qualquer momento
*		e carregado posteriormente.
*
***************************************************************************/


/********************* Diretivas de Pr�-Processamento *********************/

#ifndef DESENHO_ 
#define DESENHO_



/****************** Declara��es exportadas pelo m�dulo *******************/

	typedef void(*ExcluirValor)(void *);


/*************************************************************************
*
*  $TC Tipo de dados: DES Condicoes de retorno
*
*************************************************************************/

	typedef enum {

			DES_CondRetOK = 0 ,
			/* Executou corretamente */
			
			DES_CondRetEstadoInvalido = 1 ,
			/*O estado passado � invalido*/

			DES_CondRetErroAberturaArquivo = 2 ,
			/*O arquivo n�o p�de ser aberto*/

			DES_CondRetDesenhoExistente = 3,
			/*J� existe um desenho criado*/

			DES_CondRetCelulaNula = 4,
			/*O estado correto de uma das c�lulas � nulo*/

			DES_CondRetDesenhoCorreto = 5,
			/*O desenho foi preenchido corretamente*/

			DES_CondRetDesenhoIncorreto = 6,
			/*O desenho n�o foi preenchido corretamente*/

			DES_CondRetSemHints = 7,
			/*Todas as dicas j� foram utilizadas*/

			DES_CondRetFaltouMemoria = 8
			/* Faltou mem�ria ao alocar dados */

	} DES_tpCondRet ;



/***********************************************************************
*
*	$FC Fun��o:	DES Cria Desenho
*
*	$ED Descri��o da fun��o
*		Cria uma nova estrutura desenho caso nenhuma exista.
*
*	$EP Par�metros
*		linhas	- Inteiro representando o n�mero de linhas do desenho 
*		colunas	- Inteiro representando o n�mero de colunas do desenho 
*		nome	- String identificadora do desenho.
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetDesenhoExistente
*		DES_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		linhas e colunas s�o inteiros positivos.
*		nome nunca foi utilizado na cria��o de outro desenho.
*		
*	$AS Assertivas de sa�da
*		Se OK, a estrutura desenho � criada.
*		Sen�o, a estrutura desenho n�o � criada.
*
**********************************************************************/

	DES_tpCondRet DES_criaDesenho ( int linhas, int colunas, char* nome );


/***********************************************************************
*
*	$FC Fun��o:	DES Destroi Desenho
*
*	$ED Descri��o da fun��o
*		Destroi a estrutura desenho.
*
*	$FV Valor retornado
*		DES_CondRetOK
*
*   $AE Assertivas de entrada 
*		O desenho existe.
*
*	$AS Assertivas de sa�da
*		A estrutura desenho e seu conte�do foram desalocados.
*
**********************************************************************/

	DES_tpCondRet DES_destroiDesenho (void);


/***********************************************************************
*
*	$FC Fun��o:	DES Modifica C�lula Correto
*
*	$ED Descri��o da fun��o
*		Modifica o status correto de uma c�lula.
*
*	$EP Par�metros
*		linha	- Inteiro indicando a linha da c�lula
*		coluna	- Inteiro indicando a coluna da c�lula
*		estado	- Caracter indicando o estado a ser atribu�do.
*				  'm' para marcada
*				  'd' para desmarcada
*				  'n' para nulo
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetEstadoInvalido;
*
*   $AE Assertivas de entrada
*		O desenho est� criado.
*		linha e coluna s�o menores ou iguais as dimens�es da matriz.
*		
*	$AS Assertivas de sa�da
*		A c�lula na posi��o linha x coluna teve seu estado correto
*		alterado.
*
**********************************************************************/

	DES_tpCondRet DES_modificaCelulaCorreto ( int linha, int coluna, char estado );


/***********************************************************************
*
*	$FC Fun��o:	DES Modifica C�lula Atual
*
*	$ED Descri��o da fun��o
*		Modifica o status atual de uma c�lula.
*
*	$EP Par�metros
*		linha	- Inteiro indicando a linha da c�lula
*		coluna	- Inteiro indicando a coluna da c�lula
*		estado	- Caracter indicando o estado a ser atribu�do.
*				  'm' para marcada
*				  'd' para desmarcada
*				  'n' para nulo
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetEstadoInvalido;
*
*   $AE Assertivas de entrada
*		O desenho est� criado.
*		linha e coluna s�o menores ou iguais as dimens�es da matriz.
*		
*	$AS Assertivas de sa�da
*		A c�lula na posi��o linha x coluna teve seu estado atual
*		alterado.
*
**********************************************************************/

	DES_tpCondRet DES_modificaCelulaAtual ( int linha, int coluna, char estado);


/***********************************************************************
*
*	$FC Fun��o:	DES Calcula Valores
*
*	$ED Descri��o da fun��o
*		Calcula os valores de acordo com o status das c�lulas 
*		da matriz e os atribui a suas respectivas listas.
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		O desenho foi criado
*		
*	$AS Assertivas de sa�da
*		As listas horizontais e verticais do desenho 
*		s�o preenchidas com os valores.
*
**********************************************************************/

	DES_tpCondRet DES_calculaValores ( void );

	
/***********************************************************************
*
*	$FC Fun��o:	DES Confere Solu��o dos Valores
*
*	$ED Descri��o da fun��o
*		Analisa as c�lulas do desenho para averiguar se os valores
*		foram marcados corretamente.
*
*	$FV Valor retornado
*		DES_CondRetOK
*
*   $AE Assertivas de entrada 
*		O desenho foi criado.
*		Os valores foram calculados.
*		
*	$AS Assertivas de sa�da
*		Se as c�lulas foram preenchidas corretamente, o respectivo
*		valor � marcado como resolvido.
*		Do contr�rio, o valor � marcado como n�o resolvido.
*
**********************************************************************/
	
	DES_tpCondRet DES_confereSolucaoValores ( void );


/***********************************************************************
*
*	$FC Fun��o:	DES Salva Desenho
*
*	$ED Descri��o da fun��o
*		Cria um arquivo que armazena todas as informa��es do desenho.
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetErroAberturaArquivo
*
*   $AE Assertivas de entrada 
*		O desenho foi criado.
*		As listas de valores horizontais e verticais 
*		foram inicializadas.
*		
*	$AS Assertivas de sa�da
*		Um arquivo .txt nomeado de acordo com o nome do desenho
*		contendo a dimens�o da matriz e as listas de valores
*		horizontais e verticais.
*
**********************************************************************/	
	
	DES_tpCondRet DES_salvaDesenho (void);


/***********************************************************************
*
*	$FC Fun��o:	DES Carrega Desenho
*
*	$ED Descri��o da fun��o
*		Cria um novo desenho nome_desenho com as informa��es contidas 
*		no arquivo nome_desenho.txt. Se j� existir um desenho ativo, 
*		este ser� destru�do.
*
*	$EP Par�metros
*		nome_desenho - String que identifica o desenho a ser carregado.
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetErroAberturaArquivo
*		DES_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		O arquivo nome_desenho.txt n�o est� vazio e est� formatado corretamente.
*		
*	$AS Assertivas de sa�da
*		� criado um novo desenho com as informa��es
*		contidas no arquivo.
*
**********************************************************************/

	DES_tpCondRet DES_carregaDesenho ( char* nome_desenho );


/***********************************************************************
*
*	$FC Fun��o:	DES Confere Conclus�o do Desenho
*
*	$ED Descri��o da fun��o
*		Confere se todas as c�lulas do desenho foram
*		marcadas corretamente.
*
*	$FV Valor retornado
*		DES_CondRetDesenhoCorreto
*		DES_CondRetDesenhoIncorreto
*
*   $AE Assertivas de entrada 
*		O desenho foi criado.
*		
*	$AS Assertivas de sa�da
*		O desenho n�o � alterado.
*
**********************************************************************/

	DES_tpCondRet DES_confereConclusaoDesenho ( void );


/***********************************************************************
*
*	$FC Fun��o:	DES Usa Dica
*
*	$ED Descri��o da fun��o
*		Marca uma c�lula corretamente, se o usu�rio ainda tiver
*		hints dispon�veis.
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetDesenhoConcluido
*		DES_CondRetSemHints
*
*   $AE Assertivas de entrada 
*		O desenho foi criado.
*		
*	$AS Assertivas de sa�da
*		Se OK, uma c�lula � marcada corretamente.
*		Do contr�rio, nada acontece.
*
**********************************************************************/

	DES_tpCondRet DES_usaDica( void );



/************Fim do m�dulo de defini��o: M�dulo Desenho***************/

#endif