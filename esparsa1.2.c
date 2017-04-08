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

  printf("Informe a dimensao da matriz:\n");
  printf("Linha: ");
  scanf("%d", &x);
  *i = x;
  printf("\nColuna: ");
  scanf("%d", &x);
  *j = x;
}

void InsereNaLista(float y, int i, int j, MatrizEsparsa ***ppe) // ppe = ponteiro para externo, isto é, aponta para ponteiro externo situado na main.
{
  /* Atenção para o que acontece aqui! O ponteiro ppe aponta para o pem, ponteiro situado lá na função main.
   * Mas antes disso ele passa por um outro ponteiro, P, dentro da funcao PreencheMatriz. É por isso que ele
   * recebe um asterisco a mais na declaração da função, e também mais abaixo, quando atualizamos o valor de pem
   * com relação ao ponteiro novo
   */

  MatrizEsparsa *novo;
  novo = Aloca();

  // Alocacao do dado na lista que representa uma matriz
  novo->dado = y;
  // Alocacao dos indices
  novo->lin = i;
  novo->col = j;
  // Alocando endereco para ponteiro prox
  novo->prox = **ppe; // note que acontece uma indireção a mais, tudo por conta da funcao PreencheMatriz
  // Atualizando endereco do ponteiro externo que esta lá na main
  **ppe = novo; // mais uma vez a indireção
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
  printf("\n");
}

void PreencheMatriz(MatrizEsparsa **P)
{
  int i, j;
  char c;
  float x;

  scanf("%c", &c); // scanf incluido aqui porque foi a unica coisa que funcionou contra o problema do buffer de teclado
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

    InsereNaLista(x, i, j, &P);

    printf("Mais algum elemento diferente de zero? (s/n)");
    setbuf(stdin, NULL);
    scanf("%c", &c);
  }
}

void main()
{
  int linha1, coluna1, linha2, coluna2, i, j;
  float x;
  char c;
  MatrizEsparsa *pem1, *pem2, *aux; // pem = ponteiro externo para matriz

  InicializaMatriz(&pem1); // inicia matriz fazendo com que pem1 aponte para NULL
  InicializaMatriz(&pem2); // analogo a declaracao anterior, mas agora com pem2

  InformaLinhaColuna(&linha1, &coluna1);
  PreencheMatriz(&pem1);

  InformaLinhaColuna(&linha2, &coluna2);
  PreencheMatriz(&pem2);

  ImprimeMatriz(pem1, linha1, coluna1); // dessa vez não precisa passar o endereco de pem porque nao temos a intencao de alterar seu conteudo na main
  ImprimeMatriz(pem2, linha2, coluna2);
}
