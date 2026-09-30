// <3
// Tema: Simulation / Ad Hoc
// Resuelve "Unraveling Monty Hall": se simulan N juegos del problema de Monty Hall donde el
// jugador siempre elige la puerta 1 y luego siempre cambia a la otra puerta cerrada tras que
// el presentador revela una cabra; dado en que puerta esta el auto en cada juego, hay que
// contar en cuantos de ellos el jugador gana el auto.
// Como el jugador parte de la puerta 1 y el presentador solo puede abrir una puerta con
// cabra entre las dos no elegidas, cambiar de puerta gana el auto exactamente cuando el auto
// esta en la puerta 2 o en la puerta 3; el codigo simplemente cuenta cuantas de las N
// entradas valen 2 o 3 (variable "sum").

#include <iostream>
using namespace std;
int main()
{
    int n; cin >> n;
    int sum = 0;
    while(n--)
    {
        int a; cin >>a;
        if(a==3 or a==2)
        {
            sum++;
        }
    }
    cout << sum << endl;
  //a
    return 0;
}