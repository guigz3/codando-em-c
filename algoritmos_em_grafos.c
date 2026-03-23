//atividade: Entrar dois grafos e verificar se são isomorfos 
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 5 //usando de EX. casos de uso atividade

typedef struct {
    int quantidadeVertice;
    int quantidadeAresta;
    int grau[MAX_VERTICES];
    int matrizAdjacente[MAX_VERTICES][MAX_VERTICES];
} Grafos;

// função para comparar elementos do vetor grau para ordenacao da funcao qsort
int funcaoComparadora(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

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

int verificacoesPrevias(const Grafos *grafos1, const Grafos *grafo2) {
    if (grafos1->quantidadeVertice != grafo2->quantidadeVertice) {
        return 0;
    }
    if (grafos1->quantidadeAresta != grafo2->quantidadeAresta) {
        return 0;
    }

    int auxGuardarGraus1[MAX_VERTICES], auxGuardarGraus2[MAX_VERTICES];
    int i;
    for (i = 0; i < grafos1->quantidadeVertice; i++) {
        auxGuardarGraus1[i] = grafos1->grau[i];
        auxGuardarGraus2[i] = grafo2->grau[i];
    }

    qsort(auxGuardarGraus1, grafos1->quantidadeVertice, sizeof(int), funcaoComparadora);
    qsort(auxGuardarGraus2, grafo2->quantidadeVertice,  sizeof(int), funcaoComparadora);

    for (i = 0; i < grafos1->quantidadeVertice; i++) {
        if (auxGuardarGraus1[i] != auxGuardarGraus2[i]) {
            return 0;
        }
    }
    return 1;
}


int mapa[MAX_VERTICES];   // mapa[u] = vertice de G2 mapeado para u de G1
int usado[MAX_VERTICES];  // usado[v] = 1 se v de G2 ja foi ocupado

// verifica se mapear u de G1 para v de G2 e compativel com os mapeamentos 
int ehConsistente(const Grafos *grafos1, const Grafos *grafos2, int u, int v) {
    int w;
    for (w = 0; w < grafos1->quantidadeVertice; w++) {
        if (mapa[w] == -1) continue; // w ainda nao foi mapeado, pula
        if (grafos1->matrizAdjacente[u][w] != grafos2->matrizAdjacente[v][mapa[w]]) {
            return 0;
        }
    }
    return 1;
}

// tenta mapear os vertices de G1 a partir da profundidade atual
int backtrack(const Grafos *grafos1, const Grafos *grafos2, int prof) {
    if (prof == grafos1->quantidadeVertice) return 1; // todos mapeados com sucesso

    int v;
    for (v = 0; v < grafos2->quantidadeVertice; v++) {
        if (usado[v]) continue;                                  // ja foi usado
        if (grafos1->grau[prof] != grafos2->grau[v]) continue;  // graus diferentes
        if (ehConsistente(grafos1, grafos2, prof, v)) {
            mapa[prof] = v;   // faz o mapeamento
            usado[v]   = 1;   // marca como ocupado
            if (backtrack(grafos1, grafos2, prof + 1)) return 1;
            mapa[prof] = -1;  // desfaz o mapeamento
            usado[v]   = 0;   // libera o vertice
        }
    }
    return 0;
}

int saoIsomorfos(const Grafos *grafos1, const Grafos *grafos2) {
    int i;
    for (i = 0; i < MAX_VERTICES; i++) {
        mapa[i]  = -1;
        usado[i] =  0;
    }
    return backtrack(grafos1, grafos2, 0);
}


int main() {
    Grafos grafos1, grafos2;

    lerGrafo(&grafos1, 1);
    lerGrafo(&grafos2, 2);

    if (!verificacoesPrevias(&grafos1, &grafos2) || !saoIsomorfos(&grafos1, &grafos2)) {
        printf("\nResultado: NAO sao isomorfos.\n");
    } else {
        printf("\nResultado: SAO isomorfos!\n");
    }

    return 0;
}
