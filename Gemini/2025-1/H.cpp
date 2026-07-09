#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Otimização de I/O para Maratona
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // Vetor para contar a frequência de cada máscara de habilidades individual
    int max_mask = 1 << k;
    vector<long long> f(max_mask, 0);

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int mask = 0;
        for (int j = 0; j < k; ++j) {
            if (s[j] == '1') {
                mask |= (1 << j);
            }
        }
        f[mask]++;
    }

    // Passo 1: SOS DP para computar f(S) -> número de alunos cuja máscara é subconjunto de S
    for (int i = 0; i < k; ++i) {
        for (int mask = 0; mask < max_mask; ++mask) {
            if (mask & (1 << i)) {
                f[mask] += f[mask ^ (1 << i)];
            }
        }
    }

    // Passo 2: Computar g(S) -> número de trincas cujas habilidades combinadas são subconjunto de S
    vector<long long> g(max_mask, 0);
    for (int mask = 0; mask < max_mask; ++mask) {
        long long cnt = f[mask];
        if (cnt >= 3) {
            g[mask] = cnt * (cnt - 1) * (cnt - 2) / 6;
        }
    }

    // Passo 3: SOS DP Inverso (Inversão de Möbius) para computar Ans(E)
    // Transforma a contagem de subconjuntos na quantidade exata
    for (int i = 0; i < k; ++i) {
        for (int mask = 0; mask < max_mask; ++mask) {
            if (mask & (1 << i)) {
                g[mask] -= g[mask ^ (1 << i)];
            }
        }
    }

    // Responder a cada uma das M consultas em O(1)
    int m;
    cin >> m;
    while (m--) {
        string s;
        cin >> s;
        int query_mask = 0;
        for (int j = 0; j < k; ++j) {
            if (s[j] == '1') {
                query_mask |= (1 << j);
            }
        }
        cout << g[query_mask] << "\n";
    }

    return 0;
}
