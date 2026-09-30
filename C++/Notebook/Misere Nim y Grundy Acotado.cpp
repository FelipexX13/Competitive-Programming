// <3
// Tema: Game Theory / Misere Nim y Grundy Acotado
// O: (n) misere_nim, (1) grundy_bounded
// Uso: misere_nim(pilas) -> gana el primero?; grundy_bounded(n,k) = n % (k+1)
// Dos variantes del Nim que NO se resuelven con el XOR normal (ese caso ya esta cubierto en
// "Marbles" con Sprague-Grundy). Misere Nim invierte la condicion de victoria: pierde quien
// hace el ultimo movimiento, y la regla cambia solo en el caso degenerado en que todos los
// montones valen 1, donde gana el primero si la cantidad de montones es par; en cualquier
// otro caso se aplica el XOR de siempre.
// Grundy acotado es el atajo para cuando se pueden quitar entre 1 y k piedras: el numero de
// Grundy resulta ser exactamente n % (k+1), asi que no hace falta calcular el mex, y se
// pierde justo cuando n es multiplo de k+1.

#include <bits/stdc++.h>

using namespace std;

// devuelve true si gana el primer jugador (pierde quien mueve al final)
bool misere_nim(vector<int> a)
{
    bool all_ones = all_of(a.begin(), a.end(), [](int x){ return x == 1; });
    int xorsum = 0;
    for (int v : a) xorsum ^= v;

    if (all_ones)
    {
        return (a.size() % 2 == 0);
    }
    return (xorsum != 0);
}

// se pueden quitar entre 1 y k piedras: Grundy(n) = n % (k+1)
int grundy_bounded(int n, int k)
{
    return n % (k + 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> pilas(n);
    for (int i = 0; i < n; i++) cin >> pilas[i];

    cout << (misere_nim(pilas) ? "First" : "Second") << "\n";

    // en la version acotada, la suma de subjuegos sigue siendo el XOR de los Grundy
    int total = 0;
    for (int x : pilas) total ^= grundy_bounded(x, k);
    cout << (total ? "First" : "Second") << "\n";

    return 0;
}
