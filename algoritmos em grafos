//atividade: Entrar dois grafos e verificar se são isomorfos 
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 5 //usando de EX. casos de uso atividade

typedef struct {
    int quantidadeVertice;
    int quantidadeAresta;
    int grau[MAX_VERTICES]; //vetor para ordenar os graus de n vertirces
    int matrizAdjacente[MAX_VERTICES][MAX_VERTICES];
}Grafos;

//função para comparar elementos do vetor grau para ordenaçao da funcao qsort
int funcaoComparadora( const void *a, const void *b){
    return (*(int *) a - *(int*) b);
}

int verificacoesPrevias (const Grafos *grafos1, const  Grafos *grafo2){
        if(grafos1->quantidadeVertice != grafo2->quantidadeVertice) {
        printf("Grafos nao sao isomorfos!\n");
        return 0;
    }

    if(grafos1->quantidadeAresta != grafo2->quantidadeAresta) {
        printf("Grafos nao sao isomorfos!\n");
        return 0;
    }

    int auxGuardarGraus1[MAX_VERTICES], auxGurdarGraus2[MAX_VERTICES];
    int 1;
    for (i = 0; i <grafos1->quantidadeVertice; i++){
        auxGuardarGraus1[i] = grafos1->grau[i];
        auxGurdarGraus2[i] = grafo2->grau[i];
    }

    qsort (auxGuardarGraus1,grafos1->quantidadeVertice sizeof(int), int funcaoComparadora);
    qsort (auxGuardarGraus1,grafo2->quantidadeVertice sizeof(int), int funcaoComparadora);
    for (i = 0; grafos1-.quantidadeVertice; i++)
        if (auxGuardarGraus1[i] != auxGurdarGraus2[1]) 
        return 0;
}



int main (){

    

    return 0;
}
