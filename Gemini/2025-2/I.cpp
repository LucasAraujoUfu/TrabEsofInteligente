#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

const long long INF_TIME = 1e18;

struct Aresta {
    int v;
    long long tempo;
    double prob;
};

// Estrutura para os estados da Fila de Prioridade
struct Estado {
    long long tempo;
    double prob;
    int u;

    // Critério de ordenação para a priority_queue (min-heap para tempo, max-heap para probabilidade)
    bool operator<(const Estado& outro) const {
        if (tempo != outro.tempo) {
            return tempo > outro.tempo; // Menor tempo tem maior prioridade
        }
        return prob < outro.prob; // Maior probabilidade tem maior prioridade
    }
};

int main() {
    // Otimização de I/O para Maratona
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s;
    if (!(cin >> n >> m >> s)) return 0;

    vector<vector<Aresta>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long t;
        double p;
        cin >> u >> v >> t >> p;
        adj[u].push_back({v, t, p});
        adj[v].push_back({u, t, p}); // Se o grafo for não-direcionado
    }

    // Vetores de distância (tempo) e probabilidade máxima alcançada
    vector<long long> dist_tempo(n + 1, INF_TIME);
    vector<double> max_prob(n + 1, -1.0);

    priority_queue<Estado> pq;

    // Inicialização a partir do hospital de origem S
    dist_tempo[s] = 0;
    max_prob[s] = 1.0; // 100% de chance no ponto de origem
    pq.push({0, 1.0, s});

    while (!pq.empty()) {
        Estado atual = pq.top();
        pq.pop();

        int u = atual.u;

        // Se encontramos um estado pior do que o já registrado, descartamos
        if (atual.tempo > dist_tempo[u] || (atual.tempo == dist_tempo[u] && atual.prob < max_prob[u])) {
            continue;
        }

        // Relaxação das arestas adjacentes
        for (const auto& vizinho : adj[u]) {
            int v = vizinho.v;
            long long novo_tempo = dist_tempo[u] + vizinho.tempo;
            double nova_prob = max_prob[u] * vizinho.prob;

            // Condição 1: Encontrou um tempo estritamente menor
            // Condição 2: Encontrou o mesmo tempo, mas com probabilidade maior
            if (novo_tempo < dist_tempo[v]) {
                dist_tempo[v] = novo_tempo;
                max_prob[v] = nova_prob;
                pq.push({novo_tempo, nova_prob, v});
            } 
            else if (novo_tempo == dist_tempo[v] && nova_prob > max_prob[v]) {
                max_prob[v] = nova_prob;
                pq.push({novo_tempo, nova_prob, v});
            }
        }
    }

    // Saída dos resultados para cada hospital de 1 a N
    cout << fixed << setprecision(6);
    for (int i = 1; i <= n; ++i) {
        if (dist_tempo[i] == INF_TIME) {
            cout << "-1 -1\n"; // Hospital seguro/inalcançável
        } else {
            cout << dist_tempo[i] << " " << max_prob[i] << "\n";
        }
    }

    return 0;
}
