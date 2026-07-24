#include <bits/stdc++.h>
using namespace std;

int N, Q;
vector<int> A;        // valores comprimidos, 1-indexado
vector<int> freqArr;  // frecuencia actual de cada valor comprimido
vector<int> B;        // B[k] = cantidad de valores distintos con frecuencia >= k
int h;

inline void addElem(int val) {
    int f = freqArr[val];
    B[f + 1] += 1;
    freqArr[val] = f + 1;
    // solo puede crecer como maximo 1 (demostrado matematicamente),
    // pero dejamos el while por seguridad/robustez.
    while (h + 1 < (int)B.size() && B[h + 1] >= h + 1) h++;
}

inline void removeElem(int val) {
    int f = freqArr[val];
    B[f] -= 1;
    freqArr[val] = f - 1;
    while (h > 0 && B[h] < h) h--;
}

int main() {
    scanf("%d %d", &N, &Q);
    vector<int> rawA(N + 1);
    vector<int> sortedVals(N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &rawA[i]);
        sortedVals[i - 1] = rawA[i];
    }
    sort(sortedVals.begin(), sortedVals.end());
    sortedVals.erase(unique(sortedVals.begin(), sortedVals.end()), sortedVals.end());
    int M = (int)sortedVals.size();

    A.assign(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        int idx = (int)(lower_bound(sortedVals.begin(), sortedVals.end(), rawA[i]) - sortedVals.begin());
        A[i] = idx + 1;
    }

    freqArr.assign(M + 2, 0);
    B.assign(N + 2, 0);
    h = 0;

    vector<int> ql(Q), qr(Q), qIdx(Q);
    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &ql[i], &qr[i]);
        qIdx[i] = i;
    }

    int blockSize = max(1, (int)sqrt((double)N));
    sort(qIdx.begin(), qIdx.end(), [&](int a, int b) {
        int ba = ql[a] / blockSize, bb = ql[b] / blockSize;
        if (ba != bb) return ba < bb;
        if (ba & 1) return qr[a] > qr[b];
        return qr[a] < qr[b];
    });

    vector<int> ans(Q);
    int curL = 1, curR = 0;
    for (int qi : qIdx) {
        int l = ql[qi], r = qr[qi];
        while (curR < r) { curR++; addElem(A[curR]); }
        while (curL > l) { curL--; addElem(A[curL]); }
        while (curR > r) { removeElem(A[curR]); curR--; }
        while (curL < l) { removeElem(A[curL]); curL++; }
        ans[qi] = h;
    }

    string out;
    out.reserve(Q * 4);
    for (int i = 0; i < Q; i++) {
        out += to_string(ans[i]);
        out += '\n';
    }
    fputs(out.c_str(), stdout);
    return 0;
}