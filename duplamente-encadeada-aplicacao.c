#include <stdio.h>
#include <stdlib.h>

typedef struct Person {
    int cod, idade, sexo; } pessoa;

typedef struct node {
  pessoa p;
  struct node *ant, *prox;
} elemento;

typedef struct header {
  elemento *inicio, *fim;
  int total;
} cabecalho;

void InicializaCabecalho(cabecalho **c)
{
  (*c) = (cabecalho*)malloc(sizeof(cabecalho));
  (*c)->inicio = NULL;
  (*c)->fim = NULL;
  (*c)->total = 0;
}

void InsereNaLista(int cod, int id, int s, cabecalho *c)  // essa insercao eh feita no fim.
{
  elemento *novo = (elemento*)malloc(sizeof(elemento));
  novo->p.cod = cod;
  novo->p.idade = id;
  novo->p.sexo = s;
  novo->prox = NULL;

  if(c->inicio == NULL){
    c->inicio = novo;
    c->fim = novo;
    novo->ant = NULL;}
  else{
    novo->ant = c->fim;
    novo->ant->prox = novo;
    c->fim = novo;}

  c->total += 1;
}

void Preenche(cabecalho *c)
{
  int cod, id, s;
  printf("Digite o codigo da pessoa. Um numero negativo encerra o programa: ");
  scanf("%d", &cod);

  while(cod > 0){
    printf("Idade: "); scanf("%d", &id);
    printf("Sexo:  "); scanf("%d", &s);
    InsereNaLista(cod, id, s, c);
    printf("Digite o codigo da pessoa. Um numero negativo encerra o programa: ");scanf("%d", &cod);
  }
}

void ImprimeInicioAoFim(cabecalho *c)
{
  elemento *aux = c->inicio;

  while(aux != NULL){
    printf("Codigo: %d, idade: %d, sexo: %d\n", aux->p.cod, aux->p.idade, aux->p.sexo);
    aux = aux->prox;}
}

void ImprimeFimAoInicio(cabecalho *c)
{
  elemento *aux = c->fim;

  while(aux != NULL){
    printf("Codigo: %d, idade: %d, sexo: %d\n", aux->p.cod, aux->p.idade, aux->p.sexo);
    aux = aux->ant;}
}

elemento * Busca(int x, cabecalho *c)
{
  elemento *aux = c->inicio;

  while(aux != NULL){

    if(aux->p.cod == x)
      return(aux);
    else
      aux = aux->prox;
  }

  return(aux);
}

void Remove(cabecalho *c)
{
  int x;

  printf("\nCodigo da pessoa a ser removida: ");
  scanf("%d", &x);
  elemento *A, *P, *rm = Busca(x, c);

  if(rm != NULL){
    A = rm->ant;
    P = rm->prox;

    if(A == NULL){
      P->ant = NULL;
      c->inicio = P;
      free(rm);}
    else if(P == NULL){
      A->prox = NULL;
      c->fim = A;
      free(rm);}
    else{
      A->prox = P;
      P->ant = A;
      free(rm);}
  }
  else
    printf("Elemento nao encontrado\n");
}

void Add(int x, int cod, int id, int s, cabecalho *c)
{
  elemento *b = Busca(x,c);

  elemento *novo = (elemento*)malloc(sizeof(elemento));
  novo->p.cod = cod;
  novo->p.idade = id;
  novo->p.sexo = s;

  if(b->ant == NULL){ // insercao no incio
    novo->ant = NULL;
    novo->prox = c->inicio;
    c->inicio->ant = novo;
    c->inicio = novo;}
  else if(b->prox == NULL){ //insercao no fim
    novo->ant = c->fim;
    novo->ant->prox = novo;
    c->fim = novo;}
  else{
    novo->ant = b->ant;
    novo->prox = b;
    b->ant->prox = novo;
    b->ant = novo;}

  c->total += 1;
}

void InsereInicioMeioFim(cabecalho *c)
{
  ImprimeInicioAoFim(c);
  int n, cod, id, s;
  printf("Na frente de quem?: ");
  scanf("%d", &n);

  printf("Novos dados: \n");
  printf("Codigo: "); scanf("%d", &cod);
  printf("Idade: "); scanf("%d", &id);
  printf("Sexo: "); scanf("%d", &s);
  Add(n, cod, id, s, c);
}

void menu(int *opcao)
{
	printf("\n1. Preencher Lista\n");
	printf("2. Adicionar um elemento a lista preenchida e em qualquer posicao\n");
	printf("3. Imprimir lista do inicio ao fim\n");
	printf("4. Imprimir lista do fim ao inicio\n");
	printf("5. Remover qualquer elemento da lista\n");
	printf("6. Sair\n");
	printf("\nEscolha uma opção:\n");
  scanf ("%d", opcao);
}

void main()
{
  int opcao;
  cabecalho *c;
  InicializaCabecalho(&c);

  do{
    menu (&opcao);
    switch (opcao)
    {
      case 1: Preenche(c); break;
      case 2: InsereInicioMeioFim(c); break;
      case 3: ImprimeInicioAoFim(c); break;
      case 4: ImprimeFimAoInicio(c); break;
      case 5: Remove(c); break;
      case 6: exit(0); break;
    }
  } while ((opcao>0) && (opcao<7));
}
