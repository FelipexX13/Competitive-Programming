#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long ans = 0;

    for (int i = 1; i <= n; i++) 
    {
        long long x;
        cin >> x;
        ans += x * 1LL * i * (n - i + 1);
    }

    cout << ans << endl;
    return 0;
}