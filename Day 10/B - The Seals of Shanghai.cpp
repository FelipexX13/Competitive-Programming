#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

static char buf_[1 << 22];
static int bufLen_, bufPos_;
inline int gc() {
    if (bufPos_ == bufLen_) { bufLen_ = fread(buf_, 1, sizeof(buf_), stdin); bufPos_ = 0; if (!bufLen_) return -1; }
    return buf_[bufPos_++];
}
inline ll readLL() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    bool neg = false; if (c == '-') { neg = true; c = gc(); }
    ll x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

const ll MAXM = 1000000000LL;

ll gcdll(ll a, ll b) { while (b) { a %= b; swap(a, b); } return a; }

// Counts divisors of d that are > 1.
ll countDivisorsGt1(ll d) {
    if (d <= 1) return 0;
    ll cnt = 0;
    for (ll i = 1; i * i <= d; i++) {
        if (d % i == 0) {
            if (i > 1) cnt++;
            ll other = d / i;
            if (other != i && other > 1) cnt++;
        }
    }
    return cnt;
}

void collectDivisorsGt1(ll d, vector<ll> &out) {
    if (d <= 1) return;
    for (ll i = 1; i * i <= d; i++) {
        if (d % i == 0) {
            if (i > 1) out.push_back(i);
            ll other = d / i;
            if (other != i && other > 1) out.push_back(other);
        }
    }
}

int main() {
    int N = (int)readLL();
    vector<ll> A(N);
    for (auto &x : A) x = readLL();

    if (N == 1) {
        printf("1 %lld\n", MAXM - 1);
        return 0;
    }

    ll D = 0;
    for (int i = 1; i < N; i++) D = gcdll(D, llabs(A[i] - A[0]));

    if (D == 0) {
        printf("1 %lld\n", MAXM - 1);
        return 0;
    }
    if (D >= 2) {
        printf("1 %lld\n", countDivisorsGt1(D));
        return 0;
    }

    // D == 1: minimum is provably exactly 2 (M=2 always splits into exactly the two parity
    // classes, and D=1 rules out cost=1 for any M>1). We still need to COUNT every M that
    // achieves cost=2. Key fact used for counting: for ANY 3 elements, since there are only
    // 2 residue classes under an optimal M, by pigeonhole at least 2 of the 3 must share a
    // class, so M must divide at least one of their 3 pairwise differences. This holds for
    // every valid M and every triple, so scanning divisors of one arbitrary triple's 3
    // differences is guaranteed to contain the full set of valid M's.
    vector<ll> distinctVals;
    {
        vector<ll> tmp = A;
        sort(tmp.begin(), tmp.end());
        tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
        distinctVals = tmp;
    }

    if ((int)distinctVals.size() < 3) {
        // Only 2 distinct values overall, differing by exactly 1 (since D=1): every M>1
        // fails to merge them, so cost=2 for every single M from 2..MAXM.
        printf("2 %lld\n", MAXM - 1);
        return 0;
    }

    ll a = distinctVals[0], b = distinctVals[1], c = distinctVals[2];
    ll d1 = llabs(a - b), d2 = llabs(b - c), d3 = llabs(a - c);

    vector<ll> candidates;
    collectDivisorsGt1(d1, candidates);
    collectDivisorsGt1(d2, candidates);
    collectDivisorsGt1(d3, candidates);
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

    // Lightweight open-addressing hash set, sized by N (not by M), reused across all
    // candidates via a version stamp. This keeps memory at O(N) regardless of how large
    // M gets (unlike indexing directly by residue, which would need an array of size M,
    // and M can be up to just under 1e9 here).
    int tableSize = 1;
    while (tableSize < 4 * N + 16) tableSize <<= 1;
    int mask = tableSize - 1;
    vector<ll> tableKey(tableSize);
    vector<int> tableStamp(tableSize, -1);

    int bestCost = INT_MAX;
    ll bestCount = 0;

    for (int idx = 0; idx < (int)candidates.size(); idx++) {
        ll M = candidates[idx];
        int distinctCount = 0;
        for (ll x : A) {
            ll r = x % M;
            ull h = (ull)r * 0x9E3779B97F4A7C15ULL;
            int pos = (int)(h >> 40) & mask;
            while (tableStamp[pos] == idx && tableKey[pos] != r) {
                pos = (pos + 1) & mask;
            }
            if (tableStamp[pos] != idx) {
                tableStamp[pos] = idx;
                tableKey[pos] = r;
                distinctCount++;
            }
        }
        if (distinctCount < bestCost) {
            bestCost = distinctCount;
            bestCount = 1;
        } else if (distinctCount == bestCost) {
            bestCount++;
        }
    }

    printf("%d %lld\n", bestCost, bestCount);
    return 0;
}