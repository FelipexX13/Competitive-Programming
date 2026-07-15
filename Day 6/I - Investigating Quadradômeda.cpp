#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> x(n), y(n);
    for(int i = 0; i < n; i++) cin >> x[i] >> y[i];

    // R_i = (-1)^(i-1) * R_1 + C_i, with C_1 = 0 and C_{i+1} = d_i - C_i
    // Need R_i >= 1 for all i:
    //   i odd  -> R_1 >= 1 - C_i   (lower bound)
    //   i even -> R_1 <= C_i - 1   (upper bound)
    // Also R_i < d_i for i < n is automatically implied by R_{i+1} >= 1.

    long long C = 0; // C_i, starts at C_1 = 0
    long long L = LLONG_MIN;
    long long U = LLONG_MAX;

    for(int i = 1; i <= n; i++){
        if(i % 2 == 1){
            // odd index: lower bound constraint
            L = max(L, 1 - C);
        } else {
            // even index: upper bound constraint
            U = min(U, C - 1);
        }
        if(i < n){
            long long d;
            if(x[i - 1] == x[i]){
                d = llabs(y[i] - y[i - 1]);
            } else {
                d = llabs(x[i] - x[i - 1]);
            }
            C = d - C;
        }
    }

    if(L > U){
        cout << -1 << "\n";
    } else {
        cout << U << "\n";
    }

    return 0;
}