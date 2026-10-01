// <3
// Tema: Dynamic Programming / DP sobre Intervalos con Bandera de Inversion
// Resumen: Decidir si una cadena es un virus segun la gramatica phi
// Detalle: Resuelve "Arctic Virus" (problema A, ICPC 2024): decidir si una cadena es un virus
// segun la gramatica phi ::= A | T | phiC | A phi | A phi^-1 | G phi^-1 C, donde phi^-1 es phi
// al reves. Responde simple (la cadena es A o T), mutation (es virus y mide 2 o mas) o doomed.
// OJO CON EL LARGO 1: solo A y T son "simple". Una C o una G sola no la genera ninguna regla y
// es doomed. La primera version imprimia simple para cualquier letra sola; verificada la
// corregida contra el lenguaje generado desde la gramatica, en todas las cadenas de largo 1 a
// 8. Las reglas se deshacen de afuera hacia adentro: mirando la primera y la ultima letra se
// sabe que regla pudo haber sido la ultima, se quita lo que agrego, y se sigue con lo de
// adentro. EL TRUCO ES NO INVERTIR NUNCA LA CADENA. Dos de las reglas dejan el interior al
// reves, y copiar e invertir substrings seria caro y ademas daria estados imposibles de
// memoizar. En vez de eso el estado es (l, r, rev): el substring s[l..r], leido al derecho o al
// reves segun la bandera. Invertir es solo cambiar la bandera, y rev decide cual extremo es el
// "primero" y cual el "ultimo". Asi todos los estados posibles son O(n^2 * 2), cada uno con
// trabajo O(1). La memo va en un arreglo memo[l][r][rev] con -1 para "sin calcular". La primera
// version usaba map<tuple>, y con n = 1000 costaba entre 230 y 440 ms por caso; con varios
// casos grandes en la misma entrada eso ya arriesga el limite de tiempo. CUANDO USAR ESTE
// ESTADO: cualquier gramatica o juego sobre una cadena donde las operaciones quitan letras de
// las puntas; y la bandera de inversion en particular siempre que una operacion "de la vuelta"
// a la cadena.

#include <bits/stdc++.h>
using namespace std;

string s;
int n;

// memo[l][r][rev]: -1 = sin calcular, 0 = no, 1 = si. Un arreglo en vez de
// map<tuple>: con n = 1000 el map costaba cientos de ms por caso.
signed char memo[1001][1001][2];

bool solve(int l, int r, bool rev) {
    if (l > r) return false;

    signed char &res = memo[l][r][rev];

    if (res != -1)
        return res;

    int len = r - l + 1;

    // Llegamos a una configuracion simple
    if (len == 1) {
        char c = rev ? s[r] : s[l];
        res = (c == 'A' || c == 'T');
        return res;
    }

    // Obtener extremos de la cadena actual
    char first = rev ? s[r] : s[l];
    char last  = rev ? s[l] : s[r];

    bool ans = false;

    // phiC
    // Si termina en C, quitamos el ultimo caracter
    if (last == 'C') {
        if (!rev)
            ans |= solve(l, r - 1, false);
        else
            ans |= solve(l + 1, r, true);
    }

    // Aphi
    // Si comienza en A, quitamos el primero
    if (first == 'A') {
        if (!rev)
            ans |= solve(l + 1, r, false);
        else
            ans |= solve(l, r - 1, true);
    }

    // Aphi^-1
    // Quitamos A del inicio y luego invertimos
    if (first == 'A') {
        if (!rev)
            ans |= solve(l + 1, r, true);
        else
            ans |= solve(l, r - 1, false);
    }

    // Gphi^-1C
    // Debe comenzar en G y terminar en C
    if (first == 'G' && last == 'C' && len >= 3) {
        if (!rev)
            ans |= solve(l + 1, r - 1, true);
        else
            ans |= solve(l + 1, r - 1, false);
    }

    res = ans;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> s) {

        for (int l = 0; l < n; l++)
            for (int r = 0; r < n; r++)
                memo[l][r][0] = memo[l][r][1] = -1;

        // Largo 1: solo A y T son la etapa simple; C y G no son virus.
        if (n == 1) {
            if (s[0] == 'A' || s[0] == 'T')
                cout << "simple\n";
            else
                cout << "doomed\n";
        }
        else {
            bool ok = solve(0, n - 1, false);

            cout << (ok ? "mutation\n" : "doomed\n");
        }
    }

    return 0;
}
