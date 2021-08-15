#ifndef HASH_H_
#define HASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno {
	int idade;
	char nome[30];
	char matricula[11]; // o número de matrícula estou supondo que é igual o de 
						//um aluno da ufu, exemplo: 11711BCC028 (11 caracteres)

};

typedef struct hash Hash;


Hash* cria_hash(int TABLE_SIZE);
void libera_hash(Hash* ha);
int chavediv (int chave, int TABLE_SIZE);
int chavemult(int chave, int TABLE_SIZE);
int valor_string(char *str);

//funções de inserção:
int insere_hash_semcolisao_div(Hash* ha, struct aluno al);
int insere_hash_semcolisao_mult(Hash* ha, struct aluno al);

//funções de busca:
int buscaHash_semcolisao_div(Hash* ha, char* matricula, struct aluno * al);
int buscaHash_semcolisao_mult(Hash* ha, char* matricula, struct aluno* al);


int duplo_hash(int H1, int chave, int i, int TABLE_SIZE);

//função de espalhamento (inserção e busca)
int insereHash_end_aberto(Hash* ha, struct aluno al);
int buscaHash_end_aberto(Hash* ha,char* matricula, struct aluno* al);
/* respostas da questão 4:


a) Explique a relação entre o tamanho da tabela e a probabilidade de colisão 
da função hash.
Resposta: 
quando é realizado o hashing imperfeito, isto é, quando chaves diferentes 
ocasionalmente resultarem em uma mesma posição da tabela a quantidade de 
colisões aumentará. Uma tabela hash com um hashin imperfeito, se ela tiver 
muitos elementos, faz sentido a chance de ter mais colisões aumentar.



b)Por que a chave no método da divisão do prof. Backes sugere a conjunção
da chave com a constante "0x7FFFFFFF"?
Resposta:
esse operador & com o valor em hexadecimal acima serve para remover o  
bit de sinal do número caso ele seja negativo. Se um número é negativo,
o seu bit mais significativo é 1. Realizando a opreação & entre esse número e 
0x7FFFFFFF deixa o bit mais significativo em 0, removendo o sinal e deixando o
número positivo. Todos os outros bits do número mantêm-se iguais.

OBS: 0x7FFFFFFF equivale à 0111 1111 1111 1111 1111 1111 1111 1111 em binário,
inteiro e de 32 bits.
repare que o bit mais significativo é 0.
exemplo, comparar o número -4 (1000 0000 0000 0000 0000 0000 00000 0100 em 
binário com 32 bits.) com o número 0111 1111 1111 1111 1111 1111 1111 1111.

1000 0000 0000 0000 0000 0000 0000 0100 
0111 1111 1111 1111 1111 1111 1111 1111 &
______________________________________
000 0000 0000 0000 0000 0000 0000 0100

o resultado é o número 4, sem sinal, positivo.


c)Por Que a posição da letra deve ser considerada no cálculo da posição da tabela?
Resposta:
Devemos considerar  a posição da letra porque caso contrário palavras 
com letras iguais com posições diferentes vão gerar o mesmo valor.
exemplo:
cama: 99 +97 + 109 + 97 = 402
maca: 109 + 97 + 99 + 97 = 402



*/	


#endif 