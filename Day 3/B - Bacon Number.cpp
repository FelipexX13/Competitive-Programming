#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> movieActors(N + 1);
    unordered_map<int, vector<int>> actorMovies;

    for (int i = 1; i <= N; i++) {
        int k;
        cin >> k;
        movieActors[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> movieActors[i][j];
            actorMovies[movieActors[i][j]].push_back(i);
        }
    }

    // actor común entre películas
    vector<vector<int>> common(N + 1, vector<int>(N + 1, 0));
    vector<vector<int>> adj(N + 1);

    for (auto &it : actorMovies) {
        auto &v = it.second;
        for (int i = 0; i < (int)v.size(); i++) {
            for (int j = i + 1; j < (int)v.size(); j++) {
                int a = v[i], b = v[j];
                if (!common[a][b]) {
                    common[a][b] = common[b][a] = it.first;
                    adj[a].push_back(b);
                    adj[b].push_back(a);
                }
            }
        }
    }

    vector<vector<int>> dist(N + 1, vector<int>(N + 1, INF));
    vector<vector<int>> parent(N + 1, vector<int>(N + 1, -1));

    for (int s = 1; s <= N; s++) {
        queue<int> q;
        dist[s][s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[s][v] == INF) {
                    dist[s][v] = dist[s][u] + 1;
                    parent[s][v] = u;
                    q.push(v);
                }
            }
        }
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int x, y;
        cin >> x >> y;

        if (!actorMovies.count(x) || !actorMovies.count(y)) {
            cout << -1 << '\n';
            continue;
        }

        int bestA = -1, bestB = -1, best = INF;

        for (int a : actorMovies[x])
            for (int b : actorMovies[y])
                if (dist[a][b] < best) {
                    best = dist[a][b];
                    bestA = a;
                    bestB = b;
                }

        if (best == INF) {
            cout << -1 << '\n';
            continue;
        }

        vector<int> movies;
        int cur = bestB;
        while (cur != bestA) {
            movies.push_back(cur);
            cur = parent[bestA][cur];
        }
        movies.push_back(bestA);
        reverse(movies.begin(), movies.end());

        vector<int> out;

        out.push_back(x);

        if (x != common[movies[0]][movies[0]])
            ; // nada

        int currentActor = x;

        if (actorMovies[x][0] != movies[0]) {
            // x aparece en movies[0] por construcción
        }

        for (int i = 0; i + 1 < (int)movies.size(); i++) {
            int actor = common[movies[i]][movies[i + 1]];
            if (currentActor != actor) {
                out.push_back(movies[i]);
                out.push_back(actor);
                currentActor = actor;
            } else {
                out.push_back(movies[i]);
            }
        }

        out.push_back(movies.back());

        if (currentActor != y)
            out.push_back(y);

        int actors = 0;
        for (int i = 0; i < (int)out.size(); i += 2)
            actors++;

        cout << actors << '\n';

        for (int i = 0; i < (int)out.size(); i++) {
            if (i) cout << ' ';
            cout << out[i];
        }
        cout << '\n';
    }
}