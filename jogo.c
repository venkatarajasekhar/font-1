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
#include	<string.h>

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
	void confereComandosProjeto( void );
	void confereComandosDesafio( void );


/*************** Código das funções encapsuladas no módulo ****************/

/**************************************************************************
*
*  FC Função: JOG - Main
*
***************************************************************************/

	JOG_tpCondRet main (void){
		
		int i, j, k, colunas, linhas, opcao;

	/*Menu Principal*/
		do{
			printf("\n\nIniciar Nonogram no modo:\n 1-Projeto\n 2-Desafio\n 3-Sair\n\n");
			scanf(" %d",&opcao);
			switch (opcao){
			
			/*Modo Projeto*/
				case 1:
				{
					int linhas,colunas;
					char nome[54];
					JOG_tpCondRet ret;
					DES_tpCondRet retDes;

					//Menu do modo Projeto
					printf("\nQuais as dimensoes do desenho? (NxN)\n");
					scanf("%d%*c%d",&linhas, &colunas);

					if ( linhas <= 0 || colunas <= 0 ){
					
						printf ("\nDimensoes nao suportadas\n");
						break;
					}

					printf("\nQue nome voce gostaria de dar para esse jogo?\n");
					scanf(" %s",nome);
					printf ("\n");
					
					//Inicializa modo projeto
					retDes = DES_criaDesenho(linhas,colunas, nome);
					if ( retDes != DES_CondRetOK ){

						printf ("\nErro na criação do desenho\n");
						break;
					}

					DES_imprimeDesenhoProjeto();
					
					//Imprime ajuda
					imprimeAjudaProjeto();

					//Confere os comandos do usuário
					confereComandosProjeto();

					break;
				}

			/*Modo Desafio*/
				case 2:
				{
					char nome[54];
					JOG_tpCondRet retJog;
					DES_tpCondRet retDes;
				
					//Menu do modo Desafio
					printf("\nDigite o nome do jogo a ser carregado:\n");
					scanf(" %s",nome);

					//Carrega o desenho pedido
					retDes = DES_carregaDesenho ( nome );
					if ( retDes != DES_CondRetOK ){

						printf ("\nErro ao carregar o desenho\n");
						break;
					}

					//TODO: IMPRIME GRID VAZIA COM VALORES

					//Imprime ajuda
					imprimeAjudaDesafio();

					//Confere os comandos do usuário
					confereComandosDesafio();

					break;
				}

			/*Usuário sai do programa*/
				case 3:
				{
					return JOG_CondRetEncerrar;
				}

			/*Usuário digita comando inexistente*/
				default:
				{
					printf("\nComando incorreto\n");
					break;
				}
			}
		} while (opcao != 3 );
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
		printf("salvar: se nao existir nenhuma celula nula, salva o projeto atual\n");
		printf("atualizar: atualiza o desenho na tela\n");
		printf("sair: abandona o projeto atual e volta para o menu principal\n\n");
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
		printf("dica: marca 1 celula no desenho corretamente. Cada jogo permite ate 10 dicas\n");
		printf("salvar 'nome': salva o estado atual do jogo em um arquivo com o nome especificado\n");
		printf("fim: confere se o desenho foi preenchido corretamente\n");
		printf("atualizar: atualiza o desenho na tela\n");
		printf("sair: retorna para o menu principal\n\n");
	}


/**************************************************************************
*
*  FC Função: JOG - Confere Comandos do modo Projeto
*
***************************************************************************/

	void confereComandosProjeto ( void ){
	
		char comando[54];
		int linha, coluna;
		int ret = 0;
		DES_tpCondRet retDes;
		
		do{

			//Lê comando
			scanf (" %s", comando);
		
			//Marcar
			if ( strcmp ( comando, "marcar") == 0 ){

					scanf (" %d%*c%d", &linha,&coluna );

					retDes = DES_modificaCelulaCorreto ( linha, coluna, 'm');
					if ( retDes == DES_CondRetDimensoesInvalidas )
						printf ("\nDimensões fora do desenho\n");
			}

			//Desmarcar
			else if ( strcmp ( comando, "desmarcar") == 0 ){

				scanf (" %d%*c%d", &linha,&coluna );

				retDes = DES_modificaCelulaCorreto ( linha, coluna, 'd');
				if ( retDes == DES_CondRetDimensoesInvalidas )
					printf ("\nDimensões fora do desenho\n");
			}

			//Nula
			else if ( strcmp ( comando, "nula") == 0 ){

				scanf (" %d%*c%d", &linha,&coluna );

				retDes = DES_modificaCelulaCorreto ( linha, coluna, 'n');
				if ( retDes == DES_CondRetDimensoesInvalidas )
					printf ("\nDimensões fora do desenho\n");
			}

			//Salvar
			else if ( strcmp ( comando, "salvar") == 0 ){

			/*Calcula Valores*/
				retDes = DES_calculaValores();

				//Se existe uma linha vazia
				if ( retDes == DES_CondRetLinhaSemValor ){
					printf ("\nTodas as linhas devem ter ao menos uma celula marcada\n");
				}
				
				//Se existe uma coluna vazia
				else if ( retDes == DES_CondRetColunaSemValor ){
					printf ("\nTodas as colunas devem ter ao menos uma celula marcada\n");
				}

				//Se deu erro de memória
				else if ( retDes == DES_CondRetFaltouMemoria ){
					printf ("\nErro de alocacao de memoria\n");
				}

				//Se existem celulas nulas
				else if ( retDes == DES_CondRetCelulaNula ){
					printf ("\nO desenho não pode conter celulas nulas\n");
				}
				
				//Se OK
				else{
					
					//Salva desenho
					retDes = DES_salvaDesenho ();
					if ( retDes == DES_CondRetErroAberturaArquivo )
						printf ("\nErro na criacao do arquivo\n");

					//Destroi desenho
					DES_destroiDesenho();

					//Sai da função
					ret = -1;
				}
			}
			
			//Atualizar
			else if ( strcmp ( comando, "atualizar") == 0 ){
				
				printf("\n");
				DES_imprimeDesenhoProjeto();
				printf("\n");
			}

			//Sair
			else if ( strcmp ( comando, "sair") == 0 ){

				DES_destroiDesenho();
				ret = -1;
			}

			//Comando Inválido
			else{
				printf ("\nComando Invalido\n");
			}
		}while ( ret >= 0 );
	}


/**************************************************************************
*
*  FC Função: JOG - Confere Comandos do modo Desafio
*
***************************************************************************/

	void confereComandosDesafio ( void ){
	
	}



/************** Fim do módulo de implementação: Módulo Jogo **************/