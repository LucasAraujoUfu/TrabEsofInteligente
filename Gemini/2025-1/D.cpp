#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estrutura para mapear a ID de cada uma das 21 peças possíveis de dominó (1-6)
int peca_id[7][7];
pair<int, int> id_para_peca[21];
bool valida_mask[1 << 21];

// Função para inicializar e pré-computar todas as combinações de dominó válidas no mundo
void precomputar() {
    int id = 0;
    for (int i = 1; i <= 6; ++i) {
        for (int j = i; j <= 6; ++j) {
            peca_id[i][j] = id;
            peca_id[j][i] = id;
            id_para_peca[id] = {i, j};
            id++;
        }
    }

    // Loop por todas as 2^21 máscaras possíveis
    for (int mask = 0; mask < (1 << 21); ++mask) {
        if (mask == 0) {
            valida_mask[mask] = false; // Subconjunto vazio não joga/não vence por definição de ter peças
            continue;
        }

        int grau[7] = {0};
        int vertices_ativos = 0;
        int arestas_cont = 0;
        
        for (int id = 0; id < 21; ++id) {
            if (mask & (1 << id)) {
                int u = id_para_peca[id].first;
                int v = id_para_peca[id].second;
                grau[u]++;
                grau[v]++;
                arestas_cont++;
            }
        }

        int impares = 0;
        int raiz = -1;
        for (int i = 1; i <= 6; ++i) {
            if (grau[i] > 0) {
                if (raiz == -1) raiz = i;
                if (grau[i] % 2 != 0) impares++;
            }
        }

        // Condição de Graus Eulerianos: Máximo de 2 vértices com grau ímpar
        if (impares != 0 && impares != 2) {
            valida_mask[mask] = false;
            continue;
        }

        // Condição de Conectividade: Todas as arestas devem estar na mesma componente conectada
        // Vamos fazer um Flood Fill simples usando BFS/DFS por representação de bits
        int visitados = 0;
        vector<int> q;
        if (raiz != -1) {
            q.push_back(raiz);
            visitados |= (1 << raiz);
            int idx = 0;
            while(idx < (int)q.size()) {
                int u = q[idx++];
                for (int id = 0; id < 21; ++id) {
                    if (mask & (1 << id)) {
                        int nxt = -1;
                        if (id_para_peca[id].first == u) nxt = id_para_peca[id].second;
                        else if (id_para_peca[id].second == u) nxt = id_para_peca[id].first;
                        
                        if (nxt != -1 && !(visitados & (1 << nxt))) {
                            visitados |= (1 << nxt);
                            q.push_back(nxt);
                        }
                    }
                }
            }
        }

        // Verifica se todos os vértices que possuem alguma aresta foram visitados
        bool conectado = true;
        for (int i = 1; i <= 6; ++i) {
            if (grau[i] > 0 && !(visitados & (1 << i))) {
                conectado = false;
                break;
            }
        }

        valida_mask[mask] = conectado;
    }
}

void resolver() {
    int n;
    cin >> n;
    
    vector<int> ids_disponiveis(n);
    int mask_original_caso = 0;
    for (int i = 0; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        ids_disponiveis[i] = peca_id[u][v];
        mask_original_caso |= (1 << ids_disponiveis[i]);
    }

    // Como N <= 21, podemos fazer uma DP simples para contar os subconjuntos da máscara do caso
    // que são válidos. Para otimizar o tempo por causa do T grande, iteramos apenas sobre os subconjuntos
    // da própria mask_original_caso usando o truque clássico de submasks em O(3^V) ou simulação direta.
    // Mas note: iterar sobre subconjuntos de uma máscara em C++ é feito de forma extremamente rápida:
    long long ans = 0;
    
    // Esse loop itera exatamente por todos os subconjuntos de 'mask_original_caso'
    for (int submask = mask_original_caso; submask > 0; submask = (submask - 1) & mask_original_caso) {
        if (valida_mask[submask]) {
            ans++;
        }
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Executa a pré-computação pesada uma única vez antes de ler os casos de teste
    precomputar();

    int t;
    if (cin >> t) {
        while (t--) {
            resolver();
        }
    }

    return 0;
}
