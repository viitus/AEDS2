#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIL    1000
#define DEZMIL 10000
#define CEMMIL 100000
#define DUZMIL 200000

typedef struct aluno {
  int matricula;
  char nome[50];
  char curso[50];
  double coeRend;
  int periodo;
} Aluno;
//--------------------------------------------------função de string aleatoria para os nomes e cursos dos alunos
void gerarStringAleatoria(char *s, int tamanho) {
  for (int i = 0; i < tamanho - 1; i++) {
    s[i] = (char)(rand() % 26 + 'A');
  }
  s[tamanho - 1] = '\0';
}
//-------------------------------------------------função de aluno aleatorio,
// popula o vetor com nome, matricula, coefiente de rendimento periodo, curso 
Aluno *gerarAlunosAleatorios(int n) {
  Aluno *alunos = (Aluno *)malloc(n * sizeof(Aluno));
  for (int i = 0; i < n; i++) {
    alunos[i].matricula = rand() % 1000000 + 1;
    alunos[i].coeRend = ((double)rand() / RAND_MAX) * 10;
    alunos[i].periodo = rand() % 10 + 1;
    gerarStringAleatoria(alunos[i].nome, 50);
    gerarStringAleatoria(alunos[i].curso, 50);
  }
  return alunos;
}
//-------------------------------------------------função de aluno em ordem crescente
// a chave de ordenação que é o numero de matricula é o unico que nao é aleatorizado
Aluno *gerarAlunosCrescente(int n) {
  Aluno *alunos = (Aluno *)malloc(n * sizeof(Aluno));
  for (int i = 0; i < n; i++) {
    alunos[i].matricula = i;
    alunos[i].coeRend = ((double)rand() / RAND_MAX) * 10;
    alunos[i].periodo = rand() % 10 + 1;
    gerarStringAleatoria(alunos[i].nome, 50);
    gerarStringAleatoria(alunos[i].curso, 50);
  }
  return alunos;
}
//-------------------------------------------------função de aluno em ordem decrescente
//o numero de matricula é escrito de forma decrescente
Aluno *gerarAlunosDecrescente(int n) {
  Aluno *alunos = (Aluno *)malloc(n * sizeof(Aluno));
  for (int i = 0; i < n; i++) {
    alunos[i].matricula = n - i - 1;
    alunos[i].coeRend = ((double)rand() / RAND_MAX) * 10;
    alunos[i].periodo = rand() % 10 + 1;
    gerarStringAleatoria(alunos[i].nome, 50);
    gerarStringAleatoria(alunos[i].curso, 50);
  }
  return alunos;
}
//-------------------------------------------------função de TROCA DE LUGAR
//é usada em varias funções de ordenação
void troca(Aluno v[], int i, int j) {
  Aluno aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}
//---------------------------------------------------FUNÇÕES DO QUICKSORT
//para evitar casos ruins do quicksort é usado a mediana de 3
//a função escolhe a mediana entre 3 numeros do vetor que sera usada na função particionar
int medianadetres(Aluno vet[], int inicio, int fim) {
  int meio = (inicio + fim) / 2;
  int a = vet[inicio].matricula;
  int b = vet[meio].matricula;
  int c = vet[fim].matricula;
  if (a < b) {
    if (b < c) {
      return meio;      // a < b && b < c
    } else {
      if (a < c) {
        return fim;     // a < c && c <= b
      } else {
        return inicio;  // c <= a && a < b
      }
    }
  } else {
    if (c < b) {
      return meio;        // c < b && b <= a
    } else {
      if (c < a) {
        return fim;       // b <= c && c < a
      } else {
        return inicio;    // b <= a && a <= c
      }
    }
  }
}
void particionar(Aluno vet[], int esq, int dir, int *i, int *j, int *comp, int *troc) {
  int pivo = vet[medianadetres(vet, esq, dir)].matricula;
  *i = esq; 
  *j = dir;
  do {
    while (pivo > vet[*i].matricula) { //encontra o elemento a esquerda maior que o pivo
      (*comp)++;
      (*i)++;
    }
    while (pivo < vet[*j].matricula) { //encontra o elemento a direita menor que o pivo
      (*j)--;
      (*comp)++;
    }
    if (*i <= *j) { //troca se nescessario
      (*troc)++;
      troca(vet, *i, *j);
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}
void quickSort(Aluno vet[], int esq, int dir, int *comp, int *troc) {
  int i, j;
  particionar(vet, esq, dir, &i, &j, comp, troc);
  if (esq < j) {  //ordena recursivamente as partes esquerda e direita
    quickSort(vet, esq, j, comp, troc);
  }
  if (i < dir) {
    quickSort(vet, i, dir, comp, troc);
  }
}
//-------------------------------------------------funções de MERGESORT
void intercala(Aluno vet[], int n, int *comp, int *troc) {
  Aluno *aux = (Aluno *)malloc(n * sizeof(Aluno));
  int meio = n / 2;                               // meio do arranjo
  int i = 0;                                      // primeira metade do arranjo
  int j = meio;                                   // segunda metade do arranjo
  int k = 0;                                      // indice do aux
  while (i < meio && j < n) {                     // aux recebe o menor valor
    (*comp)++;
    if (vet[i].matricula < vet[j].matricula) {
      aux[k].matricula = vet[i].matricula;
      i++;
    } else {
      aux[k].matricula = vet[j].matricula;;
      j++;
    }
    (*troc)++;
    k++;
  }
  if (i == meio) {                                 // se i chegou ao meio
    while (j < n) {                                // aux recebe o resto de j
      aux[k].matricula = vet[j].matricula;
      j++;
      k++;
    }
  } else {                                          // se i nao chegou ao meio
    while (i < meio) {                              // aux recebe o resto de i
      aux[k].matricula = vet[i].matricula;
      i++;
      k++;
    }
  }
  for (int x = 0; x < n; x++) {                     // apos intercalados
    vet[x].matricula = aux[x].matricula;            // saem do aux e voltam para a
    (*troc)++;
  }
  free(aux);
}
void mergeSort(Aluno vet[], int n, int *comp, int *troc) {
  int meio = n / 2;
  if (n > 1) {
    mergeSort(vet, meio, comp, troc);
    mergeSort(vet + meio, n - meio, comp, troc);
    intercala(vet, n, comp, troc);
  }
}
//---------------------------------------------------funções de SELECTIONSORT
void selectionSort(Aluno vet[], int n, long long *comp, long long *troc) {
  for (int i = 0; i < n - 1; i++) {
    int menor = i; //assume que o atual é o menor 
    for (int j = i + 1; j < n; j++) {
      (*comp)++;
      if (vet[j].matricula < vet[menor].matricula) { //compara com os demais para encontrar o menor 
        menor = j;
      }
    }
    troca(vet, i, menor);
    (*troc)++;
  }
}
//-------------------------------------------------funções de INSERTIONSORT
void insertionSort(Aluno vet[], int n, long long *comp, long long *troc) {
  int x, j;
  for (int i = 1; i < n; i++) {
    x = vet[i].matricula; //guarda o elemento atual para comparação
    j = i - 1;
    (*comp)++;
    while (j >= 0 && vet[j].matricula > x) { //move os elementos maiores para direita ate que a posição correta seja encontrada
      vet[j + 1].matricula = vet[j].matricula;
      j = j - 1;
      (*troc)++;
      (*comp)++;
    }
    (*troc)++; //coloca na posição correta
    vet[j + 1].matricula = x;
  }
}
//-------------------------------------------------função para os testes de vetores aleatorios
// para os testes com vetores aletórios são feitos 10 testes e encontrado os valores das suas medias
void testeDeQS(int tamanho, FILE *arq){
  int medComp=0;
  int medTroc=0;
  double medTemp=0;
  for(int i = 0; i < 10; i++){
    Aluno *teste = gerarAlunosAleatorios(tamanho);
    int comp = 0; //contador de comparações 
    int troc = 0; //contador de movimentos
    clock_t inicio, fim; 
    inicio = clock();
    quickSort(teste, 0, tamanho-1, &comp, &troc);
    fim = clock();
    double temp = (double)(fim - inicio) / CLOCKS_PER_SEC; //contador de tempo em segundos
    medTemp += temp;
    medComp += comp;
    medTroc += troc;
    free(teste);
  }
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho); //exibe as medias dos 10 testes 
  fprintf(arq,"Tempo de execução: %f \n", medTemp/10);  
  fprintf(arq,"Número de comparações: %d \n", medComp/10);
  fprintf(arq,"Número de movimentações: %d \n", medTroc/10);
}
void testeDeMS(int tamanho, FILE *arq){
  int medComp=0;
  int medTroc=0;
  double medTemp=0;
  for(int i = 0; i < 10; i++){
    Aluno *teste = gerarAlunosAleatorios(tamanho);
    int comp = 0;
    int troc = 0;
    clock_t inicio, fim;
    inicio = clock();
    mergeSort(teste, tamanho, &comp, &troc);
    fim = clock();
    double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
    medTemp += temp;
    medComp += comp;
    medTroc += troc;
    free(teste);
  }
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho);
  fprintf(arq,"Tempo de execução: %f \n", medTemp/10);
  fprintf(arq,"Número de comparações: %d \n", medComp/10);
  fprintf(arq,"Número de movimentações: %d \n", medTroc/10);
}
void testeDeSS(int tamanho, FILE *arq){
  long long medComp=0; //para o Selection Sort e Insertion Sort foram usados variaveis extra longs para os contadores de comparações e movimentos 
  long long medTroc=0; //principalmente para que seja possivel ler os resultados de 100mil e 200mil elementos
  double medTemp=0;
  for(int i = 0; i < 10; i++){
    Aluno *teste = gerarAlunosAleatorios(tamanho);
    long long comp = 0;
    long long troc = 0;
    clock_t inicio, fim;
    inicio = clock();
    selectionSort(teste, tamanho, &comp, &troc);
    fim = clock();
    double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
    medTemp += temp;
    medComp += comp;
    medTroc += troc;
    free(teste);
  }
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho);
  fprintf(arq,"Tempo de execução: %f \n", medTemp/10);
  fprintf(arq,"Número de comparações: %lld \n", medComp/10);
  fprintf(arq,"Número de movimentações: %lld \n", medTroc/10);
}
void testeDeIS(int tamanho, FILE *arq){
  long long medComp=0;
  long long medTroc=0;
  double medTemp=0;
  for(int i = 0; i < 10; i++){
    Aluno *teste = gerarAlunosAleatorios(tamanho);
    long long comp = 0;
    long long troc = 0;
    clock_t inicio, fim;
    inicio = clock();
    insertionSort(teste, tamanho, &comp, &troc);
    fim = clock();
    double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
    medTemp += temp;
    medComp += comp;
    medTroc += troc;
    free(teste);
  }
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho);
  fprintf(arq,"Tempo de execução: %f \n", medTemp/10);
  fprintf(arq,"Número de comparações: %lld \n", medComp/10);
  fprintf(arq,"Número de movimentações: %lld \n", medTroc/10);
}
//--------------------------------------------------------------------funçoes de teste crescente
//é basicamente o mesmo que os testes anteriores, porem foi feito apenas uma vez
//então nao existe variavel para as medias 
void testeDeQScrescente(int tamanho, FILE *arq){
  Aluno *teste = gerarAlunosCrescente(tamanho);
  int comp = 0;
  int troc = 0;
  clock_t inicio, fim;
  inicio = clock();
  quickSort(teste, 0, tamanho-1, &comp, &troc);
  fim = clock();
  double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
  free(teste);
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho);
  fprintf(arq,"Tempo de execução: %f \n", temp);
  fprintf(arq,"Número de comparações: %d \n", comp);
  fprintf(arq,"Número de movimentações: %d \n", troc);
}
void testeDeMScrescente(int tamanho, FILE *arq){
  Aluno *teste = gerarAlunosCrescente(tamanho);
  int comp = 0;
  int troc = 0;
  clock_t inicio, fim;
  inicio = clock();
  mergeSort(teste, tamanho, &comp, &troc);
  fim = clock();
  double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
  free(teste);
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho);
  fprintf(arq,"Tempo de execução: %f \n", temp);
  fprintf(arq,"Número de comparações: %d \n", comp);
  fprintf(arq,"Número de movimentações: %d \n", troc);
}
void testeDeSScrescente(int tamanho, FILE *arq){
  Aluno *teste = gerarAlunosCrescente(tamanho);
  long long comp = 0;
  long long troc = 0;
  clock_t inicio, fim;
  inicio = clock();
  selectionSort(teste, tamanho, &comp, &troc);
  fim = clock();
  double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
  free(teste);
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho);
  fprintf(arq,"Tempo de execução: %f \n", temp);
  fprintf(arq,"Número de comparações: %lld \n", comp);
  fprintf(arq,"Número de movimentações: %lld \n", troc);
}
void testeDeIScrescente(int tamanho, FILE *arq){
  Aluno *teste = gerarAlunosCrescente(tamanho);
  long long comp = 0;
  long long troc = 0;
  clock_t inicio, fim;
  inicio = clock();
  insertionSort(teste, tamanho, &comp, &troc);
  fim = clock();
  double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
  free(teste);
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho);
  fprintf(arq,"Tempo de execução: %f \n", temp);
  fprintf(arq,"Número de comparações: %lld \n", comp);
  fprintf(arq,"Número de movimentações: %lld \n", troc);
}
//--------------------------------------------------------funcoes de teste decrescente 
// o mesmo que o teste crescente, só mudando a função de criação de alunos
void testeDeQSdecrescente(int tamanho, FILE *arq){
  Aluno *teste = gerarAlunosDecrescente(tamanho);
  int comp = 0;
  int troc = 0;
  clock_t inicio, fim;
  inicio = clock();
  quickSort(teste, 0, tamanho-1, &comp, &troc);
  fim = clock();
  double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
  free(teste);
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho);
  fprintf(arq,"Tempo de execução: %f \n", temp);
  fprintf(arq,"Número de comparações: %d \n", comp);
  fprintf(arq,"Número de movimentações: %d \n", troc);
}
void testeDeMSdecrescente(int tamanho, FILE *arq){
  Aluno *teste = gerarAlunosDecrescente(tamanho);
  int comp = 0;
  int troc = 0;
  clock_t inicio, fim;
  inicio = clock();
  mergeSort(teste, tamanho, &comp, &troc);
  fim = clock();
  double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
  free(teste);
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho);
  fprintf(arq,"Tempo de execução: %f \n", temp);
  fprintf(arq,"Número de comparações: %d \n", comp);
  fprintf(arq,"Número de movimentações: %d \n", troc);
}
void testeDeSSdecrescente(int tamanho, FILE *arq){
  Aluno *teste = gerarAlunosDecrescente(tamanho);
  long long comp = 0;
  long long troc = 0;
  clock_t inicio, fim;
  inicio = clock();
  selectionSort(teste, tamanho, &comp, &troc);
  fim = clock();
  double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
  free(teste);
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho);
  fprintf(arq,"Tempo de execução: %f \n", temp);
  fprintf(arq,"Número de comparações: %lld \n", comp);
  fprintf(arq,"Número de movimentações: %lld \n", troc);
}
void testeDeISdecrescente(int tamanho, FILE *arq){
  Aluno *teste = gerarAlunosDecrescente(tamanho);
  long long comp = 0;
  long long troc = 0;
  clock_t inicio, fim;
  inicio = clock();
  insertionSort(teste, tamanho, &comp, &troc);
  fim = clock();
  double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
  free(teste);
  fprintf(arq,"\nNúmero de elementos: %d \n", tamanho);
  fprintf(arq,"Tempo de execução: %f \n", temp);
  fprintf(arq,"Número de comparações: %lld \n", comp);
  fprintf(arq,"Número de movimentações: %lld \n", troc);
}
//--------------------------------------------------------função de imprimir vetor aluno
//usada para verificar se a ordenação está coreta no inicio do codigo
void imprimirAlunos(Aluno* a, int tamanho){
  for(int i=0; i<tamanho; i++){
    printf("Nº de Matrícula: %d\n",a[i].matricula);
    printf("Nome: %s\n",a[i].nome);
    printf("Periodo: %d\n",a[i].periodo);
    printf("Curso: %s\n",a[i].curso);
    printf("Coeficiente de Rendimento: %.2f\n\n",a[i].coeRend);
  }
}
//--------------------------------------------------------main
int main(void) {
  srand(time(NULL));
  FILE *arq;
  arq = fopen("dados.txt", "w"); //arquivo que armazena os resultados finais
  //--------------------------------------------------exemplo de ordenação mostrado no terminal
  char opc;
  printf("Deseja ver um exemplo de ordenação? (s/n)");
  scanf("%c",&opc);
  if(opc == 's' || opc == 'S'){
    printf("Insira o tamanho do vetor: ");
    int tamanho, escolha;
    scanf("%d",&tamanho);
    Aluno *alunos = gerarAlunosAleatorios(tamanho);
    int comp=0, troc=0;
    printf("Escolha o metodo: \n");
    printf("1-Quicksort\n");
    printf("2-MergeSort\n");
    printf("3-SelectionSort\n");
    printf("4-InsertionSort\n");
    printf("Escolha: ");
    scanf("%d", &escolha);
    printf("VETOR DESORGANIZADO:\n");
    imprimirAlunos(alunos, tamanho);
    clock_t inicio, fim;
    inicio = clock();
    switch(escolha){
      case 1:
        quickSort(alunos,0, tamanho-1, &comp, &troc);
      break;
      case 2:
        mergeSort(alunos, tamanho, &comp, &troc);
      break;
      case 3:
        selectionSort(alunos, tamanho, &comp, &troc);
      break;
      case 4:
        insertionSort(alunos, tamanho, &comp, &troc);
      break;
    }
    fim = clock();
    double temp = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("VETOR ORGANIZADO:\n");
    imprimirAlunos(alunos, tamanho);
    free(alunos);
    printf("\nNúmero de elementos: %d \n", tamanho);
    printf("Tempo de execução: %f \n", temp);
    printf("Número de comparações: %lld \n", comp);
    printf("Número de movimentações: %lld \n", troc);
  }
  return 0;
  //------------------------------------------TESTES 
  fprintf(arq,"\nTESTE DE VETORES ALETORIOS\nResultados obtidos a partir da média de 10 vetores\n");

  fprintf(arq,"\nQUICKSORT\n");
  testeDeQS(MIL, arq);
  testeDeQS(DEZMIL, arq);
  testeDeQS(CEMMIL, arq);
  testeDeQS(DUZMIL, arq);
  printf("teste de QuickSort aleatorio pronto\n"); //para saber o progresso do codigo no terminal

  fprintf(arq,"\nMERGESORT\n");
  testeDeMS(MIL, arq);
  testeDeMS(DEZMIL, arq);
  testeDeMS(CEMMIL, arq);
  testeDeMS(DUZMIL, arq);
  printf("teste de MergeSort aleatorio pronto\n");

  fprintf(arq,"\nSELECTIONSORT\n");
  testeDeSS(MIL, arq);
  testeDeSS(DEZMIL, arq);
  testeDeSS(CEMMIL, arq);
  testeDeSS(DUZMIL, arq);
  printf("teste de SelectionSort aleatorio pronto\n");

  fprintf(arq,"\nINSERTIONSORT\n");
  testeDeIS(MIL, arq);
  testeDeIS(DEZMIL, arq);
  testeDeIS(CEMMIL, arq);
  testeDeIS(DUZMIL, arq);
  printf("teste de InsertionSort aleatorio pronto\n");

  fprintf(arq,"\nTESTE DE VETORES EM ORDEM CRESCENTE\n");

  fprintf(arq,"\nQUICKSORT\n");
  testeDeQScrescente(MIL, arq);
  testeDeQScrescente(DEZMIL, arq);
  testeDeQScrescente(CEMMIL, arq);
  testeDeQScrescente(DUZMIL, arq);
  printf("teste de QuickSort crescente pronto\n");

  fprintf(arq,"\nMERGESORT\n");
  testeDeMScrescente(MIL, arq);
  testeDeMScrescente(DEZMIL, arq);
  testeDeMScrescente(CEMMIL, arq);
  testeDeMScrescente(DUZMIL, arq);
  printf("teste de MergeSort crescente pronto\n");

  fprintf(arq,"\nSELECTIONSORT\n");
  testeDeSScrescente(MIL, arq);
  testeDeSScrescente(DEZMIL, arq);
  testeDeSScrescente(CEMMIL, arq);
  testeDeSScrescente(DUZMIL, arq);
  printf("teste de SelectionSort crescente pronto\n");

  fprintf(arq,"\nINSERTIONSORT\n");
  testeDeIScrescente(MIL, arq);
  testeDeIScrescente(DEZMIL, arq);
  testeDeIScrescente(CEMMIL, arq);
  testeDeIScrescente(DUZMIL, arq);
  printf("teste de InsertionSort crescente pronto\n");  
  
  fprintf(arq,"\nTESTE DE VETORES EM ORDEM DECRESCENTE\n");

  fprintf(arq,"\nQUICKSORT\n");
  testeDeQSdecrescente(MIL, arq);
  testeDeQSdecrescente(DEZMIL, arq);
  testeDeQSdecrescente(CEMMIL, arq);
  testeDeQSdecrescente(DUZMIL, arq);
  printf("teste de QuickSort decrescente pronto\n");

  fprintf(arq,"\nMERGESORT\n");
  testeDeMSdecrescente(MIL, arq);
  testeDeMSdecrescente(DEZMIL, arq);
  testeDeMSdecrescente(CEMMIL, arq);
  testeDeMSdecrescente(DUZMIL, arq);
  printf("teste de MergeSort decrescente pronto\n");

  fprintf(arq,"\nSELECTIONSORT\n");
  testeDeSSdecrescente(MIL, arq);
  testeDeSSdecrescente(DEZMIL, arq);
  testeDeSSdecrescente(CEMMIL, arq);
  testeDeSSdecrescente(DUZMIL, arq);
  printf("teste de SelectionSort decrescente pronto\n");

  fprintf(arq,"\nINSERTIONSORT\n");
  testeDeISdecrescente(MIL, arq);
  testeDeISdecrescente(DEZMIL, arq);
  testeDeISdecrescente(CEMMIL, arq);
  testeDeISdecrescente(DUZMIL, arq);
  printf("teste de InsertionSort decrescente pronto\n");
  
  fclose(arq);
  
  return 0;
}