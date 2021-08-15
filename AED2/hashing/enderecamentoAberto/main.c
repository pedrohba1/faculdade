#include <stdio.h>
#include "hash.h"

int main() {
	Hash* hash;
	struct aluno aux;
	int x;
	char str[50];
	
	int opcao = 1;
	while(1) {
		printf("======================================\n");
		printf("1-Criar Tabela Hash\n");
		printf("2-Inserir aluno\n");
		printf("3-Buscar aluno por matricula:\n");
		printf("4-Exibir Tabela\n");
		printf("5-sair\n");
		
		scanf("%d", &opcao);
		switch(opcao) {
			case 1:
				printf("======================================\n");
				printf("Tamanho da tabela: ");
				scanf("%d", &x);
				hash = criaHash(x);
				break;
			case 2:
				printf("======================================\n");
				printf("Nome: ");
				scanf("%s", str);
				aux.nome = str;
				printf("Idade: ");
				scanf("%d", &aux.idade);
				printf("Matricula: ");
				scanf("%d", &aux.matricula);
				insereHashEnderAberto(hash, aux);
				break;
			case 3:
				printf("======================================\n");
				printf("Matricula: ");
				scanf("%d", &x);
				
				if(buscaHashEnderAberto(hash, x, &aux)) {
					printaRegistro(&aux);
				} else {
					printf("Nao encontrado\n");
				}
				
				break;	
			case 4:
				printaHash(hash);
				break;

			case 5:
				liberaHash(hash);
				printf("fechando .....\n");
				return 0;
				break;

			default:
				printf("digite uma opção válida\n");
				break;

		}
	}
	return 0;
}