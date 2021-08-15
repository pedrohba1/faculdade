#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"
#include <string.h>

struct aluno {
	char* nome;
	int matricula;
	int idade;
};

Registro* aloca_registro(int matricula, char *nome, int idade){
	Registro *p = (Registro*) malloc(sizeof(Registro));
	p->idade = idade;
	p->nome = nome;
	p->matricula = matricula;
	return p;
}

void printa_registro(Registro *r){
/*	printf("nome: %s\n",r->nome);
	printf("idade:%d\n",r->idade);	
*/	printf("%d", r->matricula);
}


struct no {
	struct aluno r;
	struct no *sae;
	struct no *sad;
};

Arv cria_vazia(){
	return NULL;
}

Arv cria_arvore(Registro *rnew , Arv esq, Arv dir) {

	struct no *node;
	node =(Arv) malloc(sizeof(struct no));

	if(node == NULL)
		return NULL;

	node->r = *rnew;
	node->sae = esq;
	node->sad = dir;

	return node;
}


int arvore_vazia(Arv T) {

	if (T == NULL)
		return 1;
	else
		return 0;
}


int libera_arvore(Arv *A)
{
	if(!arvore_vazia(*A)) {
		libera_arvore(&(*A)->sad);
		libera_arvore(&(*A)->sae);
		free(*A);
	}
	*A = NULL;
}

Registro* maior(Arv A){
	int inf_atual, inf_esq, inf_dir, inf_maior;
	Registro* atual, *esq, * dir, *maiord;
	atual = (Registro*) malloc(1*sizeof(Registro));
	esq = (Registro*) malloc(1*sizeof(Registro));
	dir = (Registro*) malloc(1*sizeof(Registro));
	maiord = (Registro*) malloc(1*sizeof(Registro));

	*atual = A->r;
	maiord = atual;
	

	if (A->sae != NULL) {
		esq = maior(A->sae);

		if (esq->idade > maiord->idade) {
			maiord = esq;
		}
	}

	if (A->sad != NULL) {
		dir =  maior(A->sad);

		if (dir->idade > esq->idade) {
			maiord = dir;
		}
	}
	return maiord;
}


int de_maior(Arv A){
	int qtd = 0;

	if(A == NULL) 
		return qtd;

	if(A->r.idade >= 18) 
		qtd++;
	
	qtd += de_maior(A->sae);
	qtd += de_maior(A->sad);
	return qtd;
}




int qtde_alunos(Arv A, int ini, int fim){
	int qtd =0;
	if(A == NULL){ 
		return qtd;
	}
	if(A != NULL){
		if(A->r.idade >= ini && A->r.idade <=fim)
			qtd++;
				
	}

	qtd += qtde_alunos(A->sad, ini, fim);
	qtd += qtde_alunos(A->sae, ini, fim);

	return qtd;
}


int um_filho(Arv A){
	int qtd = 0;

	if(A == NULL){
		return qtd;
	}

	if(A != NULL) {

		if(A->sad == NULL &&A->sae != NULL){
			qtd++;
		}
		else if(A->sad != NULL && A->sae == NULL){
			qtd++;
		}
	}
	qtd+= um_filho(A->sad);
	qtd += um_filho(A->sae);
	return qtd;
}

int qtd_nos(Arv A){
	int qtd =0;
	if(A== NULL){
		return qtd;
	}
	
	qtd ++;
	qtd += qtd_nos(A->sad);
	qtd += qtd_nos(A->sae);
	return qtd;
}




int completa(Arv A){
	int p1, p2, p3;
	
	if(A == NULL) return 1;
	if(A->sad == NULL &  A->sae ==NULL)
		p1=1;
	else if(A->sad != NULL && A->sae != NULL)
		p1=1;
	else 
		p1=0;

	p2 =completa(A->sad);
	p3= completa(A->sae);
	return p1&&p2&&p3;

}
	

int altura_arv(Arv A){
	int h = 0;
	if(A == NULL) return h;

	if(A->sad != NULL  || A->sae != NULL)
		h++;

	h += altura_arv(A->sad);
	h += altura_arv(A->sae);
	return h;


}

int insere_ord(Arv *A, Registro *r){
	if(*A == NULL){
	struct no *node;
	node =(Arv) malloc(sizeof(struct no));
	node->r = *r;
	node->sae = NULL;
	node->sad = NULL;

	*A = node;
	return 1;
	}
	if(r->idade > (*A)->r.idade){
		return insere_ord(&((*A)->sad), r);
	}
	else {
		return insere_ord(&((*A)->sae), r);
	}
	return 1;
}	

Arv juntar(Arv A1, Arv A2){
	
	if(A2== NULL)
		return NULL;

	insere_ord(&A1,&(A2->r));
	
	juntar(A1, A2->sad);
	juntar(A1, A2->sae);	
	return A1;
}

int remove_ord(Arv *A, Registro *r){
	if(*A == NULL)
		return 0;

	if(r->idade > (*A)->r.idade){
		return remove_ord(&((*A)->sad), r);
	}

	else if(r->idade < (*A)->r.idade){
		return remove_ord(&((*A)->sae),r);
	}

	else {
		if ((*A)->sad == NULL && (*A)->sae == NULL){
			free(*A);
			*A = cria_vazia();
			return 1;
		}

		else if((*A)->sad == NULL && (*A)->sae != NULL)
		{
			Arv aux;
			aux = *A;
			(*A)->sae = aux;
			free(aux);
		}

		else if((*A)->sad != NULL && (*A)->sae != NULL)
		{
			Arv aux;
			aux = *A;
			(*A)->sad = aux;
			free(aux);
		}
		else {
			Arv aux;
			aux = (*A)->sae;
			while(aux->sad != NULL){
				aux = aux->sad;
			}
			Registro *auxr;
			auxr = aloca_registro((*A)->r.idade, (*A)->r.nome, (*A)->r.matricula);
			return remove_ord(&(*A)->sae, r);

		}
	}
}

Arv busca_bin (Arv A, int matricula){
	if(A == NULL)
		return NULL;

	if(A->r.matricula == matricula){
		return A;
	}

	else if(matricula > A->r.matricula){
		return busca_bin(A->sad, matricula);
	}
	else {
		return busca_bin(A->sae,matricula);
	}
}

void printa_arv(Arv A) {
	if (A == NULL) {
		printf("<>");
		return;
	}	

	printf("<");
	printa_registro(&(A->r));
	printa_arv(A->sae);
	printa_arv(A->sad);

	printf(">");
}


void exibe_arv(Arv A) {
	printa_arv(A);
	puts("");
}


void copiaRegistro(Arv arv, Registro* a) {
	a->nome = arv->r.nome;
	a->idade = arv->r.idade;
	a->matricula = arv->r.matricula;
}