// <3
// Tema: Number Theory / Modulo de un Binario Gigante
// Resuelve "Binary Dozens" (problema B, ICPC 2025): dado un numero en binario de hasta 500 bits,
// dar su resto al dividir por 12.
// 500 bits son numeros de hasta 10^150, asi que no hay tipo entero que los guarde. Pero el resto
// si se puede calcular leyendo los digitos de izquierda a derecha con el metodo de Horner: si el
// numero visto hasta ahora vale v, agregarle un bit b lo convierte en 2v + b, y tomando modulo en
// cada paso el acumulador nunca pasa de 24.
//     rem = (rem * 2 + bit) % 12
// Funciona porque el modulo es compatible con sumas y productos: se puede reducir en cada paso en
// vez de al final. La misma idea sirve para cualquier base y cualquier modulo, no solo binario y
// 12, y es la forma estandar de sacar el resto de un numero que llega como cadena.
// Que 12 no sea primo da igual: esto no usa inversos ni nada por el estilo.
// Verificado contra los enteros exactos de Python en 3004 cadenas, incluidas las de 500 bits todos
// en 1 y todos en 0.
// El archivo B - Binary Dozens.py de esta carpeta hace lo mismo aprovechando que Python tiene
// enteros de precision arbitraria: int(b, 2) % 12. Vale tenerlo presente cuando el problema sea
// justamente de numeros gigantes y el lenguaje este permitido.

#include <bits/stdc++.h>
using namespace std;

int main() {
    string b;

    while (cin >> b && b != "*") {

        int rem = 0;

        for (char c : b) {
            rem = (rem * 2 + (c - '0')) % 12;
        }

        cout << rem << '\n';
    }

    return 0;
}
