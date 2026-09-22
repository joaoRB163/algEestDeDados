#include <iostream>
using namespace std;

int main(){
    int numero;

    cout << "Digite um numero Inteiro: ";
    cin >> numero;

    if (numero % 2 == 0){
        cout << "O numero " << numero << " e par" << endl;
    } else{
        cout << "O numero " << numero << " e impar" << endl;
    }
    system("pause"); // Mantem o programa aberto após finalizar os processos
    return 0;
}