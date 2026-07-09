#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> dist, matchL, matchR;

    HopcroftKarp(int n, int m): n(n), m(m) {
        adj.resize(n + 1);
        matchL.assign(n + 1, 0);
        matchR.assign(m + 1, 0);
        dist.resize(n + 1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (!matchL[i]) dist[i] = 0, q.push(i);
            else dist[i] = -1;
        }

        bool found = false;

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int v : adj[u]) {
                int w = matchR[v];
                if (!w) found = true;
                else if (dist[w] == -1) {
                    dist[w] = dist[u] + 1;
                    q.push(w);
                }
            }
        }

        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int w = matchR[v];
            if (!w || (dist[w] == dist[u] + 1 && dfs(w))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int maxMatching() {
        int res = 0;
        while (bfs()) {
            for (int i = 1; i <= n; i++)
                if (!matchL[i] && dfs(i))
                    res++;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<string> a(N);
    for (auto &s : a) cin >> s;

    HopcroftKarp hk(N, N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j && a[i][j] == '0') {
                hk.addEdge(i + 1, j + 1);
            }
        }
    }

    cout << hk.maxMatching() << "\n";

    return 0;
}
