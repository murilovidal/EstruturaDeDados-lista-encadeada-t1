#include <stdio.h>
#include <stdlib.h> //malloc, srand
#include <time.h> // necessaria para fucao time
#include <string.h>

typedef struct airplane {
  char voo[2], origem[3], destino[3], comp[3];
  int id;
} aeronave;

typedef struct takeoff {
  aeronave aviao;
  struct takeoff *ant, *prox;
} decolagem;

typedef struct landing {
  aeronave aviao;
  struct landing *ant, *prox;
} pouso;

typedef struct takeoffHeader {
  int total;
  decolagem *ini, *fim;
} cabDecolagem;

typedef struct landingHeader {
  int total;
  pouso *ini, *fim;
} cabPouso;

void Inicializa(cabDecolagem **d, cabPouso **p)
{
  (*d) = (cabDecolagem*)malloc(sizeof(cabDecolagem));
  (*d)->ini = NULL;
  (*d)->fim = NULL;
  (*d)->total = 0;

  (*p) = (cabPouso*)malloc(sizeof(cabPouso));
  (*p)->ini = NULL;
  (*p)->fim = NULL;
  (*p)->total = 0;
}

int Aleatorio()
{
  srand(time(NULL)); // cria um seed para ser usado pela funcao rand

  /* a funcao rand retorna um numero aleatorio, porem esse numero precisa ser
   * baseado, nesse caso, no tempo (que nunca é igual porque sempre avanca),
   * atráves da funcao time, afim de tornar o numero realmente aleatorio e
   * evitar possiveis repetições problemáticas
   */

   int x = 1 + ( rand() % 10 );

   /* somando 1 evita-se a ocorrencia de um numero igual a zero. Lembrando que aqui
    * o numero gerado é de 1 a 10 (porque o mod eh 60)
    */

    return x;
}

void InsereNaLista(char *voo, char *origem, char *destino, char *comp, int id, cabDecolagem *d, cabPouso *p, int aux)
{
  if(aux == 1){
    cabDecolagem *c = d;
    decolagem *novo = (decolagem*)malloc(sizeof(decolagem));

    strcpy(novo->aviao.voo, voo);
    strcpy(novo->aviao.origem, origem);
    strcpy(novo->aviao.destino, destino);
    strcpy(novo->aviao.comp, comp);
    novo->aviao.id = id;
    novo->prox = NULL;

    if(c->ini == NULL){
      c->ini = novo;
      c->fim = novo;
      novo->ant = NULL;}
    else{
      novo->ant = c->fim;
      novo->ant->prox = novo;
      c->fim = novo;}

    c->total += 1;}
  else{
    cabPouso *c = p;
    pouso *novo = (pouso*)malloc(sizeof(pouso));

    strcpy(novo->aviao.voo, voo);
    strcpy(novo->aviao.origem, origem);
    strcpy(novo->aviao.destino, destino);
    strcpy(novo->aviao.comp, comp);
    novo->aviao.id = id;
    novo->prox = NULL;

    if(c->ini == NULL){
      c->ini = novo;
      c->fim = novo;
      novo->ant = NULL;}
    else{
      novo->ant = c->fim;
      novo->ant->prox = novo;
      c->fim = novo;}

    c->total += 1;}
}

void PrePreenche(cabDecolagem *cd, cabPouso *cp)
{
 char voo[2], ori[3], des[3], com[3];
 int id, num = Aleatorio();
 id = (Aleatorio()) + 2357;

 printf("num: %d\n", num);

 while(num > 0) { // Preenchendo fila de decolagem
   strcpy(voo, "JJ"); strcpy(ori, "CWB"); strcpy(des, "GRU"); strcpy(com, "TAM");
   printf("id: %d\n", id);
   printf("voo: %s, ori: %s, des: %s, com: %s\n", voo, ori, des, com);
   InsereNaLista(voo, ori, des, com, id, cd, cp, 1);
   num--;
   id++;
 }

 num = Aleatorio() + 1;
 printf("num: %d\n", num);
 id = (Aleatorio()) + 3261;

 while(num > 0) { // Preenchendo fila de pouso
   strcpy(voo, "PR");
   strcpy(ori, "ASZ");
   strcpy(des, "APO");
   strcpy(com, "AZU");
   printf("voo: %s, ori: %s, des: %s, com: %s\n", voo, ori, des, com);
   InsereNaLista(voo, ori, des, com, id, cd, cp, 0);
   num--;
   id++;
 }
}

void menu(int *opcao)
{
	printf("\n1. Listar numero de avioes esperando para decolar\n");
	printf("2. Listar numero de avioes esperando para pousar\n");
	printf("3. Autorizar decolagem\n");
	printf("4. Autorizar pouso\n");
	printf("5. Adicionar aviao a fila de decolagem\n");
	printf("6. Adicionar aviao a fila de pouso\n");
  printf("7. Imprimir fila de decolagem\n");
  printf("8. Imprimir fila de pouso\n");
  printf("9. Sair\n");
	printf("\nEscolha uma opção:\n");
  scanf ("%d", opcao);
}

void Listar(cabDecolagem *d, cabPouso *p, int x)
{
  if(x == 1){
    decolagem *aux = d->ini;
    printf("\n===FILA PARA DECOLAGEM===\n\n");
    while(aux != NULL){
      printf("Voo: %s, numero: %d, origem: %s, destino: %s, companhia: %s\n", aux->aviao.voo, aux->aviao.id, aux->aviao.origem, aux->aviao.destino, aux->aviao.comp);
      aux = aux->prox;}
  }
  else{
    pouso *aux = p->ini;
    printf("\n===FILA PARA POUSO===\n\n");
    while(aux != NULL){
      printf("Voo: %s, numero: %d, origem: %s, destino: %s, companhia: %s\n", aux->aviao.voo, aux->aviao.id, aux->aviao.origem, aux->aviao.destino, aux->aviao.comp);
      aux = aux->prox;}}
}

void ListaNumero(cabDecolagem *c, cabPouso *p, int aux)
{
  aux == 1 ? printf("\n===Existem %d voos na fila para decolagem===\n", c->total) : printf("\n===Existem %d voos na fila para pouso\n", p->total);
}

void Autorizar(cabDecolagem *d, cabPouso *p, int x) // Essa funcao exibe caracteristicas de um aviao antes de remove-lo da fila
{
  char opcao;

  if(x == 1){
    if(d->total != 0){
        decolagem *aux = d->ini;
        printf("Voo: %s, numero: %d, origem: %s, destino: %s, companhia: %s\n", aux->aviao.voo, aux->aviao.id, aux->aviao.origem, aux->aviao.destino, aux->aviao.comp);
        printf("Autorizar decolagem? (S/N)\n");

        scanf(" %c", &opcao); // um espaco em " %c" parece que resolve problema de buffer
        if((opcao == 's') || (opcao == 'S')){
          d->ini = d->ini->prox;
          free(aux);
          (d->total)--;
          printf("\n===Decolagem Autorizada===\n");}
    }
    else
        printf("\n===Fila para decolagem esta vazia===\n");
  } else {
    if(p->total != 0){
        pouso *aux = p->ini;
        printf("Voo: %s, numero: %d, origem: %s, destino: %s, companhia: %s\n", aux->aviao.voo, aux->aviao.id, aux->aviao.origem, aux->aviao.destino, aux->aviao.comp);
        printf("Autorizar pouso? (S/N)\n");
        scanf(" %c", &opcao);
        if((opcao == 's') || (opcao == 'S')){
          p->ini = p->ini->prox;
          free(aux);
          (p->total)--;
          printf("\n===Pouso Autorizado===\n");}
    }
    else
      printf("\n===Fila para pouso esta vazia===\n");
  }
}

void AddAviao(cabDecolagem *d, cabPouso *p, int x)
{
  char voo[2], ori[3], des[3], com[3], opcao, b;
  int id;

  printf("Numero: \n"); scanf("%d", &id);
  printf("Nome: "); scanf("%s", voo);
  printf("Origem: "); scanf("%s", ori);
  printf("Destino: "); scanf("%s", des);
  printf("Companhia: "); scanf("%s", com);
  printf("\nVoo: %s, numero: %d, origem: %s, destino: %s, companhia: %s\n", voo, id, ori, des, com);

  if(x == 1){
    printf("Deseja incluir na fila de decolagem? (S/N)\n");
    scanf(" %c", &opcao);
    if((opcao == 's') || (opcao == 'S'))
      InsereNaLista(voo, ori, des, com, id, d, p, 1);
  } else {
    printf("Deseja incluir na fila de pouso? (S/N)\n");
    scanf(" %c", &opcao);
    if((opcao == 's') || (opcao == 'S'))
      InsereNaLista(voo, ori, des, com, id, d, p, 0);
  }
}

void main()
{
  int opcao;
  cabDecolagem *cabd;
  cabPouso *cabp;
  Inicializa(&cabd, &cabp);
  PrePreenche(cabd, cabp); // essa funcao preenche a lista com alguns valores, apenas para inicia-la ja com algum conteudo.

  do
  {
    menu(&opcao);
    switch(opcao)
    {
      case 1: ListaNumero(cabd, cabp ,1); break;
      case 2: ListaNumero(cabd, cabp, 0); break;
      case 3: Autorizar(cabd, cabp, 1); break;
      case 4: Autorizar(cabd, cabp, 0); break;
      case 5: AddAviao(cabd, cabp, 1); break;
      case 6: AddAviao(cabd, cabp, 0); break;
      case 7: Listar(cabd, cabp, 1); break;
      case 8: Listar(cabd, cabp, 0); break;
      case 9: exit(0);
      default: printf("\nOpcao invalida! Programa encerrado.\n");
    }
  } while((opcao > 0) && (opcao < 10));

}
