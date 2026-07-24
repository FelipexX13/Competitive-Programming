#include <bits/stdc++.h>
using namespace std;

// Suffix automaton over an alphabet of 26 lowercase letters + 1 separator symbol.
struct SAM {
    static const int ALPHA = 27;
    vector<array<int, ALPHA>> trans;
    vector<int> len, link_;
    int last;

    void init(int maxStates) {
        trans.clear(); len.clear(); link_.clear();
        trans.reserve(maxStates);
        len.reserve(maxStates);
        link_.reserve(maxStates);
        newNode();
        len[0] = 0; link_[0] = -1;
        last = 0;
    }
    int newNode() {
        array<int, ALPHA> a; a.fill(-1);
        trans.push_back(a);
        len.push_back(0);
        link_.push_back(-1);
        return (int)trans.size() - 1;
    }
    void extend(int c) {
        int cur = newNode();
        len[cur] = len[last] + 1;
        int p = last;
        while (p != -1 && trans[p][c] == -1) {
            trans[p][c] = cur;
            p = link_[p];
        }
        if (p == -1) {
            link_[cur] = 0;
        } else {
            int q = trans[p][c];
            if (len[p] + 1 == len[q]) {
                link_[cur] = q;
            } else {
                int clone = newNode();
                len[clone] = len[p] + 1;
                link_[clone] = link_[q];
                trans[clone] = trans[q];
                while (p != -1 && trans[p][c] == q) {
                    trans[p][c] = clone;
                    p = link_[p];
                }
                link_[q] = clone;
                link_[cur] = clone;
            }
        }
        last = cur;
    }
};

inline int charIdx(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    return 26; // separator
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    string A;
    cin >> A;
    vector<string> S(M);
    long long totalLen = 0;
    for (auto& s : S) { cin >> s; totalLen += (long long)s.size(); }

    int maxStates = 2 * (int)(totalLen + M + 5) + 10;
    SAM sam;
    sam.init(maxStates);

    for (int i = 0; i < M; i++) {
        string rev = S[i];
        reverse(rev.begin(), rev.end());
        for (char c : rev) sam.extend(charIdx(c));
        if (i + 1 < M) sam.extend(26); // separator between strings
    }

    int n2 = 2 * N;
    string doubledA = A + A;
    string revDoubledA(doubledA.rbegin(), doubledA.rend());

    vector<int> G(n2);
    {
        int v = 0, l = 0;
        for (int i = 0; i < n2; i++) {
            int c = charIdx(revDoubledA[(size_t)i]);
            while (v != 0 && sam.trans[v][c] == -1) {
                v = sam.link_[v];
                l = sam.len[v];
            }
            if (sam.trans[v][c] != -1) {
                v = sam.trans[v][c];
                l++;
            } else {
                l = 0;
            }
            G[i] = l;
        }
    }

    vector<int> C(n2);
    for (int k = 0; k < n2; k++) C[k] = G[n2 - 1 - k];

    auto feasible = [&](int ans) -> bool {
        int W = N - ans;
        if (W <= 0) return true;
        int runStart = -1;
        for (int k = 0; k <= n2; k++) {
            bool bad = (k == n2) || (C[k] > ans);
            if (!bad) {
                if (runStart == -1) runStart = k;
            } else {
                if (runStart != -1) {
                    int runEnd = k - 1;
                    int runLen = runEnd - runStart + 1;
                    if (runLen >= W && runStart <= N - 1) return true;
                }
                runStart = -1;
            }
        }
        return false;
    };

    int lo = 0, hi = N;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) hi = mid; else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}