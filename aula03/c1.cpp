#include <iostream>
using namespace std;

int main (){
    float base, altura, area;
    // entrada
    cout << "Informe a altura: "; // Operador "<<" para enviar os dados para a tela
    //saída 
    cin >> altura; // Operador ">>" para receber dados digitados e salvar na variável
    cout << "Informe a base: ";
    cin >> base;

    area = base * altura;
    
    cout << "Area: " << area;

        return 0;
}