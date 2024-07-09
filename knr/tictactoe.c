#include <stdio.h>

#define bool int
#define true 1
#define false 0

// Jogo da velha é só uma matriz 3x3 binaria
//    0 1 2  <- indices das colunas
//    _____
// 0 |0 0 1
// 1 |1 0 1
// 2 |0 1 0
// ^ indices das linhas

// Então a primeira casa tem indice (0, 0), a segunda (0, 1) e a terceira (0, 2)
// começamos no 0 ao invés do 1 pois somos gente.

// A primeira linha é: (0, 0), (0, 1), (0, 2)
// A segunda linha:    (1, 0), (1, 1), (1, 2)
// A terceira linha:   (2, 0), (2, 1), (2, 2)

// Podemos ver que a diagonal principal tem o formato (i, i) com i = {0, 1, 2}
// E a diagonal secundária tem o formato (i, 2-i) com i = {0, 1, 2}

// Vamos usar:
//   0: vazio
// 'X': jogador X
// 'O': jogador O
//
// o tabuleiro começa vazio
char Tabuleiro[3][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
};

void ImprimeTabu() {
  printf("\t|\t0\t1\t2\t|\n");
  for (int i = 0; i <= 2; i++) {
    printf("%d\t|\t%c\t%c\t%c\t|\n", i, Tabuleiro[i][0], Tabuleiro[i][1], Tabuleiro[i][2]);
  }
}

bool Ocupado(int i, int j) {
  char c = Tabuleiro[i][j];
  if (c == 'O' || c == 'X') {
    return true;
  }
  return false;
}

bool PosicaoInvalida(int linha, int coluna) {
  if (linha < 0 || linha > 2)  {
    return true;
  }
  if (coluna < 0 || coluna > 2) {
    return true;
  }
  if (Ocupado(linha, coluna)) {
    return true;
  }
  return false;
}

bool TabuleiroComVazios() {
  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 2; j++) {
      char c = Tabuleiro[i][j];
      if (c != 'O' && c != 'X') {
        return true;
      }
    }
  }
  return false;
}

char ChecarLinhasEColunas() {
  // para cada linha checamos cada coluna
  // e para cada coluna checamos cada linha
  // (por isso um 'for' dentro do outro)
  for (int i = 0; i <= 2; i++) {
    int QuantLinhaX = 0;
    int QuantLinhaO = 0;
    int QuantColunaX = 0;
    int QuantColunaO = 0;
    for (int j = 0; j <= 2; j++) {
      switch (Tabuleiro[i][j]) { // vê os indices (i, j)
        case 'O':
          QuantLinhaO++;
          break;
        case 'X':
          QuantLinhaX++;
          break;
      }
      switch (Tabuleiro[j][i]) { // aqui os indices estão trocados (começamos pelas colunas)
        case 'O':
          QuantColunaO++;
          break;
        case 'X':
          QuantColunaX++;
          break;
      }
    }
    if (QuantLinhaX == 3 || QuantColunaX == 3) {
      return 'X'; // jogador 'X' venceu em alguma linha ou coluna
    } else if (QuantLinhaO == 3 || QuantColunaO == 3) {
      return 'O'; // jogador 'O' venceu em alguma linha ou coluna
    }
  }
  return 0; // ninguém venceu por linhas ou colunas
}

char ChecarDiagonais() {
  int QuantPrinO = 0;
  int QuantPrinX = 0;
  int QuantSecO = 0;
  int QuantSecX = 0;
  for (int i = 0; i <= 2; i++) {
    switch (Tabuleiro[i][i]) {
      case 'O':
        QuantPrinO++;
        break;
      case 'X':
        QuantPrinX++;
        break;
    }
    switch (Tabuleiro[i][2-i]) {
      case 'O':
        QuantSecO++;
        break;
      case 'X':
        QuantSecX++;
        break;
    }
  }
  if (QuantPrinX == 3 || QuantSecX == 3) {
    return 'X'; // jogador 'X' venceu na diagonal principal ou secundaria
  } else if (QuantPrinO == 3 || QuantSecO == 3) {
    return 'O'; // jogador 'O' venceu na diagonal principal ou secundaria
  }
  return 0;
}

bool Ganhamo(char c) {
  return c == 'O' || c == 'X';
}

char ChecarVitoria() {
  char resultado = 0;
  resultado = ChecarLinhasEColunas();
  if (Ganhamo(resultado)) {
    return resultado;
  }
  resultado = ChecarDiagonais();
  if (Ganhamo(resultado)) {
    return resultado;
  }
  return 0;
}

int main() {
  printf("Jojo da Véia\n");
  bool VezDoJogadorX = true;
  while (TabuleiroComVazios()) {
    ImprimeTabu();
    char c = 0;
    if (VezDoJogadorX) {
      printf("Jogador X:\n");
      c = 'X';
    } else {
      printf("Jogador O:\n");
      c = 'O';
    }
    int linha = 0;
    int coluna = 0;

    printf("\tLinha: "); scanf("%d", &linha);
    printf("\tColuna: "); scanf("%d", &coluna);
    if (PosicaoInvalida(linha, coluna)) {
      printf("Posicao (%d, %d) invalida! Tente outra vez\n", linha, coluna);
      continue;
    }

    Tabuleiro[linha][coluna] = c;
    char resultado = ChecarVitoria();
    if (resultado == 'O' || resultado == 'X') {
      ImprimeTabu();
      printf("Jogador '%c' Venceu!\n", resultado);
      return 0;
    }
    VezDoJogadorX = !VezDoJogadorX;
  }
  printf("Deu Véia!\n");
  return 0;
}
