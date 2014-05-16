/**************************************************************************
*  $MCI M�dulo de implementa��o: Teste espec�fico para m�dulo valor
*
*  Arquivo gerado:				testevalor.c
*  Letras identificadoras:		TVAL
*
*  Nome de base de software:	Exemplo de teste automatizado
*  Arquivo da base de software: ArcaboucoTeste.lib
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  Flavio Bevilacqua
*  Autores:	vyc, Victor Yves Crispim
*			sa, S�rgio Argolo
*			ft, Francisco Tacora
*
*  $HA Hist�rico de evolu��o:
*		Vers�o	Autor	Data			Observa��es
*		1.00	ft		02/04/2014		In�cio do desenvolvimento
*       2.00    ft      05/04/2014      Desenvolvmento dos testes das fun��es
*		3.00    ft      15/04/2014      Revis�o dos testes
*
*  $ED Descri��o do m�dulo
*	   Este m�duo cont�m as fun��es espec�ficas para o teste do
*	   m�dulo valor.
*
***************************************************************************/

#include	<stdio.h>
#include	<string.h>
#include    <stdlib.h>

#include	"TST_ESPC.H"
#include	"GENERICO.H"
#include	"LERPARM.H"

#include	"VALOR.H"

static VAL_tppValor pValor = NULL;

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define		CRIAR_VAL_CMD		"=criar"
#define		DESTROI_CMD			"=destruir"
#define		CONFERE_CMD			"=conferir"
#define		DEFINE_CMD			"=definir"
#define		OBTEM_CEL_CMD		"=obtercel"



/************* C�digo das fun��es exportadas pelo m�dulo **************/

/***********************************************************************
*
*  $FC Fun��o: TVAL Efetuar opera��es de teste espec�ficas para valor
*
*  $ED Descri��o da fun��o
*	   Efetua os diversos comandos de teste espec�ficos para o m�dulo 
*	   valor sendo testado.
*
*  $EP Par�metros
*    $P ComandoTeste - String contendo o comando
*
*		Comandos dispon�veis:
*
*		=criar		      CondRetEsperada		numCelulas
*		=destruir	      CondRetEsperada
*		=conferir		  CondRetEsperada		solucao
*		=definir		  CondRetEsperada		solucao
*		=obtercel		  CondRetEsperada		numCelulas
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )	
	{
		VAL_tpCondRet	CondRetObtida	= VAL_CondRetOK ;
		VAL_tpCondRet	CondRetEsperada	= VAL_CondRetFaltouMemoria ;
										  /*Inicializa para qualquer coisa*/
		int		ValorDado	= -1,
				ValorObtido	= -1,
				NumLidos	= -1;

		
		/* Testar VAL Criar valor */
		if ( strcmp( ComandoTeste , CRIAR_VAL_CMD ) == 0 )
		{
			NumLidos = LER_LerParametros("ii",
							 &CondRetEsperada, &ValorDado) ;
			if ( NumLidos != 2 )
			{
				return TST_CondRetParm;
			} /* if */

			CondRetObtida = VAL_criaValor( &pValor , ValorDado ) ;

			return TST_CompararInt( CondRetEsperada , CondRetObtida ,
									"Retorno errado ao criar valor. ") ;
		}/* fim ativa: Testar VAL Criar valor */

		/* Testar VAL Define solu��o*/
		else if ( strcmp( ComandoTeste , DEFINE_CMD ) == 0 )
		{
			NumLidos = LER_LerParametros( "ii" ,
							&CondRetEsperada, &ValorDado ) ;
			if ( NumLidos != 2 )
			{
				return TST_CondRetParm ;
			} /* if */

			 CondRetObtida = VAL_defineSolucao ( pValor , ValorDado ) ;

			 return TST_CompararInt( CondRetEsperada , CondRetObtida ,
				                     "Retorno errado ao definir solu��o correta. " );

		} /* fim ativa: Testar VAL Define solucao*/

		/* Testar VAL Confere Solu��o */
		else if ( strcmp( ComandoTeste , CONFERE_CMD ) == 0 )
		{
			NumLidos = LER_LerParametros("ii" ,
								&CondRetEsperada, &ValorDado ) ;
			if ( NumLidos != 2 )
			{
				return TST_CondRetParm ;
			}

			CondRetObtida = VAL_confereSolucao ( pValor , &ValorObtido ) ;

			if ( CondRetObtida != VAL_CondRetOK ){
			
				return TST_CompararInt (CondRetEsperada, CondRetObtida,
										"Condi��o de retorno incompat�vel ao conferir solu��o");
			}

			return TST_CompararInt( ValorDado , ValorObtido ,
									"A solu��o esperada � diferente da obtida "	) ;

		} /* fim ativa: Testar VAL confere solu��o*/

		/* Testar VAL obtem numero de celulas */

				else if ( strcmp( ComandoTeste , OBTEM_CEL_CMD ) == 0 )
		{
			NumLidos = LER_LerParametros(  "ii" , 
								&CondRetEsperada, &ValorDado ) ;
			if ( NumLidos != 2 )
			{
				return	TST_CondRetParm ;
			}

			CondRetObtida = VAL_obtemNumeroCelulas( pValor , &ValorObtido ) ;
				
			if ( CondRetObtida != VAL_CondRetOK ){
				return TST_CompararInt(  CondRetEsperada , CondRetObtida ,
										"Retorno errado ao obter numero de celulas. " ) ;
			}

			return TST_CompararInt( ValorDado , ValorObtido ,
									"O n�mero de c�lulas esperado � diferente do obtido "	) ;
		} /* fim ativa: Testar VAL Obter numero de celulas. */

		/* Testar VAL Destruir valor */
		else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
		{
			NumLidos = LER_LerParametros( "i" ,	&CondRetEsperada) ;

			if ( NumLidos != 1 )
			{
				return TST_CondRetParm;
			}

			CondRetObtida = VAL_destroiValor( pValor );

			pValor = NULL;

			return TST_CompararInt( CondRetEsperada , CondRetObtida,
				"Retorno errado destruir valor." ) ;
	
		} /* fim ativa: Testar VAL Destroi valor */

		else
			return TST_CondRetNaoConhec ;

	}/* Fim fun��o: TVAL Efetuar opera��es de teste espec�ficas para valor */



/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/