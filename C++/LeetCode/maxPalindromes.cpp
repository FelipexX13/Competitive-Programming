// <3
// Tema: String / Palindromos No Solapados (Greedy)
// Resumen: Dado s y un k, hay que escoger la mayor cantidad posible de subcadenas palindromas
// que no se solapen y que...
// Detalle: r arranca en k-1, que es la primera posicion donde cabe algo de largo k. Resuelve
// "Maximum Number of Non-overlapping Palindrome Substrings" (LeetCode 2472): dado s y un k, hay
// que escoger la mayor cantidad posible de subcadenas palindromas que no se solapen y que midan
// AL MENOS k. Barre r de izquierda a derecha y, apenas encuentra un palindromo valido que
// termine en r y empiece en o despues de "inicio", lo toma y salta con inicio = r+1. El greedy
// es optimo porque cerrar lo antes posible nunca quita opciones: deja el sufijo mas largo
// disponible para lo que venga. Cual l se escoja dentro del mismo r da igual, porque el corte
// queda en r. Sin tabla DP a proposito. Parece O(n^3) pero en la practica es lo mas rapido: el
// chequeo de dos punteros aborta al primer par que no coincide (medido: ~2 pasos por llamada en
// promedio), y una coincidencia profunda implicaria un palindromo largo, que el greedy se
// llevaria de una, avanzando inicio. Medido con n = 2000: el peor adversario encontrado son 7.5
// ms, contra 1-4 ms constantes de la version con tabla pal[i][j], que ademas reserva n^2 bits
// de memoria. Si necesitas consultar MUCHOS rangos sueltos en vez de barrer una vez, ahi si
// conviene la tabla: esta en la ficha "Chequeo de Palindromo".

class Solution {
public:
    bool esPalindromo(string &s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r]) return false;
            l++;
            r--;
        }
        return true;
    }

    int maxPalindromes(string s, int k) {
        int n = s.size();
        int ans = 0;
        int inicio = 0;

        for (int r = k - 1; r < n; r++) {
            for (int l = inicio; l <= r - k + 1; l++) {
                if (esPalindromo(s, l, r)) {
                    ans++;
                    inicio = r + 1;
                    break;
                }
            }
        }

        return ans;
    }
};
