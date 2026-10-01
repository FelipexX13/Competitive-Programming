// <3
// Tema: String / Parentesis Balanceados (Todas las Variantes)
// Resumen: El BALANCE, +1 por cada '(' y -1 por cada ')'
// O: (n) todas las variantes
// Uso: valido(s); validoTipos(s); parejas(s)[i] = pareja de i, o -1
// Detalle: Todo problema de parentesis sale de UNA idea: el BALANCE, +1 por cada '(' y -1 por
// cada ')'. Una cadena es valida si y solo si el balance nunca baja de 0 y termina en 0. Las
// variantes de abajo son esa misma idea mirada desde distintos angulos. Todas verificadas
// contra fuerza bruta. CUAL USAR SEGUN LO QUE PIDAN: 1 valido un solo tipo: basta un contador,
// sin pila, O(n) y O(1) de memoria. 2 validoTipos ()[]{}: ahi SI hace falta pila, porque "([)]"
// tiene balance bien en cada tipo por separado y aun asi es invalida. 3 parejas/profundidad la
// pareja de cada parentesis (para recorrer la estructura como un arbol) y el anidamiento
// maximo, que es el balance maximo. 4 minInserciones los ')' que llegan sin '(' abierto piden
// uno, y los '(' que quedan abiertos al final piden un ')'. Suma de sueltos. 5 minVolteos
// cambiar '(' por ')' o al reves. Tras cancelar las parejas queda ")))(((": con c cerrados y a
// abiertos sueltos son ceil(c/2) + ceil(a/2). Con largo impar es imposible. 6 borrarMinimo se
// marcan los sueltos (los ')' sin pareja y los '(' que quedan en la pila) y se borran. Sirve
// aunque la cadena tenga letras mezcladas. 7 masLarga la pila guarda el indice ANTES de donde
// empieza el tramo valido actual; arranca en -1 y cada ')' suelto pasa a ser el nuevo tope. 8
// contarSubcadenas si el ')' de i casa con el '(' de j, las validas que terminan en i son
// "(...)" mas cada valida que terminaba justo en j-1: dp[i+1] = dp[j]+1. 9 validoComodines '*'
// vale '(', ')' o nada: se lleva el balance MINIMO y el MAXIMO posibles. Si el maximo baja de 0
// no hay forma; el minimo se sube a 0 porque nunca conviene pasar por negativo. Al final el
// minimo debe ser 0. 10 generar backtracking: se pone '(' mientras queden, y ')' si hay mas
// abiertos que cerrados. Sale en orden lexicografico y son Catalan(n). 11 kEsima sin generarlas
// todas: formas[i][b] = cuantas maneras hay de completar i caracteres desde balance b. Si k
// cabe en las que empiezan con '(', se pone '('; si no, se descuentan y se pone ')'. Hasta n de
// unos 30. 12 SegTree "subsecuencia balanceada mas larga en s[l..r]" con muchas consultas. Cada
// nodo guarda (parejas, '(' sobrantes, ')' sobrantes); al unir, los '(' sobrantes de la
// izquierda casan con los ')' sobrantes de la derecha. 13 maxSubsecuenciaTipos con varios tipos
// y hay que BORRAR o INSERTAR, el greedy de pila ya no es optimo: DP de intervalos O(n^3). El
// minimo de inserciones para balancear es n menos ese largo. Contar las secuencias validas de n
// pares es Catalan(n): ver la ficha de Combinatoria.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 1) Un solo tipo.
bool valido(const string &s) {
    int bal = 0;
    for (char c : s) {
        if (c == '(') bal++;
        else bal--;
        if (bal < 0) return false;
    }
    return bal == 0;
}

// 2) Varios tipos: la pila guarda los que abren.
bool validoTipos(const string &s) {
    string pila;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            pila.push_back(c);
            continue;
        }
        char abre = '(';
        if (c == ']') abre = '[';
        if (c == '}') abre = '{';
        if (pila.empty() || pila.back() != abre) return false;
        pila.pop_back();
    }
    return pila.empty();
}

// 3) Pareja de cada parentesis (-1 si queda suelto) y anidamiento maximo.
vector<int> parejas(const string &s) {
    vector<int> match(s.size(), -1), pila;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') {
            pila.push_back(i);
        } else if (!pila.empty()) {
            match[i] = pila.back();
            match[pila.back()] = i;
            pila.pop_back();
        }
    }
    return match;
}

int profundidad(const string &s) {         // para cadenas validas
    int bal = 0, mx = 0;
    for (char c : s) {
        if (c == '(') bal++;
        else bal--;
        mx = max(mx, bal);
    }
    return mx;
}

// 4) Minimo de inserciones para balancear.
int minInserciones(const string &s) {
    int abiertos = 0, faltan = 0;
    for (char c : s) {
        if (c == '(') abiertos++;
        else if (abiertos > 0) abiertos--;
        else faltan++;                      // ')' sin pareja: pide un '('
    }
    return abiertos + faltan;               // cada '(' abierto pide un ')'
}

// 5) Minimo de volteos '(' <-> ')' para balancear; -1 si es imposible.
int minVolteos(const string &s) {
    if (s.size() % 2) return -1;
    int abiertos = 0, cerrados = 0;
    for (char c : s) {
        if (c == '(') abiertos++;
        else if (abiertos > 0) abiertos--;
        else cerrados++;
    }
    return (cerrados + 1) / 2 + (abiertos + 1) / 2;
}

// 6) Borrar el minimo para que quede valida (devuelve una de las optimas).
string borrarMinimo(const string &s) {
    vector<int> pila;
    vector<bool> borrar(s.size(), false);
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') {
            pila.push_back(i);
        } else if (s[i] == ')') {
            if (!pila.empty()) pila.pop_back();
            else borrar[i] = true;
        }
    }
    for (int i : pila) borrar[i] = true;
    string res;
    for (int i = 0; i < (int)s.size(); i++)
        if (!borrar[i]) res += s[i];
    return res;
}

// 7) Largo de la subcadena valida mas larga.
int masLarga(const string &s) {
    vector<int> pila = {-1};                // indice antes del tramo valido
    int mejor = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') {
            pila.push_back(i);
            continue;
        }
        pila.pop_back();
        if (pila.empty()) pila.push_back(i);        // ')' suelto: nuevo tope
        else mejor = max(mejor, i - pila.back());
    }
    return mejor;
}

// 8) Cantidad de subcadenas validas (distintas por posicion).
ll contarSubcadenas(const string &s) {
    int n = s.size();
    vector<ll> dp(n + 1, 0);                // dp[i+1] = validas que terminan en i
    vector<int> pila;
    ll total = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            pila.push_back(i);
            continue;
        }
        if (pila.empty()) continue;
        int j = pila.back();
        pila.pop_back();
        dp[i + 1] = dp[j] + 1;
        total += dp[i + 1];
    }
    return total;
}

// 9) Con comodines '*' que valen '(', ')' o nada.
bool validoComodines(const string &s) {
    int lo = 0, hi = 0;                     // balance minimo y maximo posibles
    for (char c : s) {
        if (c == '(') {
            lo++;
            hi++;
        } else if (c == ')') {
            lo--;
            hi--;
        } else {
            lo--;
            hi++;
        }
        if (hi < 0) return false;
        lo = max(lo, 0);
    }
    return lo == 0;
}

// 10) Todas las validas de n pares, en orden lexicografico.
void generar(int n, int abiertos, int cerrados, string &cur, vector<string> &res) {
    if ((int)cur.size() == 2 * n) {
        res.push_back(cur);
        return;
    }
    if (abiertos < n) {
        cur.push_back('(');
        generar(n, abiertos + 1, cerrados, cur, res);
        cur.pop_back();
    }
    if (cerrados < abiertos) {
        cur.push_back(')');
        generar(n, abiertos, cerrados + 1, cur, res);
        cur.pop_back();
    }
}

// 11) La k-esima valida de n pares (k desde 1), en orden lexicografico.
string kEsima(int n, ll k) {
    vector<vector<ll>> formas(2 * n + 1, vector<ll>(2 * n + 2, 0));
    formas[0][0] = 1;
    for (int i = 1; i <= 2 * n; i++)
        for (int b = 0; b <= 2 * n; b++) {
            formas[i][b] = formas[i - 1][b + 1];                // poner '('
            if (b > 0) formas[i][b] += formas[i - 1][b - 1];    // poner ')'
        }
    string res;
    int b = 0;
    for (int i = 2 * n; i > 0; i--) {
        ll conAbre = formas[i - 1][b + 1];
        if (k <= conAbre) {
            res += '(';
            b++;
        } else {
            k -= conAbre;
            res += ')';
            b--;
        }
    }
    return res;
}

// 12) Subsecuencia balanceada mas larga en s[l..r], con muchas consultas.
struct Nodo {
    int par, abre, cierra;
};

Nodo unir(Nodo a, Nodo b) {
    int nuevos = min(a.abre, b.cierra);
    return {a.par + b.par + nuevos, a.abre + b.abre - nuevos,
            a.cierra + b.cierra - nuevos};
}

struct SegTree {
    int n;
    vector<Nodo> t;

    SegTree(const string &s) : n(s.size()), t(4 * s.size()) {
        build(1, 0, n - 1, s);
    }

    void build(int p, int l, int r, const string &s) {
        if (l == r) {
            if (s[l] == '(') t[p] = {0, 1, 0};
            else t[p] = {0, 0, 1};
            return;
        }
        int m = (l + r) / 2;
        build(2 * p, l, m, s);
        build(2 * p + 1, m + 1, r, s);
        t[p] = unir(t[2 * p], t[2 * p + 1]);
    }

    Nodo query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return t[p];
        int m = (l + r) / 2;
        if (qr <= m) return query(2 * p, l, m, ql, qr);
        if (ql > m) return query(2 * p + 1, m + 1, r, ql, qr);
        return unir(query(2 * p, l, m, ql, qr), query(2 * p + 1, m + 1, r, ql, qr));
    }

    int maxBalanceada(int l, int r) {       // indices desde 0
        return 2 * query(1, 0, n - 1, l, r).par;
    }
};

// 13) Varios tipos: subsecuencia balanceada mas larga (DP de intervalos).
bool casan(char a, char b) {
    return (a == '(' && b == ')') || (a == '[' && b == ']') || (a == '{' && b == '}');
}

int maxSubsecuenciaTipos(const string &s) {
    int n = s.size();
    if (n == 0) return 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1, mejor = 0;
            if (casan(s[i], s[j])) mejor = dp[i + 1][j - 1] + 2;
            for (int k = i; k < j; k++) mejor = max(mejor, dp[i][k] + dp[k + 1][j]);
            dp[i][j] = mejor;
        }
    return dp[0][n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    while (cin >> s) {
        cout << s << ": valida=" << valido(s)
             << " inserciones=" << minInserciones(s)
             << " masLarga=" << masLarga(s)
             << " subcadenas=" << contarSubcadenas(s)
             << " queda=" << borrarMinimo(s) << '\n';
    }
    return 0;
}
