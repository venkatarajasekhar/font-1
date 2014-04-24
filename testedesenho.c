/***************************************************************************
*	$MCI Módulo de implementação: TLIS Teste específico para módulo Desenho
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
*				sa, Sérgio Argolo
*				ft, Francisco Tacora
*
*	$HA Histórico de evolução:
*		Versão	Autor	Data		Observações
*		1.0		vyc		15/04/2014	Início do desenvolvimento
*
*	$ED Descrição do módulo
*		Este módulo contém as funções específicas para o teste do
*		módulo desenho. Apenas um desenho pode ser manipulado por vez.
*
***************************************************************************/



/********************* Diretivas de pré-processamento *********************/

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>

#include    "TST_ESPC.H"
#include    "GENERICO.H" 
#include    "LERPARM.H"

#include	"desenho.h"

#define MAX_STRING 54

/* Tabela dos nomes dos comandos de teste específicos */

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



/**************  Código das funções exportadas pelo módulo  **************/

/**************************************************************************
*
*	$FC Função: TLIS Efetuar operações de teste específicas para desenho
*
*	$ED Descrição da função
*		Efetua os diversos comandos de teste específicos para o módulo
*		desenho sendo testado.
*
*	$EP Parâmetros
*		ComandoTeste - String contendo o comando
*		
*		Comandos disponíveis:
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
		
		int numLidos = -1   ,		//Número de parâmetros lidos
			linhas = -1  ,
			colunas = -1 ;

		DES_tpCondRet	CondRetObtida	, 
						CondRetEsperada	;

		char nome	[MAX_STRING];	//String passada pelo usuário
		char estado ;
	
		/* Testar DES_criaDesenho */
		if ( strcmp(ComandoTeste, CRIAR_DES_CMD) == 0 ){
		
			numLidos = LER_LerParametros("iiis", &CondRetEsperada, &linhas, &colunas, nome);

			if ( numLidos != 4 )
				return TST_CondRetParm ;

			CondRetObtida = DES_criaDesenho (linhas, colunas, nome);

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condição de retorno incompatível ao criar desenho.") ;
		}//Fim Testar DES_criarDesenho


		/* Testar DES_destroiDesenho */
		else if ( strcmp(ComandoTeste, DESTRUIR_DES_CMD) == 0 ){
		
			numLidos = LER_LerParametros("i", &CondRetEsperada);

			if ( numLidos != 1 )
				return TST_CondRetParm ;
		
			CondRetObtida = DES_destroiDesenho();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condição de retorno incompatível ao destruir desenho.") ;
		}// Fim Testar DES_destroiDesenho


		/* Testar DES_modificaCelulaCorreto */
		else if (strcmp(ComandoTeste, MOD_CEL_COR_CMD) == 0 ){

			numLidos = LER_LerParametros("iiic", &CondRetEsperada, &linhas, &colunas, &estado);

			if ( numLidos != 4 )
				return TST_CondRetParm ;

			CondRetObtida = DES_modificaCelulaCorreto ( linhas, colunas, estado );

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condição de retorno incompatível ao modificar estado correto da célula.") ;

		} //Fim Testar DES_modificaCelulaCorreto
		

		/* Testar DES_modificaCelulaAtual */
		else if ( strcmp(ComandoTeste, MOD_CEL_ATU_CMD) == 0 ){

			numLidos = LER_LerParametros("iiic", &CondRetEsperada, &linhas, &colunas, &estado);

			if ( numLidos != 4 )
				return TST_CondRetParm ;

			CondRetObtida = DES_modificaCelulaAtual ( linhas, colunas, estado );

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condição de retorno incompatível ao modificar estado atual da célula.") ;

		} //Fim Testar DES_modificaCelulaAtual


		/* Testar DES_calculaValores */
		else if ( strcmp(ComandoTeste, CALCULA_VAL_CMD) == 0 ){

			numLidos = LER_LerParametros("i", &CondRetEsperada );

			if (numLidos != 1 )
				return TST_CondRetParm ;

			CondRetObtida = DES_calculaValores ();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condição de retorno incompatível ao calcular valores");
		} //Fim Testar DES_calculaValores
				
		
		/* Testar DES_confereSolucaoValores */
		else if ( strcmp(ComandoTeste, CONFERE_VAL_CMD) == 0 ){

			numLidos = LER_LerParametros("i", &CondRetEsperada );

			if (numLidos != 1 )
				return TST_CondRetParm ;

			CondRetObtida = DES_confereSolucaoValores ();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condição de retorno incompatível ao conferir valores");
		} //Fim Testar DES_confereSolucaoValores
		
		
		/* Testar DES_salvaDesenho */
		else if ( strcmp(ComandoTeste, SALVAR_CMD) == 0 ){

			numLidos = LER_LerParametros("i", &CondRetEsperada );

			if (numLidos != 1 )
				return TST_CondRetParm ;

			CondRetObtida = DES_salvaDesenho ();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condição de retorno incompatível ao salvar desenho");
		} //Fim Testar DES_salvaDesenho


		/* Testar DES_carregaDesenho */
		else if ( strcmp(ComandoTeste, CARREGAR_CMD) == 0 ){

			numLidos = LER_LerParametros("is", &CondRetEsperada, nome );

			if (numLidos != 2 )
				return TST_CondRetParm ;

			CondRetObtida = DES_carregaDesenho ( nome );

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condição de retorno incompatível ao carregar desenho");
		} //Fim Testar DES_carregaDesenho


		/* Testar DES_confereConclusaoDesenho */
		else if ( strcmp(ComandoTeste, CONFERE_DES_CMD) == 0 ){

			numLidos = LER_LerParametros("i", &CondRetEsperada );

			if (numLidos != 1 )
				return TST_CondRetParm ;

			CondRetObtida = DES_confereConclusaoDesenho ();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condição de retorno incompatível ao conferir desenho");
		} //Fim Testar DES_confereConclusaoDesenho


		/* Testar DES_usaDica */
		else if ( strcmp(ComandoTeste, USAR_DICA_CMD) == 0 ){

			numLidos = LER_LerParametros("i", &CondRetEsperada );

			if (numLidos != 1 )
				return TST_CondRetParm ;

			CondRetObtida = DES_usaDica ();

			return TST_CompararInt (CondRetEsperada, CondRetObtida, 
									"Condição de retorno incompatível ao usar dica");
		} //Fim Testar DES_usaDica
	
		return TST_CondRetNaoConhec ;
	}



/* Fim do Módulo de Implementação: Teste Específico para Módulo Desenho */