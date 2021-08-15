#include "hash.h"



int main() {
	Hash* ha = cria_hash(1427);
	
	struct aluno al;
	char* matric;
int opcao = 1;
while(1){
	printf("======================\n");
	printf("PROGRAMA DA TABELA HASH \n");
	printf("qual operação deseja realizar?\n");
	printf("1- inserir aluno na tabela hash\n");
	printf("2- buscar na tabela hash\n");
	printf("3- sair\n");
	scanf("%d",&opcao);

	switch(opcao){
		case 1: 
			printf("======================\n");
			printf("escreva o nome do aluno\n");
			scanf("%s", &al.nome);
			printf("escreva a idade do aluno\n");
			scanf("%d",&al.idade);
			printf("escreva a matricula do aluno\n");
			scanf("%s",&al.matricula);		
			insereHash_end_aberto(ha, al);
			break;
		case 2:
			printf("======================\n");
			printf("escreva o número de matrícula do aluno que quer buscar:\n");
			scanf("%s", &matric);
			buscaHash_end_aberto(ha, matric,&al);
			break;
		case 3:
			printf("======================\n");
			printf("saindo...\n");
			return 0;
			break;
		}
	}
	libera_hash(ha);
	return 0;
}