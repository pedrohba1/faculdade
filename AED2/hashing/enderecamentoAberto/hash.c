#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

struct hash {
	int qtd, table_size;
	struct aluno **itens;
};

Hash* criaHash(int table_size) {
	Hash* hash = (Hash*) malloc(sizeof(Hash));

	if (hash != NULL) {
		int i;
		hash->table_size = table_size;
		hash->itens = (struct aluno**) malloc(table_size*sizeof(struct aluno*));

		if (hash->itens == NULL) {
			free(hash);
			return NULL;
		}

		hash->qtd = 0;
		for(i=0; i<hash->table_size; i++) {
			hash->itens[i] = NULL;
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



int insereHashSemColisao(Hash* hash, struct aluno al) {
	if (hash == NULL || hash->qtd == hash->table_size) {
		return 0;
	}

	int pos = chaveDivisao(al.matricula, hash->table_size);
	// printf("Posicao do elemento: %d\n", pos);
	struct aluno* novo = (struct aluno*) malloc(sizeof(struct aluno));

	if (novo == NULL) {
		return 0;
	}

	*novo = al;
	hash->itens[pos] = novo;
	hash->qtd++;

	return 1;
}

int buscaHashSemColisao(Hash* hash, int matricula, struct aluno* a) {
	if (hash == NULL) {
		return -1;
	}

	int pos = chaveDivisao(matricula, hash->table_size);
	if (hash->itens[pos] == NULL) {
		return 0;
	}

	*a = *(hash->itens[pos]);

	return 1;
}

int insereHashEnderAberto(Hash* hash, struct aluno al) {
	if (hash == NULL || hash->qtd == hash->table_size) {
		return 0;
	}

	int i, newpos, pos = chaveDivisao(al.matricula, hash->table_size);

	for (i=0; i<hash->table_size; ++i) {
		newpos = duploHash(pos, al.matricula,i, hash->table_size);

		if (hash->itens[newpos] == NULL) {
			struct aluno* a = (struct aluno*) malloc(sizeof(struct aluno));
			
			if (a == NULL) {
				return 0;
			}

			*a = al;
			hash->itens[newpos] = a;
			hash->qtd++;

			return 1;
		}
	}

	return 0;
}

int buscaHashEnderAberto(Hash* hash, int matricula ,struct aluno* a) {
	if (hash == NULL) 
		return -1;

	int i, newpos, pos = chaveDivisao(matricula, hash->table_size);

	for (i=0; i<hash->table_size; ++i) {
		newpos = sondagemLinear(pos, i, hash->table_size);

		if(hash->itens[newpos] == NULL)
			return 0;

		if (hash->itens[newpos]->matricula == matricula) {
			printf("achou\n");
			*a = *(hash->itens[newpos]);
			return 1;
		}

	}

	return 0;
}

void printaRegistro(struct aluno* a) {
	if (a != NULL) {
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
			printaRegistro(hash->itens[i]);
			// puts("");
		}
	}
}