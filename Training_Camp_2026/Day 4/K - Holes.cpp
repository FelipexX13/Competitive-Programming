// <3
// Tema: Data Structures / Sqrt Decomposition
// Resuelve "Holes" (Training Camp 2026, Day 4 problema K): hay N agujeros en fila, cada uno con
// una potencia que hace saltar la bola a la posicion i+a_i, y hay que soportar M operaciones que
// cambian la potencia de un agujero o tiran una bola por un agujero, reportando cuantos saltos da
// y desde que agujero sale de la fila.
// Divide la fila en bloques de tamano sqrt(N) y precalcula por bloque, para cada posicion, a
// donde sale del bloque (jmp_), cuantos saltos (cnt_) y desde que agujero deja la fila si aplica
// (last_); una actualizacion solo recalcula su bloque (recomputeBlock) y una consulta encadena
// esos saltos precomputados bloque a bloque en O(sqrt(N)) por operacion.

#include <bits/stdc++.h>
using namespace std;

static char buf_[1 << 22];
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

int N, M;
vector<int> a_;      // power of each hole, 1-indexed
vector<int> jmp_;    // first position outside the hole's block reached (or N+1 sentinel = exits the row)
vector<int> cnt_;    // number of individual jumps taken to reach jmp_[i]
vector<int> last_;   // valid only when jmp_[i] == N+1: last hole visited before leaving the row
int blockSize;

void recomputeBlock(int p) {
    int blockIdx = (p - 1) / blockSize;
    int start = blockIdx * blockSize + 1;
    int end = min(N, start + blockSize - 1);
    for (int i = end; i >= start; i--) {
        int nxt = i + a_[i];
        if (nxt > N) {
            jmp_[i] = N + 1;
            cnt_[i] = 1;
            last_[i] = i;
        } else if (nxt > end) {
            // leaves the current block to a later block (nxt > i always since a_[i] >= 1)
            jmp_[i] = nxt;
            cnt_[i] = 1;
            // last_[i] intentionally left as-is; never read while jmp_[i] <= N
        } else {
            jmp_[i] = jmp_[nxt];
            cnt_[i] = cnt_[nxt] + 1;
            last_[i] = last_[nxt];
        }
    }
}

int main() {
    N = readInt();
    M = readInt();
    a_.assign(N + 2, 0);
    jmp_.assign(N + 2, 0);
    cnt_.assign(N + 2, 0);
    last_.assign(N + 2, 0);

    for (int i = 1; i <= N; i++) a_[i] = readInt();

    blockSize = max(1, (int)sqrt((double)N));

    for (int start = 1; start <= N; start += blockSize) {
        recomputeBlock(start);
    }

    string out;
    out.reserve(M * 12);
    char tmp[32];

    for (int q = 0; q < M; q++) {
        int type = readInt();
        if (type == 0) {
            int pos = readInt(), val = readInt();
            a_[pos] = val;
            recomputeBlock(pos);
        } else {
            int pos = readInt();
            long long jumps = 0;
            int cur = pos;
            int lastHole = -1;
            while (cur <= N) {
                jumps += cnt_[cur];
                if (jmp_[cur] > N) {
                    lastHole = last_[cur];
                }
                cur = jmp_[cur];
            }
            int len = sprintf(tmp, "%d %lld\n", lastHole, jumps);
            out.append(tmp, len);
        }
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}