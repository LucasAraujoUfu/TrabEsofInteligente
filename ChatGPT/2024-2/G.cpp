#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000 + 5;

int N, Q;

vector<pair<int,int>> g[MAXN];

int parent[MAXN], depth[MAXN];
long long distRoot[MAXN];

int up[MAXN][20];

void dfs(int v, int p) {
    up[v][0] = p;
    for (auto [to,w] : g[v]) {
        if (to == p) continue;
        depth[to] = depth[v] + 1;
        distRoot[to] = distRoot[v] + w;
        dfs(to, v);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a,b);

    for (int k = 19; k >= 0; k--)
        if (depth[a] - (1<<k) >= depth[b])
            a = up[a][k];

    if (a == b) return a;

    for (int k = 19; k >= 0; k--) {
        if (up[a][k] != up[b][k]) {
            a = up[a][k];
            b = up[b][k];
        }
    }

    return up[a][0];
}

long long dist(int a, int b) {
    int c = lca(a,b);
    return distRoot[a] + distRoot[b] - 2 * distRoot[c];
}

vector<int> leaves;
int owner[MAXN];

void multiSource() {
    vector<long long> d(N+1, (long long)4e18);
    vector<int> src(N+1, -1);

    priority_queue<tuple<long long,int,int>, vector<tuple<long long,int,int>>, greater<>> pq;

    for (int i = 1; i <= N; i++) {
        if (g[i].size() == 1) {
            d[i] = 0;
            src[i] = i;
            pq.push({0, i, i});
        }
    }

    while (!pq.empty()) {
        auto [cd, v, s] = pq.top(); pq.pop();
        if (cd != d[v]) continue;

        for (auto [to,w] : g[v]) {
            if (d[to] > cd + w || (d[to] == cd + w && s < src[to])) {
                d[to] = cd + w;
                src[to] = s;
                pq.push({d[to], to, s});
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        owner[i] = src[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 0; i < N-1; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

    depth[1] = 0;
    distRoot[1] = 0;
    dfs(1,1);

    for (int k = 1; k < 20; k++) {
        for (int i = 1; i <= N; i++) {
            up[i][k] = up[ up[i][k-1] ][k-1];
        }
    }

    multiSource();

    cin >> Q;
    while (Q--) {
        int S, T;
        cin >> S >> T;

        int cnt = 0;

        for (int v = 1; v <= N; v++) {
            if (owner[v] != S) continue;
            if (dist(S, v) + dist(v, T) == dist(S, T)) {
                cnt++;
            }
        }

        cout << cnt << "\n";
    }

    return 0;
}
