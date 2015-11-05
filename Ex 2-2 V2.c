#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct arvore{
    int grau;
    char nome [20];
    struct arvore *pai;
    struct arvore *mae;
};

struct arvore * search (struct arvore * raiz, char * nome){
	if(raiz!=NULL){
		search(raiz->pai,nome);
		if(strcmp(raiz->nome,nome)==0){
			return raiz;
		}
		search(raiz->mae,nome);
	}
}


void Insertion(struct arvore * raiz, char * filho, char * pai, char * mae, int k){
	struct arvore * p = (struct arvore *) malloc(sizeof(struct arvore));
	struct arvore * m = (struct arvore *) malloc(sizeof(struct arvore));
	p->pai = NULL;
    p->mae = NULL;
    m->pai = NULL;
    m->mae = NULL;
    strcpy(p->nome,pai);
    strcpy(m->nome,mae);
    search(raiz,filho)->pai = p;
    search(raiz,filho)->mae = m;
    p->grau = search(raiz,filho)->grau + 1;
    m->grau = p->grau;
    if (p->grau>k){
    	k=p->grau;
	}
}



int Parentesco(struct arvore * raiz, char * nome1, char * nome2){
	int a = search(raiz,nome1)->grau;
	int b = search(raiz,nome2)->grau;
	if (a>=b){
		if (search(search(raiz,nome1),nome2)!=NULL){
			return (a-b);
		}
		else{
			return 0;
		}
	}
	else{
		if (search(search(raiz,nome1),nome2)!=NULL){
			return (b-a);
		}
		else{
			return 0;
		}
	}
}

void ImpGeracaoN(struct arvore * raiz,int n){
	if(raiz!=NULL){
		ImpGeracaoN(raiz->pai,n);
		if(raiz->grau == n){
			printf("%s\n",raiz->nome);
		}
		ImpGeracaoN(raiz->mae,n);
	}
}

void ImpGeracaoTotal(struct arvore * raiz,int k){
	int i;
	if (raiz->grau>=k){
		printf("Nao possui antepassados\n");
	}
	else{
		for(i=raiz->grau;i<=k;i++){
			ImpGeracaoN(raiz,i);
			printf("\n");
	    }
	}
}


void ImpLabel(struct arvore * raiz){
	printf("[ %s ", raiz->nome);
     if(raiz->pai != NULL)
           ImpLabel(raiz->pai);
     else
           printf("[] ");
     if(raiz->mae!= NULL)
           ImpLabel(raiz->mae);
     else
           printf("[] ");
     printf("] ");     
}

void main(){
	int menu,i,imp,a;
	int k = 1;
	char f[20],p[20],m[20];
	struct arvore * raiz = (struct arvore *) malloc(sizeof(struct arvore));
	raiz->pai = NULL;
    raiz->mae = NULL;
    raiz->grau = k;
	printf("Digite a primeira entrada para a arvore genealogica (formato filho_pai_mae):\n");
	scanf("%s",&f);
	scanf("%s",&p);
	scanf("%s",&m);
	strcpy(raiz->nome,f);
	Insertion(raiz,f,p,m,k);
	int exit = 0;
	while (exit ==0){
    	printf("Digite 1 para inserir, 2 para grau de parentesco, 3 para imprimir, 4 para sair:  ");
    	scanf("%d",&menu);
        switch(menu){
	        case 1:
		        printf("Digite o numero de entradas (formato filho_pai_mae) a serem inseridas:\n");
		        scanf("%d", &a);
		        for(i=1;i<=a;i++){
				    printf("Digite %d-a entrada a ser inserida: ",i);
				    char f1[20],p1[20],m1[20];
				    scanf("%s",&f1);
	                scanf("%s",&p1);
	                scanf("%s",&m1);
				    Insertion(raiz,f1,p1,m1,k);
		        }
		        break;
            case 2:
    	        printf("Digite os dois nomes para a comparacao (formato nome_nome):\n");
    	        char f[20],p[20];
    	        scanf("%s",&f);
    	        scanf("%s",&p);
    	        printf("O grau de parentesco eh de: %d\n",Parentesco(raiz,f,p));
    	        break;
            case 3:
            	printf("Digite 1 para imprimir a arvore por geracao, 2 para imprimir a arvore em LABELLED BRACKETING, 3 para imprimir antepassados de um individuo:\n");
            	scanf("%d",&imp);
            	if(imp==1){
            		ImpGeracaoTotal(raiz,k);
            	}
            	if(imp==2){
            		ImpLabel(raiz);
            	}
            	if(imp==3){
            		printf("Digite o nome cujos antepassados serao impressos:\n");
            		scanf("%s",&m);
            		ImpGeracaoTotal(search(raiz,m),k);
				}
				if(imp!=1&&imp!=2&&imp!=3){
    	            printf("Numero nao pertencente ao menu\n");
				}
				break;		
    	    case 4:
    	        exit = 1;
    	        break;
	        default:
    	        printf("Numero nao pertencente ao menu\n");
        }
    }
}


