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
  printf("Informe a dimensao da matriz:\n");
  printf("Linha: ");
  scanf("%d", i);
  printf("\nColuna: ");
  scanf("%d", j);
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

MatrizEsparsa * Busca (MatrizEsparsa *M, int i, int j)
{
    /* Essa funcao retorna o endereco do numero encontrado.
     * Caso não encontre, retorna NULL.
     */

    while(M != NULL)
    {
      if( ((M->lin) == i) && ((M->col) == j) )
          return M;

      M = M->prox;
    }

    return NULL;
}

void ImprimeMatriz(MatrizEsparsa *ppe, int linha, int coluna)
{
  int i,j;
  MatrizEsparsa *aux = ppe; // aux precisa guardar o valor atual do pem, para que pem possa retornar ao seu valor original

  for(i=0; i<linha; i++){
    printf("\n");
    for(j=0; j<coluna; j++){

      ppe = Busca(ppe, i, j);
      if(ppe != NULL)
        printf("%.2f ", ppe->dado);
      else
        printf("0.00 ");

      ppe = aux;
    }
  }
  printf("\n");
}

void Soma(MatrizEsparsa *p1, MatrizEsparsa *p2, int linha, int coluna, MatrizEsparsa **R)
{
  int i, j;
  float x;
  MatrizEsparsa *aux1, *aux2;

  aux1 = p1;
  aux2 = p2;

  for(i=0; i<linha; i++)
    for(j=0; j<coluna; j++)
    {
      p1 = Busca(p1, i, j);  // verificando se existe algum dado preenchido nessa linha e nessa coluna
      p2 = Busca(p2, i, j); //  essa verificação acontece tanto pra matriz1 quanto pra matriz2

      if((p1 != NULL) && (p2 != NULL))
      {
        x = (p1->dado) + (p2->dado);
        InsereNaLista(x, i, j, &R);
      }
      else if((p1 != NULL) && (p2 == NULL))
      {
        x = p1->dado;
        InsereNaLista(x, i, j, &R);
      }
      else if((p2 != NULL) && (p1 == NULL))
      {
        x = p2->dado;
        InsereNaLista(x, i, j, &R);
      }

      p1 = aux1;
      p2 = aux2;
    }
}

void Subtrai(MatrizEsparsa *p1, MatrizEsparsa *p2, int linha, int coluna, MatrizEsparsa **R)
{
  int i, j;
  float x;
  MatrizEsparsa *aux1, *aux2;

  aux1 = p1;
  aux2 = p2;

  for(i=0; i<linha; i++)
    for(j=0; j<coluna; j++)
    {
      p1 = Busca(p1, i, j);
      p2 = Busca(p2, i, j);

      if((p1 != NULL) && (p2 != NULL))
      {
        x = (p1->dado) - (p2->dado);
        InsereNaLista(x, i, j, &R);
      }
      else if((p1 != NULL) && (p2 == NULL))
      {
        x = p1->dado;
        InsereNaLista(x, i, j, &R);
      }
      else if((p2 != NULL) && (p1 == NULL))
      {
        x = (0 - (p2->dado));
        InsereNaLista(x, i, j, &R);
      }

      p1 = aux1;
      p2 = aux2;
    }
}

void Multiplica(MatrizEsparsa *p1, MatrizEsparsa *p2, int linha1, int coluna1, int linha2, int coluna2, MatrizEsparsa **R)
{
  int i, j, k;
  float x=0;
  MatrizEsparsa *aux1, *aux2;

  aux1 = p1;
  aux2 = p2;

  if (coluna1 != linha2)
  {
    printf("Essas matrizes não podem ser multiplicadas!\n");
  }
  else
  {
    for(i=0; i<linha1; i++)//coluna1 == linha2
      for(j=0; j<coluna2; j++)
      {
        for(k=0; k<linha1; k++)
        {
          p1 = Busca(p1, i, k);  // verificando se existe algum dado preenchido nessa linha e nessa coluna
          p2 = Busca(p2, k, j); //  essa verificação acontece tanto pra matriz1 quanto pra matriz2
          if((p1 != NULL) && (p2 != NULL))
          {
            x = x + (p1->dado)*(p2->dado);
          }
          p1 = aux1;
          p2 = aux2;
        }
        InsereNaLista(x, i, j, &R);
        p1 = aux1;
        p2 = aux2;
        x=0;
      }
    }
}


void Transposta(MatrizEsparsa *p1, int linha, int coluna, MatrizEsparsa **R)
{
  int i, j;
  float x;
  MatrizEsparsa *aux1;

  aux1 = p1;

  for(i=0; i<linha; i++)
    for(j=0; j<coluna; j++)
    {
      p1 = Busca(p1, i, j);
      if((p1 != NULL))
      {
        x = p1->dado;
        InsereNaLista(x, j, i, &R);
      }
      p1 = aux1;
    }
}

void ImprimeDiagonal(MatrizEsparsa *ppe, int linha, int coluna)
{
  int i,j;
  MatrizEsparsa *aux = ppe; // aux precisa guardar o valor atual do pem, para que pem possa retornar ao seu valor original
  printf("Valores da diagonal principal\n");
  for(i=0; i<linha; i++)
  {
      ppe = Busca(ppe, i, i);
      if(ppe != NULL)
        printf("%.2f ", ppe->dado);
      else
        printf("0.00 ");

      ppe = aux;

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

void Libera (MatrizEsparsa **P)
{
  MatrizEsparsa *fim, *apagar;

  fim = *P;

  while(fim != NULL){
    apagar = fim;
    fim = fim->prox;
    free(apagar);}

  *P = NULL;
}

void main()
{
  int linha1, coluna1, linha2, coluna2, i, j;
  float x;
  char c;
  MatrizEsparsa *pem1, *pem2, *res; // pem = ponteiro externo para matriz

  InicializaMatriz(&pem1);  // inicia matriz fazendo com que pem1 aponte para NULL
  InicializaMatriz(&pem2); //  analogo a declaracao anterior, mas agora com pem2
  InicializaMatriz(&res); //   inicializando ponteiro para lista de resultados com NULL

  InformaLinhaColuna(&linha1, &coluna1);
  PreencheMatriz(&pem1);

  InformaLinhaColuna(&linha2, &coluna2);
  PreencheMatriz(&pem2);

  printf("\nConteudo de M1:\n");
  ImprimeMatriz(pem1, linha1, coluna1); // dessa vez não precisa passar o endereco de pem porque nao temos a intencao de alterar seu conteudo na main
  printf("\nConteudo de M2:\n");
  ImprimeMatriz(pem2, linha2, coluna2);

  //Menu

  int continuar=1;
  int esc;
      do
      {
          printf("\n\tSelecione uma opcao\n\n");
          printf("1. Somar\n");
          printf("2. Subtrair\n");
          printf("3. Multiplicar\n");
          printf("4. Exibir a transposta\n");
          printf("5. Exibir a diagonal principal\n");
          printf("6. Exibir as matrizes novamente\n");

          printf("0. Sair\n");

          scanf("%d", &continuar);
          system("clear");

          switch(continuar)
          {
              case 1:
                  printf("\nM1 + M2\n");
                  if((linha1 == linha2) && (coluna1 == coluna2))
                  {
                    Soma(pem1, pem2, linha1, coluna1, &res);
                    ImprimeMatriz(res, linha2, coluna2);
                    Libera(&res);
                  }
                  else
                    printf("Nao e possivel somar essas matrizes!\n");
                  break;

              case 2:
                  printf("\nM1 - M2\n");
                  if((linha1 == linha2) && (coluna1 == coluna2))
                  {
                    Subtrai(pem1, pem2, linha1, coluna1, &res);
                    ImprimeMatriz(res, linha2, coluna2);
                    Libera(&res);
                  }
                  else
                    printf("Nao e possivel subtrair essas matrizes!\n");
                  break;

              case 3:
                  if (coluna1 != linha2)
                  {
                    printf("Nao e possivel multiplicar essas matrizes!\n");
                  }
                  else{
                    printf("\nM1 * M2\n");
                    Multiplica(pem1, pem2, linha1, coluna1, linha2, coluna2, &res);
                    ImprimeMatriz(res, linha1, coluna2);
                    Libera(&res);
                  }
                  break;

              case 4:
                  printf("Escolha a matriz:(1 ou 2)\n");
                  setbuf(stdin, NULL);
                  scanf("%d",&esc);
                  if (esc ==2) {
                    Transposta(pem2, linha2, coluna2, &res);
                    ImprimeMatriz(res, coluna2, linha2);
                    Libera(&res);
                  }
                  else{
                    Transposta(pem1, linha1, coluna1, &res);
                    ImprimeMatriz(res, coluna1, linha1);
                    Libera(&res);
                  }
                  break;

              case 5:
                  printf("Escolha a matriz:(1 ou 2)\n");
                  setbuf(stdin, NULL);
                  scanf("%d",&esc);
                  if (esc ==2) {
                    ImprimeDiagonal(pem2, linha2, coluna2);
                  }
                  else
                    ImprimeDiagonal(pem1, linha1, coluna1);
                  break;

              case 6:
                    printf("\nConteudo de M1:\n");
                    ImprimeMatriz(pem1, linha1, coluna1);
                    printf("\nConteudo de M2:\n");
                    ImprimeMatriz(pem2, linha2, coluna2);
                  break;

              case 0:
                  break;

              default:
                  printf("Digite uma opcao valida\n");
          }
      } while(continuar);

}
