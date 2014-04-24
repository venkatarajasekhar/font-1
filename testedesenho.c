/***************************************************************************
*	$MCI M�dulo de implementa��o: TLIS Teste espec�fico para m�dulo Desenho
*
*	Arquivo gerado:              testdesenho.c
*	Letras identificadoras:      TLIS
*
*	Nome da base de software:    Exemplo de teste automatizado
*	Arquivo da base de software: ArcaboucoTeste.lib
*
*	Projeto: Disciplinas INF 1301
*	Gestor:  Flavio Bevilacqua
*	Autores:	vyc, Victor Yves Crispim
*				sa, S�rgio Argolo
*				ft, Francisco Tacora
*
*	$HA Hist�rico de evolu��o:
*		Vers�o	Autor	Data		Observa��es
*		1.0		vyc		15/04/2014	In�cio do desenvolvimento
*
*	$ED Descri��o do m�dulo
*		Este m�dulo cont�m as fun��es espec�ficas para o teste do
*		m�dulo desenho. Apenas um desenho pode ser manipulado por vez.
*
***************************************************************************/



/********************* Diretivas de pr�-processamento *********************/

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>

#include    "TST_ESPC.H"
#include    "GENERICO.H" 
#include    "LERPARM.H"

#include	"desenho.h"

#define MAX_STRING 54

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define		CRIAR_DES_CMD		"=criar"
#define     DESTRUIR_DES_CMD	"=destruir"
#define		MOD_CEL_COR_CMD		"=modcelcor"
#define		MOD_CEL_ATU_CMD		"=modcelatu"
#define		CALCULA_VAL_CMD		"=calculaval"
#define		CONFERE_VAL_CMD		"=confereval"
#define		SALVAR_CMD			"=salvar"
#define		CARREGAR_CMD		"=carregar"
#define		CONFERE_DES_CMD		"=conferedes"
#define		USAR_DICA_CMD		"=dica"



/**************  C�digo das fun��es exportadas pelo m�dulo  **************/

/**************************************************************************
*
*	$FC Fun��o: TLIS Efetuar opera��es de teste espec�ficas para desenho
*
*	$ED Descri��o da fun��o
*		Efetua os diversos comandos de teste espec�ficos para o m�dulo
*		desenho sendo testado.
*
*	$EP Par�metros
*		ComandoTeste - String contendo o comando
*		
*		Comandos dispon�veis:
*		
*		=criar			CondRetEsp		linhas	colunas	nome	
*		=destruir		CondRetEsp
*		=modcelcor		CondRetEsp		linhas	colunas	estado	
*		=modcelatu		CondRetEsp		linhas	colunas	estado		
*		=calculaval		CondRetEsp	
*		=confereval		CondRetEsp	
*		=salvar			CondRetEsp			
*		=carregar		CondRetEsp		nome	
*		=conferedes		CondRetEsp			
*		=dica			CondRetEsp		
*		
*
*************************************************************************/

	TST_tpCondRet TST_EfetuarComando ( char * ComandoTeste ){
		
		int numLidos = -1   ,		//N�mero de par�metros lidos
			linhas = -1  ,
			colunas = -1 ;

		DES_tpCondRet	CondRetObtida	, 
						CondRetEsperada	;

		char nome	[MAX_STRING];	//String passada pelo usu�rio
		char estado ;
	
		/* Testar DES_criaDesenho */
		if ( strcmp(ComandoTeste, CRIAR_DES_CMD) == 0 ){
		
			numLidos = LER_LerParametros("iiis", &CondRetEsperada, &linhas, &colunas, nome);

			if ( numLidos != 4 )
				return TST_CondRetParm ;

			CondRetObtida = DES_criaDesenho (linhas, colunas, nome);

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao criar desenho.") ;
		}//Fim Testar DES_criarDesenho


		/* Testar DES_destroiDesenho */
		else if ( strcmp(ComandoTeste, DESTRUIR_DES_CMD) == 0 ){
		
			numLidos = LER_LerParametros("i", &CondRetEsperada);

			if ( numLidos != 1 )
				return TST_CondRetParm ;
		
			CondRetObtida = DES_destroiDesenho();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao destruir desenho.") ;
		}// Fim Testar DES_destroiDesenho


		/* Testar DES_modificaCelulaCorreto */
		else if (strcmp(ComandoTeste, MOD_CEL_COR_CMD) == 0 ){

			numLidos = LER_LerParametros("iiic", &CondRetEsperada, &linhas, &colunas, &estado);

			if ( numLidos != 4 )
				return TST_CondRetParm ;

			CondRetObtida = DES_modificaCelulaCorreto ( linhas, colunas, estado );

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao modificar estado correto da c�lula.") ;

		} //Fim Testar DES_modificaCelulaCorreto
		

		/* Testar DES_modificaCelulaAtual */
		else if ( strcmp(ComandoTeste, MOD_CEL_ATU_CMD) == 0 ){

			numLidos = LER_LerParametros("iiic", &CondRetEsperada, &linhas, &colunas, &estado);

			if ( numLidos != 4 )
				return TST_CondRetParm ;

			CondRetObtida = DES_modificaCelulaAtual ( linhas, colunas, estado );

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao modificar estado atual da c�lula.") ;

		} //Fim Testar DES_modificaCelulaAtual


		/* Testar DES_calculaValores */
		else if ( strcmp(ComandoTeste, CALCULA_VAL_CMD) == 0 ){

			numLidos = LER_LerParametros("i", &CondRetEsperada );

			if (numLidos != 1 )
				return TST_CondRetParm ;

			CondRetObtida = DES_calculaValores ();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao calcular valores");
		} //Fim Testar DES_calculaValores
				
		
		/* Testar DES_confereSolucaoValores */
		else if ( strcmp(ComandoTeste, CONFERE_VAL_CMD) == 0 ){

			numLidos = LER_LerParametros("i", &CondRetEsperada );

			if (numLidos != 1 )
				return TST_CondRetParm ;

			CondRetObtida = DES_confereSolucaoValores ();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao conferir valores");
		} //Fim Testar DES_confereSolucaoValores
		
		
		/* Testar DES_salvaDesenho */
		else if ( strcmp(ComandoTeste, SALVAR_CMD) == 0 ){

			numLidos = LER_LerParametros("i", &CondRetEsperada );

			if (numLidos != 1 )
				return TST_CondRetParm ;

			CondRetObtida = DES_salvaDesenho ();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao salvar desenho");
		} //Fim Testar DES_salvaDesenho


		/* Testar DES_carregaDesenho */
		else if ( strcmp(ComandoTeste, CARREGAR_CMD) == 0 ){

			numLidos = LER_LerParametros("is", &CondRetEsperada, nome );

			if (numLidos != 2 )
				return TST_CondRetParm ;

			CondRetObtida = DES_carregaDesenho ( nome );

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao carregar desenho");
		} //Fim Testar DES_carregaDesenho


		/* Testar DES_confereConclusaoDesenho */
		else if ( strcmp(ComandoTeste, CONFERE_DES_CMD) == 0 ){

			numLidos = LER_LerParametros("i", &CondRetEsperada );

			if (numLidos != 1 )
				return TST_CondRetParm ;

			CondRetObtida = DES_confereConclusaoDesenho ();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao conferir desenho");
		} //Fim Testar DES_confereConclusaoDesenho


		/* Testar DES_usaDica */
		else if ( strcmp(ComandoTeste, USAR_DICA_CMD) == 0 ){

			numLidos = LER_LerParametros("i", &CondRetEsperada );

			if (numLidos != 1 )
				return TST_CondRetParm ;

			CondRetObtida = DES_usaDica ();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condi��o de retorno incompat�vel ao usar dica");
		} //Fim Testar DES_usaDica
	
		return TST_CondRetNaoConhec ;
	}



/* Fim do M�dulo de Implementa��o: Teste Espec�fico para M�dulo Desenho */