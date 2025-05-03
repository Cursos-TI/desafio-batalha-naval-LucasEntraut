#include <stdio.h>

// Configurações do jogo - MODIFIQUE AQUI PARA ALTERAR AS POSIÇÕES
#define TAMANHO 10          // Tamanho do tabuleiro
#define TAMANHO_NAVIO 3     // Tamanho de cada navio

// Navio horizontal (linha, coluna)
#define H_LINHA 2
#define H_COLUNA 3

// Navio vertical (linha, coluna)
#define V_LINHA 5
#define V_COLUNA 7

// Navio diagonal 1 (linha inicial)
#define D1_LINHA 0         // Diagonal principal (linha = coluna)

// Navio diagonal 2 (linha inicial)
#define D2_LINHA 7          // Diagonal secundária (linha + coluna = 9) do maior para o menor (9 à 0)

// Constantes para representação
#define AGUA 0
#define NAVIO 3

// Protótipos de funções
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]);
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]);
int posicionarNavioHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna);
int posicionarNavioVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna);
int posicionarNavioDiagonal1(int tabuleiro[TAMANHO][TAMANHO], int inicio);
int posicionarNavioDiagonal2(int tabuleiro[TAMANHO][TAMANHO], int inicio);
int posicaoValida(int linha, int coluna);
int celulaLivre(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna);

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    
    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    printf("-----Batalha Naval-----\n");
    printf("Posicionando navios...\n");
    
    // Posiciona os navios
    int h_sucesso = posicionarNavioHorizontal(tabuleiro, H_LINHA, H_COLUNA);
    int v_sucesso = posicionarNavioVertical(tabuleiro, V_LINHA, V_COLUNA);
    int d1_sucesso = posicionarNavioDiagonal1(tabuleiro, D1_LINHA);
    int d2_sucesso = posicionarNavioDiagonal2(tabuleiro, D2_LINHA);
    
    // Verifica se todos os navios foram posicionados
    if (!h_sucesso || !v_sucesso || !d1_sucesso || !d2_sucesso) {
        printf("\nErro ao posicionar navios! Verifique as configurações.\n");
        return 1;
    }
    
    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);
    
    // Mostra as configurações usadas
    printf("\nConfigurações usadas:\n");
    printf("Navio Horizontal: linha %d, coluna %d\n", H_LINHA, H_COLUNA);
    printf("Navio Vertical: linha %d, coluna %d\n", V_LINHA, V_COLUNA);
    printf("Navio Diagonal 1: linha inicial %d (linha = coluna)\n", D1_LINHA);
    printf("Navio Diagonal 2: linha inicial %d (linha + coluna = 9)\n", D2_LINHA);
    
    return 0;
}

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Exibe o tabuleiro formatado
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("   ");
    printf("\nTabuleiro de Batalha Naval:\n");
    printf("   ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%2d ", j); // Cabeçalho das colunas
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAMANHO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
        
    }
}

// Posiciona navio horizontal
int posicionarNavioHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    // Verifica se cabe no tabuleiro
    if (!posicaoValida(linha, coluna) || !posicaoValida(linha, coluna + TAMANHO_NAVIO - 1)) {
        printf("Navio horizontal não cabe nas coordenadas (%d,%d)\n", linha, coluna);
        return 0;
    }
    
    // Verifica células livres
    for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++) {
        if (!celulaLivre(tabuleiro, linha, j)) {
            printf("Sobreposição na posição (%d,%d) do navio horizontal\n", linha, j);
            return 0;
        }
    }
    
    // Posiciona o navio
    for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++) {
        tabuleiro[linha][j] = NAVIO;
    }
    
    return 1;
}

// Posiciona navio vertical
int posicionarNavioVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    // Verifica se cabe no tabuleiro
    if (!posicaoValida(linha, coluna) || !posicaoValida(linha + TAMANHO_NAVIO - 1, coluna)) {
        printf("Navio vertical não cabe nas coordenadas (%d,%d)\n", linha, coluna);
        return 0;
    }
    
    // Verifica células livres
    for (int i = linha; i < linha + TAMANHO_NAVIO; i++) {
        if (!celulaLivre(tabuleiro, i, coluna)) {
            printf("Sobreposição na posição (%d,%d) do navio vertical\n", i, coluna);
            return 0;
        }
    }
    
    // Posiciona o navio
    for (int i = linha; i < linha + TAMANHO_NAVIO; i++) {
        tabuleiro[i][coluna] = NAVIO;
    }
    
    return 1;
}

// Posiciona navio na diagonal principal (linha = coluna)
int posicionarNavioDiagonal1(int tabuleiro[TAMANHO][TAMANHO], int inicio) {
    // Verifica se cabe no tabuleiro
    if (inicio < 0 || inicio + TAMANHO_NAVIO - 1 >= TAMANHO) {
        printf("Navio diagonal 1 não cabe começando em %d\n", inicio);
        return 0;
    }
    
    // Verifica células livres
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = inicio + i;
        int coluna = inicio + i;
        if (!celulaLivre(tabuleiro, linha, coluna)) {
            printf("Sobreposição na posição (%d,%d) do navio diagonal 1\n", linha, coluna);
            return 0;
        }
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = inicio + i;
        int coluna = inicio + i;
        tabuleiro[linha][coluna] = NAVIO;
    }
    
    return 1;
}

// Posiciona navio na diagonal secundária (linha + coluna = 9)
int posicionarNavioDiagonal2(int tabuleiro[TAMANHO][TAMANHO], int inicio) {
    // Verifica se cabe no tabuleiro
    if (inicio < 0 || inicio + TAMANHO_NAVIO - 1 >= TAMANHO) {
        printf("Navio diagonal 2 não cabe começando em %d\n", inicio);
        return 0;
    }
    
    // Verifica células livres
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = inicio + i;
        int coluna = (TAMANHO - 1) - linha;
        if (!celulaLivre(tabuleiro, linha, coluna)) {
            printf("Sobreposição na posição (%d,%d) do navio diagonal 2\n", linha, coluna);
            return 0;
        }
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = inicio + i;
        int coluna = (TAMANHO - 1) - linha;
        tabuleiro[linha][coluna] = NAVIO;
    }
    
    return 1;
}

// Verifica se a posição está dentro do tabuleiro
int posicaoValida(int linha, int coluna) {
    return linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO;
}

// Verifica se a célula está livre (água)
int celulaLivre(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    return tabuleiro[linha][coluna] == AGUA;
}