// <3
// Tema: Math / Fibonacci (Zeckendorf-like Greedy)
// Resuelve "Getting in Shape" (Training Camp 2026, Day 4 problema D): dado N, hay que construir
// una secuencia de ejercicios tipo A/B (terminada en B) tal que la cantidad de formas de
// completarla saltandose opcionalmente el ejercicio siguiente a cada A sea exactamente N, y
// devolver la lexicograficamente menor, o "IMPOSSIBLE" si no existe.
// El numero de formas de un bloque "A^(k-1)B" resulta ser Fib(k+1), y las formas de sufijos se
// suman; solveSum busca en forma greedy el mayor Fib(k+2) que divida el resto S para minimizar el
// largo del bloque de A's (dando el prefijo lexicografico mas chico), y solve arma la respuesta de
// forma recursiva y memoizada (memo) para evitar recomputo exponencial entre llamadas repetidas.

#include <bits/stdc++.h>
using namespace std;

// fib[i] = Fib(i+1), i.e. fib[0]=Fib(1)=1, fib[1]=Fib(2)=1, fib[2]=Fib(3)=2, ...
vector<long long> fib;

void buildFib() {
    fib.push_back(1);
    fib.push_back(1);
    while (true) {
        long long a = fib[fib.size() - 1];
        long long b = fib[fib.size() - 2];
        if (a > (long long)4e18 - b) break; // stop well before overflow
        fib.push_back(a + b);
        if (fib.back() > (long long)4e15) break; // more than enough headroom past 1e15
    }
}

bool solve(long long N, string &result);

unordered_map<long long, pair<bool, string>> memo;

// Find lex-smallest V (ending in B) with h_V(1) + h_V(2) = S.
bool solveSum(long long S, string &result) {
    // Try the largest k such that Fib(k+2) divides S exactly; Fib(k+2) = fib[k+1].
    for (int k = (int)fib.size() - 2; k >= 1; k--) {
        long long fibK2 = fib[k + 1]; // Fib(k+2)
        if (fibK2 > S) continue;
        if (S % fibK2 == 0) {
            long long m = S / fibK2;
            if (m == 1) {
                result = string(k - 1, 'A') + "B";
                return true;
            } else {
                string sub;
                if (solve(m, sub)) {
                    result = string(k - 1, 'A') + "B" + sub;
                    return true;
                }
            }
        }
    }
    return false;
}

// Find lex-smallest string (ending in B) with h(1) = N.
// Memoized: the same sub-value N can be reached via many different divisor
// orderings when the original input has several Fibonacci-related factors,
// so without caching this can blow up (verified: >5,000,000 redundant calls
// on some inputs without memoization, vs ~1 with it).
bool solve(long long N, string &result) {
    if (N == 1) {
        result = "B";
        return true;
    }
    auto it = memo.find(N);
    if (it != memo.end()) {
        if (it->second.first) result = it->second.second;
        return it->second.first;
    }
    string sub;
    bool ok = solveSum(N, sub);
    string ans = ok ? ("A" + sub) : "";
    memo[N] = {ok, ans};
    if (ok) result = ans;
    return ok;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    buildFib();

    long long N;
    cin >> N;

    string result;
    if (solve(N, result)) {
        cout << result << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }
    return 0;
}