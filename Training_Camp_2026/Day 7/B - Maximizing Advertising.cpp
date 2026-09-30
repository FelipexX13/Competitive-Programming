// <3
// Tema: Greedy / Prefix Sums
// Resuelve "Maximizing Advertising": dados N votantes con coordenadas (x,y) y preferencia 'b'
// o 'w', hay que elegir dos rectangulos disjuntos de lados paralelos a los ejes (uno para PSD,
// otro para PS) que maximicen la suma de votantes 'b' cubiertos por el primero mas los votantes
// 'w' cubiertos por el segundo.
// Como la particion optima siempre puede lograrse separando el plano con una linea vertical u
// horizontal, bestSplit ordena los puntos por una coordenada (x o y) y usa sumas prefijas
// (prefB, prefW) para probar, en cada corte posible, poner los 'b' de un lado y los 'w' del
// otro (o viceversa); el main toma el mejor resultado entre cortar por X o por Y.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static char buf[1 << 25];
static int bufLen = 0, bufPos = 0;

inline int gc() {
    if (bufPos == bufLen) {
        bufLen = (int)fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen <= 0) return -1;
    }
    return buf[bufPos++];
}

inline int readInt() {
    int c = gc();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = gc();
    bool neg = false;
    if (c == '-') { neg = true; c = gc(); }
    int x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

inline char readChar() {
    int c = gc();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = gc();
    return (char)c;
}

int N;
vector<int> Xs, Ys;
vector<char> Cs;

// dado un vector de coordenadas (alineado con Cs), calcula el mejor
// resultado separando en dos grupos (izq/der) por esa coordenada
ll bestSplit(vector<int>& coord) {
    int n = N;
    vector<pair<int,char>> arr(n);
    for (int i = 0; i < n; i++) arr[i] = {coord[i], Cs[i]};
    sort(arr.begin(), arr.end(), [](const pair<int,char>& a, const pair<int,char>& b) {
        return a.first < b.first;
    });

    ll totalB = 0, totalW = 0;
    for (auto& pr : arr) { if (pr.second == 'b') totalB++; else totalW++; }

    ll best = max(totalB, totalW); // caso: todo a un lado, el otro rectangulo vacio

    ll prefB = 0, prefW = 0;
    int i = 0;
    while (i < n) {
        int j = i;
        int cur = arr[i].first;
        ll gB = 0, gW = 0;
        while (j < n && arr[j].first == cur) {
            if (arr[j].second == 'b') gB++; else gW++;
            j++;
        }
        prefB += gB; prefW += gW;
        // corte justo despues de este grupo de coordenada 'cur'
        ll optA = prefB + (totalW - prefW); // b a la izquierda, w a la derecha
        ll optB = prefW + (totalB - prefB); // w a la izquierda, b a la derecha
        best = max(best, max(optA, optB));
        i = j;
    }
    return best;
}

int main() {
    N = readInt();
    Xs.resize(N); Ys.resize(N); Cs.resize(N);
    for (int i = 0; i < N; i++) {
        Xs[i] = readInt();
        Ys[i] = readInt();
        Cs[i] = readChar();
    }

    ll ans = max(bestSplit(Xs), bestSplit(Ys));
    printf("%lld\n", ans);
    return 0;
}