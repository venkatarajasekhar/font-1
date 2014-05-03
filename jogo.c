/***************************************************************************
*
*	$MCI Módulo de implementação: Módulo Jogo
*
*	Arquivo gerado:				 jogo.c
*	Letras identificadoras:		 JOG
*
*	Nome da base de software:    Exemplo de teste automatizado
*	Arquivo da base de software: ArcaboucoTeste.lib
*
*	Projeto: Disciplinas INF1301
*	Gestor:  Flavio Bevilacqua
*	Autores:	vyc, Victor Yves Crispim
*				sa, Sergio Argolo
*				ft, Francisco Tacora
*
*	$HA Histórico de evolução:
*		Versão	Autor	Data		Observações
*		1.0		vyc		24/04/2014	Início do Desenvolvimento
*
***************************************************************************/

/********************* Diretivas de Pré-Processamento *********************/

#include	<stdio.h>

#include	"celula.h"
#include	"valor.h"
#include	"lista.h"
#include	"matriz.h"
#include	"desenho.h"

#define		JOGO_OWN
#include	"jogo.h"
#undef		JOGO_OWN


/************** Protótipos das funções encapuladas no módulo **************/

	JOG_tpCondRet main (void);
	void imprimeAjudaProjeto( void );
	void imprimeAjudaDesafio( void );
	JOG_tpCondRet confereComandosProjeto( void );
	JOG_tpCondRet confereComandosDesafio( void );


/*************** Código das funções encapsuladas no módulo ****************/

/**************************************************************************
*
*  FC Função: JOG - Main
*
***************************************************************************/

	JOG_tpCondRet main (void){
		
		int i, j, k, colunas, linhas;
		char aux = 'd';
		char aux2 = 'd';

		DES_criaDesenho ( 3, 3, "d1");
		DES_modificaCelulaAtual ( 3, 3, aux);
		DES_modificaCelulaAtual ( 3, 2, aux);
		DES_imprimeDesenho ( aux2 );

	//	int opcao;

	//*Menu Principal*/
	//	do{
	//		printf("\n\nIniciar Nonogram no modo:\n 1-Projeto\n 2-Desafio\n 3-Sair\n\n");
	//		scanf(" %d",&opcao);
	//		switch (opcao){
	//		
	//		/*Modo Projeto*/
	//			case 1:
	//			{
	//				int linhas,colunas;
	//				char nome[54];
	//				JOG_tpCondRet ret;
	//				DES_tpCondRet retDes;

	//				//Menu do modo Projeto
	//				printf("\nQual o tamanho do jogo? (NxN)\n");
	//				scanf("%d%c%d",&linhas, nome, &colunas);

					//TODO: confere se linhas && colunas > 0

	//				printf("\nQue nome voce gostaria de dar para esse jogo?\n");
	//				scanf(" %s",nome);
	//				
	//				//Inicializa modo projeto
	//				retDes = DES_criaDesenho(linhas,colunas, nome);
	//				if ( retDes /*alguma treta*/ ){
	//				}

	//				//TODO: EXIBE GRID VAZIA
	//				
	//				//Imprime ajuda
	//				imprimeAjudaProjeto();

	//				//Confere os comandos do usuário
	//			//	ret = confereComandosProjeto();
	//			//	if ( ret /*alguma coisa*/ ){
	//			//	}

	//				break;
	//			}

	//		/*Modo Desafio*/
	//			case 2:
	//			{
	//				char nome[54];
	//				JOG_tpCondRet retJog;
	//				DES_tpCondRet retDes;
	//				
	//				//Menu do modo Desafio
	//				printf("\nDigite o nome do jogo a ser carregado:\n");
	//				scanf(" %s",nome);

	//				//Carrega o desenho pedido
	//				retDes = DES_carregaDesenho ( nome );
	//				if ( retDes /*alguma treta*/ ){
	//				}

	//				//TODO: IMPRIME GRID VAZIA COM VALORES

	//				//Imprime ajuda
	//				imprimeAjudaDesafio();

	//				//Confere os comandos do usuário
	//			//	ret = confereComandosDesafio();
	//			//	if ( ret /*alguma coisa*/ ){
	//			//	}

	//				break;
	//			}

	//		/*Usuário sai do programa*/
	//			case 3:
	//			{
	//				return JOG_CondRetEncerrar;
	//			}

	//		/*Usuário digita comando inexistente*/
	//			default:
	//			{
	//				printf("\nComando incorreto\n");
	//				break;
	//			}
	//		}
	//	} while (opcao != 3 );
	}

/**************************************************************************
*
*  FC Função: JOG - Imprime Ajuda do modo Projeto
*
***************************************************************************/

	void imprimeAjudaProjeto ( void ){
	
		printf("\nComandos disponiveis:\n\n");
		printf("marcar NxN: muda o estado da celula NxN para MARCADA\n");
		printf("desmarcar NxN: muda o estado da celula NxN para DESMARCADA\n");
		printf("nulo NxN: muda o estado da celula NxN para NULO\n");
		printf("salvar 'nome': se não existir nenhuma celula nula, salva o projeto atual\ncom o nome especificado");
		printf("sair: retorna para o menu principal");
	}


/**************************************************************************
*
*  FC Função: JOG - Imprime Ajuda do modo Desenho
*
***************************************************************************/

	void imprimeAjudaDesafio ( void ){
	
		printf("\nComandos disponiveis:\n\n");
		printf("marcar NxN: muda o estado da celula NxN para MARCADA\n");
		printf("desmarcar NxN: muda o estado da celula NxN para DESMARCADA\n");
		printf("nulo NxN: muda o estado da celula NxN para NULO\n");
		printf("dica: marca 1 celula no desenho corretamente. Cada jogo permite ate 10 dicas");
		printf("salvar 'nome': salva o estado atual do jogo em um arquivo com o nome especificado");
		printf("fim: confere se o desenho foi preenchido corretamente");
		printf("sair: retorna para o menu principal");
	}


/**************************************************************************
*
*  FC Função: JOG - Confere Comandos do modo Projeto
*
***************************************************************************/

	JOG_tpCondRet confereComandosProjeto ( void ){
	
	}


/**************************************************************************
*
*  FC Função: JOG - Confere Comandos do modo Desafio
*
***************************************************************************/

	JOG_tpCondRet confereComandosDesafio ( void ){
	
	}



/************** Fim do módulo de implementação: Módulo Jogo **************/