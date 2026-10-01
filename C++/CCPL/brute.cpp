// <3
// Tema: Graph / MST con Prim (Grafo Denso)
// Resumen: Una caja fuerte con N llaves de 4 digitos que hay que desbloquear todas
// O: (n^2), Prim para grafo denso
// Detalle: Resuelve "Anti-brute Force Lock" (problema B, CCPL 2026): una caja fuerte con N
// llaves de 4 digitos que hay que desbloquear todas. Los diales arrancan en 0000, cada rueda
// gira de 0 a 9 dando la vuelta (de 9 se pasa a 0), y hay un boton JUMP que lleva los diales
// GRATIS a cualquier llave YA desbloqueada. Se pide el minimo total de giros. El costo entre
// dos combinaciones es la suma, rueda por rueda, de min(|x-y|, 10-|x-y|): girar por el lado
// corto del circulo. Esa es toda la funcion distancia. EL JUMP ES LO QUE CONVIERTE ESTO EN UN
// MST. Sin el, habria que recorrer las llaves en orden y el problema seria un TSP, o sea
// NP-dificil. Con el JUMP gratis, para abrir una llave nueva uno se para en la llave ya abierta
// que mas le convenga y paga solo ese tramo. Entonces el costo total es la suma de las aristas
// de un arbol que conecta todas las llaves: el minimo es el arbol de expansion minima. EL
// DETALLE FINO, Y ES LO QUE HACE A ESTE PROBLEMA MAS QUE UN MST DE LIBRO: el 0000 NO es una
// llave desbloqueada, asi que el JUMP nunca puede devolverte ahi. El 0000 sirve una sola vez,
// para la primerisima llave, y despues deja de existir. Por eso NO entra como nodo del grafo:
// se paga una vez min d(0000, llave) y aparte se calcula el MST de las llaves SOLAS. Y se puede
// separar asi porque el MST de las llaves no depende de cual se abra primero: el peso del arbol
// es el mismo empiece Prim donde empiece. Entonces el total es min sobre k de [ d(0000, k) ] +
// MST(llaves) y minimizar cada parte por separado da el optimo global. SI EL 0000 SI FUERA
// SALTABLE la respuesta seria otra y MENOR: seria el MST del grafo con el 0000 adentro como un
// nodo mas, que puede gastar VARIAS aristas desde el 0000. Con las llaves {1000, 9000}:
// d(0000,1000)=1, d(0000,9000)=1, d(1000,9000)=2. Como el 0000 no es saltable la respuesta es
// 1+2 = 3; si lo fuera, seria 1+1 = 2. Vale la pena tener claro el ejemplo, porque meter el
// origen al grafo por costumbre es el error natural aqui. POR QUE PRIM Y NO KRUSKAL: el grafo
// es COMPLETO, las aristas son N^2. Prim con arreglo simple es O(N^2), que con N <= 500 son
// 250000 pasos y ni se siente. Kruskal tendria que ordenar las N^2 aristas, O(N^2 log N), y
// ademas construirlas todas en memoria. La regla: grafo denso, Prim con arreglo; grafo
// disperso, Kruskal con DSU o Prim con priority_queue. Verificado: los 4 casos del sample dan
// 16, 20, 26 y 17, y ademas 100000 casos aleatorios (incluidos adversarios con llaves pegadas
// al 0000) contra una DP de mascara de bits que simula las reglas del enunciado al pie de la
// letra, sin una sola diferencia.

#include <bits/stdc++.h>

using namespace std;

// Giros para pasar de la combinacion a a la b, por el lado corto de cada rueda.
int distancia(const string& a, const string& b)
{
    int dis = 0;

    for (int i = 0; i < 4; i++)
    {
        int x = a[i] - '0';
        int y = b[i] - '0';

        dis += min(abs(x - y), 10 - abs(x - y));
    }

    return dis;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        int N;
        cin >> N;

        vector<string> locks(N);

        for (int i = 0; i < N; i++)
            cin >> locks[i];

        // Costo de llegar inicialmente desde 0000
        // a cada una de las llaves.
        int respuestaInicial = INT_MAX;

        for (int i = 0; i < N; i++)
        {
            respuestaInicial = min(
                respuestaInicial,
                distancia("0000", locks[i])
            );
        }

        // Prim solamente entre las llaves.
        // 0000 NO forma parte del grafo.
        const int INF = INT_MAX;

        vector<int> mejor(N, INF);
        vector<bool> visitado(N, false);

        // Podemos comenzar el MST desde cualquier llave,
        // porque el costo inicial desde 0000 ya lo escogimos
        // como el minimo posible.
        mejor[0] = 0;

        int total = respuestaInicial;

        for (int k = 0; k < N; k++)
        {
            int u = -1;

            for (int i = 0; i < N; i++)
            {
                if (!visitado[i] &&
                    (u == -1 || mejor[i] < mejor[u]))
                {
                    u = i;
                }
            }

            visitado[u] = true;
            total += mejor[u];

            for (int v = 0; v < N; v++)
            {
                if (!visitado[v])
                {
                    int peso = distancia(locks[u], locks[v]);

                    mejor[v] = min(mejor[v], peso);
                }
            }
        }

        cout << total << '\n';
    }

    return 0;
}
