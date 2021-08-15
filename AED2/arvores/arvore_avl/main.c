#include <stdio.h>
#include "arvore_avl.h"

int main() {
	int b;
	
	reg *r1 = aloca_registro("Manaus", 50, 300, 200);
	reg *r2 = aloca_registro("Rio De Janeiro", 50, 300, 250);
	reg *r3 = aloca_registro("Sao Paulo", 50, 300, 320);
	reg *r4 = aloca_registro("Uberlandia", 50, 300, 475);
	reg *r5 = aloca_registro("Curitiba", 50, 300, 500);
	reg *r6 = aloca_registro("Rio Grande do Sul", 50, 300, 600);
	reg *r7 = aloca_registro("Mato Grosso", 50, 300, 550);

	Arv A = cria_arv(r1, NULL, NULL);

	insere_avl(&A, r2, &b);
	insere_avl(&A, r3, &b);
	insere_avl(&A, r4, &b);
	insere_avl(&A, r5, &b);
	insere_avl(&A, r6, &b);
	insere_avl(&A, r7, &b);
	
	exibe_arv(A);
	

	return 0;
}