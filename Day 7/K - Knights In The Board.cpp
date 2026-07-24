#include <bits/stdc++.h>
using namespace std;

int N, K;
map<pair<int,int>, int> pos2idx;
vector<int> R, C, color_;
vector<vector<int>> adj;
vector<int> matchRight;
vector<bool> visited;

int dr[8] = {1,1,-1,-1,2,2,-2,-2};
int dc[8] = {2,-2,2,-2,1,-1,1,-1};

bool tryKuhn(int u) {
    for (int v : adj[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (matchRight[v] == -1 || tryKuhn(matchRight[v])) {
                matchRight[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main(){
    cin >> N >> K;
    R.resize(K); C.resize(K); color_.resize(K);
    for (int i = 0; i < K; i++) {
        cin >> R[i] >> C[i];
        pos2idx[{R[i], C[i]}] = i;
        color_[i] = (R[i] + C[i]) % 2;
    }
    adj.assign(K, {});
    for (int i = 0; i < K; i++) {
        if (color_[i] != 0) continue;
        for (int d = 0; d < 8; d++) {
            auto it = pos2idx.find({R[i]+dr[d], C[i]+dc[d]});
            if (it != pos2idx.end()) adj[i].push_back(it->second);
        }
    }
    matchRight.assign(K, -1);
    int matching = 0;
    for (int i = 0; i < K; i++) {
        if (color_[i] != 0 || adj[i].empty()) continue;
        visited.assign(K, false);
        if (tryKuhn(i)) matching++;
    }
    cout << matching << "\n";
}