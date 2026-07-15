#include <bits/stdc++.h>
using namespace std;
 
static const int MOD = 1000000007;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, Q;
    cin >> N >> Q;
 
    vector<int> X(Q + 1);
 
    long long inv2 = (MOD + 1) / 2;
 
    vector<long long> invPow(Q + 1), pow2(Q + 1);
    invPow[0] = 1;
    pow2[0] = 1;
    for (int i = 1; i <= Q; i++) {
        invPow[i] = invPow[i - 1] * inv2 % MOD;
        pow2[i] = pow2[i - 1] * 2 % MOD;
    }
 
    vector<long long> coeff(Q + 1);
    for (int i = 1; i <= Q; i++) {
        cin >> X[i];
        coeff[i] = 1LL * X[i] * invPow[i] % MOD;
    }
 
    vector<long long> suffix(Q + 2, 0);
    for (int i = Q; i >= 1; i--) {
        suffix[i] = (suffix[i + 1] + coeff[i]) % MOD;
    }
 
    vector<long long> ans(N + 1, 0);
 
    // initial value at table 1
    ans[1] = suffix[1];
 
    // increments
    for (int i = 1; i <= Q; i++) {
        long long add = pow2[i - 1] * suffix[i + 1] % MOD;
        ans[X[i]] += add;
        if (ans[X[i]] >= MOD) ans[X[i]] -= MOD;
    }
 
    for (int i = 1; i <= N; i++)
        cout << ans[i] % MOD << "\n";
 
    return 0;
}