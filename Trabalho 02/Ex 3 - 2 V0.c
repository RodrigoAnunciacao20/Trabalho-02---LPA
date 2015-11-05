#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>

struct arvore
{
	char entrada[1];
	struct arvore *esquerda;
	struct arvore *direita;
};

void emordem(struct arvore*no)//Imprime Infixa
{	
	if(no!=NULL)
	{
		emordem(no->esquerda);
		if (no->entrada[0] >= 48 && no->entrada[0] <=57)
		printf("(");		
		printf("%s", no->entrada); 
		if (no->entrada[0] >= 48 && no->entrada[0] <=57)
		printf(")");
		emordem(no->direita);
	}
}


posordem(struct arvore *lista)//Imprime RPN
{
	if(lista != NULL)
	{
		posordem(lista->esquerda);
		posordem(lista->direita);
		printf("%s ", lista->entrada);
	}
}

void InserirSinal(struct arvore *no, char *k)//Insere os operadores da equação, à esquerda
{
	struct arvore *aux = no;
	struct arvore *novo = (struct arvore *)malloc(sizeof(struct arvore));
	novo->esquerda = NULL;
	novo->direita = NULL;
	strcpy(novo->entrada, k);
	while (aux->esquerda != NULL)
	{
		aux = aux->esquerda;
	}
	aux->esquerda = novo;
}
void InserirNro(struct arvore *no, char *k, int n, int i) 
{
	int count = 1;
	struct arvore *aux = no;
	struct arvore *a = NULL;
	struct arvore *novo = (struct arvore *)malloc(sizeof(struct arvore));
	novo->esquerda = NULL;
	novo->direita = NULL;
	strcpy(novo->entrada, k);
	if (n == 1)
	{
		while (aux->esquerda != NULL)
		{
			aux = aux->esquerda;
		}
		aux->esquerda = novo;
	}
	else if (n == 2)
	{
		while (count < i)
		{
			aux = aux->esquerda;
			count++;
		}
		aux->direita = novo;
	}
	else if (n > 2)
	{
		while (no->direita == NULL)
		{
			if (aux->esquerda->esquerda != NULL && aux->esquerda->direita != NULL && aux->direita == NULL)
			{
				aux->direita = novo;
				break;
			}
			else 
			aux = aux->esquerda;
			break;
		}
	}
}

int main()
{
	struct arvore *raiz = NULL;
	int i = 1, j = 1, k, menu;
	char a[1], b[1];
	printf("Digite sua equacao em notacao polonesa separando os numeros e sinais por espaco e entao tecle Enter:\n");
	raiz = (struct arvore *)malloc(sizeof(struct arvore)); //aloca memoria para a raiz criada
	raiz->esquerda = NULL;
	raiz->direita = NULL;
	scanf("%s", a);
	strcpy(raiz->entrada, a);
	scanf("%s", a);
	while(a[0] == 42 || a[0] == 43 || a[0] == 45 || a[0] == 47) 
	{
		InserirSinal(raiz, a);
		scanf("%s", a);
		i++;	
	} 
	InserirNro(raiz, a, j, i); 
	for (j = 2; j < i + 2; j++)
	{
		scanf("%s", a);
		InserirNro(raiz, a, j, i);
	}
	while (menu != 3) //repete o menu ate que seja escolhida a opcao "sair"
	{
		printf("Digite 1 para imprimir em RPN, 2 para imprimir em notacao infixa e 3 para sair\n");
		scanf("%d", &menu);
		if (menu > 3 || menu <1) 
		{
			printf("Escolher uma opção válida para o menu:\n");
		}
		else
		{
			switch(menu)
			{
				case 1:
					printf("\nRPN:\n");
					posordem(raiz);
					break;
				case 2:
					printf("Infixa:\n");	
					emordem(raiz);
					break;
			}
		}
	}
}
