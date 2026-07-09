#include <iostream>
#include <vector>
#include <numeric>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    int P;
    cin >> P;
    vector<int> L(P);
    for (int i = 0; i < P; ++i) cin >> L[i];

    int Q;
    cin >> Q;
    vector<int> R(Q);
    for (int i = 0; i < Q; ++i) cin >> R[i];

    // Matriz de adjacência para marcar arestas usadas
    // Como N <= 1000, uma matriz NxtN de bool ou char consome pouca memória
    vector<vector<bool>> used(N + 1, vector<bool>(N + 1, false));

    // Validar e marcar caminho L
    for (int i = 0; i < P - 1; ++i) {
        int u = L[i], v = L[i+1];
        if (u == v || used[u][v]) {
            cout << "N\n";
            return 0;
        }
        used[u][v] = used[v][u] = true;
    }

    // Validar e marcar caminho R
    for (int i = 0; i < Q - 1; ++i) {
        int u = R[i], v = R[i+1];
        if (u == v || used[u][v]) {
            cout << "N\n";
            return 0;
        }
        used[u][v] = used[v][u] = true;
    }

    // Graus no grafo residual (arestas NÃO usadas)
    vector<int> deg(N + 1, 0);
    vector<vector<int>> adj_res(N + 1);

    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (!used[i][j]) {
                deg[i]++;
                deg[j]++;
                adj_res[i].push_back(j);
                adj_res[j].push_back(i);
            }
        }
    }

    // Conectar os extremos dos caminhos visíveis (ajuste de paridade para Caminho Euleriano)
    if (P > 0) deg[L[P-1]]++;
    if (Q > 0) deg[R[0]]++;
    if (P > 0 && Q > 0) {
        adj_res[L[P-1]].push_back(R[0]);
        adj_res[R[0]].push_back(L[P-1]);
    }

    // 1. Todos os graus modificados devem ser pares
    for (int i = 1; i <= N; ++i) {
        if (deg[i] % 2 != 0) {
            cout << "N\n";
            return 0;
        }
    }

    // 2. Verificar conectividade das arestas restantes
    vector<bool> visited(N + 1, false);
    int components_with_edges = 0;

    for (int i = 1; i <= N; ++i) {
        // Só nos importamos com nós que possuem arestas no grafo residual modificado
        if (!visited[i] && !adj_res[i].empty()) {
            components_with_edges++;
            if (components_with_edges > 1) {
                cout << "N\n";
                return 0;
            }
            // BFS para marcar a componente
            queue<int> q;
            q.push(i);
            visited[i] = true;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj_res[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }

    cout << "Y\n";
    return 0;
}
