#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

// Função para calcular a potência modular (A^B)%MOD
long long powmod(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// Inverso multiplicativo modular via Pequeno Teorema de Fermat
long long modInverse(long long n) {
    return powmod(n, MOD - 2);
}

int main() {
    // Otimização de I/O para Maratona
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> X(q + 1);
    for (int i = 1; i <= q; ++i) {
        cin >> X[i];
    }

    // Pré-computação das potências de 2 e de 0.5 (inverso de 2)
    vector<long long> inv2(q + 1), pow2(q + 1);
    inv2[0] = 1;
    pow2[0] = 1;
    long long INV_2 = modInverse(2);

    for (int i = 1; i <= q; ++i) {
        inv2[i] = (inv2[i - 1] * INV_2) % MOD;
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    // Pré-computação das somas de prefixo S[t] = somatório (0.5^k * X_k)
    vector<long long> S(q + 1, 0);
    for (int k = 1; k <= q; ++k) {
        long long termo = (inv2[k] * X[k]) % MOD;
        S[k] = (S[k - 1] + termo) % MOD;
    }

    // Estruturas para a atualização Lazy
    vector<long long> val(n + 1, 0);
    vector<int> last_t(n + 1, 0);
    vector<long long> E(n + 1, 0);

    // Estado inicial no tempo t=0: robô na mesa 1 com probabilidade 1.0
    val[1] = 1; 

    // Simulação amortizada em O(1) por comando
    for (int t = 1; t <= q; ++t) {
        int j = X[t];

        // Calcula a contribuição acumulada no intervalo em que val[j] ficou constante
        long long delta_S = (S[t] + MOD - S[last_t[j]]) % MOD;
        long long ganho = (val[j] * delta_S) % MOD;
        E[j] = (E[j] + ganho) % MOD;

        // Atualiza a representação da probabilidade da mesa j
        val[j] = (val[j] + pow2[t - 1]) % MOD;
        last_t[j] = t;
    }

    // Atualização final para todas as mesas até o tempo total Q
    for (int j = 1; j <= n; ++j) {
        long long delta_S = (S[q] + MOD - S[last_t[j]]) % MOD;
        long long ganho = (val[j] * delta_S) % MOD;
        E[j] = (E[j] + ganho) % MOD;
    }

    // Impressão dos valores esperados para cada mesa
    for (int j = 1; j <= n; ++j) {
        cout << E[j] << "\n";
    }

    return 0;
}
