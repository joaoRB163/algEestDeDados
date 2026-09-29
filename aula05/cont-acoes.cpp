#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
long ops = 0; // contador global: cada ops++ marca um passo do trabalho principal

// ---------- Caixa A ----------
// Insere N elementos, sempre na posicao 0. O vetor ja tem espaco (nao conta).
void caixaA(int N)
{
    vector<int> v(N + 1);
    int tam = 0;
    for (int x = 0; x < N; x++)
    {
        for (int i = tam; i > 0; i--)
        {
            ops++;
            v[i] = v[i - 1];
        }
        v[0] = x;
        tam++;
    }
}

// ---------- Caixa B ----------
// Le uma posicao qualquer do vetor. O preenchimento e preparacao.
void caixaB(int N)
{
    vector<int> v(N, 7);
    int k = N / 2;
    ops++;
    int x = v[k];
}

// ---------- Caixa C ----------
// Procura o ultimo valor de um vetor ja ordenado. O preenchimento e preparacao.
void caixaC(int N)
{
    vector<int> v(N);
    for (int i = 0; i < N; i++)
        v[i] = i;
    int alvo = N - 1, e = 0, d = N - 1;
    while (e <= d)
    {
        ops++;
        int m = (e + d) / 2;
        if (v[m] == alvo)
            break;
        if (v[m] < alvo)
            e = m + 1;
        else
            d = m - 1;
    }
}

// ---------- Caixa D ----------
// Tira o primeiro elemento de uma fila guardada em vetor. O preenchimento e preparacao.
void caixaD(int N)
{
    vector<int> fila(N);
    for (int i = 0; i < N; i++)
        fila[i] = i;
    int tam = N;
    int x = fila[0];
    for (int i = 1; i < tam; i++)
    {
        ops++;
        fila[i - 1] = fila[i];
    }
    tam--;
    if (x < 0)
        cout << x;
}

// ---------- Caixa E ----------
// Soma todos os elementos e depois procura o maior. O preenchimento e preparacao.
void caixaE(int N)
{
    vector<int> v(N);
    for (int i = 0; i < N; i++)
        v[i] = i;
    long soma = 0;
    int maior = v[0];
    for (int i = 0; i < N; i++)
    {
        ops++;
        soma += v[i];
    }
    for (int i = 0; i < N; i++)
    {
        ops++;
        if (v[i] > maior)
            maior = v[i];
    }
    if (soma < 0 || maior < 0)
        cout << soma;
}

// ---------- Caixa F ----------
// Empilha um valor e desempilha em seguida. O vetor ja existe (preparacao).
void caixaF(int N) {
 vector<int> pilha(N + 1);
 int topo = 0;
 ops++; pilha[topo++] = 42;
 ops++; int x = pilha[--topo];
 if (x < 0) cout << x;
}

// ---------- Caixa G ----------
// Acrescenta N elementos, alocando um vetor novo (1 posicao maior) a cada vez.
void caixaG(int N)
{
    int *dados = new int[0];
    int cap = 0;
    for (int x = 0; x < N; x++)
    {
        int *novo = new int[cap + 1];
        for (int k = 0; k < cap; k++)
        {
            ops++;
            novo[k] = dados[k];
        }
        novo[cap] = x;
        delete[] dados;
        dados = novo;
        cap++;
    }
    delete[] dados;
}

// ---------- Caixa H ----------
// Chega ao ultimo no de uma lista encadeada. A montagem da lista e preparacao.
struct No
{
    int valor;
    No *prox;
};
void caixaH(int N)
{
    No *cab = nullptr;
    for (int i = 0; i < N; i++)
        cab = new No{i, cab};
    No *p = cab;
    while (p->prox)
    {
        ops++;
        p = p->prox;
    }
    int ult = p->valor;
    while (cab)
    {
        No *t = cab;
        cab = cab->prox;
        delete t;
    }
    if (ult < 0)
        cout << ult;
}

// ---------- Caixa I ----------
// Tira o primeiro elemento de uma fila circular. O vetor ja existe (preparacao).
void caixaI(int N)
{
    vector<int> fila(N);
    for (int i = 0; i < N; i++)
        fila[i] = i;
    int ini = 0, tam = N;
    ops++;
    int x = fila[ini];
    ini = (ini + 1) % N;
    tam--;
    if (x < 0)
        cout << x;
}

// ---------- Caixa J ----------
// Procura o ultimo valor em um vetor sem ordem. O preenchimento e preparacao.
void caixaJ(int N)
{
    vector<int> v(N);
    for (int i = 0; i < N; i++)
        v[i] = i;
    int alvo = N - 1;
    for (int i = 0; i < N; i++)
    {
        ops++;
        if (v[i] == alvo)
            break;
    }
}

// ---------- Caixa K ----------
// Acrescenta N elementos; quando o vetor enche, aloca outro com o dobro do tamanho.
void caixaK(int N)
{
    int cap = 1, tam = 0;
    int *dados = new int[cap];
    for (int x = 0; x < N; x++)
    {
        if (tam == cap)
        {
            int *novo = new int[cap * 2];
            for (int k = 0; k < tam; k++)
            {
                ops++;
                novo[k] = dados[k];
            }
            delete[] dados;
            dados = novo;
            cap *= 2;
        }
        dados[tam++] = x;
    }
    delete[] dados;
}

// ---------- MAIN: roda todas as caixas para cada N ----------
int main()
{
    int Ns[] = {10, 100, 1000, 10000};
    void (*caixas[])(int) = {caixaA, caixaB, caixaC, caixaD, caixaE, caixaF,
                             caixaG, caixaH, caixaI, caixaJ, caixaK};
    cout << "caixa N=10 N=100 N=1000 N=10000\n";
    for (int c = 0; c < 11; c++)
    {
        cout << " " << char('A' + c) << " ";
        for (int k = 0; k < 4; k++)
        {
            ops = 0; // zera antes de cada execucao
            caixas[c](Ns[k]);
            cout << setw(9) << ops;
        }
        cout << "\n";
    }
    return 0;
}