#include <stdio.h>
#include <stdlib.h>


#define LINHAS 6
#define COLUNAS 7
#define VAZIO ' '


void inicializarTabuleiro(char tabuleiro[LINHAS][COLUNAS]);
void imprimirTabuleiro(char tabuleiro[LINHAS][COLUNAS]);
int soltarPeca(char tabuleiro[LINHAS][COLUNAS], int coluna, char peca);
int verificarVitoria(char tabuleiro[LINHAS][COLUNAS], char peca);
int jogadaai(char tabuleiro[LINHAS][COLUNAS], char pecaIA, char pecaJogador);
int verificarVitoria(char tabuleiro[LINHAS][COLUNAS], char peca);
int encontrarJogadaVitoria(char tabuleiro[LINHAS][COLUNAS], char peca);
int bloquearJogador(char tabuleiro[LINHAS][COLUNAS], char pecaJogador);
int jogadaAleatoria();
void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void space(){
    getchar();
    getchar();
}
int menu();
int menujogo();

int jogo() {
    char tabuleiro[LINHAS][COLUNAS];
    int coluna, turno = 0;
    char jogadores[2] = {'X', 'O'};

    inicializarTabuleiro(tabuleiro);

    while (1) {
        imprimirTabuleiro(tabuleiro);
        printf("\n Jogador %d (%c), escolha uma coluna (1-7): ", turno + 1, jogadores[turno]);
        scanf("%d", &coluna);

        if (coluna <= 0 || coluna > COLUNAS || !soltarPeca(tabuleiro, coluna, jogadores[turno])) {
            printf("Movimento inválido, tente novamente.\n");
            continue;
        }

        if (verificarVitoria(tabuleiro, jogadores[turno])) {
            int resposta;
            imprimirTabuleiro(tabuleiro);
            printf("\n Jogador %d (%c) venceu!\n", turno + 1, jogadores[turno]);
            printf("\n\n\n Quer jogar novamente (1 = Sim ; 2 = Não): ");
            scanf("%d", &resposta);
            switch (resposta)
            {
            case 1:
                jogo();
                break;
            case 2:
                menu();
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
                break;
            }
            
        }

        turno = 1 - turno;
    }
    return 0;
}
int aijogo(){
    clear();
    char tabuleiro[LINHAS][COLUNAS];
    int turnojg = 0;
    printf("Bem vindo");
    printf("\n Jogador do ao jogo quatro em linha contra o computador\n");
    printf("Quer jogar primeiro? (1 = Sim [X] ; 2 = Não [O]): ");
    scanf("%d", &turnojg);
    int coluna, turno = 0;
    char jogadores[2] = {'X', 'O'};

    inicializarTabuleiro(tabuleiro);

    while (1) {
        imprimirTabuleiro(tabuleiro);
        if(turno == turnojg-1){
            printf("\n Jogador %d (%c), escolha uma coluna (1-7): ", turno + 1, jogadores[turno]);
            scanf("%d", &coluna);

            if (coluna <= 0 || coluna > COLUNAS || !soltarPeca(tabuleiro, coluna, jogadores[turno])) {
                printf("Movimento inválido, tente novamente.\n");
                continue;
            }
        }else{
            coluna = jogadaai(tabuleiro, jogadores[turno], jogadores[turnojg-1]);
            soltarPeca(tabuleiro, coluna, jogadores[turno]);
            space();
        }

        if (verificarVitoria(tabuleiro, jogadores[turno])) {
            int resposta;
            imprimirTabuleiro(tabuleiro);
            
            if(turno == turnojg-1){printf("\n O Jogador venceu!\n");}
            else{printf("\n O Computador venceu!\n");}
            printf("\n\n\n Quer jogar novamente (1 = Sim ; 2 = Não): ");
            scanf("%d", &resposta);
            switch (resposta)
            {
            case 1:
                aijogo();
                break;
            case 2:
                menu();
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
                space();
                menu();
                break;
            }
    
        }
        turno = 1 - turno;
    }
    return 0;
}


int regras(){
    clear();
    printf("Regras do jogo quatro em linha: \n");
    printf("O jogo é jogado num tabuleiro vertical composto por 6 linhas e 7 colunas. \n");
    printf("Cada jogador tem uma peça, que pode ser X ou O. \n");
    printf("Os jogadores jogam alternadamente, uma peça de cada vez. \n");
    printf("O objetivo do jogo é alinhar 4 peças da mesma cor, horizontal, vertical ou diagonalmente. \n");
    printf("O jogo termina quando um dos jogadores alinha 4 peças da mesma cor ou quando o tabuleiro fica cheio. \n");
    printf("Boa sorte! \n");
    printf("Pressione qualquer tecla para voltar ao menu principal.\n");
    space();
    menu();
    return 1;
}

void inicializarTabuleiro(char tabuleiro[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            tabuleiro[i][j] = VAZIO;
}


void imprimirTabuleiro(char tabuleiro[LINHAS][COLUNAS]) {
    clear();
    for (int i = 0; i < LINHAS; i++) {
        printf("\t");
        printf("|");
        for (int j = 0; j < COLUNAS; j++)
            printf(" %c |", tabuleiro[i][j]);
        printf("\n");
    }
    printf("\t  1   2   3   4   5   6   7  \n");
}


int soltarPeca(char tabuleiro[LINHAS][COLUNAS], int coluna, char peca) {
    for (int i = LINHAS - 1; i >= 0; i--) {
        if (tabuleiro[i][coluna - 1] == VAZIO) {
            tabuleiro[i][coluna - 1] = peca;
            return 1;
        }
    }
    printf("\n Coluna cheia, tente novamente.\n");
    space();
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

int menu(){
    clear();
    int escomenu;
    printf("Bem vindo ao menu do jogo quatro em linha \n\n");
    printf("1 - Jogar \n");
    printf("2 - Regras \n");
    printf("3 - Tabela de rankings \n");
    printf("9 - Sair \n");
    printf("Introduza uma opção: ");
    scanf("%d", &escomenu);
    switch (escomenu){
        case 1:
            menujogo();
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
int jogadaai(char tabuleiro[LINHAS][COLUNAS], char pecaIA, char pecaJogador) {
    int coluna;
    
    // 1. Verificar se a IA pode ganhar
    coluna = encontrarJogadaVitoria(tabuleiro, pecaIA);
    if (coluna != -1) {
        return coluna;
    }
    
    // 2. Bloquear o jogador se estiver prestes a ganhar
    coluna = encontrarJogadaVitoria(tabuleiro, pecaJogador);
    if (coluna != -1) {
        return coluna;
    }
    
    // 3. Escolher uma jogada aleatória válida
    do {
        coluna = jogadaAleatoria();
    } while (tabuleiro[0][coluna - 1] != VAZIO);  // Verifica se a coluna não está cheia
    
    return coluna;
}

int encontrarJogadaVitoria(char tabuleiro[LINHAS][COLUNAS], char peca) {
    for (int j = 0; j < COLUNAS; j++) {
        for (int i = LINHAS - 1; i >= 0; i--) {
            if (tabuleiro[i][j] == VAZIO) {  // Testa colocando temporariamente a peça
                tabuleiro[i][j] = peca;
                if (verificarVitoria(tabuleiro, peca)) {
                    tabuleiro[i][j] = VAZIO; // Reverte o teste
                    return j + 1;
                }
                tabuleiro[i][j] = VAZIO;  // Reverte o teste
                break;
            }
        }
    }
    return -1;
}


int bloquearJogador(char tabuleiro[LINHAS][COLUNAS], char pecaJogador) {
    return encontrarJogadaVitoria(tabuleiro, pecaJogador);
}

int jogadaAleatoria() {
    return (rand() % COLUNAS) + 1;
}
int menujogo(){
    clear();
    int escomenu;
    printf("Escolha um modo de jogo \n\n");
    printf("1 - Dois Jogadores \n");
    printf("2 - Um jogador \n");
    printf("9 - Voltar \n\n\n");
    printf("Introduza uma opção: ");
    scanf("%d", &escomenu);
    switch (escomenu){
        case 1:
            jogo();
            break;
        case 2:
            aijogo();
            break;
        case 9:
            menu();
            break;
        default:
            printf("Opção inválida, tente novamente.\n");
            break;
    }
    return 0;
}

int main(){
    system("chcp 65001 > nul");
    menu();
    return 0;
}