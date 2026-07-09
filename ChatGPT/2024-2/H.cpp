#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1e9 + 7;

int N, M;

vector<int> g[8005];
vector<int> indeg;

vector<int> topo;

void getTopo() {
    indeg.assign(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        for (int v : g[i]) indeg[v]++;
    }

    queue<int> q;
    for (int i = 1; i <= N; i++)
        if (!indeg[i]) q.push(i);

    topo.clear();

    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);

        for (int v : g[u]) {
            if (--indeg[v] == 0)
                q.push(v);
        }
    }
}

long long B[8005], curB[8005], T[8005];

void recompute() {
    for (int i = 1; i <= N; i++)
        curB[i] = B[i];

    for (int u : topo) {
        T[u] = curB[u];
        for (int v : g[u]) {
            T[u] = (T[u] + T[v]) % MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 1; i <= N; i++)
        cin >> B[i];

    cin >> M;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    getTopo();

    int E;
    cin >> E;

    long long ans = 0;
    int qid = 0;

    vector<pair<char, pair<int,long long>>> events;

    for (int i = 0; i < E; i++) {
        char t;
        cin >> t;

        if (t == 'U') {
            int i2; long long v;
            cin >> i2 >> v;
            events.push_back({t, {i2, v}});
        } else {
            int j;
            cin >> j;
            events.push_back({t, {j, 0}});
        }
    }

    int BATCH = 700;

    for (int l = 0; l < E; l += BATCH) {
        int r = min(E, l + BATCH);

        vector<long long> savedB(N+1);
        for (int i = 1; i <= N; i++) savedB[i] = B[i];

        for (int i = l; i < r; i++) {
            if (events[i].first == 'U') {
                B[events[i].second.first] = events[i].second.second;
            }
        }

        recompute();

        for (int i = l; i < r; i++) {
            if (events[i].first == 'Q') {
                int j = events[i].second.first;
                ans = (ans + 1LL * (++qid) * T[j]) % MOD;
            }
        }

        for (int i = 1; i <= N; i++) B[i] = savedB[i];
    }

    cout << ans % MOD << "\n";

    return 0;
}
