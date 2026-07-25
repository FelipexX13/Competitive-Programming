#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<double> X(N), Y(N);
    for (int i = 0; i < N; i++) cin >> X[i] >> Y[i];

    vector<vector<double>> dist(N, vector<double>(N, 0.0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double dx = X[i] - X[j], dy = Y[i] - Y[j];
            dist[i][j] = sqrt(dx * dx + dy * dy);
        }
    }

    vector<int> nonCap;
    for (int v = K; v < N; v++) nonCap.push_back(v);
    int M = (int)nonCap.size();

    const double INF = 1e18;
    int fullMask = (1 << K) - 1;
    // dp[mask][idx] : idx indexes into nonCap (0..M-1)
    vector<vector<double>> dp(1 << K, vector<double>(M, INF));

    // base case: each capital connects directly to each non-capital
    for (int i = 0; i < K; i++) {
        for (int idx = 0; idx < M; idx++) {
            dp[1 << i][idx] = dist[i][nonCap[idx]];
        }
    }

    for (int mask = 1; mask <= fullMask; mask++) {
        // MERGE step: combine two disjoint submasks meeting at the same non-capital
        for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
            int other = mask ^ sub;
            if (sub < other) {
                for (int idx = 0; idx < M; idx++) {
                    double cand = dp[sub][idx] + dp[other][idx];
                    if (cand < dp[mask][idx]) dp[mask][idx] = cand;
                }
            }
        }

        // EXTEND step: simple O(M^2) Dijkstra among non-capitals only
        vector<bool> done(M, false);
        for (int iter = 0; iter < M; iter++) {
            int u = -1;
            double best = INF;
            for (int idx = 0; idx < M; idx++) {
                if (!done[idx] && dp[mask][idx] < best) { best = dp[mask][idx]; u = idx; }
            }
            if (u == -1) break;
            done[u] = true;
            for (int w = 0; w < M; w++) {
                if (!done[w]) {
                    double cand = dp[mask][u] + dist[nonCap[u]][nonCap[w]];
                    if (cand < dp[mask][w]) dp[mask][w] = cand;
                }
            }
        }
    }

    double answer = INF;
    for (int idx = 0; idx < M; idx++) answer = min(answer, dp[fullMask][idx]);

    printf("%.5f\n", answer);
    return 0;
}