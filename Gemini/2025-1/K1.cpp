#include <iostream>

using namespace std;

// Função para calcular o número de bits 1 em um inteiro de 64 bits
int popcount(unsigned long long x) {
    return __builtin_popcountll(x);
}

// Exponenciação modular rápida: (base^exp) % mod
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    unsigned long long A, B;
    if (!(cin >> A >> B)) return 0;

    long long MOD = 1000000007;

    // Calculando o expoente necessário usando a fórmula de Kummer/Legendre
    unsigned long long n = A + B - 2;
    unsigned long long k = A - 1;
    
    long long v2_binomial = popcount(k) + popcount(n - k) - popcount(n);
    long long E = A + B - 1 - v2_binomial;

    // O resultado final é (2^E) % MOD
    long long ans = power(2, E, MOD);
    cout << ans << "\n";

    return 0;
}
