#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tadArvore.h"

int main(int argc, char const *argv[])
{
	
	tree *Arvore = IniciaArvore();
	char comando1[20], comando2[20];
	char* teste;
	int valor;
	//float nota1, nota2, nota3;
	FILE *arq;
	FILE *arq2;
	arq2 = fopen("saida.txt", "w");
	arq = fopen(argv[1], "r");
	if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		while( (fscanf(arq,"%s %s\n", comando1, comando2))!=EOF ){
			//printf("%s\n",comando1);
			if(strcmp(comando1,"INCLUI")==0){
				valor = strtol(comando2,&teste,10);
				//valor = comando2 - 48;
				Insere(Arvore,valor);
				//listar(Arvore->root);
				
			}
			else if(strcmp(comando1,"EXCLUI")==0){
				int valor2 = strtol(comando2,&teste,10);
				Arvore->root = Excluir(Arvore->root,valor2);
				balancear_tree(Arvore);
				
				
			}
			else if(strcmp(comando1,"BUSCA")==0){
				valor = strtol(comando2,&teste,10);
				Node* aux = Buscar(Arvore,valor);
				if(aux!=NULL){
					fprintf(arq2,"%d\n",aux->valor);
				}
				else{
					fprintf(arq2, "Elemento %d não encontrado\n",valor);
				}
			}
			else if(strcmp(comando1,"IMPRIME")==0){
				if(strcmp(comando2,"INORDEM")==0){
					//printf("Entrou INORDEM\n");
					fprintf(arq2,"<");
					arq2 = listarINORDEM(Arvore->root, arq2);
					fprintf(arq2,">\n");
				}
				if(strcmp(comando2,"PREORDEM")==0){
					fprintf(arq2,"<");
					arq2 = listarPREORDER(Arvore->root, arq2);
					fprintf(arq2,">\n");
				}
				if(strcmp(comando2,"POSORDEM")==0){
					fprintf(arq2,"<");
					arq2 = listarPOSORDEM(Arvore->root, arq2);
					fprintf(arq2,">\n");
				}
			}
		}
	
	fclose(arq);
	fclose(arq2);
	liberar_memoria(Arvore);
	return 0;
} 
