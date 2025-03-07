#include <stdio.h>
#include <stdlib.h>

#define LINHAS 6
#define COLUNAS 7
#define VAZIO ' '


void inicializarTabuleiro(char tabuleiro[LINHAS][COLUNAS]);
void imprimirTabuleiro(char tabuleiro[LINHAS][COLUNAS]);
int soltarPeca(char tabuleiro[LINHAS][COLUNAS], int coluna, char peca);
int verificarVitoria(char tabuleiro[LINHAS][COLUNAS], char peca);

int jogo() {
    char tabuleiro[LINHAS][COLUNAS];
    int coluna, turno = 0;
    char jogadores[2] = {'X', 'O'};

    inicializarTabuleiro(tabuleiro);

    while (1) {
        imprimirTabuleiro(tabuleiro);
        printf("Jogador %d (%c), escolha uma coluna (1-7): ", turno + 1, jogadores[turno]);
        scanf("%d", &coluna);

        if (coluna <= 0 || coluna > COLUNAS || !soltarPeca(tabuleiro, coluna, jogadores[turno])) {
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

int regras(){
    printf("\n\n\n");
    printf("Regras do jogo quatro em linha: \n");
    printf("O jogo é jogado num tabuleiro vertical composto por 6 linhas e 7 colunas. \n");
    printf("Cada jogador tem uma peça, que pode ser X ou O. \n");
    printf("Os jogadores jogam alternadamente, uma peça de cada vez. \n");
    printf("O objetivo do jogo é alinhar 4 peças da mesma cor, horizontal, vertical ou diagonalmente. \n");
    printf("O jogo termina quando um dos jogadores alinha 4 peças da mesma cor ou quando o tabuleiro fica cheio. \n");
    printf("Boa sorte! \n");
    return 1;
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
        if (tabuleiro[i][coluna - 1] == VAZIO) {
            tabuleiro[i][coluna - 1] = peca;
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

int menu(int a){
    switch (a){
        case 1:
            jogo();
            break;
        case 2:
            regras();
            break;
        case 9:
            exit(0);
            break;
        default:
            printf("Opção inválida, tente novamente.\n");
            break;
    }
    return 0;
}

int main(){
    int escomenu;
    printf("Bem vindo ao menu do jogo quatro em linha \n\n");
    printf("1 - Jogar \n");
    printf("2 - Regras \n");
    printf("9 - Sair \n");
    
    printf("Introduza uma opção: ");
    scanf("%d", &escomenu);
    menu(escomenu);
    }