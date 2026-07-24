#include <bits/stdc++.h>
using namespace std;

static char buf_[1 << 25];
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

int N;
vector<int> bitArr;

inline void update(int pos, int val) {
    for (; pos <= N; pos += pos & (-pos)) {
        if (val < bitArr[pos]) bitArr[pos] = val;
    }
}

inline int queryPrefixMin(int pos) {
    int res = INT_MAX;
    for (; pos > 0; pos -= pos & (-pos)) {
        if (bitArr[pos] < res) res = bitArr[pos];
    }
    return res;
}

int main() {
    int t = readInt();
    string out;
    while (t--) {
        N = readInt();
        vector<array<int,3>> people(N);
        for (int i = 0; i < N; i++) {
            int a = readInt(), b = readInt(), c = readInt();
            people[i] = {a, b, c};
        }
        sort(people.begin(), people.end(), [](const array<int,3>& x, const array<int,3>& y) {
            return x[0] < y[0];
        });
        bitArr.assign(N + 1, INT_MAX);
        int count = 0;
        for (int i = 0; i < N; i++) {
            int b = people[i][1];
            int c = people[i][2];
            int mn = queryPrefixMin(b - 1);
            if (mn >= c) count++;
            update(b, c);
        }
        out += to_string(count);
        out += "\n";
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}