#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, id, color;
};

int N, M, K;

vector<vector<Edge>> g;
vector<int> eu_path;
vector<int> used;

bool dfs(int v, int cnt, int lastColor) {
    if (cnt == M) {
        return true;
    }

    for (auto &e : g[v]) {
        if (used[e.id]) continue;
        if (e.color == lastColor) continue;

        used[e.id] = 1;
        eu_path.push_back(e.id);

        if (dfs(e.to, cnt + 1, e.color)) return true;

        used[e.id] = 0;
        eu_path.pop_back();
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;

    g.assign(N + 1, {});

    vector<pair<int,int>> edges(M + 1);
    vector<int> color(M + 1);

    for (int i = 1; i <= M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        edges[i] = {u, v};
        color[i] = c;

        g[u].push_back({v, i, c});
        g[v].push_back({u, i, c});
    }

    // checagem simples de conectividade (ignora cores)
    vector<int> vis(N + 1, 0);
    function<void(int)> dfs0 = [&](int v) {
        vis[v] = 1;
        for (auto &e : g[v]) {
            if (!vis[e.to]) dfs0(e.to);
        }
    };

    int start = 1;
    dfs0(start);

    for (int i = 1; i <= N; i++) {
        if (!vis[i]) {
            cout << -1 << "\n";
            return 0;
        }
    }

    used.assign(M + 1, 0);

    for (int i = 1; i <= N; i++) {
        eu_path.clear();
        fill(used.begin(), used.end(), 0);

        if (dfs(i, 0, -1)) {
            cout << i << "\n";
            for (int e : eu_path)
                cout << e << " ";
            cout << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}
