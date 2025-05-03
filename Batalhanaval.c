#include <stdio.h>

// Configurações do tabuleiro
#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5

// Posições dos navios
#define H_LINHA 0   // Navio horizontal (linha 0)
#define H_COLUNA 0  // Navio horizontal (coluna 0-2)
#define V_LINHA 3   // Navio vertical (linha 3-5)
#define V_COLUNA 9  // Navio vertical (coluna 9)
#define D1_LINHA 6  // Navio diagonal 1 (linha 6-8, coluna 6-8)
#define D2_LINHA 0  // Navio diagonal 2 (linha 0-2, coluna 9-7)

// Posições das habilidades (centros)
#define CONE_LINHA 2
#define CONE_COLUNA 4
#define CRUZ_LINHA 7
#define CRUZ_COLUNA 2
#define OCTAEDRO_LINHA 4
#define OCTAEDRO_COLUNA 7

// Constantes numéricas para representação
#define AGUA 0
#define NAVIO 1
#define HABILIDADE 2

// Função para calcular valor absoluto
int valor_absoluto(int num) {
    return (num < 0) ? -num : num;
}

// Protótipos
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]);
void exibirTabuleiroNumerico(int tabuleiro[TAMANHO][TAMANHO]);
int posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tipo);
void criarHabilidade(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int tipo);
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linha, int coluna);

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);

    printf("-----Batalha Naval-----\n");
    printf("Posicionando navios...\n\n");

    // Posiciona navios (0-horizontal, 1-vertical, 2-diagonal1, 3-diagonal2)
    posicionarNavio(tabuleiro, H_LINHA, H_COLUNA, 0);
    posicionarNavio(tabuleiro, V_LINHA, V_COLUNA, 1);
    posicionarNavio(tabuleiro, D1_LINHA, D1_LINHA, 2);
    posicionarNavio(tabuleiro, D2_LINHA, TAMANHO-1-D2_LINHA, 3);

    // Cria e aplica habilidades (1-cone, 2-cruz, 3-octaedro)
    int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    criarHabilidade(habilidade, 1); // Cone
    aplicarHabilidade(tabuleiro, habilidade, CONE_LINHA, CONE_COLUNA);
    
    criarHabilidade(habilidade, 2); // Cruz
    aplicarHabilidade(tabuleiro, habilidade, CRUZ_LINHA, CRUZ_COLUNA);
    
    criarHabilidade(habilidade, 3); // Octaedro
    aplicarHabilidade(tabuleiro, habilidade, OCTAEDRO_LINHA, OCTAEDRO_COLUNA);

    printf("Tabuleiro de Batalha Naval:\n");
    exibirTabuleiroNumerico(tabuleiro);
    return 0;
}

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for(int i = 0; i < TAMANHO; i++)
        for(int j = 0; j < TAMANHO; j++)
            tabuleiro[i][j] = AGUA;
}

void exibirTabuleiroNumerico(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\n   ");
    for(int j = 0; j < TAMANHO; j++) printf("%2d ", j); // Cabeçalho colunas
    printf("\n");
    
    for(int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i); // Número da linha
        for(int j = 0; j < TAMANHO; j++) {
            printf("%2d ", tabuleiro[i][j]); // Exibe valor numérico
        }
        printf("\n");
    }
    
    printf("\nLegenda Numerica:\n");
    printf(" 0 = Agua\n 1 = Navio\n 2 = Area de habilidade\n");
}

int posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tipo) {
    for(int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha, y = coluna;
        
        switch(tipo) {
            case 0: y += i; break; // Horizontal
            case 1: x += i; break; // Vertical
            case 2: x += i; y += i; break; // Diagonal 1
            case 3: x += i; y -= i; break; // Diagonal 2
        }
        
        if(x >= TAMANHO || y >= TAMANHO || x < 0 || y < 0 || tabuleiro[x][y] != AGUA) {
            printf("Erro ao posicionar navio em (%d,%d)\n", linha, coluna);
            return 0;
        }
    }
    
    for(int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha, y = coluna;
        
        switch(tipo) {
            case 0: y += i; break;
            case 1: x += i; break;
            case 2: x += i; y += i; break;
            case 3: x += i; y -= i; break;
        }
        
        tabuleiro[x][y] = NAVIO;
    }
    return 1;
}

void criarHabilidade(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int tipo) {
    int centro = TAMANHO_HABILIDADE/2;
    
    for(int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for(int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = 0;
            
            switch(tipo) {
                case 1: // Cone
                    if((i == 0 && j == centro) ||
                       (i == 1 && j >= centro-1 && j <= centro+1) ||
                       (i == 2 && j >= centro-2 && j <= centro+2) ||
                       (i == 3 && j >= centro-1 && j <= centro+1) ||
                       (i == 4 && j == centro))
                        matriz[i][j] = 1;
                    break;
                    
                case 2: // Cruz
                    if(i == centro || j == centro)
                        matriz[i][j] = 1;
                    break;
                    
                case 3: // Octaedro
                    {
                        int dist_i = (i > centro) ? i - centro : centro - i;
                        int dist_j = (j > centro) ? j - centro : centro - j;
                        if(dist_i + dist_j <= centro)
                            matriz[i][j] = 1;
                    }
                    break;
            }
        }
    }
}

void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linha, int coluna) {
    int centro = TAMANHO_HABILIDADE/2;
    
    for(int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for(int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int x = linha - centro + i;
            int y = coluna - centro + j;
            
            if(x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO && habilidade[i][j] && tabuleiro[x][y] == AGUA)
                tabuleiro[x][y] = HABILIDADE;
        }
    }
}