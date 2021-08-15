#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "arvores.h"

struct hash {
	int qtd, table_size;
	Arv* itens;
};

Hash* criaHash(int table_size) {
	Hash* hash = (Hash*) malloc(sizeof(Hash));

	if (hash != NULL) {
		int i;
		hash->table_size = table_size;
		hash->itens = (Arv*) malloc(table_size*sizeof(Arv));

		if (hash->itens == NULL) {
			free(hash);
			return NULL;
		}

		hash->qtd = 0;
		for(i=0; i<hash->table_size; i++) {
			hash->itens[i] = cria_vazia();
		}
	}

	return hash;
}

void liberaHash(Hash* hash) {
	if (hash != NULL) {
		int i;
		
		for(i=0; i<hash->table_size; i++) {
			if (hash->itens[i] != NULL) {
				free(hash->itens[i]);
			}
		}

		free(hash->itens);
		free(hash);
	}
}

int chaveDivisao(int chave, int table_size) {
	return (chave & 0x7FFFFFFF) % table_size;
}

int chaveMultiplicacao(int chave, int table_size) {
	float val = chave*0.6180339887;
	val = val - (int) val;
	return (int) (table_size*val);
}

int duploHash(int h1, int chave, int i, int table_size) {
	int h2 =  chaveMultiplicacao(chave, table_size-1) + 1;
	return chaveDivisao((h1 + i*h2), table_size);
}

int sondagemLinear(int pos, int i, int table_size) {
	return ((pos + i) & 0x7FFFFFFF) % table_size;
}

int sondagemQuadratica(int pos, int i, int table_size) {
	pos = pos + 2*i + 5*i*i;
	return (pos & 0x7FFFFFFF) % table_size;
}

int insereHashComArv(Hash* hash, struct aluno al) {
	if (hash == NULL || hash->qtd == hash->table_size) {
		return 0;
	}

	int pos = chaveDivisao(al.matricula, hash->table_size);
	// printf("Posicao do elemento: %d\n", pos);

	Registro* novo = aloca_registro(al.matricula, al.nome, al.idade);

	insere_ord(&(hash->itens[pos]), novo);
	hash->qtd++;

	return 1;
}

int buscaHashComArv(Hash* hash, int matricula, struct aluno* a) {
	if (hash == NULL) {
		return -1;
	}

	int pos = chaveDivisao(matricula, hash->table_size);
	if (hash->itens[pos] == NULL) {
		return 0;
	}

	Arv arv = busca_bin(hash->itens[pos], matricula);
	
	copiaRegistro(arv, a); 

	return 1;
}

void printaRegistro(struct aluno* a) {
	if (a != NULL) {
		printf("%s\n", a->nome);
		printf("%d\n", a->idade);
		printf("%d\n", a->matricula);
	} else {
		printf("---------------------------------------------------\n");
	}
}

void printaHash(Hash* hash) {
	if (hash != NULL) {
		int i;
		printf("Quantidade maxima de elementos: %d\n", hash->table_size);
		printf("Quantidade de elementos: %d\n\n", hash->qtd);

		printf("Registros:\n");
		for (i=0; i<hash->table_size; ++i) {
			printf("%d)\t", i);
			exibe_arv(hash->itens[i]);
			// puts("");
		}
	}
}