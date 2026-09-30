// <3
// Tema: Geometry / 2D Difference Array (Coordinate Compression)
// Resuelve "Office Space" (Kattis): en una oficina rectangular de w x h pies, hasta 20
// empleados piden un cubiculo rectangular (esquinas suroeste y noreste); pide reportar el area
// total, el area sin reclamar, el area en conflicto (solicitada por 2 o mas empleados) y, para
// cada empleado, el area que tiene garantizada (lo que pidio menos lo que se solapa con otros).
// Comprime las coordenadas x/y de las esquinas de todos los rectangulos en `xs`/`ys`, y usa un
// arreglo de diferencias 2D (`grid`) para contar cuantas solicitudes cubren cada celda
// comprimida, junto con un arreglo paralelo `sumIdx` que acumula (indice+1) del empleado para
// identificar sin ambiguedad al unico dueno cuando una celda queda cubierta exactamente una
// vez; una suma prefija 2D final obtiene el conteo y dueno real de cada celda.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static char buf_[1 << 22];
static int bufLen_, bufPos_;
inline int gc() {
    if (bufPos_ == bufLen_) { bufLen_ = fread(buf_, 1, sizeof(buf_), stdin); bufPos_ = 0; if (!bufLen_) return -1; }
    return buf_[bufPos_++];
}
inline bool readInt(int &out) {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    if (c == -1) return false;
    bool neg = false; if (c == '-') { neg = true; c = gc(); }
    int x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    out = neg ? -x : x;
    return true;
}
inline bool isSpaceChar(int c) { return c == ' ' || c == '\n' || c == '\r' || c == '\t'; }
inline bool readWord(string &s) {
    s.clear();
    int c = gc();
    while (c != -1 && isSpaceChar(c)) c = gc();
    if (c == -1) return false;
    while (c != -1 && !isSpaceChar(c)) { s.push_back((char)c); c = gc(); }
    return true;
}

int main() {
    int W, H;
    string out;
    while (readInt(W)) {
        readInt(H);
        int n;
        readInt(n);

        vector<string> names(n);
        vector<int> X1(n), Y1(n), X2(n), Y2(n);
        vector<int> xs, ys;
        xs.reserve(2 * n + 2);
        ys.reserve(2 * n + 2);
        xs.push_back(0); xs.push_back(W);
        ys.push_back(0); ys.push_back(H);

        for (int i = 0; i < n; i++) {
            readWord(names[i]);
            readInt(X1[i]); readInt(Y1[i]); readInt(X2[i]); readInt(Y2[i]);
            xs.push_back(X1[i]); xs.push_back(X2[i]);
            ys.push_back(Y1[i]); ys.push_back(Y2[i]);
        }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        int M = (int)xs.size() - 1; // number of cell columns
        int K = (int)ys.size() - 1; // number of cell rows
        int W2 = K + 1;             // row width for flat indexing over the (M+1) x (K+1) corner grid

        auto xIdx = [&](int v) { return (int)(lower_bound(xs.begin(), xs.end(), v) - xs.begin()); };
        auto yIdx = [&](int v) { return (int)(lower_bound(ys.begin(), ys.end(), v) - ys.begin()); };
        auto at = [&](int i, int j) { return i * W2 + j; };

        // Flat 2D difference array (row-major) over the (M+1) x (K+1) grid of "corner"
        // points, computed in place into the count grid (avoids a second full grid, and
        // flat 1D storage avoids the per-row bookkeeping overhead of nested vectors).
        vector<int> grid((size_t)(M + 1) * (K + 1), 0);
        // Parallel difference array summing (employee_index + 1) instead of 1. When a
        // cell's final count is exactly 1, this sum unambiguously equals that single
        // covering employee's (index + 1), letting us identify the owner without a
        // separate large prefix-sum array.
        vector<ll> sumIdx((size_t)(M + 1) * (K + 1), 0);

        for (int i = 0; i < n; i++) {
            int a = xIdx(X1[i]), b = xIdx(X2[i]);
            int c = yIdx(Y1[i]), d = yIdx(Y2[i]);
            grid[at(a, c)] += 1;
            grid[at(b, c)] -= 1;
            grid[at(a, d)] -= 1;
            grid[at(b, d)] += 1;

            ll idPlus1 = (ll)i + 1;
            sumIdx[at(a, c)] += idPlus1;
            sumIdx[at(b, c)] -= idPlus1;
            sumIdx[at(a, d)] -= idPlus1;
            sumIdx[at(b, d)] += idPlus1;
        }

        // 2D prefix sum in place -> grid[.] becomes the count of rectangles covering each
        // cell, and sumIdx[.] becomes the sum of (index+1) of covering rectangles.
        for (int i = 0; i <= M; i++) {
            int rowBase = i * W2;
            int prevRowBase = rowBase - W2;
            for (int j = 0; j <= K; j++) {
                int idx = rowBase + j;
                if (i > 0) { grid[idx] += grid[prevRowBase + j]; sumIdx[idx] += sumIdx[prevRowBase + j]; }
                if (j > 0) { grid[idx] += grid[idx - 1]; sumIdx[idx] += sumIdx[idx - 1]; }
                if (i > 0 && j > 0) { grid[idx] -= grid[prevRowBase + j - 1]; sumIdx[idx] -= sumIdx[prevRowBase + j - 1]; }
            }
        }

        ll total = (ll)W * H;
        ll unalloc = 0, contested = 0;
        vector<ll> guaranteed(n, 0);

        for (int i = 0; i < M; i++) {
            ll colWidth = (ll)(xs[i + 1] - xs[i]);
            int rowBase = i * W2;
            for (int j = 0; j < K; j++) {
                ll cellArea = colWidth * (ll)(ys[j + 1] - ys[j]);
                int c = grid[rowBase + j];
                if (c == 0) {
                    unalloc += cellArea;
                } else if (c >= 2) {
                    contested += cellArea;
                } else { // c == 1
                    int owner = (int)(sumIdx[rowBase + j] - 1);
                    guaranteed[owner] += cellArea;
                }
            }
        }

        out += "Total " + to_string(total) + "\n";
        out += "Unallocated " + to_string(unalloc) + "\n";
        out += "Contested " + to_string(contested) + "\n";

        for (int i = 0; i < n; i++) {
            out += names[i] + " " + to_string(guaranteed[i]) + "\n";
        }
        out += "\n";
    }

    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}