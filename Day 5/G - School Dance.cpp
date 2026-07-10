#include <bits/stdc++.h>
using namespace std;

int n, m, k;
vector<vector<int>> pairs;
vector<int> matchGirl;
vector<bool> visited;

bool tryMatch(int boy) {
    if (visited[boy]) return false;
    visited[boy] = true;

    for (int girl : pairs[boy]) {
        if (matchGirl[girl] == 0 || tryMatch(matchGirl[girl])) {
            matchGirl[girl] = boy;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    pairs.assign(n + 1, {});

    for (int i = 0; i < k; i++) {
        int boy, girl;
        cin >> boy >> girl;
        pairs[boy].push_back(girl);
    }

    matchGirl.assign(m + 1, 0);

    int maximumPairs = 0;

    for (int boy = 1; boy <= n; boy++) {
        visited.assign(n + 1, false);
        if (tryMatch(boy)) {
            maximumPairs++;
        }
    }

    cout << maximumPairs << endl;

    for (int girl = 1; girl <= m; girl++) {
        if (matchGirl[girl] != 0) {
            cout << matchGirl[girl] << " " << girl << endl;
        }
    }

    return 0;
}