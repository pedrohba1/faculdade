#ifndef GENTREE_H_INCLUDED
#define GENTREE_H_INCLUDED

typedef struct _NODE *GenTree;

int empty_gen_tree(GenTree A);
GenTree new_gen_tree(int Element);
int gen_tree_insert(GenTree A, GenTree SA);
void show_gen_tree(GenTree A);
int gen_tree_search(GenTree A, int Element);
void gen_tree_free(GenTree *A);
int gen_tree_height(GenTree A);
void pre_order(GenTree A);
void post_order(GenTree A);
void level_print(GenTree root);
GenTree search(GenTree A, int Element);
int number_leaves(GenTree A);
int number_children(GenTree A);
int number_nodes(GenTree A, int n_children);
int height_node(GenTree A, int Element);

#endif // GENTREE_H_INCLUDED