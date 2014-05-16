/***************************************************************************
*  $MCI Módulo de implementação: Teste específico para módulo célula
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
*  $HA Histórico de evolução:
*		Versão	Autor	Data		Observações
*		1.0		vyc		30/03/2014	Início do desenvolvimento
*		2.0		sa		06/04/2014	Desenvolvimento dos testes 
*       3.0     sa      15/04/2014  Revisão dos testes
*		4.0		sa		04/05/2014	Revisão dos testes 
*		5.0		sa		08/05/2014	Revisão dos testes
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo célula.
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

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_CEL_CMD             "=criar"
#define     OBTER_EST_ATUAL_CMD       "=obterestadoatual"
#define     OBTER_EST_CORRETO_CMD     "=obterestadocorreto"
#define     ALTERAR_EST_ATUAL_CMD     "=alterarestadoatual"
#define     ALTERAR_EST_CORRETO_CMD   "=alterarestadocorreto"
#define     DESTRUIR_CEL_CMD          "=destruir"

/************* Código das funções exportadas pelo módulo **************/

/***********************************************************************
*
*  $FC Função: TCEL Efetuar operações de teste específicas para a célula
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     célula sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*		Comandos disponíveis:
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

      /* Testar CEL Cria Célula */

         if ( strcmp( ComandoTeste , CRIAR_CEL_CMD ) == 0 )		 
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            
			if ( NumLidos != 1 )
               return TST_CondRetParm ;


            CondRetObtida = CEL_criaCelula ( &pCelula );
			
			return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao criar Celula." );

         } /* fim ativa: Testar CEL Cria Célula */


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
										"Condição de retorno incompatível ao obter estado atual");
			}

            return TST_CompararInt( ValorEsperado , ValorObtido ,
                                   "O estado atual esperado é diferente do obtido." );

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
										"Condição de retorno incompatível ao obter estado correto");
			}

            return TST_CompararInt( ValorEsperado , ValorObtido ,
                                   "O estado correto esperado é diferente do obtido."  );

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
		 

      /* Testar CEL Destroi Célula */
	
         else if ( strcmp( ComandoTeste , DESTRUIR_CEL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtida = CEL_destroiCelula( pCelula ) ;

			pCelula = NULL; // setar ponteiro para null após destruir célula

            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao destruir Celula." );

         } /* fim ativa: Testar CEL Destroi Célula */
		 
		 else
			 return TST_CondRetNaoConhec ;

   }/* Fim função: TCEL Efetuar operações de teste específicas para celula */
  


/********** Fim do módulo de implementação: Módulo de teste específico **********/