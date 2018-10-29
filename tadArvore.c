#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "tadArvore.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))

void liberar(Node * no){
	if ( no == NULL )
		return;

	liberar( no->esq );
	liberar( no->dir );

	free (no);
}


void liberar_memoria (tree * tree )
{
	liberar(tree->root);
}



tree* IniciaArvore(){
	tree *Arvore = (tree*)malloc(sizeof(struct arvore));// Aloca arvore
	Arvore->root = NULL;
	return Arvore;
}

Node* IniciaNodo(int valor){
	Node *novo = (Node*)malloc(sizeof(struct nodo));
	novo->esq = NULL;
	novo->dir = NULL;
	novo->valor = valor; 
	return novo; 
}

int altura(Node *nodo){
	int alturaEsq = 0;
	int alturaDir = 0;//alturas iniciadas com 0

	if (nodo->esq) {//se existir filho a esquerda
		alturaEsq = altura(nodo->esq); //atualiza altura á esquerda
	}
	
	if (nodo->dir){ //se existir filho a direita
		alturaDir = altura(nodo->dir); //atualiza altura á direita
	}	

	return(MAX(alturaDir, alturaEsq) + 1); //realiza a operação de maior que, retorna direita+1 se > e esquerda se menor+1
}

int calculoFB(Node* nodo){
	int fb = 0;

	if (nodo->esq){ //a partir desse nodo se ele tiver valor a esquerda 
		fb = fb + altura(nodo->esq); //calcula toda a altura à esquerda desse nó. FB no final é altura da arvore de nodo pela esquerda
	}

	if (nodo->dir){ //a partir desse nodo se ele tiver valor a direita
		fb = fb - altura(nodo->dir);//pega o fb(que ja contem o valor da subarvore a esquerda de nodo) e subtrai pela altura da subarvore a direita
	}

	return fb; //retorna o fator de balanceamento 2, -2,-1, 1 ou 0
}

Node * rotaciona_RR( Node* nodo){
	Node* aux = nodo; //AUxiliar recebe o no
	Node *left = aux->esq; //left recebe o filho a esquerda do no
	aux->esq = left->dir;//auxiliar de no a esquerda recebe o seu neto a direita(filho do seu filho a esqueda) 
	left->dir = aux; //o no se torna filho a direita de left(Que era anteriormente seu filho a esquerda)
	return left;
}

Node * rotaciona_LL(Node *nodo){
	Node *aux = nodo;
	Node *right = aux->dir;
	aux->dir = right->esq;
	right->esq = aux;
	return right;
}

Node * rotationa_LR(Node* nodo){
	Node *aux = nodo;// aux é o novo nodo 
	Node *left = aux->esq;//left recebe o no à esquerda 
	Node *right = left->dir; //right recebe o filho a direita do filho do no afetado
	aux->esq = right->dir; //a esquerda do no recebe do no afetado o filho do seu filho a direita;
	left->dir = right->esq;
	right->esq = left;
	right->dir = aux;

	return right;
}


Node * rotaciona_RL(Node* nodo){
	Node * aux = nodo;
	Node * right = aux->dir;
	Node * left = right->esq;
	aux->dir = left->esq;
	right->esq = left->dir;
	left->dir = right;
	left->esq = aux;
	return left;
}



Node * balanceamento(Node* nodo){

	Node *no_balanceado = NULL;
	if (nodo->esq){//se existir filho esquerdo
		nodo->esq = balanceamento(nodo->esq); //percorre a subarvore a esquerda de nodo
	}
	if (nodo->dir){ //se existir filho direito
		nodo->dir = balanceamento(nodo->dir); //percorre a subarvore a direita do no 
	}
	int fb = calculoFB(nodo); // Calcula-se o FB de cada no percorrido na subarvore;
	if(fb >= 2){ //Quando o FB for 2 significa que existe mais nós a esquerda
		if (calculoFB( nodo->esq) <= -1 ){ //se o nodo a esquerda desse no tiver um fb 
			no_balanceado = rotationa_LR(nodo);//se tiver um negativo no primeiro nodo a esquerda da subarvore acontece rotação dupla
		}
		else{ //se o fb do filho esquerdo não for negativo, a rotação é simples .
			no_balanceado = rotaciona_RR(nodo);
		}
	}
	else if (fb <= -2){// existe mais nó's na direita 
		if (calculoFB(nodo->dir) >= 1){ //verifica se a filho a direita do no afetado é positivo
			no_balanceado=rotaciona_RL(nodo); //Se a condição for verdadeira é feita uma rotação dupla no no afetado
		}
		else{
			no_balanceado = rotaciona_LL(nodo); //Se o filho da direita do no afetado não for positivo realiza uma rotação simples a direita
		}
	}
	else //Se FB não cair em nenhum caso onde a altura é -2 ou 2, significa que a arvore já está balanceada.
	{
		no_balanceado = nodo; //no balanceado recebe o proprio no(pois ele n está desbalanceado)
	}
	return no_balanceado;
}

void balancear_tree (tree *Arvore ){
	Node* novoR = NULL; 
	novoR = balanceamento(Arvore->root);//Chama a função de balanceamento apartir do nó raiz da arvore;
	//novoR é a nova raiz já com a arvore balanceada;
	if (novoR!= Arvore->root){ //Se a nova raiz for diferente da raiz original da arvore, significa que houve um desbalaceamento que alterou a arvore original
		Arvore->root = novoR; //A raiz da arvore recebe o valor da nova raiz;
	}
}

void Insere(tree* Arvore, int valor){
	Node* ultimo = NULL;
	Node* prox = NULL;
	Node* novo = NULL;

	if (Arvore->root == NULL ){ //Se a arvore é vazia
		novo = IniciaNodo(valor); //Chama a função que cria o novo nó.
		Arvore->root = novo; //Como a arvore era vazia, o novo nó se torna raiz da arvore;
	}
	else{//Se a arvore não é vazia e existe uma raiz
		prox = Arvore->root;
		while (prox!= NULL){ //percorre a arvore nesse while até atigir vazio;
			ultimo=prox; //ultimo é uma variavel que pega o ultimo nó valido que prox visitou antes de vazio
			// O caminhamento da arvore será feito de acordo com o valor a ser inserido, se ele for maior ou menor que a raiz determina a subarvore que será percorrida 
			if(valor < prox->valor){//Se o valor for menor que o no atual ele desce pra esquerda;
				prox = prox->esq; //prox recebe o nó a esquerda
			}
			else if(valor > prox->valor){//Se o valor do novo nó não é menor que o nó atual e ele é maior então o prox desce pra direita
				prox = prox->dir; //proximo recebe seu filho a direita
			}
			else if(valor == prox->valor){ //Se o valor do nó é igual ao valor a ser inserido, entao ja existe e ele retorna
				return; //Sai do laço pq ja existe esse valor
			}
		}//Chegou no nulo da arvore e é onde o novo nó será inserido
		novo = IniciaNodo(valor);//O nó é criado e novo recebe; 
		if (valor < ultimo->valor){
		//ultimo aponto pro nó folha que receberá o novo valor, se o valor a ser inserido é menor que nó atual
			ultimo->esq = novo; // O novo nó será filho a esquerda de ultimo
		}
		if ( valor > ultimo->valor ){
			//Se o valor for maior que ultimo;
			ultimo->dir = novo; // O novo nó será filho a direita de ultimo
		}

	}
	balancear_tree (Arvore);
}


Node *Buscar(tree *Arvore,int valor){
	Node* aux = Arvore->root; //A variavel auxiliar recebe raiz da arvore
	while(aux && aux->valor != valor){ //o loop percorre toda a arvore enquanto valor for difere do valor buscado
		if ( valor > aux->valor ){ // se o valor for maior que o no atual aux segue seu filho a direita
			aux = aux->dir;
		}
		else{
			aux = aux->esq; 
		}
	}

	return aux;
}

Node* MaiorDireita(Node *no){
	
	if(no->dir != NULL){
		return MaiorDireita(no->dir);
	}
	return no;
}

Node* Excluir(Node *raiz, int valor){
	if(raiz == NULL){   // esta verificacao serve para caso o numero nao exista na arvore.
       printf("Numero nao existe na arvore!");
       return raiz;
    }
    if(valor < raiz->valor)
       raiz->esq = Excluir(raiz->esq, valor);
    else
       if(valor > raiz->valor)
          raiz->dir = Excluir(raiz->dir, valor);
       else{    // se nao eh menor nem maior, logo, eh o numero que estou procurando! :)
       	//printf("ENTROU\n");
          Node* aux = raiz;     // quem programar no Embarcadero vai ter que declarar o pAux no inicio do void! :[
          if ((raiz->esq == NULL) && (raiz->dir == NULL)){         // se nao houver filhos...
          	//printf("ESQUERDA E DIREITA NULO\n");
                free(raiz);
                raiz = NULL; 
               }
          else{     // so tem o filho da direita
             if (raiz->esq == NULL){
             //	printf("FILHO NA DIREITA %d",raiz->dir->valor);
                raiz = raiz->dir;
                free(aux);
                aux = NULL;
                }
             else{            //so tem filho da esquerda
                if (raiz->dir == NULL){
               // 	printf("FILHO NA ESQUERDA %d",raiz->esq->valor);
                    raiz = raiz->esq;
                    free(aux); 
                    aux = NULL;
                    }
                else{       //Escolhi fazer o maior filho direito da subarvore esquerda.
                 //  printf("DOIS FILHOS ESQ%d E DIR: %d\n",raiz->esq->valor, raiz->dir->valor );
                   aux = MaiorDireita(raiz->esq); //se vc quiser usar o Menor da esquerda, so o que mudaria seria isso:
                   raiz->valor = aux->valor;
                   aux->valor = valor;
                   raiz->esq = Excluir(raiz->esq,valor);
               		}
                   }
                }
             }
             return raiz;
          }
        


FILE* listarPREORDER(Node* no,FILE* arq){
	if(arq == NULL){
     	printf("Erro na abertura do arquivo!");
     	return arq;
  	}
	if (no!=NULL){
		//fprintf(arq,"No = %d,altura = %d,FATBAL = %d;",no->valor,altura(no),calculoFB(no));
		fprintf(arq, "%d - ", no->valor);
		listarPREORDER(no->esq,arq);
		listarPREORDER(no->dir,arq);
	}
	return arq;
}

FILE* listarINORDEM(Node* no, FILE* arq){
 	
 	if(arq == NULL){
     	printf("Erro na abertura do arquivo!");
     	return arq;
  	}
 	if (no!=NULL){
		listarINORDEM(no->esq,arq);
		//fprintf(arq, "No = %d, Altura = %d, FATBAL = %d;",no->valor,altura(no),calculoFB(no));
		fprintf(arq, "%d - ", no->valor);
		listarINORDEM(no->dir,arq);
	}
  //fclose(arq);
  return arq;
}

 
 FILE* listarPOSORDEM(Node* no, FILE* arq){
 	
 	if(arq == NULL){
     	printf("Erro na abertura do arquivo!");
     	return arq;
  	}
 	if (no!=NULL){
		listarPOSORDEM(no->esq,arq);
		listarPOSORDEM(no->dir,arq);
		//fprintf(arq, "No = %d, Altura = %d, FATBAL = %d;",no->valor,altura(no),calculoFB(no));
		fprintf(arq, "%d - ", no->valor);
	}
  //fclose(arq);
  return arq;
}
		









