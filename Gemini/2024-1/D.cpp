#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1e9 + 7;
long long N;
int M;
int memo[62][2005];

struct Magia {
    int a, b;
};
vector<Magia> magias;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N >> M)) return 0;

    magias.resize(M);
    for (int i = 0; i < M; i++) {
        cin >> magias[i].a >> magias[i].b;
    }

    // dp[carry] indicando número de maneiras de ter esse carry no bit atual
    vector<long long> dp(2005, 0);
    dp[0] = 1;

    for (int bit = 0; bit <= 60; bit++) {
        vector<long long> proximo_dp(2005, 0);
        int bit_atual = (N >> bit) & 1;

        // Transições completas usando Knapsack completo para as magias que podem ser usadas neste bit
        vector<long long> transicao = dp;
        for (const auto& m : magias) {
            if (m.b <= bit) {
                for (int c = m.a; c < 2005; c++) {
                    transicao[c] = (transicao[c] + transicao[c - m.a]) % MOD;
                }
            }
        }

        // Passando o carry para o próximo bit
        for (int c = 0; c < 2005; c++) {
            if (transicao[c] == 0) continue;
            if ((c & 1) == bit_atual) {
                int nxt_carry = c >> 1;
                proximo_dp[nxt_carry] = (proximo_dp[nxt_carry] + transicao[c]) % MOD;
            }
        }
        dp = move(proximo_dp);
    }

    cout << dp[0] << "\n";
    return 0;
}
