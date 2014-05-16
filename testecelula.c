/***************************************************************************
*  $MCI M�dulo de implementa��o: Teste espec�fico para m�dulo c�lula
*
*  Arquivo gerado:              testecelula.c
*  Letras identificadoras:      TCEL
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: ArcaboucoTeste.lib
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  Flavio Bevilacqua
*  Autores:	vyc, Victor Yves Crispim
*			sa, Sergio Argolo
*			ft, Francisco Tacora
*
*  $HA Hist�rico de evolu��o:
*		Vers�o	Autor	Data		Observa��es
*		1.0		vyc		30/03/2014	In�cio do desenvolvimento
*		2.0		sa		06/04/2014	Desenvolvimento dos testes 
*       3.0     sa      15/04/2014  Revis�o dos testes
*		4.0		sa		04/05/2014	Revis�o dos testes 
*		5.0		sa		08/05/2014	Revis�o dos testes
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo c�lula.
*
************************************************************************************/

#include	<stdio.h>
#include	<string.h>
#include    <stdlib.h>

#include	"TST_ESPC.H"
#include	"GENERICO.H"
#include	"LERPARM.H"

#include    "CELULA.H"

static CEL_tppCelula pCelula = NULL;

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_CEL_CMD             "=criar"
#define     OBTER_EST_ATUAL_CMD       "=obterestadoatual"
#define     OBTER_EST_CORRETO_CMD     "=obterestadocorreto"
#define     ALTERAR_EST_ATUAL_CMD     "=alterarestadoatual"
#define     ALTERAR_EST_CORRETO_CMD   "=alterarestadocorreto"
#define     DESTRUIR_CEL_CMD          "=destruir"

/************* C�digo das fun��es exportadas pelo m�dulo **************/

/***********************************************************************
*
*  $FC Fun��o: TCEL Efetuar opera��es de teste espec�ficas para a c�lula
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     c�lula sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*		Comandos dispon�veis:
*
*		=criar				      CondRetObtido  
*		=obterestadoatual	      CondRetObtido     pEstado
*		=obterestadocorreto		  CondRetObtido		pEstado
*		=alterarestadoatual		  CondRetObtido		valor	
*		=alterarestadocorreto	  CondRetObtido		valor	
*		=destruir				  CondRetObtido			
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      CEL_tpCondRet CondRetObtida   = CEL_CondRetOK ;
      CEL_tpCondRet CondRetEsperada = CEL_CondRetFaltouMemoria ;
      
      int NumLidos		= -1 ;
	  int ValorEsperado = -1 ;
	  int ValorObtido	= -1 ;

      TST_tpCondRet Ret ;

      /* Testar CEL Cria C�lula */

         if ( strcmp( ComandoTeste , CRIAR_CEL_CMD ) == 0 )		 
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            
			if ( NumLidos != 1 )
               return TST_CondRetParm ;


            CondRetObtida = CEL_criaCelula ( &pCelula );
			
			return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao criar Celula." );

         } /* fim ativa: Testar CEL Cria C�lula */


      /* Testar CEL Obtem Estado Atual */

         else if ( strcmp( ComandoTeste , OBTER_EST_ATUAL_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "ii" ,
                                &ValorEsperado, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } 

            CondRetObtida = CEL_obtemEstadoAtual( pCelula, &ValorObtido ) ;

			if ( CondRetObtida != CEL_CondRetOK ){
				return TST_CompararInt (CondRetEsperada, CondRetObtida,
										"Condi��o de retorno incompat�vel ao obter estado atual");
			}

            return TST_CompararInt( ValorEsperado , ValorObtido ,
                                   "O estado atual esperado � diferente do obtido." );

         } /* fim ativa: CEL Obtem Estado Atual */

		 /* Testar CEL Obtem Estado Correto */

         else if ( strcmp( ComandoTeste , OBTER_EST_CORRETO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } 

            CondRetObtida = CEL_obtemEstadoCorreto( pCelula, &ValorObtido ) ;

			if ( CondRetObtida != CEL_CondRetOK ){
				return TST_CompararInt (CondRetEsperada, CondRetObtida,
										"Condi��o de retorno incompat�vel ao obter estado correto");
			}

            return TST_CompararInt( ValorEsperado , ValorObtido ,
                                   "O estado correto esperado � diferente do obtido."  );

         } /* fim ativa: CEL Obtem Estado Correto */

		 /* Testar CEL Altera Estado Atual */
	
         else if ( strcmp( ComandoTeste , ALTERAR_EST_ATUAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } 

            CondRetObtida = CEL_alteraEstadoAtual( pCelula , ValorEsperado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                   "Retorno errado ao alterar o Estado Atual da celula." );

         } /* fim ativa: CEL Altera Estado Atual */
		
		 /* Testar CEL Altera Estado Correto */

         else if ( strcmp( ComandoTeste , ALTERAR_EST_CORRETO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } 

            CondRetObtida = CEL_alteraEstadoCorreto( pCelula , ValorEsperado ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                   "Retorno errado ao alterar Estado Correto da celula." );
									
         } /* fim ativa: CEL Altera Estado Correto */
		 

      /* Testar CEL Destroi C�lula */
	
         else if ( strcmp( ComandoTeste , DESTRUIR_CEL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtida = CEL_destroiCelula( pCelula ) ;

			pCelula = NULL; // setar ponteiro para null ap�s destruir c�lula

            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao destruir Celula." );

         } /* fim ativa: Testar CEL Destroi C�lula */
		 
		 else
			 return TST_CondRetNaoConhec ;

   }/* Fim fun��o: TCEL Efetuar opera��es de teste espec�ficas para celula */
  


/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/