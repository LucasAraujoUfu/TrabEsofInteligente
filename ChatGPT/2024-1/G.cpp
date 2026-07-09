#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int N, Q;
long long val[MAXN];
vector<int> g[MAXN];

long long sum[MAXN];
int best[MAXN];

void dfs(int u) {
    if (u <= N) {
        sum[u] = val[u];
        best[u] = u;
        return;
    }

    int a = g[u][0];
    int b = g[u][1];

    dfs(a);
    dfs(b);

    sum[u] = sum[a] + sum[b];

    if (sum[a] > sum[b]) best[u] = best[a];
    else if (sum[b] > sum[a]) best[u] = best[b];
    else best[u] = min(best[a], best[b]);
}

void update(int u, int target) {
    if (u <= N) {
        if (u == target) sum[u]++, val[u]++;
        return;
    }

    int a = g[u][0];
    int b = g[u][1];

    if (a >= 1 && a <= N) dfs(a);
    else update(a, target);

    if (b >= 1 && b <= N) dfs(b);
    else update(b, target);

    sum[u] = sum[a] + sum[b];

    if (sum[a] > sum[b]) best[u] = best[a];
    else if (sum[b] > sum[a]) best[u] = best[b];
    else best[u] = min(best[a], best[b]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 1; i <= N; i++) {
        cin >> val[i];
    }

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        int id = N + i + 1;
        g[id].push_back(a);
        g[id].push_back(b);
    }

    int root = 2 * N - 1;

    dfs(root);

    cout << best[root] << "\n";

    cin >> Q;
    while (Q--) {
        int v;
        long long q;
        cin >> v >> q;

        val[v] += q;

        dfs(root);

        cout << best[root] << "\n";
    }

    return 0;
}
