#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"


int main() {
	




	Registro *p1;
	p1 = aloca_registro(12,"miguel", "Cîência da Computação");
	Registro *p2;
	p2 = aloca_registro(25,"duda", "Direito");
	Registro *p3;
	p3 = aloca_registro(27,"rafel", "Engenharia");
	Registro *p4;
	p4 = aloca_registro(23,"Juninho lorde das trevas","Engenharia de explosivos");
	Registro *p5;
	p5 = aloca_registro(42,"Ricardo", "Sistemas");
	



	Arv A;
	A = cria_vazia();
	insere_ord(&A,p1);
	insere_ord(&A,p2);
	insere_ord(&A,p3);
	insere_ord(&A,p4);
	
	Arv A2;
	A2 = cria_vazia();
	insere_ord(&A2, p5);



	int opcao = 1;
	while(1)
	{
	printf("======================================\n");
	printf("Bem vindo à ABB, que operação deseja realizar? \n");

	printf("1-Buscar o aluno mais velho cadastrado\n");
	printf("2-Verificar quantos alunos são maiores de 18 anos\n");
	printf("3-Retornar a quantidade de nós que possuem apenas 1 filho\n");
	printf("4-Retornar a quantidade de alunos entre determinada faixa de idades\n");
	printf("5-Verificar se árvore é completa\n");
	printf("6-Verificar a altura da árvore\n");
	printf("7-Juntar duas árvores\n");
	printf("8-Escrever a árvore em ordem\n");
	printf("9-sair\n");
	
	scanf("%d", &opcao);


		switch(opcao) {
			case 1:
				printf("======================================\n");
				printf("o maior aluno é o seguinte:\n\n");
				printa_registro(maior(A));
				break;
			case 2:
				printf("======================================\n");
				printf("total de alunos maiores que 18 anos: %d \n", de_maior(A));
				break;
			case 3:
				printf("======================================\n");
				printf("nós com apenas um filho %d\n",um_filho(A));
				break;
			case 4:
				printf("======================================\n");
				printf("digite o limite inferior da faixa\n");
				int menor;
				scanf("%d", &maior);
				printf("agora, digite o limite superior\n");
				int maior;
				scanf("%d", &maior);
				printf("A quantidade de alunos entre essa faixa de idades é %d\n",qtde_alunos(A,menor,maior));
				break;
			case 5:
				printf("======================================\n");
				if(completa(A))
					printf("sim, essa árvore é completa\n");
				else 
					printf("não, essa árvore não é completa\n");
				break;
			case 6:
				printf("======================================\n");
				printf("a altura dessa ávore é %d", altura_arv(A));
				break;
			case 7:
				printf("======================================\n");
				if(juntar(A,A2))
						printf("Árvores unidas com sucesso!\n");
				break;
			
			case 8:
				printf("======================================\n");
				exibe_ordenado(A);
				break;

			case 9:
				libera_arvore(&A);
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