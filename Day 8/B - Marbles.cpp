// <3
// Tema: Game Theory / Sprague-Grundy
// Resuelve "Marbles": en un tablero indexado por filas y columnas, un jugador elige una
// canica en (l,c) y un entero u>0 y la mueve a (l-u,c), (l,c-u) o (l-u,c-u) sin salir del
// tablero; el primero en llevar una canica a (0,0) gana y el Emperador siempre juega primero.
// Dado el reparto inicial de N canicas, hay que decidir si el Emperador puede ganar jugando
// optimo. Modela el juego como la suma de N subjuegos independientes (teoria de Sprague-
// Grundy): precomputeGrundy calcula el numero de Grundy de cada posicion (l,c) via mex de
// posiciones alcanzables (marcando INSTA cuando l==0, c==0 o l==c, movimiento ganador
// inmediato), y el XOR de los Grundy de todas las canicas (mas el chequeo instaWin) decide si
// hay victoria.

#include <bits/stdc++.h>
using namespace std;

static char buf_[1 << 16];
static int bufLen_, bufPos_;
inline int gc() {
    if (bufPos_ == bufLen_) { bufLen_ = fread(buf_, 1, sizeof(buf_), stdin); bufPos_ = 0; if (!bufLen_) return -1; }
    return buf_[bufPos_++];
}
inline int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    bool neg = false; if (c == '-') { neg = true; c = gc(); }
    int x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

const int MAXV = 101;                // coordinates go from 0 to 100
const int INSTA = 1000000;           // sentinel for "instant win" positions: (i,0), (0,i), (i,i)
int grundy_[MAXV][MAXV];

void precomputeGrundy() {
    // process states in order of increasing max(l,c): every move strictly decreases
    // max(l,c) or keeps l the same while decreasing c (or vice versa), so processing
    // by increasing (l+c) is a safe topological order (all moves reduce l+c).
    vector<int> seen(3 * MAXV + 10, -1); // seen[v] == stamp means v currently marked reachable
    int stamp = 0;

    vector<pair<int,int>> order;
    for (int l = 0; l < MAXV; l++)
        for (int c = 0; c < MAXV; c++)
            order.push_back({l, c});
    sort(order.begin(), order.end(), [](const pair<int,int>&a, const pair<int,int>&b){
        return (a.first + a.second) < (b.first + b.second);
    });

    for (auto &pr : order) {
        int l = pr.first, c = pr.second;
        if (l == 0 || c == 0 || l == c) {
            grundy_[l][c] = INSTA;
            continue;
        }
        stamp++;
        for (int u = 1; u <= max(l, c); u++) {
            int g;
            if (l - u >= 0) {
                g = grundy_[l - u][c];
                if (g < (int)seen.size()) seen[g] = stamp;
            }
            if (c - u >= 0) {
                g = grundy_[l][c - u];
                if (g < (int)seen.size()) seen[g] = stamp;
            }
            if (l - u >= 0 && c - u >= 0) {
                g = grundy_[l - u][c - u];
                if (g < (int)seen.size()) seen[g] = stamp;
            }
        }
        int mex = 0;
        while (mex < (int)seen.size() && seen[mex] == stamp) mex++;
        grundy_[l][c] = mex;
    }
}

int main() {
    precomputeGrundy();

    int N = readInt();
    vector<pair<int,int>> marbles(N);
    for (auto &m : marbles) { m.first = readInt(); m.second = readInt(); }

    bool instaWin = false;
    for (auto &m : marbles) {
        if (m.first == m.second) { instaWin = true; break; }
    }

    if (instaWin) {
        printf("Y\n");
        return 0;
    }

    int x = 0;
    for (auto &m : marbles) {
        x ^= grundy_[m.first][m.second];
    }
    printf(x != 0 ? "Y\n" : "N\n");
    return 0;
}