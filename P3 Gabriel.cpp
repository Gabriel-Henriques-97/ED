#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>



struct Fila {
	struct CelulaFila *primeiro;
	struct CelulaFila *ultimo;
};
//typedef struct Fila myfila;

struct Celula {
	char tipopersona;
	struct Celula *esq;
	struct Celula *dir;
};

struct Pilha {
	struct Celula *topo;
};

typedef struct Pilha duracell;

struct Pessoa {
	int inscricao;
	char nome[30];
	char sexo;
	char telefone[15];
	duracell personalidade;
	struct Fila pretendente;
	struct Pessoa *relacao = NULL;
	struct Pessoa *proximo;
};
typedef struct Pessoa listapessoas;

struct CelulaFila {
	listapessoas * pessoa;
	struct CelulaFila *proximo;
};





// Início funções pilha
void Pinit(struct Pilha *pilha) {
	pilha->topo = NULL;
}

int PisEmpty(struct Pilha *pilha) {
	return (pilha->topo == NULL)?1:0;
}

struct Celula * CriarCelula(char tipopersona) {
	struct Celula *novaCelula = (struct Celula *)malloc(sizeof(struct Celula));
	novaCelula->tipopersona = tipopersona;
	novaCelula->esq = NULL;
	novaCelula->dir = NULL;
	return novaCelula;
}

void PUSH(struct Pilha *pilha, char tipopersona) {
	struct Celula *celula = CriarCelula(tipopersona);
	if (!PisEmpty(pilha)) {
	celula->esq = pilha->topo;
	pilha->topo->dir = celula;   
	}
	pilha->topo = celula;
}

int POP(struct Pilha *pilha, char *tipopersona) {
	struct Celula *celula;
	if (PisEmpty(pilha)) {
		return 0;
	}
	
	celula = pilha->topo;
	*tipopersona = celula->tipopersona;
	pilha->topo = celula->esq;
	if (!PisEmpty(pilha)) {
		pilha->topo->dir = NULL;
	}
	free(celula);
	return 1;
}

void PRINTPILHA(duracell *pilha) {
	struct Celula *celula = pilha->topo;
	if (PisEmpty(pilha)) {
		printf("Pilha Vazia!");
	}else{
		do{
			printf("[%c]", celula->tipopersona);
			celula = celula->esq;
		}while(celula != NULL);
	}
}
/*
int TOP(struct Pilha *pilha, char *tipopersona) {
	if (!PisEmpty(pilha)) {
		*tipopersona = pilha->topo->tipopersona;
		return 0;
	}
	return 0;
}
*/
char TOP(struct Pilha *pilha) {
	if (PisEmpty(pilha)) {
		printf("Pilha Vazia");
	}else{
		return pilha->topo->tipopersona;
	}
}
//Fim funções pilha





// Início das funções da Fila
void Qinit(struct Fila *fila) {
	fila->primeiro = NULL;
}


int QisEmpty(struct Fila *fila) {
	return (fila->primeiro == NULL)?1:0;
}

struct CelulaFila * CriarCelula(listapessoas *pessoa) {
	struct CelulaFila *novaCelula = (struct CelulaFila *)malloc(sizeof(struct CelulaFila));
	novaCelula->pessoa = pessoa;
	novaCelula->proximo = NULL;
	return novaCelula;
}

void ENQUEUE(struct Fila *fila, listapessoas* pessoa) {
	struct CelulaFila * celula = CriarCelula(pessoa);
	if (QisEmpty(fila)) {
		fila->primeiro = celula;
	}
	else {
		fila->ultimo->proximo = celula;
	}
	fila->ultimo = celula;
}

int DEQUEUE(struct Fila *fila, listapessoas *pessoa) {
	struct CelulaFila *celula;
	if (QisEmpty(fila)) {
		return 0;
	}
	celula = fila->primeiro;
	fila->primeiro = celula->proximo;
	pessoa = celula->pessoa;
	free(celula);
	return 1;
}


void PRINTFILA(struct Fila *fila){
	if (QisEmpty(fila)) {
		printf(" Sem fila de pretendentes.\n");
	}else{
		printf("Fila:");
		for(struct Fila *ptr = fila; ptr->primeiro != NULL; ptr->primeiro = ptr->primeiro->proximo){
			printf(" [%d]", ptr->primeiro->pessoa->inscricao);
			printf("\n");
		}
	}	
}

void imprimeFila(struct Fila *fila){
	struct Fila *ptr = fila;
	printf("Fila: ");
	while(ptr->primeiro->proximo != NULL){
		printf(" %d ", ptr->primeiro->pessoa->inscricao);
		ptr->primeiro = ptr->primeiro->proximo;
		
	}
}

//Final funções fila



// Início funções lista
listapessoas* inicializa(){
	return NULL;
}

listapessoas* insereInicio(listapessoas* listaPTR, int inscricao, char nome[30], char sexo, char telefone[15], duracell P){
	listapessoas* novoNoh = (listapessoas* ) malloc(sizeof(listapessoas));
	novoNoh->inscricao = inscricao;
	strcpy(novoNoh->nome, nome);
	novoNoh->sexo = sexo;
	strcpy(novoNoh->telefone, telefone);
	novoNoh->personalidade = P;
	novoNoh->proximo = listaPTR;
	return novoNoh;
}

void imprimeLista(listapessoas* listaPTR){
	for(listapessoas* ptr = listaPTR; ptr != NULL; ptr = ptr->proximo){
		printf("\nNúmero de inscrição: %d\n", ptr->inscricao);
		printf("Nome: %s\n", ptr->nome);
		printf("Sexo: %c\n", ptr->sexo);
		printf("Telefone: %s\n", ptr->telefone);
		printf("Personalidade mais acentuada: \n");
		printf("[%c]",TOP(&ptr->personalidade));
		printf("Pretendentes: \n");
		//PRINTFILA(&ptr->pretendente);
	}
}

void imprimePretendentes(listapessoas* listaPTR,char sexo, char persona){
	char n;
	for(listapessoas* ptr = listaPTR; ptr != NULL; ptr = ptr->proximo){
		duracell p = ptr->personalidade;
		if(ptr->relacao==NULL && ptr->sexo == sexo && TOP(&p)==persona){
			printf("\nNúmero de inscrição: %d\n", ptr->inscricao);
			printf("Nome: %s\n", ptr->nome);
			printf("Sexo: %c\n", ptr->sexo);
			printf("Telefone: %s\n", ptr->telefone);
			printf("Personalidade mais acentuada: \n");
			printf("[%c]",TOP(&p));
			printf("Pretendentes: \n");
			//PRINTFILA(&ptr->pretendente);
			printf("\n");
			
		}else{
			//printf("Pessoas não encontradas!");
			break;
		}
	}
}
// Fim funções lista



int main () {
	setlocale(LC_ALL,"");
	int i, opc, inscricao, inscricao2, aux=1;
	char nome[30], sexo, telefone[15], personalidade, n, tp;
	duracell P;
	struct Fila F;
	listapessoas p;

	listapessoas* listaPTR;
	listaPTR = inicializa();

	while (opc != 4) {
		printf("*****************************");
		printf("\nPrograma de Relacionamentos\n");
		printf("*****************************\n\n");
		printf("Escolha uma opção: \n");
	    printf("1 - Cadastrar pessoa\n");
	    printf("2 - Registrar Pretendente\n");
	    printf("3 - Relacionar pessoas\n");
	    printf("4 - Listar casais\n");
		printf("5 - Sair\n");
		scanf ("%d", &opc);
		// system("cls");
		
		switch (opc) {
			case 1:
				printf("*****************************");
				printf("\nPrograma de Relacionamentos\n");
				printf("*****************************\n\n");
				printf("\n");
				
				printf("*****************************");
				printf("\nPreencha as Informações:\n");
				printf("*****************************\n\n");

				printf("Insira o número de inscrição: ");
				scanf (" %d", &inscricao);
				printf("\n");

				printf("Insira o nome: ");
				scanf (" %s", nome);
				printf("\n");

				printf("Insira o sexo: ");
				scanf (" %c", &sexo);
				printf("\n");

				printf ("Insira o telefone: ");
				scanf (" %s", telefone);
				
				printf("\n");

				Pinit(&P);

				printf("Agora seus tipos de personalidade. \nLembre-se que elas devem ser inseridas\nda menos predominante para a mais predominante: \n");
				for(i=0;i<4;i++){
					printf("Insira a %dº personalidade: ", i+1);
					scanf (" %c", &tp);
					PUSH(&P,tp);
				}
				
				//Mostrando o cadastro
				printf("\nNúmero de inscrição: %d\n", inscricao);
				printf("Nome: %s\n", nome);
				printf("Sexo: %c\n", sexo);
				printf("Telefone: %s\n", telefone);
				printf("Tipos de personalidade: \n");
				PRINTPILHA(&P);
				printf("\n");
				printf("\nPersonalide mais acentuada: \n");
				printf("[%c]",TOP(&P));

				listaPTR = insereInicio(listaPTR, inscricao, nome, sexo, telefone, P);
				printf("\n");
				
				break;

				
				
			


			

			case 2:
				printf("*****************************");
				printf("\nPrograma de Relacionamentos\n");
				printf("*****************************\n\n");
				
				printf("Insira o sexo do pretendente: ");
				scanf (" %c", &sexo);
				printf("\n");
				
				printf("Insira a personalidade do pretendente: ");
				scanf (" %c", &tp);
					
				imprimePretendentes(listaPTR,sexo,tp);
				
				printf("\n");
				//criando a fila
				Qinit(&F);
				
				while (aux) {
					printf("Digite o número de inscrição da pessoa para entrar na fila de pretendentes\n");
					scanf (" %d", &inscricao);
					for(listapessoas* ptr = listaPTR; ptr != NULL; ptr = ptr->proximo){
						if(ptr->inscricao == inscricao){
							ENQUEUE(&F,ptr);
						}
					}
					//imprimeFila(&F);
					printf("Deseja cadastrar mais um pretendente? Sim(1) ou não(0)?\n");
					scanf (" %d", &aux);
				}
				//inserindo a fila numa pessoa
				printf("Insira o número de inscrição da pessoa\nque receberá a fila de pretendentes: ");
				scanf (" %d", &inscricao);
				for(listapessoas* ptr = listaPTR; ptr != NULL; ptr = ptr->proximo){
						if(ptr->inscricao == inscricao){
							ptr->pretendente = F;
						}
					}
				printf("\n");
				
				printf("\n");
				/*
				Qinit(&F);
				ENQUEUE(&F,1);
				
				
				while (DEQUEUE(&F,&p)) {
					printf("%d\n",p);
				}
				*/
				break;



			case 3:
				
				//system("cls");
				printf("*****************************");
				printf("\nPrograma de Relacionamentos\n");
				printf("*****************************\n\n");
				printf("Relacionar Pessoas: \n");
				
				listapessoas* ex;
				
				printf("Digite o número de inscrição da pessoa para ver sua lista de Pretendentes: \n");
				scanf (" %d", &inscricao);
				for(listapessoas* ptr = listaPTR; ptr != NULL; ptr = ptr->proximo){
					if(ptr->inscricao == inscricao){
						PRINTFILA(&ptr->pretendente);
						printf("Digite o número de inscrição da pessoa na qual deseja-se relacionar: \n");
						scanf (" %d", &inscricao2);
						for(listapessoas* ptr2 = listaPTR; ptr2 != NULL; ptr2 = ptr2->proximo){
							if(ptr2->inscricao == inscricao2){
								ptr->relacao = ptr2;
								ptr2->relacao = ptr;
								printf("\nA Pessoa que foi relacionada com a primeira pessoa: ");
								printf("%s\n",ptr->relacao->nome);
								printf("\nA pessoa que se relacionou com a segunda pessoa: ");
								printf("%s\n",ptr2->relacao->nome);
								while (DEQUEUE(&ptr->pretendente,ex)) {
									printf("%d\n",ex);
								}
							}
						}
					}
				}
				
					
			break;
			
			
			case 4:
				printf("Casais:");
				for(listapessoas* ptr = listaPTR; ptr != NULL; ptr = ptr->proximo){
					if(ptr->relacao != NULL){
						
						printf("Nome: %d\n",ptr->inscricao);
						printf("Inscrição: %s\n",ptr->nome);
						printf("Nome: %d\n",ptr->relacao->inscricao);
						printf("Inscrição: %s\n",ptr->relacao->nome);
					}
				}
			
			break;
			
			
			case 5:
				printf("O programa será encerrado. ");
			break;
			
			default:
				printf("Opção inválida! \n");
		}
	}
}
