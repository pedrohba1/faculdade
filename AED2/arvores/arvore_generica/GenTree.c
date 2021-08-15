#include <stdio.h>
#include <stdlib.h>
#include "GenTree.h"
#include "Queue.h"

int max(int x, int y){
	if(x>y) return x;
	return y;
}
struct _NODE {
	int info;
	struct _NODE *child;
	struct _NODE *sibling;
};

int empty_gen_tree(GenTree A) {
	if(A == NULL)
		return 1;
	else
		return 0;
}

GenTree new_gen_tree(int Element) {
	GenTree new = (GenTree)malloc(sizeof (struct _NODE));
	if(new == NULL) 
		return NULL;
	else{
		new->info = Element;
		new->child = NULL;
		new->sibling =  NULL;
		return new;
	}
}

int gen_tree_insert(GenTree A, GenTree SA) {
	if(A == NULL)
		return 0;
	else {
		SA->sibling = A->child;
		A->child = SA;
		return 1;	
	}
}

void show_gen_tree(GenTree A) {
	if(empty_gen_tree(A)) {
		printf("arvore vazia!");
		return;
	}
	else {
		printf("<%d ", A->info);
		show_gen_tree(A->child);
		printf("> ");
		show_gen_tree(A->sibling);
	}
}

int gen_tree_search(GenTree A, int Element) {
	if (empty_gen_tree(A))
		return 0;
	else if (A->info == Element)
		return 1;
	else if(gen_tree_search(A->child, Element))
		return 1;
	else
		return gen_tree_search(A->sibling, Element);
}

void gen_tree_free(GenTree *A) {
	if(empty_gen_tree(*A) != 1) {
		gen_tree_free(&((*A)->child));
		gen_tree_free(&((*A)->sibling));
		free(*A);
	}
	*A = NULL;
}

int gen_tree_height(GenTree A) {
	if(empty_gen_tree(A))
		return -1;
	else{
		GenTree aux;
		int ans = 0;
	
		for(aux = A->child; aux; aux = aux->sibling)
			ans = max(ans,gen_tree_height(aux)+1);
		return ans;
	}
}

void pre_order(GenTree A) {
	if(empty_gen_tree(A))
		return;
	else {
		printf("%d ", A->info);	
		GenTree aux;
		for(aux = A->child; aux; aux = aux->sibling){
			pre_order(aux);
		}
		pre_order(A->sibling);
	}
}

void post_order(GenTree A) {
	if(empty_gen_tree(A))
		return;
	else {
		GenTree aux;
		for(aux = A->child; aux; aux = aux->sibling){
			post_order(aux);
		}
		post_order(A->sibling);
		printf("%d ", A->info);
	}
}

void level_print(GenTree root) {
	QUEUE *q = new_queue();
	queue_insert(q, root->info);

	GenTree aux;
	while(empty_queue(q) != 1) {
		aux = search(root,queue_front(q));
		queue_remove(q);
		printf("%d ", aux->info);
		for(aux = aux->child; aux; aux = aux->sibling) {
			queue_insert(q, aux->info);
		}
	}
	puts("");
}

GenTree search(GenTree A, int Element) {
	if(empty_gen_tree(A) == 1)
		return NULL;
	if(A->info == Element)
		return A;
	GenTree aux, tmp;
	for(aux = A->child; aux; aux = aux->sibling) {
		tmp = search(aux, Element);
		if(tmp)
			return tmp; 	
	}
	return NULL;
}

int number_leaves(GenTree A) {
	if(empty_gen_tree(A) == 1)
		return 0;
	else if(A->child == NULL)
		return 1;
	else {
		GenTree aux;
		int ans=0;
		for(aux = A->child; aux; aux = aux->sibling) 
		ans = ans + number_leaves(aux);
		return ans;
	}
}

int number_children(GenTree A) {
	if(empty_gen_tree(A))
		return -1;
	else {
		GenTree aux;
		int ans=0,
			x=0;
		for(aux = A->child; aux; aux = aux->sibling, x++)
		ans = max(ans,empty_gen_tree(aux));
		ans = max(ans, x);	
		return ans;
	}
}

int number_nodes(GenTree A, int n_children){
	if(empty_gen_tree(A) == 1)
		return 0;
	else {
		GenTree aux;
		int ans=(number_children(A) == n_children);
		for(aux = A->child; aux; aux = aux->sibling) 
		ans = ans + number_nodes(aux, n_children);
		return ans;
	}
}

int height_node(GenTree A, int Element) {
	if(empty_gen_tree(A) == 1)
		return -1;
	else if(A->info == Element)
		return gen_tree_height(A);
	else {
		GenTree aux;
		int x;
		for(aux = A->child; aux; aux = aux->sibling) {
			x = height_node(aux, Element);
		if(~x)
			return x; 	
		}
		return -1;
	}
}