#include <stdio.h>
#include "GenTree.h"

int main() {
	GenTree A = new_gen_tree(1);
	GenTree B = new_gen_tree(2);
	GenTree C = new_gen_tree(3);
	GenTree D = new_gen_tree(4);
	GenTree E = new_gen_tree(5);
	GenTree F = new_gen_tree(6);
	GenTree G = new_gen_tree(7);
	GenTree H = new_gen_tree(8);
	GenTree I = new_gen_tree(9);

	gen_tree_insert(F,I);
	gen_tree_insert(F,H);
	gen_tree_insert(C,F);
	gen_tree_insert(C,E);
	gen_tree_insert(D,G);
	gen_tree_insert(A,D);
	gen_tree_insert(A,C);
	gen_tree_insert(A,B);

	show_gen_tree(A);
	puts("");

	level_print(A);
	puts("");

	printf("ALTURA 1: %d\n", height_node(A,1));
	printf("ALTURA 2: %d\n", height_node(A,2));
	printf("ALTURA 3: %d\n", height_node(A,3));
	printf("ALTURA 4: %d\n", height_node(A,4));
	printf("ALTURA 5: %d\n", height_node(A,5));
	printf("ALTURA 6: %d\n", height_node(A,6));
	printf("ALTURA 7: %d\n", height_node(A,7));
	printf("ALTURA 8: %d\n", height_node(A,8));
	printf("ALTURA 9: %d\n", height_node(A,9));

	gen_tree_free(&A);		
	if(A == NULL)
		puts("ARVORE DESTRUIDA");

	return 0;
}














