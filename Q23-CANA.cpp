/*
  Trabalho de Estrutura de Dados
  Alunos:
    - Pedro Henrique Sabi
    - Nome do colega 2
    - Nome do colega 3
*/

#include <iostream>
using namespace std;

// Estrutura do no da lista duplamente encadeada
// Cada elemento da lista é representado por um nó.
struct No {
    int valor;
    No* anterior;
    No* proximo;

    No(int val) {
        valor = val;
        anterior = nullptr;
        proximo = nullptr;
    }
};

// Classe da lista duplamente encadeada
class ListaDupla {
public:
    No* inicio;
    No* fim;

    //CONSTRUTOR: Inicializa a lista como vazia
    ListaDupla() {
        inicio = nullptr;
        fim = nullptr;
    }

    //DESTRUTOR: Libera memoria alocada
    ~ListaDupla() {
        No* atual = inicio;
        while (atual != nullptr) {
            No* proximo = atual->proximo;
            delete atual;
            atual = proximo;
        }
        inicio = nullptr;
        fim = nullptr;
    }

    // cria um novo nó
    //se estiver vazia, vira o início e se já tiver elementos, vai para o fim 
    void inserir(int val) {
        No* novo = new No(val);
        if (!inicio) {
            inicio = fim = novo;
        } else {
            fim->proximo = novo;
            novo->anterior = fim;
            fim = novo;
        }
    }
    //perccore toda a lista printando cada item 
    void imprimir() {
        No* atual = inicio;
        while (atual != nullptr) {
            cout << atual->valor << " ";
            atual = atual->proximo;
        }
        cout << endl;
    }

    // Busca sequencial
    No* buscaSequencial(int alvo) {
        No* atual = inicio;
        while (atual != nullptr) {
            if (atual->valor == alvo)
                return atual;
            atual = atual->proximo;
        }
        return nullptr;
    }

    // Funcao auxiliar para encontrar o meio
    No* encontrarMeio(No* inicio, No* fim) {
        if (!inicio) return nullptr;

        No* lento = inicio;
        No* rapido = inicio;

        while (rapido != fim && rapido->proximo != fim) {
            rapido = rapido->proximo;
            if (rapido != fim)
                rapido = rapido->proximo;
            lento = lento->proximo;
        }
        return lento;
    }

    // Busca binaria recursiva
    No* buscaBinaria(No* inicio, No* fim, int alvo) {
        if (!inicio || inicio == fim->proximo) return nullptr;

        No* meio = encontrarMeio(inicio, fim);

        if (!meio) return nullptr;

        if (meio->valor == alvo)
            return meio;
        else if (meio->valor < alvo)
            return buscaBinaria(meio->proximo, fim, alvo);
        else
            return buscaBinaria(inicio, meio->anterior, alvo);
    }
};

// Funcao principal para testar
int main() {
    ListaDupla lista;

    // Inserir elementos ordenados para permitir busca binaria
    for(int i = 0; i < 101; i++)
    {
        lista.inserir(i);
    }
    

    cout << "Lista: ";
    lista.imprimir();

    cout << "Insira um valor de 1 a 100 para ser o alvo: ";
    int alvo;
    cin >> alvo;

    // Teste de busca sequencial
    No* resultadoSeq = lista.buscaSequencial(alvo);
    if (resultadoSeq)
        cout << "Busca sequencial: Encontrado " << resultadoSeq->valor << endl;
    else
        cout << "Busca sequencial: Nao encontrado\n";

    // Teste de busca binaria
    No* resultadoBin = lista.buscaBinaria(lista.inicio, lista.fim, alvo);
    if (resultadoBin)
        cout << "Busca binaria: Encontrado " << resultadoBin->valor << endl;
    else
        cout << "Busca binaria: Nao encontrado\n";

    return 0;
}
