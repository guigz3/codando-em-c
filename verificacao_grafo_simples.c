// atividade: Dado um grafo simples, verificar se ele e ciclo, completo ou roda
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 5

typedef struct {
    int quantidadeVertice;
    int quantidadeAresta;
    int grau[MAX_VERTICES];
    int matrizAdjacente[MAX_VERTICES][MAX_VERTICES];
} Grafos;

// Ler Grafo
void lerGrafo(Grafos *grafo, int numero) {
    int i, j;

    // zera graus e matriz
    for (i = 0; i < MAX_VERTICES; i++) {
        grafo->grau[i] = 0;
        for (j = 0; j < MAX_VERTICES; j++) {
            grafo->matrizAdjacente[i][j] = 0;
        }
    }
    grafo->quantidadeAresta = 0;

    printf("\nEntre com numero de vertices do grafo %d (1 a %d): ", numero, MAX_VERTICES);
    scanf("%d", &grafo->quantidadeVertice);

    if (grafo->quantidadeVertice < 1 || grafo->quantidadeVertice > MAX_VERTICES) {
        printf("ERRO! A entrada deve ser de 1 a %d.\n", MAX_VERTICES);
        return;
    }

    printf("\nPara cada par de vertices, digite 1 se existe aresta ou 0 se nao existe:\n\n");

    int u, v, entradaUsuario;
    for (u = 0; u < grafo->quantidadeVertice; u++) {
        for (v = u + 1; v < grafo->quantidadeVertice; v++) {
            printf("  grafo %d [v%d] [v%d]: ", numero, u, v);
            scanf("%d", &entradaUsuario);
            if (entradaUsuario == 1) {
                grafo->matrizAdjacente[u][v] = grafo->matrizAdjacente[v][u] = 1;
                grafo->grau[u]++;
                grafo->grau[v]++;
                grafo->quantidadeAresta++;
            }
        }
    }
}

// verificar se o grafo é Simples
int verificarSimplicidade(const Grafos *grafo) {
    int i, j;
    for (i = 0; i < grafo->quantidadeVertice; i++) {
        for (j = 0; j < grafo->quantidadeVertice; j++) {
            // verifica laco — vertice ligado a si mesmo
            if (i == j && grafo->matrizAdjacente[i][j] == 1) {
                return 0;
            }
            // verifica aresta multipla
            if (grafo->matrizAdjacente[i][j] > 1) {
                return 0;
            }
        }
    }
    return 1;
}

// Verificar se o grafo é ciclo
void verificarCiclo(const Grafos *grafo) {
    int i;

    if (grafo->quantidadeVertice < 3) {
        printf("Esse grafo simples nao e ciclo!\n");
        return;
    }

    for (i = 0; i < grafo->quantidadeVertice; i++) {
        if (grafo->grau[i] != 2) {
            printf("Esse grafo simples nao e ciclo!\n");
            return;
        }
    }

    printf("Esse grafo simples e ciclo!\n");
}

// Verificar se o grafo e completo
void verificarCompleto(const Grafos *grafos) {
    int i;

    for (i = 0; i < grafos->quantidadeVertice; i++) {
        if (grafos->grau[i] != grafos->quantidadeVertice - 1) {
            printf("Esse grafo simples nao eh completo!\n");
            return;
        }
    }

    printf("Esse grafo simples eh completo!\n");
}

//  Verificar se o grafo e roda
void verificarRoda(const Grafos *grafos) {
    int i, contador;
    contador = 0;

    if (grafos->quantidadeVertice < 4) {
        printf("Esse grafo simples nao e roda!\n");
        return;
    }

    for (i = 0; i < grafos->quantidadeVertice; i++) {
        if (grafos->grau[i] == grafos->quantidadeVertice - 1) {
            contador++;
        }
        if (grafos->grau[i] != grafos->quantidadeVertice - 1 && grafos->grau[i] != 3) {
            printf("Esse grafo simples nao e roda!\n");
            return;
        }
    }

    if (contador != 1) {
        printf("Esse grafo simples nao e roda!\n");
        return;
    }

    printf("Esse grafo simples e roda!\n");
}


int main(void) {
    Grafos grafo;

    lerGrafo(&grafo, 1);

    if (verificarSimplicidade(&grafo)) {
        printf("\nO grafo e simples!\n\n");
        verificarCiclo(&grafo);
        verificarCompleto(&grafo);
        verificarRoda(&grafo);
    } else {
        printf("\nO grafo nao e simples!\n");
    }

    return 0;
}
