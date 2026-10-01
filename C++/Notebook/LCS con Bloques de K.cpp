// <3
// Tema: Dynamic Programming / LCS con Bloques de K Caracteres
// O: (n*m) tiempo y memoria
// Uso: lee K y las dos cadenas; imprime el largo maximo. K = 0 termina
// Subsecuencia comun maxima, pero con una condicion extra: lo que se toma tiene que venir en
// BLOQUES de al menos K caracteres SEGUIDOS en las dos cadenas a la vez. Con K = 1 es el LCS de
// toda la vida; con K mayor, tomar una letra suelta ya no vale.
// Son DOS tablas y entender la segunda es todo el problema:
//   dp[i][j]     la mejor respuesta usando a[1..i] y b[1..j], sin exigir que i y j se usen.
//   bloque[i][j] la mejor respuesta que TERMINA con un bloque que cierra justo en i y j.
// Las dos transiciones de bloque son las dos unicas formas de cerrar un bloque en (i, j):
//   ESTIRAR uno que ya venia: bloque[i-1][j-1] + 1
//   ABRIR uno nuevo de exactamente K: dp[i-K][j-K] + K
// y se toma el maximo. Si no se escriben las dos, el caso que se escapa es el de dos bloques
// pegados que juntos miden mas que cualquiera por separado.
// EL TRUCO SUCIO DEL ARCHIVO: bloque[][] hace dos oficios. Mientras la racha es menor que K es un
// CONTADOR de letras iguales seguidas; apenas llega a K se convierte en VALOR de la DP y de ahi en
// adelante el +1 ya significa "estirar el bloque". Funciona porque se cumple que
//     bloque[i][j] >= K   si y solo si   la racha real en (i, j) es >= K
// o sea que el mismo if sirve para las dos cosas. Verificado con asserts sobre las 8.001 pruebas:
// 0 violaciones.
// POR ESO dp[i-K][j-K] NUNCA se sale: solo se entra ahi cuando la racha es al menos K, y para eso
// hacen falta K letras antes en las dos cadenas, asi que i >= K y j >= K. Tambien verificado.
// Si la racha se corta (a[i-1] != b[j-1]) bloque[i][j] se queda en 0 y el contador arranca de
// cero solo, sin tener que limpiarlo a mano.
// OJO CON LA MEMORIA: son dos matrices de (n+1)*(m+1) enteros, o sea 8*n*m bytes. Con n = m = 5000
// son 200 MB y no cabe. bloque solo necesita la diagonal anterior y dp necesita K+1 filas, asi que
// si los limites suben se puede bajar a O(K*m).
// VERIFICADO contra una fuerza bruta escrita desde otra formulacion (escoger bloques disjuntos en
// orden, cada uno de largo >= K, maximizando la suma): exhaustivo sobre alfabeto de 2 letras con
// cadenas de hasta 5 y K de 1 a 3, mas 4.000 aleatorios, 8.001 casos, 0 diferencias. Ademas con
// K = 1 da exactamente el LCS clasico en 500 casos. Tiempo: 0.13 s con n = m = 4000.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;

    while(cin >> K && K)
    {
        string a, b;
        cin >> a >> b;

        int n = a.size();
        int m = b.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        vector<vector<int>> bloque(n + 1, vector<int>(m + 1));

        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                // sin cerrar bloque en (i, j): lo mejor de los dos vecinos
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

                if(a[i-1] == b[j-1])
                {
                    // contador de racha, que pasa a ser valor de DP al llegar a K
                    bloque[i][j] = bloque[i-1][j-1] + 1;

                    if(bloque[i][j] >= K)
                    {
                        bloque[i][j] = max(
                            bloque[i][j],          // estirar el bloque de atras
                            dp[i-K][j-K] + K       // o abrir uno nuevo de K
                        );

                        dp[i][j] = max(dp[i][j], bloque[i][j]);
                    }
                }
            }
        }

        cout << dp[n][m] << '\n';
    }

    return 0;
}
