#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>

#include	"desenho.h"

int main (){

	DES_tpCondRet ret;
	char m = 'm';
	char d = 'd';

	DES_criaDesenho ( 3, 3, "d2" );
	DES_modificaCelulaCorreto (1,1,m);
	DES_modificaCelulaCorreto (1,2,d);
	DES_modificaCelulaCorreto (1,3,d);
	DES_modificaCelulaCorreto (2,1,d);
	DES_modificaCelulaCorreto (2,2,m);
	DES_modificaCelulaCorreto (2,3,m);
	DES_modificaCelulaCorreto (3,1,d);
	DES_modificaCelulaCorreto (3,2,m);
	DES_modificaCelulaCorreto (3,3,m);
	DES_modificaCelulaAtual (1,1,m);
	DES_modificaCelulaAtual (1,2,d);
	DES_modificaCelulaAtual (1,3,d);
	DES_modificaCelulaAtual (2,1,d);
	DES_modificaCelulaAtual (2,2,m);
	DES_modificaCelulaAtual (2,3,m);
	DES_modificaCelulaAtual (3,1,d);
	DES_modificaCelulaAtual (3,2,m);
	DES_modificaCelulaAtual (3,3,m);

	DES_calculaValores();
	DES_confereSolucaoValores();
	DES_salvaDesenho();
	DES_destroiDesenho();
	DES_carregaDesenho("d2");
	ret = DES_salvaDesenho();
	return ret;

}