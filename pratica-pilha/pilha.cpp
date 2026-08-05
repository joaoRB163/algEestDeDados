// pilha.cpp
// Algoritmos e Estruturas de Dados - IFSC
//
// PARTE 1: construir uma pilha DO ZERO, sem usar a std::stack pronta.
// A pilha guarda inteiros num vetor de tamanho fixo.
// LIFO: o ultimo que entra e o primeiro que sai.

#include <iostream>
using namespace std;

const int CAPACIDADE = 5;   // tamanho fixo da pilha

class Pilha {
private:
    int dados[CAPACIDADE];  // os dados ficam neste vetor
    int topo;               // indice do ultimo item (-1 = vazia)

public:
    Pilha() {
        topo = -1;          // comeca vazia
    }

    void empilhar(int valor) {
        if (topo == CAPACIDADE - 1) {
            cout << "Pilha cheia! Nao cabe " << valor << endl;
            return;
        }
        topo++;             // sobe uma posicao
        dados[topo] = valor; // guarda no novo topo
    }

    int desempilhar() {
        if (estaVazia()) {
            cout << "Pilha vazia! Nada para desempilhar." << endl;
            return -1;      // valor de erro
        }
        int valor = dados[topo]; // pega o do topo
        topo--;                  // desce (o item sai)
        return valor;
    }

    int espiar() {
        if (estaVazia()) {
            cout << "Pilha vazia!" << endl;
            return -1;
        }
        return dados[topo];
    }

    bool estaVazia() {
        return topo == -1;
    }

    int tamanho() {
        return topo + 1;
    }

    void mostrar() {
        cout << "Pilha (base -> topo): [";
        for (int i = 0; i <= topo; i++) {
            cout << dados[i];
            if (i < topo) cout << ", ";
        }
        cout << "]" << endl;
    }
};

int main() {
    Pilha p;

    cout << "Vazia no inicio? " << (p.estaVazia() ? "sim" : "nao") << endl;

    cout << "\nEmpilhando 10, 20, 30:" << endl;
    p.empilhar(10);
    p.empilhar(20);
    p.empilhar(30);
    p.mostrar();
    cout << "Tamanho: " << p.tamanho() << endl;
    cout << "Topo (espiar): " << p.espiar() << endl;

    cout << "\nDesempilhando dois:" << endl;
    cout << "saiu: " << p.desempilhar() << endl;
    cout << "saiu: " << p.desempilhar() << endl;
    p.mostrar();

    cout << "\nRepare: saiu 30 e depois 20 - a ordem INVERSA" << endl;
    cout << "da que entrou. Isso e LIFO na pratica." << endl;

    return 0;
}