#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    int score;
};

struct DSU {
    vector<int> p, sz;

    DSU(int n) {
        p.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N + 1);
    vector<pair<int,int>> inputEdges;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        inputEdges.push_back({u, v});
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= N; i++)
        sort(g[i].begin(), g[i].end());

    vector<Edge> edges;

    for (auto [u, v] : inputEdges) {
        int cnt = 0;

        auto &A = g[u];
        auto &B = g[v];

        int i = 0, j = 0;
        while (i < (int)A.size() && j < (int)B.size()) {
            if (A[i] == B[j]) {
                cnt++;
                i++;
                j++;
            } else if (A[i] < B[j])
                i++;
            else
                j++;
        }

        edges.push_back({u, v, cnt});
    }

    sort(edges.begin(), edges.end(),
         [](const Edge &a, const Edge &b) {
             return a.score > b.score;
         });

    DSU dsu(N);

    vector<pair<int,int>> tree;
    vector<vector<int>> tg(N + 1);

    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            tree.push_back({e.u, e.v});
            tg[e.u].push_back(e.v);
            tg[e.v].push_back(e.u);
        }
    }

    if ((int)tree.size() != N - 1) {
        cout << "*\n";
        return 0;
    }

    set<pair<int,int>> generated;

    for (auto [u,v] : tree) {
        if (u > v) swap(u,v);
        generated.insert({u,v});
    }

    for (int c = 1; c <= N; c++) {
        auto &adj = tg[c];
        int s = adj.size();
        for (int i = 0; i < s; i++)
            for (int j = i + 1; j < s; j++) {
                int a = adj[i], b = adj[j];
                if (a > b) swap(a,b);
                generated.insert({a,b});
            }
    }

    set<pair<int,int>> original(inputEdges.begin(), inputEdges.end());

    if (generated != original) {
        cout << "*\n";
        return 0;
    }

    for (auto [u,v] : tree)
        cout << u << " " << v << "\n";

    return 0;
}
