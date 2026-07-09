#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Aresta {
    int para;
    double peso;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, origem, destino;
    if (!(cin >> n >> m >> origem >> destino)) return 0;

    vector<vector<Aresta>> adj(n + 1);
    vector<int> grau_entrada(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        grau_entrada[v]++;
    }

    // Ordenação Topológica (Algoritmo de Kahn)
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (grau_entrada[i] == 0) {
            q.push(i);
        }
    }

    vector<int> ordem_topologica;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ordem_topologica.push_back(u);

        for (auto& edge : adj[u]) {
            grau_entrada[edge.para]--;
            if (grau_entrada[edge.para] == 0) {
                q.push(edge.para);
            }
        }
    }

    // DP para encontrar o caminho de produto máximo
    // Usamos -1.0 para indicar que o vértice ainda é inalcançável
    vector<double> dp(n + 1, -1.0);
    dp[origem] = 1.0;

    for (int u : ordem_topologica) {
        if (dp[u] < 0) continue; // Inalcançável a partir da origem

        for (auto& edge : adj[u]) {
            if (dp[u] * edge.peso > dp[edge.para]) {
                dp[edge.para] = dp[u] * edge.peso;
            }
        }
    }

    if (dp[destino] < 0) {
        cout << "-1\n";
    } else {
        cout << fixed;
        cout.precision(6);
        cout << dp[destino] << "\n";
    }

    return 0;
}
