#include<stdlib.h>
#include<stdio.h>
struct arvore{
int chave;
struct arvore *esq;
struct arvore *dir;
};
void insercao(struct arvore * no, int chave){
    if(chave <= no->chave){
           if(no->esq != NULL)
                  insercao(no->esq, chave);
           else{
                  struct arvore * novo = (struct arvore *) malloc(sizeof(struct arvore));
                  novo->chave = chave;
                  novo->esq = NULL;
                  novo->dir = NULL;
                  no->esq = novo;
                  printf("%d - esq do %d\n" ,chave ,no->chave);
           }
    }else{
           if(no->dir != NULL)
                  insercao(no->dir, chave);
           else{
                  struct arvore * novo = (struct arvore *) malloc(sizeof(struct arvore));
                  novo->chave = chave;
                  novo->esq = NULL;
                  novo->dir = NULL;
                  no->dir = novo;
                  printf("%d - dir do %d\n" ,chave ,no->chave);
           }
    }
}

    void remocao(struct arvore *no, int chave){
    struct arvore *p = no;
    struct arvore *pai = NULL;
     
    while(p != NULL && p->chave != chave) {
        pai = p;
        if (p->chave >= chave) {
            p = p->esq;
        } else {
            p = p->dir;
        }
    }
        if(p == NULL){
                 return;
    }
     struct arvore *m = p->dir;
    while(m != NULL && m->esq != NULL){
            m = m->esq;
    }
    struct arvore *n;
        if(m != NULL){
        m -> esq = p -> esq;
        n = p->dir;
    } else {
        n = p->esq;
    }
        if(pai->chave < chave) {
        pai->dir = n;
    } else {
        pai->esq = n;
    }
    free(p);
}

    struct arvore*busca(struct arvore*raiz, int chave){
    if(raiz==NULL){return NULL;}
    if(raiz->chave==chave){
        return raiz;
    }
    if(chave>=raiz->chave){
        return busca(raiz->dir, chave);}
    if(chave < raiz->chave){
        return busca(raiz->esq, chave);
    }
}
void emordem(struct arvore*no){
	if(no!=NULL){
		emordem(no->esq);
		printf ("%d\n", no->chave);
		emordem(no->dir);
	}
}
void label(struct arvore * no){ // IMPRESSAO LABELLED BRACKETING
     printf("[ %d ", no->chave);
     if(no->esq != NULL)
           label(no->esq);
     else
           printf("[] ");
     if(no->dir!= NULL)
           label(no->dir);
     else
           printf("[] ");
     printf("] ");     
}
void preordem(struct arvore*no)
{
	if(no!=NULL)
	{
		printf("%d\n", no->chave); //aqui voce faz o que quiser quando tiver no no. imprimir chave, ou qualquer outra coisa
		preordem(no->esq);
		preordem(no->dir);
	}
}
void posordem(struct arvore*no)
{
	if(no!=NULL)
	{
		posordem(no->esq);
		posordem(no->dir);
		printf("%d\n", no->chave);
	}
}
void main(){
	int n, menu,i;
  struct arvore * raiz = (struct arvore *) malloc(sizeof(struct arvore));
  raiz->chave = 25;
  raiz->esq = NULL;
  raiz->dir = NULL;
    printf("Digite 1 para inserir, 2 para remover, 3 para buscar\n");
  	scanf("%d",&menu);
  switch(menu){
	case 1:
		printf("Digite o numero de elementos a serem inseridos: %d\n",n);
		scanf("%d",&n);
		for(i=1;i<=n;i++){
				scanf("%dº numero a ser inserido",&i);
				insercao(raiz,i);
		}
	
	case 2:
		printf("Digite o elemento a ser removido:%d\n",n);
		scanf("%d",&n);
		remocao(raiz,n);
    case 3:
    	printf("Digite o elemento a ser buscado:%d\n",&n);
    	scanf("%d",&n);
    	busca(raiz,n);
	
	default:
    	printf("Numero nao pertencente ao menu\n");
    	
}
}


