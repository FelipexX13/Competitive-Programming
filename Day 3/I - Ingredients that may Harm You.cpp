#include <bits/stdc++.h>
using namespace std;

const int MAXV = 1000000;
const int MOD = 1000000007;

int spf[MAXV + 1];
int cnt[MAXV + 1];
int pw[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // SPF
    for (int i = 0; i <= MAXV; i++) spf[i] = i;
    for (int i = 2; i * i <= MAXV; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= MAXV; j += i)
                if (spf[j] == j) spf[j] = i;
        }
    }

    int N;
    cin >> N;

    pw[0] = 1;
    for (int i = 1; i <= N; i++)
        pw[i] = (2LL * pw[i - 1]) % MOD;

    while (N--) {
        int x;
        cin >> x;

        vector<int> p;
        while (x > 1) {
            int pr = spf[x];
            p.push_back(pr);
            while (x % pr == 0) x /= pr;
        }

        int m = p.size();

        for (int mask = 0; mask < (1 << m); mask++) {
            int d = 1;
            for (int i = 0; i < m; i++)
                if (mask & (1 << i))
                    d *= p[i];
            cnt[d]++;
        }
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int x;
        cin >> x;

        vector<int> p;
        while (x > 1) {
            int pr = spf[x];
            p.push_back(pr);
            while (x % pr == 0) x /= pr;
        }

        int m = p.size();

        int coprime = 0;

        for (int mask = 0; mask < (1 << m); mask++) {
            int d = 1;
            int bits = 0;

            for (int i = 0; i < m; i++) {
                if (mask & (1 << i)) {
                    d *= p[i];
                    bits++;
                }
            }

            if (bits & 1)
                coprime -= cnt[d];
            else
                coprime += cnt[d];
        }

        cout << pw[coprime] << '\n';
    }

    return 0;
}