#ifndef _tadArvore
#define _tadArvore

typedef struct nodo Node;

struct nodo{
	Node *esq;
	Node *dir;
	int valor;
};

typedef struct arvore tree; 

struct arvore{
	Node *root;
};

tree* IniciaArvore();
Node* IniciaNodo(int valor);
int altura(Node *nodo);
int calculoFB(Node* nodo);
Node * rotaciona_RR( Node* nodo);
Node * rotaciona_LL(Node *nodo);
Node * rotationa_LR(Node* nodo);
Node * rotaciona_RL(Node* nodo);
Node * balanceamento(Node* nodo);
void balancear_tree (tree *Arvore );
void Insere(tree* Arvore, int valor);
Node *Buscar(tree *Arvore,int valor);
Node* MaiorDireita(Node *no);
Node* Excluir(Node *raiz, int valor);
FILE* listarPREORDER(Node* no,FILE* arq);
FILE* listarINORDEM(Node* no, FILE* arq);
FILE* listarPOSORDEM(Node* no, FILE* arq);
void liberar_memoria( tree * tree );
void liberar(Node * no);

#endif
