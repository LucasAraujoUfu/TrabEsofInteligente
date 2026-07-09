#include <bits/stdc++.h>
using namespace std;

const int MAXM = 300000 + 5;

int N, M;

vector<pair<int,int>> g[MAXM];

int tin[MAXM], low[MAXM], timer;
bool isBridge[MAXM];

int U[MAXM], V[MAXM];

void dfsBridge(int v, int pe) {
    tin[v] = low[v] = ++timer;

    for (auto [to, id] : g[v]) {
        if (id == pe) continue;

        if (!tin[to]) {
            dfsBridge(to, id);
            low[v] = min(low[v], low[to]);

            if (low[to] > tin[v])
                isBridge[id] = true;
        } else {
            low[v] = min(low[v], tin[to]);
        }
    }
}

vector<int> path;
vector<int> parentEdge;
vector<int> vis;

bool found = false;

void dfsCycle(int v, int p) {
    vis[v] = 1;

    for (auto [to, id] : g[v]) {
        if (id == p || isBridge[id]) continue;

        if (!vis[to]) {
            parentEdge[to] = id;
            dfsCycle(to, id);
            if (found) return;
        } else if (vis[to] == 1) {
            // found cycle
            path.push_back(id);
            int cur = v;

            while (cur != to) {
                path.push_back(parentEdge[cur]);
                for (auto [nx, eid] : g[cur]) {
                    if (eid == parentEdge[cur]) {
                        cur = nx;
                        break;
                    }
                }
            }

            found = true;
            return;
        }
    }

    vis[v] = 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        cin >> U[i] >> V[i];

        g[U[i]].push_back({V[i], i});
        g[V[i]].push_back({U[i], i});
    }

    for (int i = 1; i <= N; i++) {
        if (!tin[i]) dfsBridge(i, -1);
    }

    vis.assign(N + 1, 0);
    parentEdge.assign(N + 1, -1);

    for (int i = 1; i <= N; i++) {
        if (!vis[i]) {
            dfsCycle(i, -1);
            if (found) break;
        }
    }

    if (!found || path.size() < 3) {
        cout << "*\n";
        return 0;
    }

    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i] << (i + 1 == (int)path.size() ? '\n' : ' ');
    }

    return 0;
}
