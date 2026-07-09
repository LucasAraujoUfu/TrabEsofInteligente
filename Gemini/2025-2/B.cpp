#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N;
    int K;
    if (!(cin >> N >> K)) return 0;

    const int MOD = 998244353;

    // dp[q] armazenará o número de formas de ter uma média de 'q' balões por pessoa
    vector<long long> dp(K + 1, 0);
    
    // Passo 1: O primeiro membro traz entre 1 e K balões
    for (int q = 1; q <= K; ++q) {
        dp[q] = 1;
    }

    // Iterar para os próximos membros até min(N, K)
    int limit = min((long long)K, N);
    for (int i = 2; i <= limit; ++i) {
        vector<long long> next_dp(K + 1, 0);
        
        for (int q_prev = 1; q_prev <= K; ++q_prev) {
            if (dp[q_prev] == 0) continue;
            
            // Calcular a faixa de q_curr baseada em q_prev
            long long min_sum = (long long)(i - 1) * q_prev + 1;
            long long max_sum = (long long)(i - 1) * q_prev + K;
            
            // Encontrar o menor e maior q_curr inteiro no intervalo
            int min_q = (min_sum + i - 1) / i; // teto de min_sum / i
            int max_q = max_sum / i;           // piso de max_sum / i
            
            for (int q_curr = min_q; q_curr <= max_q; ++q_curr) {
                if (q_curr >= 1 && q_curr <= K) {
                    next_dp[q_curr] = (next_dp[q_curr] + dp[q_prev]) % MOD;
                }
            }
        }
        dp = move(next_dp);
    }

    // Somar todas as maneiras possíveis acumuladas no estado final
    long long ans = 0;
    for (int q = 1; q <= K; ++q) {
        ans = (ans + dp[q]) % MOD;
    }

    cout << ans << "\n";

    return 0;
}
