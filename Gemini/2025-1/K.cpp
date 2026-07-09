#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Função que checa se é possível garantir que todos os segmentos tenham altura pelo menos H
bool possivel(long long H, const vector<long long>& x, int n, long long K) {
    long long j_maximo = n - 1; // Índice máximo permitido para j (0-indexed)
    long long i_maximo_necessitado = -1;

    for (int i = 0; i < n; ++i) {
        if (x[i] < H) {
            long long precisa = H - x[i];
            
            // Se o que o segmento precisa é maior do que o máximo que a escada dá (K), impossível
            if (precisa > K) return false;

            // Atualiza o maior índice que precisa de ajuda
            i_maximo_necessitado = max(i_maximo_necessitado, (long long)i);

            // Condição 1: K - (j - i) >= precisa  =>  j <= K + i - precisa
            long long limite1 = K + i - precisa;
            // Condição 2: j - i < K  =>  j <= i + K - 1
            long long limite2 = i + K - 1;

            j_maximo = min({j_maximo, limite1, limite2});
        }
    }

    // Se nenhum segmento precisa de ajuda, a altura H já foi atingida originalmente
    if (i_maximo_necessitado == -1) return true;

    // Para ser possível, o ponto de aplicação j_maximo deve conseguir cobrir até o último necessitado à direita
    return j_maximo >= i_maximo_necessitado;
}

int main() {
    // Otimização de I/O padrão da ICPC
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long K;
    if (!(cin >> n >> K)) return 0;

    vector<long long> x(n);
    long long min_inicial = 2e18;
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        min_inicial = min(min_inicial, x[i]);
    }

    // Busca binária na resposta (na altura mínima final)
    long long low = min_inicial;
    long long high = min_inicial + K;
    long long ans = min_inicial;

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (possivel(mid, x, n, K)) {
            ans = mid;        // Armazena o melhor resultado válido encontrado
            low = mid + 1;    // Tenta uma altura ainda maior
        } else {
            high = mid - 1;   // Reduz o alvo de altura
        }
    }

    cout << ans << "\n";

    return 0;
}
