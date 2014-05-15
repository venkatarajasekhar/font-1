#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>

#include	"desenho.h"

int main (){

	DES_tpCondRet ret;
	char m = 'm';
	char d = 'd';

	DES_criaDesenho ( 5, 5, "d2" );
	DES_modificaCelulaCorreto (1,1,m);
	DES_modificaCelulaCorreto (1,2,d);
	DES_modificaCelulaCorreto (1,3,m);
	DES_modificaCelulaCorreto (1,4,d);
	DES_modificaCelulaCorreto (1,5,m);
	DES_modificaCelulaCorreto (2,1,d);
	DES_modificaCelulaCorreto (2,2,m);
	DES_modificaCelulaCorreto (2,3,d);
	DES_modificaCelulaCorreto (2,4,m);
	DES_modificaCelulaCorreto (2,5,m);
	DES_modificaCelulaCorreto (3,1,d);
	DES_modificaCelulaCorreto (3,2,d);
	DES_modificaCelulaCorreto (3,3,m);
	DES_modificaCelulaCorreto (3,4,d);
	DES_modificaCelulaCorreto (3,5,d);
	DES_modificaCelulaCorreto (4,1,d);
	DES_modificaCelulaCorreto (4,2,m);
	DES_modificaCelulaCorreto (4,3,d);
	DES_modificaCelulaCorreto (4,4,m);
	DES_modificaCelulaCorreto (4,5,m);
	DES_modificaCelulaCorreto (5,1,d);
	DES_modificaCelulaCorreto (5,2,m);
	DES_modificaCelulaCorreto (5,3,m);
	DES_modificaCelulaCorreto (5,4,d);
	DES_modificaCelulaCorreto (5,5,d);


	DES_calculaValores();
	DES_confereSolucaoValores();
	DES_salvaDesenho();
	DES_destroiDesenho();
	DES_carregaDesenho("d2");
	ret = DES_imprimeDesenhoDesafio();
	return ret;

}