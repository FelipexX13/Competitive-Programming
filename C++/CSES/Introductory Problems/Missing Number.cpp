// <3
// Tema: CSES / Suma de Gauss
// Resumen: La suma de 1..n se sabe de formula, n*(n+1)/2
// O: (n), suma de Gauss menos la suma real
// Detalle: La suma de 1..n se sabe de formula, n*(n+1)/2, asi que el que falta es esa suma
// menos la suma de lo que llego. Una sola pasada, memoria O(1), sin ordenar nada. OJO CON EL
// TIPO: con n = 2*10^5 la suma pasa de 2*10^10, o sea que int se desborda. long long.
// ALTERNATIVA QUE EVITA EL PROBLEMA: hacer XOR de 1..n con XOR de la entrada. Los repetidos se
// cancelan y queda el que falta, sin sumas grandes y sin riesgo de desbordar. Vale tenerla
// presente cuando n sea tan grande que hasta long long apriete. CUANDO USAR ESTE PATRON: "falta
// exactamente uno", "hay exactamente uno repetido". La idea es comparar contra el total que
// DEBERIA haber.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n; cin >> n;
    long long god = 1;
    long long pre = 0;
    for(int i = 0 ; i < n - 1 ; i++)
    {
        god += i +2;
        long long a;
        cin >> a;
        pre += a;
    }
    cout << god-pre << endl;

    return 0;
}
