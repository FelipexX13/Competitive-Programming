// <3
// Tema: Number Theory / BFS sobre Residuos
// Resumen: Resuelve "Only1s0s" (problema H, ICPC 2024)
// Detalle: Resuelve "Only1s0s" (problema H, ICPC 2024). El codigo busca el menor multiplo M de
// N que se escribe solo con unos y ceros, y responde M / N. M puede tener muchisimos digitos,
// asi que no se busca entre numeros sino entre RESIDUOS modulo N: dos numeros con el mismo
// residuo se comportan igual de ahi en adelante (agregarles un digito lleva al mismo residuo),
// asi que basta quedarse con el primero que llega a cada residuo. Hay a lo sumo N estados, y el
// BFS termina en O(N). Siempre existe: entre 1, 11, 111, ... (N+1 numeros) dos tienen el mismo
// residuo, y su resta es un multiplo de N hecho de unos y ceros. POR QUE SALE EL MENOR: el BFS
// encuentra primero los mas cortos, y dentro del mismo largo, como se agrega el 0 antes que el
// 1 y la cola ya viene ordenada, los numeros salen en orden creciente. Asi que la primera vez
// que se alcanza el residuo 0 es con el menor M. Se reconstruye con parent[] y digit[]. Al
// final M se divide entre N como en la escuela, digito por digito con el resto, porque no cabe
// en ningun tipo entero. El 10LL en la transicion evita el desborde de cur * 10.

#include <bits/stdc++.h>
using namespace std;

string solve(int N) {

    vector<int> parent(N, -1);
    vector<char> digit(N);
    vector<bool> visited(N, false);

    queue<int> q;

    // Empezamos con el numero 1
    int r = 1 % N;

    visited[r] = true;
    digit[r] = '1';

    q.push(r);

    while (!q.empty()) {

        int cur = q.front();
        q.pop();

        // Encontramos un multiplo de N
        if (cur == 0)
            break;

        // Agregar 0
        int r0 = (cur * 10LL) % N;

        if (!visited[r0]) {

            visited[r0] = true;
            parent[r0] = cur;
            digit[r0] = '0';

            q.push(r0);
        }

        // Agregar 1
        int r1 = (cur * 10LL + 1) % N;

        if (!visited[r1]) {

            visited[r1] = true;
            parent[r1] = cur;
            digit[r1] = '1';

            q.push(r1);
        }
    }

    // Reconstruir M
    string M;

    int cur = 0;

    while (cur != -1) {
        M.push_back(digit[cur]);
        cur = parent[cur];
    }

    reverse(M.begin(), M.end());

    return M;
}


// Divide un numero gigante representado como string
// entre N.
string divide(string M, int N) {

    string ans;
    long long rem = 0;

    for (char c : M) {

        rem = rem * 10 + (c - '0');

        ans += char('0' + rem / N);

        rem %= N;
    }

    // Quitar ceros iniciales
    int pos = 0;

    while (pos + 1 < (int)ans.size() &&
           ans[pos] == '0') {
        pos++;
    }

    return ans.substr(pos);
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;

    while (cin >> N && N != 0) {

        string M = solve(N);

        string D = divide(M, N);

        cout << D << '\n';
    }

    return 0;
}
