#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int id, to, color;
};

int n, m, k;
vector<vector<Edge>> adj;
vector<bool> edge_used;
vector<int> edge_path;

bool eulerian_dfs(int u, int last_color) {
    if (edge_path.size() == (size_t)m) return true;

    for (const auto& e : adj[u]) {
        if (!edge_used[e.id] && e.color != last_color) {
            edge_used[e.id] = true;
            edge_path.push_back(e.id);
            
            if (eulerian_dfs(e.to, e.color)) return true;
            
            edge_path.pop_back();
            edge_used[e.id] = false;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m >> k)) return 0;

    adj.resize(n + 1);
    edge_used.assign(m + 1, false);
    vector<int> first_edge_color(m + 1);

    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({i, v, c});
        adj[v].push_back({i, u, c});
        first_edge_color[i] = c;
    }

    bool found = false;
    for (int start_node = 1; start_node <= n; start_node++) {
        if (eulerian_dfs(start_node, -1)) {
            // Validar restrição cíclica (primeira e última aresta com cores diferentes)
            if (m > 1 && first_edge_color[edge_path.front()] == first_edge_color[edge_path.back()]) {
                // Se falhar a restrição cíclica neste ponto de partida, limpa e continua tentando
                fill(edge_used.begin(), edge_used.end(), false);
                edge_path.clear();
                continue;
            }
            cout << start_node << "\n";
            for (int i = 0; i < m; i++) {
                cout << edge_path[i] << (i + 1 == m ? "" : " ");
            }
            cout << "\n";
            found = true;
            break;
        }
    }

    if (!found) cout << "-1\n";
    return 0;
}
