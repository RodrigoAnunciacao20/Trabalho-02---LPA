#include<stdlib.h>
#include<stdio.h>


struct arvore{
int chave;
struct arvore *esq;
struct arvore *dir;
};


void insercao(struct arvore * no, int chave){  
	struct arvore * novo = (struct arvore *) malloc(sizeof(struct arvore));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    if(chave <= no->chave){
           if(no->esq != NULL)
                  insercao(no->esq, chave);
           else{
                  no->esq = novo;
                  printf("%d - esq do %d\n" ,chave ,no->chave);
           }
    }else{
           if(no->dir != NULL)
                  insercao(no->dir, chave);
           else{
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


int busca(struct arvore*raiz, int chave){
    if(raiz==NULL){
	    return 0;
		}
    if(raiz->chave==chave){
        return 1;
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


void preordem(struct arvore*no){
	if(no!=NULL){
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
    int menu,imp,i,a,b,c,aux;
    struct arvore * raiz = (struct arvore *) malloc(sizeof(struct arvore));
    raiz->esq = NULL;
    raiz->dir = NULL;
    printf("Digite a raiz: ");
    scanf("%d",&raiz->chave);
    int exit = 0;
    while (exit ==0){
    	printf("Digite 1 para inserir, 2 para remover, 3 para buscar, 4 para imprimir, 5 para sair: ");
    	scanf("%d",&menu);
        switch(menu){
	        case 1:
		        printf("Digite o numero de elementos a serem inseridos: ");
		        scanf("%d", &a);
		        for(i=1;i<=a;i++){
				    printf("Digite %d-o numero a ser inserido: ",i);
				    scanf("%d",&aux);
				    insercao(raiz,aux);
		        }
		        break;
	        case 2:
		        printf("Digite o elemento a ser removido: ");
		        scanf("%d",&b);
		        remocao(raiz,b);
		        break;
            case 3:
    	        printf("Digite o elemento a ser buscado: ");
    	        scanf("%d",&c);
    	        if(busca(raiz,c)==1){
    	        	printf("O numero esta na arvore!\n");
				}else{
					printf("O numero nao esta na arvore!\n");
				}
    	        break;
            case 4:
            	printf("Digite 1 para em ordem, 2 para preordem, 3 para posordem, 4 para labelled: ");
            	scanf("%d",&imp);
            	if(imp==1){
            		emordem(raiz);
            	}
            	if(imp==2){
            		preordem(raiz);
            	}
         		if(imp==3){
           			posordem(raiz);
			    }
            	if(imp==4){
            		label(raiz);
                }
				if(imp!=1&&imp!=2&&imp!=3&&imp!=4){
    	            printf("Numero nao pertencente ao menu\n");
				}
				break;		
    	    case 5:
    	        exit = 1;
    	        break;
	        default:
    	        printf("Numero nao pertencente ao menu\n");
    	
        }
    }
}
   



