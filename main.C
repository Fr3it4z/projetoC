#include <stdio.h>
#include <stdlib.h>

#define LINHAS 6
#define COLUNAS 7
#define VAZIO ' '


void inicializarTabuleiro(char tabuleiro[LINHAS][COLUNAS]);
void imprimirTabuleiro(char tabuleiro[LINHAS][COLUNAS]);
int soltarPeca(char tabuleiro[LINHAS][COLUNAS], int coluna, char peca);
int verificarVitoria(char tabuleiro[LINHAS][COLUNAS], char peca);

int main() {
    char tabuleiro[LINHAS][COLUNAS];
    int coluna, turno = 0;
    char jogadores[2] = {'X', 'O'};

    inicializarTabuleiro(tabuleiro);

    while (1) {
        imprimirTabuleiro(tabuleiro);
        printf("Jogador %d (%c), escolha uma coluna (1-7): ", turno + 1, jogadores[turno]);
        scanf("%d", &coluna);

        if (coluna <= 0 || coluna >= COLUNAS || !soltarPeca(tabuleiro, coluna, jogadores[turno])) {
            printf("Movimento inválido, tente novamente.\n");
            continue;
        }

        if (verificarVitoria(tabuleiro, jogadores[turno])) {
            imprimirTabuleiro(tabuleiro);
            printf("Jogador %d (%c) venceu!\n", turno + 1, jogadores[turno]);
            break;
        }

        turno = 1 - turno;
    }

    return 0;
}


void inicializarTabuleiro(char tabuleiro[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            tabuleiro[i][j] = VAZIO;
}


void imprimirTabuleiro(char tabuleiro[LINHAS][COLUNAS]) {
    system("cls");
    for (int i = 0; i < LINHAS; i++) {
        printf("|");
        for (int j = 0; j < COLUNAS; j++)
            printf(" %c |", tabuleiro[i][j]);
        printf("\n");
    }
    printf("  1   2   3   4   5   6   7  \n");
}


int soltarPeca(char tabuleiro[LINHAS][COLUNAS], int coluna, char peca) {
    for (int i = LINHAS - 1; i >= 0; i--) {
        if (tabuleiro[i][coluna] == VAZIO) {
            tabuleiro[i][coluna] = peca;
            return 1;
        }
    }
    return 0;
}


int verificarVitoria(char tabuleiro[LINHAS][COLUNAS], char peca) {

    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++) {
            if (j + 3 < COLUNAS && tabuleiro[i][j] == peca && tabuleiro[i][j+1] == peca && tabuleiro[i][j+2] == peca && tabuleiro[i][j+3] == peca)
                return 1;

            if (i + 3 < LINHAS && tabuleiro[i][j] == peca && tabuleiro[i+1][j] == peca && tabuleiro[i+2][j] == peca && tabuleiro[i+3][j] == peca)
                return 1;

            if (i + 3 < LINHAS && j + 3 < COLUNAS && tabuleiro[i][j] == peca && tabuleiro[i+1][j+1] == peca && tabuleiro[i+2][j+2] == peca && tabuleiro[i+3][j+3] == peca)
                return 1;

            if (i - 3 >= 0 && j + 3 < COLUNAS && tabuleiro[i][j] == peca && tabuleiro[i-1][j+1] == peca && tabuleiro[i-2][j+2] == peca && tabuleiro[i-3][j+3] == peca)
                return 1;
        }
    return 0;
}