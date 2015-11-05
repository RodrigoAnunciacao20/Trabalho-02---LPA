#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct arvore{ //variavél da arvore genealógica
    int grau;
    char nome [20];
    struct arvore *pai;
    struct arvore *mae;
};

struct arvore *search(struct arvore *raiz, char *nome){ //função para a busca de um determinado indivíduo da árvore pelo seu nome
	int sign; //variavél auxiliar responsável por determinar se a comparação é ou não verdadeira
	if(raiz==NULL){
		return (NULL);
	}
	sign = strcmp(nome,raiz->nome);
	if(sign== 0){
			return(raiz);
	}
	if(sign<0){
		return(search(raiz->pai, nome));
	}else{
		return(search(raiz->mae, nome));
	    }
}

int Insertion(struct arvore *raiz, char *filho, char *pai, char *mae, int k){ //função que insere os pais de um determinado individuo da árvore
	struct arvore *aux = NULL;
	struct arvore *p = (struct arvore *)malloc(sizeof(struct arvore));
	struct arvore *m = (struct arvore *)malloc(sizeof(struct arvore));
	aux = search(raiz,filho);
	p->pai = NULL;
    p->mae = NULL;
    m->pai = NULL;
    m->mae = NULL;
    strcpy(p->nome,pai);
    strcpy(m->nome,mae);
    aux->pai = p;
    aux->mae = m;
    p->grau = aux->grau + 1;
    m->grau = p->grau;
    if(p->grau>k){
    	k = p->grau;
	}
	return (k); //A função atualiza e retorna o valor referente ao maior grau da árvore 
}



int Parentesco(struct arvore *raiz, char *nome1, char *nome2){ //função que compara e retorna graus de parentesco
	int a = search(raiz,nome1)->grau;
	int b = search(raiz,nome2)->grau;
	if (a>=b){
		if (search(search(raiz,nome1),nome2)!=NULL){ //Teste para se saber se os individus possuem parentesco
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

void ImpGeracaoCocaCola(struct arvore *raiz,int n){//Função para impressão de uma determinada geração n
	if(raiz!=NULL){
		ImpGeracaoCocaCola(raiz->pai,n);
		if(raiz->grau == n){
			printf("%s ",raiz->nome);
		}
		ImpGeracaoCocaCola(raiz->mae,n);
	}
}


void ImpLabel(struct arvore *raiz){ //Função que imprime a árvore no modo LABELLED BRACKETING
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
	int menu,i,j,x,imp,a;
	int k = 1;
	char f[20],p[20],m[20];
	struct arvore *raiz = (struct arvore *)malloc(sizeof(struct arvore)); //Alocando memória dinâmica para a raiz da árvore
	raiz->pai = NULL;
    raiz->mae = NULL;
    raiz->grau = k;
	printf("Digite a primeira entrada para a arvore genealogica (formato filho_pai_mae):\n ");
	setbuf(stdin, NULL); //limpa o buffer do teclado
	scanf("%s",f);
	scanf("%s",p);
	scanf("%s",m);
	strcpy(raiz->nome,f);
	k = Insertion(raiz,f,p,m,k); //Atualizou o valor do k
	int exit = 0;
	while (exit ==0){
		printf("\nDigite:\n\n");
		printf("1 para inserir uma entrada na arvore genealogica\n\n"); 
		printf("2 para determinar grau de parentesco\n\n"); 
		printf("3 para imprimir\n\n");
		printf("4 para sair\n\n ");
    	scanf("%d",&menu);
        switch(menu){
	        case 1:
		        printf("Digite o numero de entradas a serem inseridas: ");
		        scanf("%d", &a);
		        for(i=1;i<=a;i++){
				    printf("Digite %d-a entrada (formato filho_pai_mae) a ser inserida: ",i);
				    scanf("%s",f);
	                scanf("%s",p);
	                scanf("%s",m);
				    k = Insertion(raiz,f,p,m,k);
		        }
		        break;
            case 2:
    	        printf("Digite os dois nomes para a comparacao (formato nome_nome): ");
    	        scanf("%s",f);
    	        scanf("%s",p);
    	        printf("O grau de parentesco eh de: %d\n",Parentesco(raiz,f,p));
    	        break;
            case 3:
            	printf("\nDigite: \n\n1 para imprimir a arvore por geracao\n\n"); 
				printf("2 para imprimir a arvore em LABELLED BRACKETING\n\n"); 
				printf("3 para imprimir antepassados de um individuo\n\n ");
            	scanf("%d",&imp);
            	if(imp==1){
            		for(i=1;i<=k;i++){ //Imprime até a última geração começando da raiz
            			ImpGeracaoCocaCola(raiz,i);
            			printf("\n");
					}
            	}
            	if(imp==2){
            		ImpLabel(raiz);
            	}
            	if(imp==3){
            		printf("Digite o nome cujos antepassados serao impressos: ");
            		scanf("%s",&m);
            		x = search(raiz,m)->grau; //Geração do individuo m
            		for(j=x;j<=k;j++){  //Imprime até a última geração começando da geração do individuo selecionado
            			ImpGeracaoCocaCola(raiz,j);
            			printf("\n");
					}
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
    free(raiz);
}


