#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int p[7];

    DSU() {
        for (int i = 1; i <= 6; i++) p[i] = i;
    }

    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) p[a] = b;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<pair<int,int>> e(N);
        for (int i = 0; i < N; i++)
            cin >> e[i].first >> e[i].second;

        long long ans = 0;
        int LIM = 1 << N;

        for (int mask = 0; mask < LIM; mask++) {
            int deg[7] = {};
            DSU dsu;

            for (int i = 0; i < N; i++) {
                if (!(mask & (1 << i))) continue;

                auto [u,v] = e[i];
                deg[u]++;
                deg[v]++;
                dsu.unite(u,v);
            }

            int root = -1;
            bool ok = true;

            for (int v = 1; v <= 6; v++) {
                if (deg[v] == 0) continue;
                if (root == -1)
                    root = dsu.find(v);
                else if (dsu.find(v) != root) {
                    ok = false;
                    break;
                }
            }

            if (!ok) continue;

            int odd = 0;
            for (int v = 1; v <= 6; v++)
                odd += deg[v] & 1;

            if (odd == 0 || odd == 2)
                ans++;
        }

        cout << ans << '\n';
    }

    return 0;
}
