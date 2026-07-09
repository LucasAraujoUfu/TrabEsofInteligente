#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

struct Limpador {
    long long custo_por_rua;
    // Adicionar outros atributos como limite_max_ruas se especificado no enunciado
};

int main() {
    // Otimização de I/O para Maratona
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N; // Número de limpadores disponíveis
    long long S; // Total de ruas a serem limpas
    if (!(cin >> N >> S)) return 0;

    vector<Limpador> limpadores(N);
    for (int i = 0; i < N; ++i) {
        cin >> limpadores[i].custo_por_rua;
    }

    // dp[j] guardará o custo mínimo para limpar exatamente j ruas
    vector<long long> dp(S + 1, INF);
    dp[0] = 0;

    // Processar cada limpador
    for (int i = 0; i < N; ++i) {
        long long custo = limpadores[i].custo_por_rua;
        
        // Criamos um vetor temporário para a transição, pois cada limpador contratado 
        // deve limpar PELO MENOS 1 rua (s_i >= 1) e não pode ser recontado incorretamente.
        vector<long long> next_dp(S + 1, INF);
        
        for (int j = 0; j <= S; ++j) {
            if (dp[j] == INF) continue;
            
            // Atribuir 'k' ruas para o limpador i (onde k >= 1)
            for (int k = 1; j + k <= S; ++k) {
                long long custo_adicional = k * custo;
                next_dp[j + k] = min(next_dp[j + k], dp[j] + custo_adicional);
            }
        }
        
        // Se o problema permitir que o limpador NÃO seja contratado (s_i = 0),
        // mantemos também os estados anteriores combinados:
        for (int j = 0; j <= S; ++j) {
            next_dp[j] = min(next_dp[j], dp[j]);
        }
        
        dp = move(next_dp);
    }

    // Saída do resultado
    if (dp[S] == INF) {
        cout << -1 << "\n"; // Caso seja impossível cumprir as metas exatas
    } else {
        cout << dp[S] << "\n";
    }

    return 0;
}
