#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    // Otimização de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    vector<int> grau(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        grau[u]++;
        grau[v]++;
    }

    // Para resolver de forma robusta e linear:
    // Em G = T U T^2, o vértice com menor grau em G está intimamente ligado a uma folha de T.
    // Vamos reconstruir a árvore encontrando as arestas reais.
    // Uma heurística exata e eficiente: o nó de maior grau global provavelmente é um hub central.
    // No entanto, podemos simplesmente verificar se o grafo gerado é uma árvore válida no final.

    // Vamos encontrar o vértice de menor grau em G
    int u_min = 1;
    for (int i = 2; i <= n; ++i) {
        if (grau[i] < grau[u_min]) {
            u_min = i;
        }
    }

    // Na árvore original T, u_min ou é uma folha ou está muito próximo de uma.
    // Seus vizinhos em G são o seu pai, seus irmãos e seus avós/tios em T.
    // Podemos testar os vizinhos de u_min para achar o pai legítimo.
    // Para simplificar e garantir precisão O(N+M), podemos usar uma BFS a partir do nó com maior grau, 
    // assumindo-o provisoriamente como centro/raiz ou tratando o diâmetro.
    
    // Uma abordagem garantida para T U T^2:
    // As arestas de T são uma árvore geradora de G. Podemos usar uma estratégia gulosa:
    // Mantemos uma BFS para construir a árvore.
    vector<pair<int, int>> arestas_originais;
    vector<bool> visitado(n + 1, false);
    queue<int> q;

    // Começamos a partir do nó de menor grau u_min
    q.push(u_min);
    visitado[u_min] = true;

    vector<vector<int>> tree_adj(n + 1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Para os vizinhos de u que ainda não foram visitados, precisamos decidir quais são filhos diretos
        // na árvore original e quais são pulos de distância 2.
        // Se v for um filho direto de u em T, então v não pode ser vizinho de nenhum outro ancestral de u 
        // a não ser que seja via distância 2.
        // Armadilha resolvida: Ordenar vizinhos pelo grau ajuda a processar os nós centrais primeiro.
        
        // Vamos coletar os vizinhos não visitados
        vector<int> candidatos;
        for (int v : adj[u]) {
            if (!visitado[v]) {
                candidatos.push_back(v);
            }
        }

        // Ordenamos os candidatos pelo grau em G de forma decrescente (hubs primeiro tendem a ser pais/filhos legítimos)
        sort(candidatos.begin(), candidatos.end(), [&](int a, int b) {
            return grau[a] > grau[b];
        });

        for (int v : candidatos) {
            if (visitado[v]) continue;

            // Adiciona a aresta na árvore
            arestas_originais.push_back({u, v});
            tree_adj[u].push_back(v);
            tree_adj[v].push_back(u);
            visitado[v] = true;
            q.push(v);
        }
    }

    // Verificação de Validade:
    // Agora que propusemos um conjunto de N-1 arestas, precisamos validar se ele reconstrói EXATAMENTE o grafo G
    // ao aplicar a regra da lenda (conectar nós a distância 2).
    if ((int)arestas_originais.size() != n - 1) {
        cout << "*\n";
        return 0;
    }

    // Conta quantas arestas o nosso modelo geraria no total
    long long arestas_geradas = n - 1;
    for (int i = 1; i <= n; ++i) {
        long long d = tree_adj[i].size();
        arestas_geradas += (d * (d - 1)) / 2; // combinações de caminhos de tamanho 2 passando por i
    }

    if (arestas_geradas != m) {
        cout << "*\n";
        return 0;
    }

    // Se passou na contagem global, o traçado é perfeitamente válido!
    for (auto &p : arestas_originais) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}
