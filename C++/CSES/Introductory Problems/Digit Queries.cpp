// <3
// Tema: CSES / Busqueda por Bloques de Longitud
// Resumen: La cadena infinita 123456789101112... se recorre por BLOQUES segun la cantidad de
// digitos
// Detalle: La cadena infinita 123456789101112... se recorre por BLOQUES segun la cantidad de
// digitos: hay 9 numeros de 1 digito, 90 de 2, 900 de 3, o sea 9*10^(d-1) numeros de d digitos,
// que aportan d*9*10^(d-1) caracteres. Se le resta a k bloque por bloque hasta que quepa, y ahi
// division y modulo dan el numero exacto y la posicion dentro de el. CUANDO USAR: cualquier
// "cual es el k-esimo elemento de esta secuencia infinita" donde la secuencia crece por tramos
// regulares. El patron es siempre el mismo, saltar tramos completos restando su tamano y
// despues aterrizar con division entera y modulo. El while corre a lo sumo 18 veces con k de
// 10^18, asi que no hay que optimizar nada. long long en todo: k llega a 10^18.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;

    while (q--) {
        long long k;
        cin >> k;

        long long digits = 1;
        long long count = 9;
        long long start = 1;

        while (k > digits * count) {
            k -= digits * count;
            digits++;
            count *= 10;
            start *= 10;
        }

        long long num = start + (k - 1) / digits;
        long long pos = (k - 1) % digits;

        string s = to_string(num);

        cout << s[pos] << '\n';
    }
}
