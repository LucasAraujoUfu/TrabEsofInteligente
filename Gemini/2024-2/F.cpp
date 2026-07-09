#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int MAXA = 1000005;
int menor_fator_primo[MAXA];

// Inicializa o crivo para fatoração ultra-rápida
void construir_crivo() {
    for (int i = 1; i < MAXA; i++) menor_fator_primo[i] = i;
    for (int i = 2; i * i < MAXA; i++) {
        if (menor_fator_primo[i] == i) {
            for (int j = i * i; j < MAXA; j += i) {
                if (menor_fator_primo[j] == j) {
                    menor_fator_primo[j] = i;
                }
            }
        }
    }
}

// Retorna a quantidade de fatores primos distintos de um número
int contar_fatores_primos(int n) {
    int contagem = 0;
    while (n > 1) {
        int p = menor_fator_primo[n];
        contagem++;
        while (n % p == 0) {
            n /= p;
        }
    }
    return contagem;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    construir_crivo();

    int a, b;
    if (cin >> a >> b) {
        int fat_a = contar_fatores_primos(a);
        int fat_b = contar_fatores_primos(b);

        // Processamento da fração de fatores
        long long num = fat_a;
        long long den = fat_b;
        long long g = std::gcd(num, den);

        if (den == 0) {
            cout << "0\n";
        } else {
            cout << num / g << "/" << den / g << "\n";
        }
    }
    return 0;
}
