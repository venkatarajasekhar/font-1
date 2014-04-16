/***************************************************************************
*
*	$MCD Módulo de definição: Módulo Desenho
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
*				sa, Sérgio Argolo	
*				ft, Francisco Tacora
*
*	$HA Histórico de evolução:
*	Versão	Autor	Data		Observações
*	1.0		vyc		11/04/2014	Início do desenvolvimento
*
*	$ED Descrição do módulo
*		Este é o módulo responsável pela criação e manipulação
*		do desenho no jogo Nonogram.
*		Só existe um desenho em execução de cada vez.
*		Cada desenho possui 10 hints.
*		Um desenho pode ser salvo a qualquer momento
*		e carregado posteriormente.
*
***************************************************************************/


/********************* Diretivas de Pré-Processamento *********************/

#ifndef DESENHO_ 
#define DESENHO_



/****************** Declarações exportadas pelo módulo *******************/

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
			/*O estado passado é invalido*/

			DES_CondRetErroAberturaArquivo = 2 ,
			/*O arquivo não pôde ser aberto*/

			DES_CondRetDesenhoExistente = 3,
			/*Já existe um desenho criado*/

			DES_CondRetCelulaNula = 4,
			/*O estado correto de uma das células é nulo*/

			DES_CondRetDesenhoCorreto = 5,
			/*O desenho foi preenchido corretamente*/

			DES_CondRetDesenhoIncorreto = 6,
			/*O desenho não foi preenchido corretamente*/

			DES_CondRetSemHints = 7,
			/*Todas as dicas já foram utilizadas*/

			DES_CondRetFaltouMemoria = 8
			/* Faltou memória ao alocar dados */

	} DES_tpCondRet ;



/***********************************************************************
*
*	$FC Função:	DES Cria Desenho
*
*	$ED Descrição da função
*		Cria uma nova estrutura desenho caso nenhuma exista.
*
*	$EP Parâmetros
*		linhas	- Inteiro representando o número de linhas do desenho 
*		colunas	- Inteiro representando o número de colunas do desenho 
*		nome	- String identificadora do desenho.
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetDesenhoExistente
*		DES_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		linhas e colunas são inteiros positivos.
*		nome nunca foi utilizado na criação de outro desenho.
*		
*	$AS Assertivas de saída
*		Se OK, a estrutura desenho é criada.
*		Senão, a estrutura desenho não é criada.
*
**********************************************************************/

	DES_tpCondRet DES_criaDesenho ( int linhas, int colunas, char* nome );


/***********************************************************************
*
*	$FC Função:	DES Destroi Desenho
*
*	$ED Descrição da função
*		Destroi a estrutura desenho.
*
*	$FV Valor retornado
*		DES_CondRetOK
*
*   $AE Assertivas de entrada 
*		O desenho existe.
*
*	$AS Assertivas de saída
*		A estrutura desenho e seu conteúdo foram desalocados.
*
**********************************************************************/

	DES_tpCondRet DES_destroiDesenho (void);


/***********************************************************************
*
*	$FC Função:	DES Modifica Célula Correto
*
*	$ED Descrição da função
*		Modifica o status correto de uma célula.
*
*	$EP Parâmetros
*		linha	- Inteiro indicando a linha da célula
*		coluna	- Inteiro indicando a coluna da célula
*		estado	- Caracter indicando o estado a ser atribuído.
*				  'm' para marcada
*				  'd' para desmarcada
*				  'n' para nulo
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetEstadoInvalido;
*
*   $AE Assertivas de entrada
*		O desenho está criado.
*		linha e coluna são menores ou iguais as dimensões da matriz.
*		
*	$AS Assertivas de saída
*		A célula na posição linha x coluna teve seu estado correto
*		alterado.
*
**********************************************************************/

	DES_tpCondRet DES_modificaCelulaCorreto ( int linha, int coluna, char estado );


/***********************************************************************
*
*	$FC Função:	DES Modifica Célula Atual
*
*	$ED Descrição da função
*		Modifica o status atual de uma célula.
*
*	$EP Parâmetros
*		linha	- Inteiro indicando a linha da célula
*		coluna	- Inteiro indicando a coluna da célula
*		estado	- Caracter indicando o estado a ser atribuído.
*				  'm' para marcada
*				  'd' para desmarcada
*				  'n' para nulo
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetEstadoInvalido;
*
*   $AE Assertivas de entrada
*		O desenho está criado.
*		linha e coluna são menores ou iguais as dimensões da matriz.
*		
*	$AS Assertivas de saída
*		A célula na posição linha x coluna teve seu estado atual
*		alterado.
*
**********************************************************************/

	DES_tpCondRet DES_modificaCelulaAtual ( int linha, int coluna, char estado);


/***********************************************************************
*
*	$FC Função:	DES Calcula Valores
*
*	$ED Descrição da função
*		Calcula os valores de acordo com o status das células 
*		da matriz e os atribui a suas respectivas listas.
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		O desenho foi criado
*		
*	$AS Assertivas de saída
*		As listas horizontais e verticais do desenho 
*		são preenchidas com os valores.
*
**********************************************************************/

	DES_tpCondRet DES_calculaValores ( void );

	
/***********************************************************************
*
*	$FC Função:	DES Confere Solução dos Valores
*
*	$ED Descrição da função
*		Analisa as células do desenho para averiguar se os valores
*		foram marcados corretamente.
*
*	$FV Valor retornado
*		DES_CondRetOK
*
*   $AE Assertivas de entrada 
*		O desenho foi criado.
*		Os valores foram calculados.
*		
*	$AS Assertivas de saída
*		Se as células foram preenchidas corretamente, o respectivo
*		valor é marcado como resolvido.
*		Do contrário, o valor é marcado como não resolvido.
*
**********************************************************************/
	
	DES_tpCondRet DES_confereSolucaoValores ( void );


/***********************************************************************
*
*	$FC Função:	DES Salva Desenho
*
*	$ED Descrição da função
*		Cria um arquivo que armazena todas as informações do desenho.
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
*	$AS Assertivas de saída
*		Um arquivo .txt nomeado de acordo com o nome do desenho
*		contendo a dimensão da matriz e as listas de valores
*		horizontais e verticais.
*
**********************************************************************/	
	
	DES_tpCondRet DES_salvaDesenho (void);


/***********************************************************************
*
*	$FC Função:	DES Carrega Desenho
*
*	$ED Descrição da função
*		Cria um novo desenho nome_desenho com as informações contidas 
*		no arquivo nome_desenho.txt. Se já existir um desenho ativo, 
*		este será destruído.
*
*	$EP Parâmetros
*		nome_desenho - String que identifica o desenho a ser carregado.
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetErroAberturaArquivo
*		DES_CondRetFaltouMemoria
*
*   $AE Assertivas de entrada 
*		O arquivo nome_desenho.txt não está vazio e está formatado corretamente.
*		
*	$AS Assertivas de saída
*		É criado um novo desenho com as informações
*		contidas no arquivo.
*
**********************************************************************/

	DES_tpCondRet DES_carregaDesenho ( char* nome_desenho );


/***********************************************************************
*
*	$FC Função:	DES Confere Conclusão do Desenho
*
*	$ED Descrição da função
*		Confere se todas as células do desenho foram
*		marcadas corretamente.
*
*	$FV Valor retornado
*		DES_CondRetDesenhoCorreto
*		DES_CondRetDesenhoIncorreto
*
*   $AE Assertivas de entrada 
*		O desenho foi criado.
*		
*	$AS Assertivas de saída
*		O desenho não é alterado.
*
**********************************************************************/

	DES_tpCondRet DES_confereConclusaoDesenho ( void );


/***********************************************************************
*
*	$FC Função:	DES Usa Dica
*
*	$ED Descrição da função
*		Marca uma célula corretamente, se o usuário ainda tiver
*		hints disponíveis.
*
*	$FV Valor retornado
*		DES_CondRetOK
*		DES_CondRetDesenhoConcluido
*		DES_CondRetSemHints
*
*   $AE Assertivas de entrada 
*		O desenho foi criado.
*		
*	$AS Assertivas de saída
*		Se OK, uma célula é marcada corretamente.
*		Do contrário, nada acontece.
*
**********************************************************************/

	DES_tpCondRet DES_usaDica( void );



/************Fim do módulo de definição: Módulo Desenho***************/

#endif