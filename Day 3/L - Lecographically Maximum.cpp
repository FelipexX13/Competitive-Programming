#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> cnt(31, 0);

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        for (int b = 0; b <= 30; b++)
            if (x & (1 << b))
                cnt[b]++;
    }

    vector<int> ans(N, 0);

    for (int b = 0; b <= 30; b++)
        for (int i = 0; i < cnt[b]; i++)
            ans[i] |= (1 << b);

    for (int i = 0; i < N; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}