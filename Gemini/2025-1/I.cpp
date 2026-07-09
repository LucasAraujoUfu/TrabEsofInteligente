#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Estrutura para armazenar as coordenadas de uma estrela
struct Estrela {
    long long x, y;
};

int main() {
    // Otimização de I/O para Maratona
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Estrela> estrelas(n);
    for (int i = 0; i < n; ++i) {
        cin >> estrelas[i].x >> estrelas[i].y;
    }

    // Limites para R_1: [L, TR]
    long long L = 1; 
    long long TR = 2e18; // Inicializado com um valor suficientemente grande

    // C_i atual na recorrência. Para i = 1 (ímpar), R_1 = 0 + R_1, logo C_1 = 0.
    long long C_atual = 0; 

    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            // i é 0-indexed no código, o que corresponde aos índices ímpares (1, 3, 5...) do problema
            // R_i = C_atual + R_1 >= 1  =>  R_1 >= 1 - C_atual
            L = max(L, 1 - C_atual);
        } else {
            // Correspondente aos índices pares (2, 4, 6...) do problema
            // R_i = C_atual - R_1 >= 1  =>  R_1 <= C_atual - 1
            TR = min(TR, C_atual - 1);
        }

        // Se ainda houver uma próxima estrela, atualiza a constante C_atual para o próximo passo
        if (i < n - 1) {
            long long dist = abs(estrelas[i].x - estrelas[i+1].x) + abs(estrelas[i].y - estrelas[i+1].y);
            // R_i + R_{i+1} = D_i  =>  R_{i+1} = D_i - R_i
            // Se i era ímpar: R_{i+1} = D_i - (C_atual + R_1) = (D_i - C_atual) - R_1
            // Se i era par:   R_{i+1} = D_i - (C_atual - R_1) = (D_i - C_atual) + R_1
            C_atual = dist - C_atual;
        }
    }

    // Verifica se o intervalo encontrado é válido
    if (L <= TR) {
        cout << TR << "\n";
    } else {
        cout << -1 << "\n";
    }

    return 0;
}
