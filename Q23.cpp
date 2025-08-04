/*
TRABALHO COMPUTACIONAL 02 
– 
PESQUISA E ORDENAÇÃO 
Disciplina: C.A.N.A
  Aluno Responsável pela questão:
    - Pedro Henrique Sabi

    Equipe: 
    - Jéssica Carvalho e Silva
    - Allyson Keveny Medeiros Félix
    - João Lucas de Albuquerque Gabriel
    - Pedro Henrique Silveira Gomes Sabi 
    - Francisco Wellesson Bezerra da Silva
*/

//QUESTÃO 23 
//Implemente em C/C++ os algoritmos de busca sequencial e binária para listas duplamente encadeadas

#include <iostream> 
#include <utility>  

//Estrutura do nó da Lista Duplamente Encadeada
struct No {
    int valor;    
    No* anterior; 
    No* proximo;  

    // Construtor de um novo nó com valor
    No(int val) {
        valor = val;
        anterior = nullptr; 
        proximo = nullptr;  
    }
};

//gerencia a colecao de nos, permitindo operacoes como insercao, impressao e busca
class ListaDupla {
public:
    No* inicio; 
    No* fim;    

    //inicializa a lista vazia
    ListaDupla() {
        inicio = nullptr;
        fim = nullptr;
    }

    //destrutor: libera toda a memoria alocada
    ~ListaDupla() {
        No* atual = inicio; 
        while (atual != nullptr) { //enquanto houver nós na lista
            No* proximoNo = atual->proximo; //salva o ponteiro para o proximo nó
            delete atual;                   //libera a memoria do nó atual
            atual = proximoNo;              //move para o proximo nó a ser liberado
        }
        inicio = nullptr; 
        fim = nullptr;    
    }

    //Insere um novo valor no final da lista
    void inserir(int val) {
        No* novo = new No(val); //cria um novo no com o valor forneciddo
        if (!inicio) {          //se a lista estiver vazia, o novo nó e tanto o inicio quanto o fim da lista
            inicio = fim = novo; 
        } else {                 // Se a lista ja tem nós
            fim->proximo = novo;   //o ultimo aponta pro novo nó
            novo->anterior = fim;  //o novo nó aponta pro último nó
            fim = novo;            //o novo fim é o novo nó 
        }
    }

    // Imprime todos os valores 
    void imprimir() {
        No* atual = inicio; 
        if (atual == nullptr) { 
            std::cout << "Lista vazia." << std::endl;
            return;
        }
        std::cout << "Elementos da Lista: ";
        while (atual != nullptr) { 
            std::cout << atual->valor << " "; 
            atual = atual->proximo;           
        }
        std::cout << std::endl;
    }

    //Busca Sequencial:percorre a lista nó por nó, procurando um valor específico
    std::pair<No*, int> buscaSequencial(int alvo) {
        No* atual = inicio; 
        int iteracoes = 0;  
        while (atual != nullptr) { 
            iteracoes++;           
            if (atual->valor == alvo) { 
                return {atual, iteracoes}; //se achar o valor retorna o ponteiro e a contagem
            }
            atual = atual->proximo; //passa para o proximo nó
        }
        return {nullptr, iteracoes}; //Se o alvo nao for encontrado, retorna null e as iterações
    }

    // Função Auxiliar para Busca Binária: busca o nó do meio
    std::pair<No*, int> encontrarMeio(No* inicioSegmento, No* fimSegmento) {
        if (!inicioSegmento) return {nullptr, 0}; //se o segmento e vazio, nao tem meio

        No* lento = inicioSegmento;  
        No* rapido = inicioSegmento; 
        int iteracoes = 0;           // Contador de iteracoes para encontrar o meio.

        while (rapido != fimSegmento && rapido->proximo != fimSegmento) {
            rapido = rapido->proximo;
            if (rapido != fimSegmento) { // Garante que o rapido nao passe do fim ao dar o segundo passo.
                rapido = rapido->proximo;
            }
            lento = lento->proximo; 
            iteracoes++;            
        }
        return {lento, iteracoes}; // Retorna o nó do meio e a contagem de iterações
    }

    //Busca Binaria:Procura um valor alvo em um segmento ordenado da lista duplamente encadeada.
    std::pair<No*, int> buscaBinaria(No* inicioSegmento, No* fimSegmento, int alvo) {//a função já assume que a lista ordenada
        return buscaBinariaHelper(inicioSegmento, fimSegmento, alvo, 0); // Chama a funcao auxiliar com contador inicial.
    }

private:    
    std::pair<No*, int> buscaBinariaHelper(No* inicioSegmento, No* fimSegmento, int alvo, int iteracoesAcumuladas) {
        // Caso Base 1: Segmento e vazio ou invalido (inicio passou do fim)
        // Isso indica que o alvo nao esta no segmento
        if (!inicioSegmento || inicioSegmento == fimSegmento->proximo) {
            return {nullptr, iteracoesAcumuladas};
        }

        //encontra o no do meio no segmento atual, e pega suas iteracoes internas
        std::pair<No*, int> meioResultado = encontrarMeio(inicioSegmento, fimSegmento);
        No* meio = meioResultado.first;
        iteracoesAcumuladas += meioResultado.second; //add as iteracoes de 'encontrarMeio'

        // Caso Base 2: Se 'meio' for nulo (nao deveria ocorrer se 'inicioSegmento' nao for nulo).
        if (!meio) return {nullptr, iteracoesAcumuladas};

        iteracoesAcumuladas++; // Incrementa para a comparacao do valor do meio.
        // Se o valor no meio é o alvo, encontramos!
        if (meio->valor == alvo) {
            return {meio, iteracoesAcumuladas};
        } else if (meio->valor < alvo) {
            // Se o valor do meio for menor que o alvo, o alvo deve estar na metade direita do segmento.
            // A busca continua do no seguinte ao meio ate o fim do segmento.
            return buscaBinariaHelper(meio->proximo, fimSegmento, alvo, iteracoesAcumuladas);
        } else { // (meio->valor > alvo)
            // Se o valor do meio for maior que o alvo, o alvo deve estar na metade esquerda do segmento.
            // A busca continua do inicio do segmento ate o no anterior ao meio.
            return buscaBinariaHelper(inicioSegmento, meio->anterior, alvo, iteracoesAcumuladas);
        }
    }
};

int main() {
    ListaDupla lista;

    for (int i = 1; i <= 1000; ++i) {
        lista.inserir(i);     // Popula a lista 
    }

    int alvo_buscado; 

    std::cout << "\n--- Teste de Busca na Lista Duplamente Encadeada ---" << std::endl;
    std::cout << "\nDigite o valor alvo (entre 1 e 1.000): ";
    std::cin >> alvo_buscado; //Pede o Valor Alvo Para o Usuário

    auto resultadoSeq = lista.buscaSequencial(alvo_buscado);
    if (resultadoSeq.first) {
        std::cout << "\n\nBusca Sequencial: Valor Encontrado:  " << resultadoSeq.first->valor
                  << ". QTD Iteracoes: " << resultadoSeq.second << std::endl;
    } else {
        std::cout << "\n\nBusca Sequencial: Valor Encontrado:  " << alvo_buscado << " nao encontrado."
                  << " QTD Iteracoes: " << resultadoSeq.second << std::endl;
    }

    auto resultadoBin = lista.buscaBinaria(lista.inicio, lista.fim, alvo_buscado);
    if (resultadoBin.first) {
        std::cout << "\n\nBusca Binaria: Valor Encontrado:  " << resultadoBin.first->valor
                  << ". QTD Iteracoes: " << resultadoBin.second << std::endl;
    } else {
        std::cout << "\n\nBusca Binaria: Valor " << alvo_buscado << " nao encontrado."
                  << " QTD Iteracoes: " << resultadoBin.second << std::endl;
    }

    return 0;
}