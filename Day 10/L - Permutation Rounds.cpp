#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

const ll MOD = 1000000007LL;

ll power_mod(ll base, ll exp, ll mod) {
    base %= mod;
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    int n = readInt();
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) p[i] = readInt();

    vector<char> visited(n + 1, 0);
    unordered_map<int, int> maxPower; // prime -> max exponent seen across all cycle lengths

    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;
        int length = 0;
        int j = i;
        while (!visited[j]) {
            visited[j] = 1;
            j = p[j];
            length++;
        }
        // factorize `length`, updating maxPower
        int x = length;
        for (int d = 2; (ll)d * d <= x; d++) {
            if (x % d == 0) {
                int exp = 0;
                while (x % d == 0) { x /= d; exp++; }
                auto it = maxPower.find(d);
                if (it == maxPower.end() || it->second < exp) maxPower[d] = exp;
            }
        }
        if (x > 1) {
            auto it = maxPower.find(x);
            if (it == maxPower.end() || it->second < 1) maxPower[x] = 1;
        }
    }

    ll result = 1;
    for (auto &pr : maxPower) {
        result = (result * power_mod(pr.first, pr.second, MOD)) % MOD;
    }

    printf("%lld\n", result);
    return 0;
}