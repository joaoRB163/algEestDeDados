#include <iostream>
using namespace std;

int main(){
    float notas[3], media = 0;

    for (int i = 0; i < 3; i++)
    {
        cout << "Insira a nota " << i+1 << ": " ;
        cin >> notas[i];
    }
    for (int i = 0; i < 3; i++)
    {
        media = media + notas[i];
    }
    media = media/3;
    if (media >= 7)
    {
        cout << "Media: " << media << " Aprovada!";
    } else
    {
        cout << "Media: " << media << " Reprovado!";
    }
    return 0;
}