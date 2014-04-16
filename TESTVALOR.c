/**************************************************************************
*  $MCI Módulo de implementação: Teste específico para módulo valor
*
*  Arquivo gerado:				TESTAVALOR.C
*  Letras identificadoras:		TVAL
*
*  Nome de base de software:	Exemplo de teste automatizado
*  Arquivo da base de software: ArcaboucoTeste.lib
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  Flavio Bevilacqua
*  Autores:	vyc, Victor Yves Crispim
*			sa, Sérgio Argolo
*			ft, Francisco Tacora
*  $HA Histórico de evolução:
*		Versão	Autor	Data		Observações
*		1.00	ft		02/04/2014	Início do desenvolvimento
*       2.00    ft      05/04/2014      Desenvolvmento dos testes das funções
*		3.00    ft      15/04/2014      Revisão dos testes
*
*  $ED Descrição do módulo
*	   Este móduo contém as funções específicas para o teste do
*	   módulo valor. Ilustra como redigir um interpretador de comandos
*	   de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*		Comandos de teste específicos para testar o módulo valor:
*		
*		=criar			-	chama a função VAL_criaValor( )
*		=destruir		-	chama a função VAL_destroiValor( )
*		=conferir		-	chama a função VAL_confereSolução( <Int> )
*		=definir		-	chama a função VAL_defineSolução( ) 
*		=obtercel		-	chama a função VAL_obtemNumeroCelulas( <Int> )

***************************************************************************/

#include	<stdio.h>
#include	<string.h>
#include    <stdlib.h>

#include	"TST_ESPC.H"
#include	"GENERICO.H"
#include	"LERPARM.H"
#include	"VALOR.H"

static VAL_tppValor pValor=NULL;

/* Tabela dos nomes dos comandos de teste específicos */

#define		CRIAR_VAL_CMD		"=criar"
#define		DESTROI_CMD			"=destruir"
#define		CONFERE_CMD			"=conferir"
#define		DEFINE_CMD			"=definir"
#define		OBTEM_CEL_CMD		"=obtercel"



/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TVAL Efetuar operações de teste específicas para valor
*
*  $ED Descrição da função
*	   Efetua os diversos comandos de teste específicos para o módulo 
*	   valor sendo testado.
*
*  $EP Parâmetros
*    $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )	
	{
		VAL_tpCondRet	CondRetObtido	= VAL_CondRetOK ;
		VAL_tpCondRet	CondRetEsperada	= VAL_CondRetFaltouMemoria ;
										  /*Inicializa para qualquer coisa*/
		int		ValorDado	= -1	,
				ValorObtido	= -1	,
				NumLidos = -1 ;

		
		/* Testar VAL Criar valor */
		if ( strcmp( ComandoTeste , CRIAR_VAL_CMD ) == 0 )
		{
			NumLidos = LER_LerParametros("ii",
							 &ValorDado, &CondRetEsperada) ;
			if ( NumLidos != 2 )
			{
				return TST_CondRetParm;
			} /* if */

			CondRetObtido = VAL_criaValor( &pValor , ValorDado ) ;

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"Retorno errado ao criar valor. ") ;
		}/* fim ativa: Testar VAL Criar valor */

		/* Testar VAL Define solução*/
		else if ( strcmp( ComandoTeste , DEFINE_CMD ) == 0 )
		{
			NumLidos = LER_LerParametros( "ii" ,
							&ValorDado , &CondRetEsperada ) ;
			if ( NumLidos != 2 )
			{
				return TST_CondRetParm ;
			} /* if */

			 CondRetObtido = VAL_defineSolucao ( pValor , ValorDado ) ;

			 return TST_CompararInt( CondRetEsperada , CondRetObtido ,
				                     "Retorno errado ao definir solução correta. " );

		} /* fim ativa: Testar VAL Define solucao*/

		/* Testar VAL Confere Solução */
		else if ( strcmp( ComandoTeste , CONFERE_CMD ) == 0 )
		{
			NumLidos = LER_LerParametros("ii" ,
								&ValorDado , &CondRetEsperada ) ;
			if ( NumLidos != 2 )
			{
				return TST_CondRetParm ;
			} /* if*/

			CondRetObtido = VAL_confereSolução ( pValor , &ValorObtido ) ;

			if ( CondRetObtido != VAL_CondRetOK ){
			
				return TST_CompararInt (CondRetEsperada, CondRetObtido,
										"Condição de retorno incompatível ao conferir solução");
			}


			return TST_CompararInt( ValorDado , ValorObtido ,
									"A solução esperada é diferente da obtida "	) ;

		} /* fim ativa: Testar VAL confere solução*/

		/* Testar VAL obtem numero de celulas */

				else if ( strcmp( ComandoTeste , OBTEM_CEL_CMD ) == 0 )
		{
			NumLidos = LER_LerParametros(  "ii" , 
								&ValorDado, &CondRetEsperada ) ;
			if ( NumLidos != 2 )
			{
				return	TST_CondRetParm ;
			}  /* if */

			/*int if*/

			CondRetObtido = VAL_obtemNumeroCelulas( pValor , &ValorObtido ) ;
				
			if ( CondRetObtido != VAL_CondRetOK ){
				TST_CompararInt(  CondRetEsperada , CondRetObtido ,
										"Retorno errado ao obter numero de celulas. " ) ;
			}

			return TST_CompararInt( ValorDado , ValorObtido ,
									"O número de células esperado é diferente do obtido "	) ;
				} /* fim ativa: Testar VAL Obter numero de celulas. */

		/* Testar VAL Destruir valor */
		else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
		{
			NumLidos = LER_LerParametros( "i" ,
							&CondRetEsperada) ;
			if ( NumLidos != 1 )
			{
				return TST_CondRetParm;
			} /* if*/

			CondRetObtido = VAL_destroiValor( pValor );

			return TST_CompararInt( CondRetEsperada , CondRetObtido,
				"Retorno errado destruir valor." ) ;
	
		} /* fim ativa: Testar VAL Destroi valor */

	/*Fim do modulo de implementação: Modulo de teste específico*/
}



