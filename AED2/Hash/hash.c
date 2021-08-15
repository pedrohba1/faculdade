#include "hash.h"

struct hash{
	int qtd; 
	int TABLE_SIZE;
	struct aluno **itens;
};


Hash* cria_hash(int TABLE_SIZE){
	Hash* ha = (Hash*) malloc(sizeof(Hash));
	if(ha != NULL){
		int i;
		ha->TABLE_SIZE = TABLE_SIZE;
		ha->itens = (struct aluno **) malloc(TABLE_SIZE = sizeof(struct aluno*));
	
		if(ha->itens == NULL){
			free(ha);
			return NULL;
		}

		ha->qtd = 0;

		for(i=0; i< ha->TABLE_SIZE; i++){
			ha->itens[i] = NULL;
		}
	}
	return ha;
}

void libera_hash(Hash* ha){
	if(ha != NULL){
		int i;
		for(i=0; i< ha->TABLE_SIZE;  i++){
			if(ha->itens[i] != NULL)
				free(ha->itens[i]);
			free(ha->itens);
			free(ha);
		}
	}
}


//método da congruência linear (divisão)
int chavediv (int chave, int TABLE_SIZE){
	return(chave & 0x7FFFFFFF) % TABLE_SIZE;
	

}

//método da congruência linear multiplicativa (multiplicação)
int chavemult (int chave, int TABLE_SIZE){
	float A = 0.618;
	float val = chave * A;
	val = val - (int) val;
	return (int) TABLE_SIZE * val;
}


//função para usar caso o valor chave seja uma string

int valor_string(char *str){
	int i, valor = 7;
	int tam = strlen (str);
	for(i=0; i< tam; i++){
		valor = 31 *valor + (int) str[i];
	}
	return valor;
}


int insere_hash_semcolisao_div(Hash* ha, struct aluno al){
	if(ha == NULL || ha->qtd == ha->TABLE_SIZE)
		return 0;

	char *chave;
	strcpy(chave, al.matricula);
	int valor_chave = valor_string(chave);
	int pos = chavediv(valor_chave, ha->TABLE_SIZE);


	struct aluno* novo;
	novo = (struct aluno*) malloc(sizeof(struct aluno));
	if(novo == NULL)
		return 0;
	*novo = al;
	ha->itens[pos] = novo;
	ha->qtd++;
	return 1;
}


int insere_hash_semcolisao_mult(Hash* ha, struct aluno al){
	if(ha == NULL || ha->qtd == ha->TABLE_SIZE)
		return 0;

	char *chave;
	strcpy(chave, al.matricula);
	int valor_chave = valor_string(chave);
	int pos = chavemult(valor_chave, ha->TABLE_SIZE);


	struct aluno* novo;
	novo = (struct aluno*) malloc(sizeof(struct aluno));
	if(novo == NULL)
		return 0;
	*novo = al;
	ha->itens[pos] = novo;
	ha->qtd++;
	return 1;
}


int buscaHash_semcolisao_div(Hash* ha, char* matricula, struct aluno* al){
	if(ha == NULL)
		return 0;

	int valor_mat = valor_string(matricula);
	int pos = chavediv(valor_mat, ha->TABLE_SIZE);
	*al = *(ha->itens[pos]);
	return 1;
}
int buscaHash_semcolisao_mult(Hash* ha, char* matricula, struct aluno* al){
	if(ha == NULL)
		return 0;

	int valor_mat = valor_string(matricula);
	int pos = chavemult(valor_mat, ha->TABLE_SIZE);
	*al = *(ha->itens[pos]);
	return 1;
}

int duplo_hash(int H1, int chave, int i, int TABLE_SIZE){
	int H2 = chavediv(chave, TABLE_SIZE-1) +1;
	return ((H1 + i* H2)) & 0x7FFFFFFF % TABLE_SIZE;
}


//espalhamento usando a função de duplo hash
int insereHash_end_aberto(Hash* ha, struct aluno al){
	if(ha == NULL || ha->qtd == ha -> TABLE_SIZE)
		return 0;

	char *chave;
	strcpy(chave, al.matricula);
	int valor_chave = valor_string(chave);
	int pos = chavemult(valor_chave, ha->TABLE_SIZE);


	int i, newPos;
	for(i=0; i< ha->TABLE_SIZE; i++){
		newPos = duplo_hash(pos,valor_chave, i, ha->TABLE_SIZE);
		if(ha->itens[newPos]==NULL){
			struct aluno* novo;
			novo = (struct aluno*) malloc(sizeof(struct aluno));

			if(novo == NULL)
				return 0;

			*novo = al;
			ha->itens[newPos] = novo;
			ha->qtd++;
			return 1;
		}
	}
	return 0;
}


int buscaHash_end_aberto(Hash* ha,char* matricula, struct aluno* al){
	if(ha == NULL)
		return 0;


	int valor_mat = valor_string(matricula);
	//primeiro função de hash que faz pela multiplicação
	int pos = chavemult(valor_mat, ha->TABLE_SIZE);

	int i, newPos;

	for(i=0; i< ha->TABLE_SIZE; i++){
		
		//em seguida duplo hash que faz pela divisão
		newPos = duplo_hash(pos,valor_mat, i, ha->TABLE_SIZE);
		if(ha->itens[newPos] == NULL)
			return 0;

		if(valor_string(ha->itens[newPos]->matricula) == valor_mat){
			*al = *(ha->itens[newPos]);
			return 1;
		}
	}
	return 0;
}






