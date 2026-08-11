
#include <iostream>
#include <thread>
#include <vector>
#include <string>

using namespace std;

struct No {
    string dado;
    No* proximo;

    No(string d) : dado(d), proximo(nullptr) {}
};

class ListaInsegura {
private:
    No* inicio = nullptr;
    int tamanho = 0;

public:

    void inserir(string dado) {
        No* novo = new No(dado);

        // 1. Lê o início atual
        No* antigoInicio = inicio;

        // Aumenta a janela da condição de corrida
        this_thread::yield();

        // 2. Escreve o novo início
        novo->proximo = antigoInicio;
        inicio = novo;

        // Incrementa o contador
        tamanho++;
    }

    int getTamanho() {
        return tamanho;
    }

    // Percorre a lista e conta os nós existentes
    int contarDeVerdade() {
        int c = 0;

        No* a = inicio;

        while (a != nullptr) {
            c++;
            a = a->proximo;
        }

        return c;
    }
};

int main() {

    const int THREADS = 4;
    const int INSERCOES = 2000;

    ListaInsegura lista;

    vector<thread> ts;

    // Cria as threads
    for (int i = 0; i < THREADS; i++) {

        ts.push_back(
            thread([&lista, i, INSERCOES]() {

                for (int j = 0; j < INSERCOES; j++) {

                    lista.inserir(
                        "T" +
                        to_string(i) +
                        "-" +
                        to_string(j)
                    );
                }
            })
        );
    }

    // Espera todas as threads terminarem
    for (auto& t : ts) {
        t.join();
    }

    int esperado = THREADS * INSERCOES;

    cout << "Esperado : "
         << esperado << endl;

    cout << "Contador tamanho : "
         << lista.getTamanho() << endl;

    cout << "Contando os nos : "
         << lista.contarDeVerdade() << endl;

    cout << "Nos PERDIDOS : "
         << (esperado - lista.contarDeVerdade())
         << endl;

    return 0;
}