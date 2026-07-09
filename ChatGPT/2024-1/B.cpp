#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    int M;
    cin >> N >> M;

    vector<vector<int>> g;

    // filmes: 0..N-1
    g.resize(N);

    unordered_map<int, int> actorNode;
    vector<int> actorId; // id original do ator para cada nó de ator

    auto getActorNode = [&](int actor) -> int {
        auto it = actorNode.find(actor);
        if (it != actorNode.end()) return it->second;

        int idx = (int)g.size();
        actorNode[actor] = idx;
        g.push_back({});
        actorId.push_back(actor);
        return idx;
    };

    for (int film = 0; film < N; film++) {
        int ni;
        cin >> ni;

        for (int j = 0; j < ni; j++) {
            int actor;
            cin >> actor;

            int aNode = getActorNode(actor);

            g[film].push_back(aNode);
            g[aNode].push_back(film);
        }
    }

    int V = (int)g.size();

    const int LOG = 18;

    vector<int> depth(V, 0);
    vector<int> comp(V, -1);
    vector<array<int, LOG>> up(V);

    for (int i = 0; i < V; i++)
        up[i].fill(-1);

    int compId = 0;

    for (int root = 0; root < V; root++) {
        if (comp[root] != -1) continue;

        queue<int> q;
        q.push(root);

        comp[root] = compId;
        depth[root] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int to : g[v]) {
                if (comp[to] != -1) continue;

                comp[to] = compId;
                depth[to] = depth[v] + 1;
                up[to][0] = v;

                for (int k = 1; k < LOG; k++) {
                    int p = up[to][k - 1];
                    if (p != -1)
                        up[to][k] = up[p][k - 1];
                }

                q.push(to);
            }
        }

        compId++;
    }

    auto lca = [&](int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);

        int diff = depth[a] - depth[b];

        for (int k = LOG - 1; k >= 0; k--) {
            if (diff & (1 << k))
                a = up[a][k];
        }

        if (a == b) return a;

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[a][k] != up[b][k]) {
                a = up[a][k];
                b = up[b][k];
            }
        }

        return up[a][0];
    };

    int Q;
    cin >> Q;

    while (Q--) {
        int x, y;
        cin >> x >> y;

        auto itx = actorNode.find(x);
        auto ity = actorNode.find(y);

        if (itx == actorNode.end() || ity == actorNode.end()) {
            cout << -1 << '\n';
            continue;
        }

        int ax = itx->second;
        int ay = ity->second;

        if (comp[ax] != comp[ay]) {
            cout << -1 << '\n';
            continue;
        }

        int w = lca(ax, ay);

        vector<int> leftPart;
        vector<int> rightPart;

        int cur = ax;
        while (cur != w) {
            leftPart.push_back(cur);
            cur = up[cur][0];
        }
        leftPart.push_back(w);

        cur = ay;
        while (cur != w) {
            rightPart.push_back(cur);
            cur = up[cur][0];
        }

        reverse(rightPart.begin(), rightPart.end());

        vector<int> path = leftPart;
        path.insert(path.end(), rightPart.begin(), rightPart.end());

        int actorsCount = ((int)path.size() + 1) / 2;
        cout << actorsCount << '\n';

        for (int i = 0; i < (int)path.size(); i++) {
            int node = path[i];

            if (node < N) {
                cout << (node + 1); // filme
            } else {
                cout << actorId[node - N]; // ator
            }

            if (i + 1 < (int)path.size()) cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}
