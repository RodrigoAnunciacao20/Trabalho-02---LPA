#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct arvore{
    int ant;
    char nome [20];
    struct arvore *pai;
    struct arvore *mae;
};

struct arvore * search (struct arvore * raiz, char * nome){
	if (strcmp(raiz->nome,nome)==0){
		return raiz;
	}
	if (strcmp(raiz->nome,nome)!=0){
		return search(raiz->pai, nome);
	}
	if (strcmp(raiz->nome,nome)!=0){
		return search(raiz->mae, nome);
	}
}

void Insertion(struct arvore * raiz, char * filho, char * pai, char * mae){
	struct arvore * aux1 = (struct arvore *) malloc(sizeof(struct arvore));
	aux1->pai = NULL;
    aux1->mae = NULL;
	struct arvore * aux2 = (struct arvore *) malloc(sizeof(struct arvore));
	aux2->pai = NULL;
    aux2->mae = NULL;
	if (strcmp(raiz->nome,filho)==0){
		raiz->pai = aux1;
		strcpy(pai,aux1->nome);
		aux1->ant = raiz->ant + 1;
		raiz->mae = aux2;
		strcpy(mae,aux2->nome);
		aux2->ant = raiz->ant + 1;
	}
	if(strcmp(raiz->nome,filho)!=0){
		Insertion(raiz->pai, filho, mae, pai);
	}
	if(strcmp(raiz->nome,filho)!=0){
		Insertion(raiz->mae, filho, mae, pai);
	}
}

int Parentesco(struct arvore * raiz, char * nome1, char * nome2){
	int a = search(raiz,nome1)->ant;
	int b = search(raiz,nome2)->ant;
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

void ImpGeracao(struct arvore * raiz){
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
	char * f = (char *)malloc(20*sizeof(char));
	char * p = (char *)malloc(20*sizeof(char));
	char * m = (char *)malloc(20*sizeof(char));
	struct arvore * raiz = (struct arvore *) malloc(sizeof(struct arvore));
	raiz->pai = NULL;
    raiz->mae = NULL;
	printf("Digite a primeira entrada para a arvore genealogica (formato filho_pai_mae): ");
	scanf("%s",&f);
	scanf("%s",&p);
	scanf("%s",&m);
	strcpy(f,raiz->nome);
	Insertion(raiz,f,p,m);
	free(f);
	free(p);
	free(m);
	int exit = 0;
	while (exit ==0){
    	printf("Digite 1 para inserir, 2 para grau de parentesco, 3 para imprimir, 4 para sair:  ");
    	scanf("%d",&menu);
        switch(menu){
	        case 1:
		        printf("Digite o numero de entradas (formato filho_pai_mae) a serem inseridas: ");
		        scanf("%d", &a);
		        for(i=1;i<=a;i++){
				    printf("Digite %d-a entrada a ser inserida: ",i);
				    scanf("%s",&f);
	                scanf("%s",&p);
	                scanf("%s",&m);
				    Insertion(raiz,f,p,m);
				    free(f);
	                free(p);
	                free(m);
		        }
		        break;
            case 2:
    	        printf("Digite os dois nomes para a comparacao (formato nome_nome): ");
    	        scanf("%s",&f);
    	        scanf("%s",&p);
    	        printf("O grau de parentesco eh de: %d",Parentesco(raiz,f,p));
    	        break;
            case 3:
            	printf("Digite 1 para imprimir a arvore por geracao, 2 para imprimir a arvore em LABELLED BRACKETING, 3 para imprimir antepassados de um individuo: ");
            	scanf("%d",&imp);
            	if(imp==1){
            		ImpGeracao(raiz);
            	}
            	if(imp==2){
            		ImpLabel(raiz);
            	}
            	if(imp==3){
            		printf("Digite o nome cujos antepassados serao impressos: ");
            		scanf("%s",&m);
            		ImpGeracao(search(raiz,m));
				}
				if(imp!=1&&imp!=2&&imp!=3){
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
    free(f);
	free(p);
	free(m);
}

