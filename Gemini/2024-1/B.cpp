#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Grafo: atores 1..M e filmes (M+1)..(M+n)
    vector<vector<int>> adj(m + n + 1);
    for (int i = 1; i <= n; i++) {
        int ni;
        cin >> ni;
        for (int j = 0; j < ni; j++) {
            int ator;
            cin >> ator;
            adj[ator].push_back(m + i);
            adj[m + i].push_back(ator);
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;

        if (x == y) {
            cout << "1\n" << x << "\n";
            continue;
        }

        queue<int> fila;
        vector<int> pai(m + n + 1, 0);
        vector<bool> visitado(m + n + 1, false);

        fila.push(x);
        visitado[x] = true;
        bool achou = false;

        while (!fila.empty()) {
            int u = fila.front();
            fila.pop();

            if (u == y) {
                achou = true;
                break;
            }

            for (int v : adj[u]) {
                if (!visitado[v]) {
                    visitado[v] = true;
                    pai[v] = u;
                    fila.push(v);
                }
            }
        }

        if (!achou) {
            cout << "-1\n";
        } else {
            vector<int> caminho;
            int atual = y;
            while (atual != x) {
                caminho.push_back(atual);
                atual = pai[atual];
            }
            caminho.push_back(x);
            reverse(caminho.begin(), caminho.end());

            // Contar quantos atores existem no caminho alternado
            // O caminho possui a estrutura: ator1 -> filme1 -> ator2 -> filme2 -> ator3
            int num_atores = (caminho.size() + 1) / 2;
            cout << num_atores << "\n";
            for (size_t i = 0; i < caminho.size(); i++) {
                if (caminho[i] > m) {
                    cout << caminho[i] - m << (i == camino.size() - 1 ? "" : " ");
                } else {
                    cout << caminho[i] << (i == camino.size() - 1 ? "" : " ");
                }
            }
            cout << "\n";
        }
    }

    return 0;
}
