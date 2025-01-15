#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  char cor[20];
  int posicao[4];
  int pontos;
  int dado[3];
} jogador;

void exibirTabuleiro(jogador *p, int n);
void rolaDado(jogador *p, int i);
void movimento(jogador *p, int i);
int nDeJogadores();
void iniciaNoLugarCerto(jogador *p, int i, int k);
int verificaVolta(int i, int novaPosicao, int velhaPosicao);
void comer(jogador *p, int i, int j);
int espacoseguro(int i);

int main() {
  // inicializando as peças e jogadores
  jogador p[4] = {{" Amarelo  (A)", {0, 0, 0, 0}, 0, {0, 0, 0}},
                  {" Vermelho (B)", {0, 0, 0, 0}, 0, {0, 0, 0}},
                  {"   Azul   (C)", {0, 0, 0, 0}, 0, {0, 0, 0}},
                  {"  Verde   (D)", {0, 0, 0, 0}, 0, {0, 0, 0}}};
  printf("\n ---------- LUDO ---------- \n");

  // definir numero de jogadores
  int n = nDeJogadores();

  // loop de jogadas
  int i = 0;
  while (1) {

    memset(p[i].dado, 0, sizeof(p[i].dado));
    printf("\n --- Vez do Jogador %s --- \n", p[i].cor);

    rolaDado(p, i);
    // nao se mexe se nao tirar um 6
    if (!(p[i].posicao[0] == 0 && p[i].posicao[1] == 0 &&
          p[i].posicao[2] == 0 && p[i].posicao[3] == 0 && p[i].dado[0] != 6)) {
      movimento(p, i);
    }

    // verifica vitoria
    for (int x = 0; x < 4; x++) {
      if (p[x].pontos == 4) {
        printf("Jogador %s GANHOU!!!\n", p[x].cor);
        exibirTabuleiro(p, n);
        return 0;
      }
    }

    exibirTabuleiro(p, n);
    // troca de jogador
    i++;
    if (i >= n) {
      i = 0;
    }
  }

  return 0;
}

void exibirTabuleiro(jogador p[], int n) {
  printf("----- TABULEIRO -------------\n");
  printf("\n --- Base ---\n");
  for (int i = 0; i < n; i++) {
    printf("[ ");
    for (int k = 0; k < 4; k++) {
      if (i == 0 && p[i].posicao[k] == 0)  printf("\033[1;33mA%d \033[0m", k + 1);
      if (i == 1 && p[i].posicao[k] == 0)  printf("\033[1;31mB%d \033[0m", k + 1);
      if (i == 2 && p[i].posicao[k] == 0)  printf("\033[1;34mC%d \033[0m", k + 1);
      if (i == 3 && p[i].posicao[k] == 0)  printf("\033[1;32mD%d \033[0m", k + 1);
      if (p[i].posicao[k] != 0)  printf("   ");
    }
    printf("]\n");
  }
  printf("\n --- Campo --- \n");
  for (int i = 1; i < 58; i++) {
    if (i == 53)  printf("\n");
    printf("[");
    int vazio = 1;
    for (int k = 0; k < 4; k++) {
      if (p[0].posicao[k] == i) {
        printf("\033[1;33mA%d\033[0m ", k + 1);
        vazio = 0;
      }
      if (p[1].posicao[k] == i) {
        printf("\033[1;31mB%d\033[0m ", k + 1);
        vazio = 0;
      }
      if (p[2].posicao[k] == i) {
        printf("\033[1;34mC%d\033[0m ", k + 1);
        vazio = 0;
      }
      if (p[3].posicao[k] == i) {
        printf("\033[1;32mD%d\033[0m ", k + 1);
        vazio = 0;
      }
    }
    if (vazio)  printf("   ");
    if (i >= 53 && i < 58)  printf(".");
    if (i == 51)  printf("\033[1;33ma\033[0m");
    if (i == 25)  printf("\033[1;31mb\033[0m");
    if (i == 38)  printf("\033[1;34mc\033[0m");
    if (i == 12)  printf("\033[1;32md\033[0m");
    if (espacoseguro(i))  printf("+");
    printf("]");
    if (i % 13 == 0)  printf("\n");
  }
  printf("\n --- Final ---\n");
  for (int i = 0; i < n; i++) {
    printf("[ ");
    for (int k = 0; k < 4; k++) {
      if (p[i].posicao[k] == 59)  printf("F%d ", k + 1);
      if (p[i].posicao[k] != 59)  printf("   ");
    }
    printf("]\n");
  }
  printf("-----------------------------\n");
}

void movimento(jogador *p, int i) {
  int k;
  
  for (int j = 0; j < 3; j++) {
    if (p[i].dado[j] != 0) {
      printf("Mover qual peça com o %dº dado ?\n", j + 1);
      scanf("%d", &k);
      getchar();

      if (k < 1 || k > 4) {
        printf("Peça inválida\n");
        j--;
        continue;
      }

      if (p[i].dado[j] == 6 && p[i].posicao[k - 1] == 0) {
        iniciaNoLugarCerto(p, i, k);

      } else if (p[i].posicao[k - 1] != 0) {
        int novaPosicao = p[i].posicao[k - 1] + p[i].dado[j];
        int velhaPosicao = p[i].posicao[k - 1];
        novaPosicao = verificaVolta(i, novaPosicao, velhaPosicao);

        if (novaPosicao == 58) {
          p[i].posicao[k - 1] = novaPosicao;
          printf("Peça chegou ao destino!\n");
          memset(p[i].dado, 0, sizeof(p[i].dado));
          p[i].pontos++;
          rolaDado(p, i);
          movimento(p, i);
        } else if (novaPosicao > 58) {
          printf("Movimento inválido\n");
          j--;
          continue;
        } else {
          p[i].posicao[k - 1] = novaPosicao;
          if (!espacoseguro(i) && i >= 1 && i <= 52) {
            comer(p, i, k - 1);
          }
        }
      } else {
        printf("Não pode mover essa peça\n");
      }
    }
  }
}

int espacoseguro(int i) {
  if (i ==  1 || i ==  9 || i == 14 || i == 22 || 
      i == 27 || i == 35 || i == 40 ||  i == 48) {
    return 1;
  } else {
    return 0;
  }
}

void comer(jogador *p, int i, int j) {
  for (int x = 0; x < 4; x++) {
    if (x == i) {
      continue;
    }
    for (int y = 0; y < 4; y++) {
      if (p[x].posicao[y] == p[i].posicao[j]) {
        p[x].posicao[y] = 0;
      }
    }
  }
}

void iniciaNoLugarCerto(jogador *p, int i, int k) {
  if (i == 0)  p[i].posicao[k - 1] = 1;
  if (i == 1)  p[i].posicao[k - 1] = 27;
  if (i == 2)  p[i].posicao[k - 1] = 40;
  if (i == 3)  p[i].posicao[k - 1] = 14;
}

void rolaDado(jogador *p, int i) {
  int d, contador = 0;
  for (int j = 0; j < 3; j++) {
    printf("Enter para jogar Dado\n");
    getchar();
    srand(time(NULL));
    d = (rand() % 6) + 1;
    printf("Rolou um %d.\n\n", d);
    if (d == 6) {
      printf("Jogar novamente!\n");
      p[i].dado[j] = d;
      contador++;
    }
    if (contador == 3) {
      printf("Perdeu a vez!!!\n");
      memset(p[i].dado, 0, sizeof(p[i].dado));
    }
    if (d != 6) {
      p[i].dado[j] = d;
      break;
    }
  }
}

int verificaVolta(int i, int novaPosicao, int velhaPosicao) {
  if (i == 0) {
    if (velhaPosicao <= 51 && novaPosicao >= 52) {
      return novaPosicao + 1;
    } else {
      return novaPosicao;
    }
  }
  if (velhaPosicao <= 52 && novaPosicao > 52 && i != 0) {
    return novaPosicao - 52;
  }
  if (i == 1) {
    if (velhaPosicao <= 25 && novaPosicao >= 26) {
      return novaPosicao + 27;
    } else {
      return novaPosicao;
    }
  }
  if (i == 2) {
    if (velhaPosicao <= 38 && novaPosicao >= 39) {
      return novaPosicao + 15;
    } else {
      return novaPosicao;
    }
  }
  if (i == 3) {
    if (velhaPosicao <= 12 && novaPosicao >= 13) {
      return novaPosicao + 41;
    } else {
      return novaPosicao;
    }
  }
  return novaPosicao;
}

int nDeJogadores() {
  int n;
  while (1) {
    printf("\nQuantos Jogadores vão participar? (2-4)\n");
    scanf("%d", &n);
    getchar();
    if (n == 2 || n == 4) {
      return n;
    } else {
      printf("Numero de jogadores não permitido\n");
    }
  }
}