#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100

// Função de comparação para ordenar por tamanho
int comparaTamanho(const void *a, const void *b) {
    char *nomeA = *(char **)a;
    char *nomeB = *(char **)b;

    int tamA = strlen(nomeA);
    int tamB = strlen(nomeB);

    // Primeiro compara pelo tamanho
    if (tamA != tamB) {
        return tamA - tamB; // menor tamanho primeiro
    }
    // Se tiverem o mesmo tamanho, ordena alfabeticamente
    return strcmp(nomeA, nomeB);
}

int main() {
    int N;
    char temp[MAX_NOME];

    printf("Digite a quantidade de nomes: ");
    scanf("%d", &N);
    getchar(); // limpar o \n do buffer

    // Aloca um vetor de ponteiros para strings
    char **nomes = (char **)malloc(N * sizeof(char *));
    if (nomes == NULL) {
        printf("Erro de memória.\n");
        return 1;
    }

    // Lê os nomes e aloca dinamicamente cada um
    for (int i = 0; i < N; i++) {
        printf("Digite o nome %d: ", i + 1);
        fgets(temp, MAX_NOME, stdin);
        temp[strcspn(temp, "\n")] = '\0'; // remove \n

        nomes[i] = (char *)malloc((strlen(temp) + 1) * sizeof(char));
        if (nomes[i] == NULL) {
            printf("Erro de memória.\n");
            return 1;
        }
        strcpy(nomes[i], temp);
    }

    // Ordena usando qsort
    qsort(nomes, N, sizeof(char *), comparaTamanho);

    // Exibe os nomes ordenados
    printf("\nNomes ordenados pelo tamanho:\n");
    for (int i = 0; i < N; i++) {
        printf("%s\n", nomes[i]);
        free(nomes[i]); // libera cada string
    }

    free(nomes); // libera o vetor de ponteiros

    return 0;
}