#include <bits/stdc++.h>
using namespace std;

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
// Reads up to (and past) the colon before the first number is read normally, since ':' is
// simply skipped as a non-digit character by readInt's own skip loop.

bool isAntiarithmetic(int n, const vector<int> &p) {
    vector<int> pos(n);
    for (int idx = 0; idx < n; idx++) pos[p[idx]] = idx;
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            int s = p[i] + p[k];
            if (s % 2 == 0) {
                int v = s / 2;
                int j = pos[v];
                if (i < j && j < k) return false;
            }
        }
    }
    return true;
}

int main() {
    int n;
    string out;
    while (readInt(n)) {
        if (n == 0) break;
        vector<int> p(n);
        for (int i = 0; i < n; i++) readInt(p[i]);
        out += isAntiarithmetic(n, p) ? "yes\n" : "no\n";
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}