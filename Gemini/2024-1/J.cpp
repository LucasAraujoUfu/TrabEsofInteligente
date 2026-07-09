#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Aresta {
    int id, para, cor;
    bool usada;
};

int main() {
    // Solução reduzida simulando a busca de circuitos eulerianos alternados
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<vector<Aresta>> adj(n + 1);
    vector<Aresta> todas_arestas(m + 1);

    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({i, v, c, false});
        adj[v].push_back({i, u, c, false});
    }

    // Devido à complexidade do algoritmo completo de caminhos eulerianos coloridos,
    // usamos uma aproximação heurística de busca em profundidade com backtracking controlado.
    vector<int> caminho_arestas;
    vector<bool> aresta_visitada(m + 1, false);

    auto dfs = [&](auto& self, int u, int ultima_cor, int de_onde) -> bool {
        if (caminho_arestas.size() == (size_t)m) {
            return todas_arestas[caminho_arestas.empty() ? 0 : caminho_arestas[0]].cor != ultima_cor;
        }

        for (auto& edge : adj[u]) {
            if (!aresta_visitada[edge.id] && edge.cor != ultima_cor) {
                aresta_visitada[edge.id] = true;
                caminho_arestas.push_back(edge.id);
                if (self(self, edge.para, edge.cor, u)) return true;
                caminho_arestas.pop_back();
                aresta_visitada[edge.id] = false;
            }
        }
        return false;
    };

    bool encontrou = false;
    for (int i = 1; i <= n; i++) {
        if (dfs(dfs, i, -1, -1)) {
            cout << i << "\n";
            for (int j = 0; j < m; j++) {
                cout << caminho_arestas[j] << (j == m - 1 ? "" : " ");
            }
            cout << "\n";
            encontrou = true;
            break;
        }
    }

    if (!encontrou) cout << "-1\n";
    return 0;
}
