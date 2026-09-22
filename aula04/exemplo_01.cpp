#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// 1. VETOR: push_back total
void testeVetor(int N)
{
    int *v = new int[N];
    int tam = 0;

    auto t0 = high_resolution_clock::now();
    for (int i = 0; i < N; i++)
        v[tam++] = i;
    auto t1 = high_resolution_clock::now();

    long us = duration_cast<microseconds>(t1 - t0).count();
    cout << " vetor push_back: " << us << " us (ult=" << v[tam - 1] << ")\n";
    delete[] v;
}

// 2. PILHA: push + pop
int pilha[10000000];
int topo = 0;
void testePilha(int N)
{
    topo = 0;
    auto t0 = high_resolution_clock::now();
    for (int i = 0; i < N; i++)
        pilha[topo++] = i;
    for (int i = 0; i < N; i++)
        topo--;
    auto t1 = high_resolution_clock::now();

    long us = duration_cast<microseconds>(t1 - t0).count();
    cout << " pilha push+pop: " << us << " us\n";
}

// 3. FILA: enfileirar + desenfileirar
int fila[10000000];
void testeFila(int N)
{
    int ini = 0, fim = 0, tam = 0;
    auto t0 = high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        fila[fim] = i;
        fim = (fim + 1) % 10000000;
        tam++;
        for (int i = 0; i < N; i++)
        {
            ini = (ini + 1) % 10000000;
            tam--;
        }
    }
    auto t1 = high_resolution_clock::now();

    long us = duration_cast<microseconds>(t1 - t0).count();
    cout << " fila enfileirar+desenfileirar: " << us << " us\n";
}
//   4. LISTA : push_back + acessar(ultimo)
struct No
{
    int valor;
    No *prox;
};
void testeLista(int N)
{
    No *cabeca = nullptr;
    No *cauda = nullptr;

    auto t0 = high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        No *novo = new No{i, nullptr};
        if (!cabeca)
            cabeca = cauda = novo;
        else
        {
            cauda->prox = novo;
            cauda = novo;
        }
    }

    auto t1 = high_resolution_clock::now();

    No *p = cabeca;
    while (p->prox)
        p = p->prox;
    int ult = p->valor;
    auto t2 = high_resolution_clock::now();

    long us1 = duration_cast<microseconds>(t1 - t0).count();
    long us2 = duration_cast<microseconds>(t2 - t1).count();
    cout << " lista push_back: " << us1 << " us"
         << " acessar(ultimo): " << us2 << " us (ult=" << ult << ")\n";

    while (cabeca)
    {
        No *t = cabeca;
        cabeca = cabeca->prox;
        delete t;
    }
}

// 5. BUSCA: linear us binaria
int buscaLinear(int *v, int n, int alvo)
{
    for (int i = 0; i < n; i++)
        if (v[i] == alvo)
            return i;
    return -1;
}

int buscaBinaria(int *v, int n, int alvo)
{
    int e = 0, d = n - 1;
    while (e <= d)
    {
        int m = (e + d) / 2;
        if (v[m] == alvo)
            return m;
        if (v[m] < alvo)
            e = m + 1;
        else
            d = m - 1;
    }
    return -1;
}

void testeBusca(int N)
{
    int *v = new int[N];
    for (int i = 0; i < N; i++)
        v[i] = i;
    int alvo = N - 1;

    auto t0 = high_resolution_clock::now();
    int r1 = buscaLinear(v, N, alvo);
    auto t1 = high_resolution_clock::now();

    auto t2 = high_resolution_clock::now();
    int r2 = buscaBinaria(v, N, alvo);
    auto t3 = high_resolution_clock::now();

    long us1 = duration_cast<microseconds>(t1 - t0).count();
    long us2 = duration_cast<microseconds>(t3 - t2).count();
    cout << " busca linear: " << us1 << " us (r=" << r1 << ")"
         << " binaria: " << us2 << " us (r=" << r2 << ")\n";

    delete[] v;
}

// 6. ORDENACAO: bubble us merge
void bubbleSort(int *v, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (v[j] > v[j + 1])
            {
                int t = v[j];
                v[j] = v[j + 1];
                v[j + 1] = t;
            }
}

void merge(int *v, int *aux, int e, int m, int d)
{
    int i = e, j = m + 1, k = e;
    while (i <= m && j <= d)
        aux[k++] = (v[i] <= v[j]) ? v[i++] : v[j++];
    while (i <= m)
        aux[k++] = v[i++];
    while (j <= d)
        aux[k++] = v[j++];
    for (int t = e; t <= d; t++)
        v[t] = aux[t];
}

void mergeSort(int *v, int *aux, int e, int d)
{
    if (e >= d)
        return;
    int m = (e + d) / 2;
    mergeSort(v, aux, e, m);
    mergeSort(v, aux, m + 1, d);
    merge(v, aux, e, m, d);
}

void testeOrdenacao(int N)
{
    int *a = new int[N];
    int *b = new int[N];
    for (int i = 0; i < N; i++)
    {
        int r = rand();
        a[i] = r;
        b[i] = r;
    }

    auto t0 = high_resolution_clock::now();
    bubbleSort(a, N);
    auto t1 = high_resolution_clock::now();

    int *aux = new int[N];
    auto t2 = high_resolution_clock::now();
    mergeSort(b, aux, 0, N - 1);
    auto t3 = high_resolution_clock::now();

    long us1 = duration_cast<microseconds>(t1 - t0).count();
    long us2 = duration_cast<microseconds>(t3 - t2).count();
    cout << " bubble: " << us1 << " us (a0=" << a[0] << ")"
         << " merge: " << us2 << " us (b0=" << b[0] << ")\n";
}

// MAIN: roda tudo para cada N
int main()
{
    srand(42);
    int Ns[] = {1000, 10000, 100000, 1000000};
    int tam = 4;
    cout << "============ordenacao=============\n";
    for (int k = 0; k < tam; k++)
    {
        int N = Ns[k];
        cout << " === N =" << N << " === \n";
        if (N <= 100000)testeOrdenacao(N);
        cout << "\n";
    }

    cout << "============vetor=============\n";
    for (int k = 0; k < tam; k++)
    {
        int N = Ns[k];
        cout << " === N =" << N << " === \n";
        testeVetor(N);
        cout << "\n";
    }

    cout << "============pilha=============\n";
    for (int k = 0; k < tam; k++)
    {
        int N = Ns[k];
        cout << " === N =" << N << " === \n";
        testePilha(N);
        cout << "\n";
    }

    cout << "============fila=============\n";
    for (int k = 0; k < tam; k++)
    {
        int N = Ns[k];
        cout << " === N =" << N << " === \n";
        if (N <= 100000)testeFila(N);
        cout << "\n";
    }
    cout << "============lista=============\n";
    for (int k = 0; k < tam; k++)
    {
        int N = Ns[k];
        cout << " === N =" << N << " === \n";
        testeLista(N);
        cout << "\n";
    }
    cout << "============busca=============\n";
    for (int k = 0; k < tam; k++)
    {
        int N = Ns[k];
        cout << " === N =" << N << " === \n";
        testeBusca(N);
        cout << "\n";
    }

    return 0;
}