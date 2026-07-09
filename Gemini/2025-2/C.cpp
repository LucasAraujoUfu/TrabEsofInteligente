#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Otimização de I/O para Maratona
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long V;
    if (!(cin >> n >> V)) return 0;

    vector<long long> moedas(n);
    for (int i = 0; i < n; ++i) {
        cin >> moedas[i];
    }

    // Se o sistema for estritamente canônico (ex: potências), a abordagem gulosa é O(N):
    // (Descomente ou use se o enunciado garantir propriedades gulosas)
    /*
    long long qtd_moedas = 0;
    sort(moedas.rbegin(), moedas.rend()); // Ordena do maior para o menor
    for (int i = 0; i < n; ++i) {
        if (V >= moedas[i]) {
            qtd_moedas += V / moedas[i];
            V %= moedas[i];
        }
    }
    if (V == 0) cout << qtd_moedas << "\n";
    else cout << -1 << "\n";
    return 0;
    */

    // Caso necessite de Programação Dinâmica devido a moedas arbitrárias:
    // Aloca vetor de DP até V (ajustar caso V seja gigante, o que exigiria DP de dígitos)
    const long long INF = 1e18;
    vector<long long> dp(V + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= V; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i >= moedas[j] && dp[i - moedas[j]] != INF) {
                dp[i] = min(dp[i], dp[i - moedas[j]] + 1);
            }
        }
    }

    if (dp[V] == INF) {
        cout << -1 << "\n";
    } else {
        cout << dp[V] << "\n";
    }

    return 0;
}
