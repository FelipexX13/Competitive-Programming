#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<ll> treeL, treeR;                 // treeL: max de L en el rango, treeR: min de R en el rango
const ll NEG_INF = -2000000000000000000LL;
const ll POS_INF =  2000000000000000000LL;

inline void pull(int i) {
    treeL[i] = max(treeL[2*i], treeL[2*i+1]);
    treeR[i] = min(treeR[2*i], treeR[2*i+1]);
}

// actualiza el guarda en posicion 0-indexada 'pos' con nuevo intervalo [lVal, rVal]
void updatePos(int pos, ll lVal, ll rVal) {
    pos += n;
    treeL[pos] = lVal;
    treeR[pos] = rVal;
    for (pos >>= 1; pos >= 1; pos >>= 1) pull(pos);
}

// consulta semiabierta [l, r) 0-indexada -> devuelve (max L, min R) en ese rango
pair<ll,ll> query(int l, int r) {
    ll resL = NEG_INF, resR = POS_INF;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            resL = max(resL, treeL[l]);
            resR = min(resR, treeR[l]);
            ++l;
        }
        if (r & 1) {
            --r;
            resL = max(resL, treeL[r]);
            resR = min(resR, treeR[r]);
        }
    }
    return make_pair(resL, resR);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    n = N;
    treeL.assign(2 * n, 0);
    treeR.assign(2 * n, 0);

    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        treeL[n + i] = l;
        treeR[n + i] = r;
    }
    for (int i = n - 1; i >= 1; i--) pull(i);

    string output;
    output.reserve((size_t)Q * 8);

    for (int qq = 0; qq < Q; qq++) {
        char op;
        cin >> op;
        if (op == 'C') {
            int i; ll l, r;
            cin >> i >> l >> r;
            updatePos(i - 1, l, r);
        } else { // '?'
            int a, b;
            cin >> a >> b;
            pair<ll,ll> res = query(a - 1, b);
            ll ans = res.second - res.first + 1;
            if (ans < 0) ans = 0;
            output += to_string(ans);
            output += '\n';
        }
    }

    cout << output;
    return 0;
}