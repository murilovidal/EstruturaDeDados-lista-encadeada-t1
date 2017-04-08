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
  // Alocacao dos indices
  novo->lin = i;
  novo->col = j;
  // Alocando endereco para ponteiro prox
  novo->prox = *ppe;
  // Atualizando endereco do ponteiro externo que esta lá na main
  *ppe = novo;
}

void ImprimeMatriz(MatrizEsparsa *ppe, int linha, int coluna)
{
  int i,j;
  MatrizEsparsa *aux = ppe; // aux precisa guardar o valor atual do pem, para que pem possa retornar ao seu valor original

  for(i=0; i<linha; i++){
    printf("\n");
    for(j=0; j<coluna; j++){
      ppe = aux;
      int z = 0; // caso algum valor seja encontrado na lista encadeada, z se tornará 1 e portanto não imprimiremos zero.
      while( ppe != NULL ){
        if( ((ppe->lin) == i) && ((ppe->col) == j) ){
          printf("%.2f ", ppe->dado);
          z = 1;
          break;}

        ppe = ppe->prox;}
      if(z == 0)
        printf("0.00 ");
    }
  }
}

void main()
{
  int linha, coluna, i, j;
  float x;
  char c;
  MatrizEsparsa *pem, *aux; // pem = ponteiro externo para matriz

  InicializaMatriz(&pem); // inicia matriz fazendo com que pem aponte para NULL
  InformaLinhaColuna(&linha, &coluna);

  // inicia preenchimento da matriz

  setbuf(stdin, NULL);
  printf("Existe algum elemento diferente de zero? (s/n)\n");
  scanf("%c", &c);

  while((c == 's') || (c == 'S'))
  {
    printf("Linha: ");
    scanf("%d", &i);
    printf("\nColuna: ");
    scanf("%d", &j);
    printf("\nDado: ");
    scanf("%f", &x);

    InsereNaLista(x, i, j, &pem);

    printf("Mais algum elemento diferente de zero? (s/n)");
    setbuf(stdin, NULL);
    scanf("%c", &c);
  }

  // fim do preenchimento da matriz

  ImprimeMatriz(pem, linha, coluna); // dessa vez não precisa passar o endereco de pem porque nao temos a intencao de alterar seu conteudo na main
}
