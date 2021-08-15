#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"

struct registro {
	char *id;
	int x, y;
	int trafego;
};

typedef struct no {
	int h;
	struct registro r;
	struct no *sae;
	struct no *sad;
} no;

reg* aloca_registro(char* id, int x, int y, int trafego) {
	reg *p = (reg*) malloc(sizeof(reg));
	
	p->id = id;
	p->x = x;
	p->y = y;
	p->trafego = trafego;
	
	return p;
}

void printa_registro(reg *r) {
	printf("Id: %s\n", r->id);
	printf("X: %d | Y: %d\n", r->x, r->y);	
	printf("Trafego: %d\n\n", r->trafego);
}


Arv cria_vazia() {
	return NULL;
}

Arv cria_arv(reg* r, Arv sae, Arv sad) {
	Arv arv = (Arv)malloc(sizeof(no));

	if (arv == NULL) {
		return NULL;
	}

	arv->r = *r;
	arv->sae = sae;
	arv->sad = sad;

	return arv;
}

void printa_arv(Arv A) {
	if (A == NULL) {
		printf("<>");
		return;
	}	

	printf("<");
	printf("%s", A->r.id);
	printa_arv(A->sae);
	printa_arv(A->sad);

	printf(">");
}


void exibe_arv(Arv A) {
	printa_arv(A);
	puts("");
}

void libera_arv(Arv* A) {
	if (*A != NULL)	{
		libera_arv(&(*A)->sae);
		libera_arv(&(*A)->sad);
		free(*A);
	}

	*A = NULL;
}

int alt_no(no* n) {
	if (n == NULL) {
		return -1;
	}

	return n->h;
}

int fatorBalancemento(Arv A) {
	return alt_no(A->sae) - alt_no(A->sad);
}

int maior(int x, int y) {
	if (x > y) {
		return x;
	} 	

	return y;
}

int rot_dir(Arv *raiz) {
	if (*raiz != NULL && (*raiz)->sae != NULL) {
		Arv n = (*raiz)->sae;
		(*raiz)->sae = n->sad;
		n->sad = *raiz;
		(*raiz)->h = 0;
		n->h = 0;
		*raiz = n;

		return 1;	
	}

	return 0;
}

int rot_esq(Arv *raiz) {
	if (*raiz != NULL && (*raiz)->sad != NULL) {
		Arv n = (*raiz)->sad;
		(*raiz)->sad = n->sae;
		n->sae = *raiz;
		(*raiz)->h = 0;
		n->h = 0;
		*raiz = n;

		return 1;	
	}
	
	return 0;
}

int rot_dir_esq(Arv *raiz) {
	if (*raiz != NULL && (*raiz)->sae != NULL) {
		rot_dir(&(*raiz)->sae);
		rot_esq(raiz);
		return 1;
	}

	return 0;
}

int rot_esq_dir(Arv *raiz) {
	if (*raiz != NULL && (*raiz)->sad != NULL) {
		rot_esq(&(*raiz)->sad);
		rot_dir(raiz);
		return 1;
	}

	return 0;
}

int balacearEsq(Arv* A) {
	if (((*A)->sae)->h > 0) {
		return rot_dir(A);
	} else {
		return rot_dir_esq(A);
	}
}

int balacearDir(Arv* A) {
	if (((*A)->sad)->h < 0) {
		return rot_esq(A);
	} else {
		return rot_esq_dir(A);
	}
}


int insere_avl(Arv* A, reg* elem, int* b) {
	if (A == NULL) {
		return 0;
	}

	if (*A == NULL) {
		no* n = (no*)malloc(sizeof(no));
		
		n->r = *elem;
		n->sae = NULL;
		n->sad = NULL;
		n->h = 0;

		*A = n;
		*b = 1;

	} else if (elem->trafego <= (*A)->r.trafego) {
		insere_avl(&(*A)->sae, elem, b);
		if (*b == 1) {
			if ((*A)->h == 1) {
				balacearEsq(A);
				*b = 0;
			} else if ((*A)->h == 0) {
				(*A)->h =1;
			} else {
				(*A)->h = 0;
				*b = 0;
			}
		}
	} else {
		insere_avl(&(*A)->sad, elem, b);
		if (*b == 1) {
			if ((*A)->h == -1) {
				balacearDir(A);
				*b = 0;	
			} else if ((*A)->h == 0) {
				(*A)->h = -1;
			} else {
				(*A)->h = 0;
				*b = 0;
			}
		}
	}

	return 1;
}