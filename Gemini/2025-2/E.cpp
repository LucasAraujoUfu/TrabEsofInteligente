#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estrutura para representar uma aresta no grafo
struct Aresta {
    int u, v;
    long long custo;
    bool operator<(const Aresta& outra) const {
        return custo < outra.custo;
    }
};

// Estrutura para o Union-Find (Disjoint Set Union)
struct DSU {
    vector<int> pai;
    DSU(int n) {
        pai.resize(n + 1);
        for (int i = 0; i <= n; ++i) pai[i] = i;
    }
    int find(int i) {
        if (pai[i] == i) return i;
        return pai[i] = find(pai[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            pai[root_i] = root_j;
            return true;
        }
        return false;
    }
};

int main() {
    // Otimização de I/O para Maratona
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    // N: total de nós, M: arestas existentes, K: nós iniciais da coleção
    if (!(cin >> n >> m >> k)) return 0;

    DSU dsu(n);

    // Ler os K nós que já fazem parte da coleção inicial
    // Unimos todos eles em uma única componente com custo 0
    int primeiro_no;
    if (k > 0) {
        cin >> primeiro_no;
        for (int i = 1; i < k; ++i) {
            int no;
            cin >> no;
            dsu.unite(primeiro_no, no);
        }
    }

    // Ler todas as M arestas possíveis para a expansão
    vector<Aresta> arestas(m);
    for (int i = 0; i < m; ++i) {
        cin >> arestas[i].u >> arestas[i].v >> arestas[i].custo;
    }

    // Ordenar as arestas pelo custo (Kruskal)
    sort(arestas.begin(), arestas.end());

    long long custo_total = 0;
    int arestas_conectadas = 0;

    // Aplicar Kruskal para expandir a coleção para os nós restantes
    for (int i = 0; i < m; ++i) {
        if (dsu.unite(arestas[i].u, arestas[i].v)) {
            custo_total += arestas[i].custo;
            arestas_conectadas++;
        }
    }

    // Verifica se todos os nós foram conectados com sucesso à coleção
    // O número de arestas necessárias para conectar N nós em 1 componente é N - 1.
    // Mas como já unimos K nós inicialmente, precisamos de (N - 1) - (K - 1) = N - K arestas.
    if (arestas_conectadas == n - (k > 0 ? k : 1)) {
        cout << custo_total << "\n";
    } else {
        // Se não foi possível expandir para todos os nós exigidos
        cout << -1 << "\n";
    }

    return 0;
}
