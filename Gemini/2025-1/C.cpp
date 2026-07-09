#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Otimização de I/O para a ICPC
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Usamos unsigned long long para evitar qualquer overflow de bits durante o crescimento do polinômio
    unsigned long long mask = 0;

    // Lendo os coeficientes: a_N, a_{N-1}, ..., a_0
    for (int i = n; i >= 0; --i) {
        int coef;
        cin >> coef;
        if (coef == 1) {
            mask |= (1ULL << i);
        }
    }

    long long operacoes = 0;

    // O processo repete até que o polinômio se reduza a P(x) = 1 (apenas o bit 0 ativo)
    while (mask > 1) {
        if (mask & 1) {
            // Possui termo constante (bit 0 é 1)
            // P(x)*(x + 1) + 1 equivalente a: (mask << 1) XOR mask XOR 1
            mask = (mask << 1) ^ mask ^ 1ULL;
        } else {
            // Não possui termo constante (bit 0 é 0)
            // Divide por x (shift right de 1 bit)
            mask >>= 1;
        }
        operacoes++;
    }

    cout << operacoes << "\n";

    return 0;
}
