#include <stdio.h>

// Tamanho do tabuleiro
#define TAMANHO 10
// Tamanho dos navios
#define TAMANHO_NAVIO 3
// Representação da água
#define AGUA 0
// Representação do navio
#define NAVIO 3

// CONFIGURAÇÃO DOS NAVIOS - MODIFIQUE AQUI PARA ALTERAR AS POSIÇÕES
// Navio horizontal: linha (0-9) e coluna (A-J)
#define LINHA_H 4
#define COLUNA_H 'D'  // Letra entre A-J

// Navio vertical: linha (0-9) e coluna (A-J)
#define LINHA_V 1
#define COLUNA_V 'G'  // Letra entre A-J

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para converter letra em índice (A=0, B=1, ..., J=9)
int letraParaIndice(char letra) {
    if (letra >= 'a' && letra <= 'j') {
        return letra - 'a';
    } else if (letra >= 'A' && letra <= 'J') {
        return letra - 'A';
    }
    return -1; // Inválido
}

// Função para converter índice em letra (0=A, 1=B, ..., 9=J)
char indiceParaLetra(int indice) {
    return 'A' + indice;
}

// Função para verificar se a posição do navio é válida
int posicaoValida(int linha, int coluna, int tamanho, int vertical) {
    if (vertical) {
        return (linha >= 0) && (linha + tamanho - 1 < TAMANHO) && (coluna >= 0) && (coluna < TAMANHO);
    } else {
        return (linha >= 0) && (linha < TAMANHO) && (coluna >= 0) && (coluna + tamanho - 1 < TAMANHO);
    }
}

// Função para verificar se há sobreposição de navios
int semSobreposicao(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, int vertical) {
    if (vertical) {
        for (int i = linha; i < linha + tamanho; i++) {
            if (tabuleiro[i][coluna] == NAVIO) {
                return 0;
            }
        }
    } else {
        for (int j = coluna; j < coluna + tamanho; j++) {
            if (tabuleiro[linha][j] == NAVIO) {
                return 0;
            }
        }
    }
    return 1;
}

// Função para posicionar um navio no tabuleiro
int posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, int vertical) {
    // Verifica se a posição é válida
    if (!posicaoValida(linha, coluna, tamanho, vertical)) {
        printf("Posição inválida para o navio!\n");
        return 0;
    }
    
    // Verifica se não há sobreposição
    if (!semSobreposicao(tabuleiro, linha, coluna, tamanho, vertical)) {
        printf("Navio sobreposto a outro navio!\n");
        return 0;
    }
    
    // Posiciona o navio
    if (vertical) {
        for (int i = linha; i < linha + tamanho; i++) {
            tabuleiro[i][coluna] = NAVIO;
        }
    } else {
        for (int j = coluna; j < coluna + tamanho; j++) {
            tabuleiro[linha][j] = NAVIO;
        }
    }
    
    return 1;
}

// Função para exibir o tabuleiro com letras nas colunas
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nTabuleiro de Batalha Naval:\n");
    printf("   ");
    for (int j = 0; j < TAMANHO; j++) {
        printf(" %c ", indiceParaLetra(j)); // Imprime letras das colunas (A-J)
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i); // Imprime número da linha
        for (int j = 0; j < TAMANHO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\nLegenda: 0 = Água, 3 = Navio\n");
    printf("Navio horizontal: linha %d, coluna %c\n", LINHA_H, COLUNA_H);
    printf("Navio vertical: linha %d, coluna %c\n", LINHA_V, COLUNA_V);
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    
    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    printf("-----Batalha Naval-----\n");
    printf("Posicionando navios...\n");
    
    // Posiciona o navio horizontal
    int linha_h = LINHA_H;
    int coluna_h = letraParaIndice(COLUNA_H);
    int sucesso_h = posicionarNavio(tabuleiro, linha_h, coluna_h, TAMANHO_NAVIO, 0); // 0 = horizontal
    
    // Posiciona o navio vertical
    int linha_v = LINHA_V;
    int coluna_v = letraParaIndice(COLUNA_V);
    int sucesso_v = posicionarNavio(tabuleiro, linha_v, coluna_v, TAMANHO_NAVIO, 1); // 1 = vertical
    
    // Verifica se ambos os navios foram posicionados com sucesso
    if (!sucesso_h || !sucesso_v) {
        printf("Erro ao posicionar os navios. Verifique as coordenadas.\n");
        return 1;
    }
    
    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);
    
    return 0;
}