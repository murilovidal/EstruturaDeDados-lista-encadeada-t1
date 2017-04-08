#include <stdio.h>
#include <stdlib.h> // malloc

typedef struct nodo
{ // criacao da estrutura/nodo
  float dado;
  int lin, col;
  struct nodo *prox;
}MatrizEsparsa;

// __fpurge(stdin); para limpar buffer do teclado
// setbuf(stdin, NULL); tbm limpa buffer

void InicializaMatriz(MatrizEsparsa **N){*N = NULL;} // inserindo NULL no ponteiro externo

MatrizEsparsa *Aloca()
{
  MatrizEsparsa *p;

  p = (MatrizEsparsa*)malloc(sizeof(MatrizEsparsa));

  if(!p){
    printf("Problema de alocacao\n");
    exit(0);}

  return p;
}

void InformaLinhaColuna(int *i, int *j)
{
  int x;

  printf("Ola! Informe a dimensao da matriz:\n");
  printf("Linha: ");
  scanf("%d", &x);
  *i = x;
  printf("\nColuna: ");
  scanf("%d", &x);
  *j = x;
}

void InsereNaLista(float y, int i, int j, MatrizEsparsa **ppe) // ppe = ponteiro para externo, isto é, aponta para ponteiro externo situado na main
{
  MatrizEsparsa *novo;
  novo = Aloca();

  // Alocacao do dado na lista que representa uma matriz
  novo->dado = y;
  printf("novo->dado vale: %f\n", novo->dado);
  // Alocacao dos indices
  novo->lin = i;
  novo->col = j;
  // Alocando endereco para ponteiro prox
  novo->prox = *ppe;
  // Atualizando endereco do ponteiro externo que esta lá na main
  *ppe = novo;
}

/*void ImprimeMatriz(MatrizEsparsa *ppe, int linha, int coluna)
{
  int i, j;
  MatrizEsparsa *aux = ppe;

  for(i=0; i<linha; i++){
    printf("\n");
    for(j=0; j<coluna; j++)
      if( ((aux->lin) == i) && ((aux->col) == j) ){
        printf("&d" ,aux->dado);
        aux = aux->prox;}
  }
}*/

void main()
{
  MatrizEsparsa *pem; // pem = ponteiro externo para matriz
  InicializaMatriz(&pem);

  int linha, coluna, i, j;
  float x;
  InformaLinhaColuna(&linha, &coluna);

  // iniciando preenchimento da matriz:

  for(i=0; i<linha; i++)
    for(j=0; j<linha; j++){
      scanf("%f", &x);
      if(x != 0){
        InsereNaLista(x, i, j, &pem);
        printf("dado: %f\n", pem->dado);
        printf("linha dado: %d\n", pem->lin);
        printf("coluna dado: %d\n", pem->col);}
    }

  //ImprimeMatriz(&pem, linha, coluna);

  printf("pem->col: %d\n", pem->col);
  printf("pem->lin: %d\n", pem->lin);
  printf("pem->dado:%f\n", pem->dado);

  // parei aqui, problemas pra mostrar conteudo da lista/matriz

  for(i=(linha-1); i>=0; i--){
    printf("entrou no primeiro for\n");
    for(j=(coluna-1); j>=0; j--){
      printf("entrou no segundo for\n");
      if( ((pem->lin) == i) && ((pem->col) == j) ){
        printf("entrou no if\n");
        printf("%f", pem->dado);
        pem = pem->prox;}
      else
        printf("0");
    }
  }


}
