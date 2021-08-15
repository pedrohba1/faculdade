#ifndef ARVORES_H_INCLUDED
#define ARVORES_H_INCLUDED

typedef struct no* Arv;
typedef struct aluno Registro;

Registro* aloca_registro(int matricula, char *nome, int idade);
Arv cria_vazia();
Arv cria_arvore(Registro * rnew, Arv esq, Arv dir);
int arvore_vazia(Arv A);
int libera_arvore(Arv *A);
Registro* maior(Arv A);
int de_maior(Arv A);
int qtde_alunos(Arv A, int ini, int fim);
int um_filho(Arv A);
int completa(Arv A);
int altura_arv(Arv A);
Arv juntar(Arv A1, Arv A2);
void copiaRegistro(Arv arv, Registro* a);

//TAD
void exibe_arv(Arv A);
int insere_ord(Arv *A, Registro *r);
int remove_ord(Arv* A, Registro * r);
void printa_registro(Registro *r);
int qtd_nos(Arv A);
Arv busca_bin(Arv A, int matricula);

#endif // ARVORES_H_INCLUDED
