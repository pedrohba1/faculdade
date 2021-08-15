#ifndef HASH_H
#define HASH_H

struct aluno {
	char* nome;
	int matricula;
	int idade;
};

typedef struct hash Hash;

Hash* criaHash(int table_size);
void liberaHash(Hash* hash);
int valorString(char* str);
int insereHashComArv(Hash* hash, struct aluno al);
int buscaHashComArv(Hash* hash, int matricula, struct aluno* a);
void printaHash(Hash* hash);
void printaRegistro(struct aluno* a);

#endif
