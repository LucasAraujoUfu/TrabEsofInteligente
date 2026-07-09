#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 1e9;

// Função para calcular o maior overlap entre o sufixo de 'a' e o prefixo de 'b'
int getOverlap(const string& a, const string& b) {
    int max_len = min(a.length(), b.length());
    for (int len = max_len; len > 0; --len) {
        if (a.substr(a.length() - len) == b.substr(0, len)) {
            return len;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<string> temp_strings(n);
    for (int i = 0; i < n; ++i) {
        cin >> temp_strings[i];
    }

    // Filtrar strings que já estão completamente contidas dentro de outras
    vector<string> s;
    for (int i = 0; i < n; ++i) {
        bool contida = false;
        for (int j = 0; j < n; ++j) {
            if (i != j && temp_strings[j].find(temp_strings[i]) != string::npos) {
                // Se têm o mesmo conteúdo, mantém apenas uma com base no índice
                if (temp_strings[i] == temp_strings[j] && i > j) continue;
                contida = true;
                break;
            }
        }
        if (!contida) {
            s.push_back(temp_strings[i]);
        }
    }

    n = s.size();

    // Pré-calcular a tabela de overlaps
    vector<vector<int>> overlap(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                overlap[i][j] = getOverlap(s[i], s[j]);
            }
        }
    }

    // dp[mask][u] -> mask armazena as strings usadas, u é a última string na ponta
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));

    // Casos base: iniciar a superstring com apenas uma única string
    for (int i = 0; i < n; ++i) {
        dp[1 << i][i] = s[i].length();
    }

    // Preencher a tabela DP
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int u = 0; u < n; ++u) {
            if (dp[mask][u] == INF) continue;

            for (int v = 0; v < n; ++v) {
                if (!(mask & (1 << v))) { // Se a string 'v' ainda não foi usada
                    int next_mask = mask | (1 << v);
                    int custo_adicional = s[v].length() - overlap[u][v];
                    dp[next_mask][v] = min(dp[next_mask][v], dp[mask][u] + custo_adicional);
                }
            }
        }
    }

    // Encontrar o menor comprimento contido na máscara com todas as strings preenchidas
    int total_mask = (1 << n) - 1;
    int ans = INF;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[total_mask][i]);
    }

    cout << ans << "\n";

    return 0;
}
