#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const int MOD = 998244353;
const int MAXA = 100005;

// Função para calcular a potência modular
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// Inverso multiplicativo modular
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

// Retorna o número de dígitos da parte inteira de um número
int numDigits(int x) {
    if (x == 0) return 1;
    int digits = 0;
    while (x > 0) {
        digits++;
        x /= 10;
    }
    return digits;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<int> count(MAXA, 0);
    vector<int> unique_A;
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        if (count[a] == 0) {
            unique_A.push_back(a);
        }
        count[a]++;
    }

    // Pré-computar o comprimento do período L(k) para os ímpares não múltiplos de 5
    vector<int> period(MAXA, 0);
    for (int k = 1; k < MAXA; k += 2) {
        if (k % 5 == 0) continue;
        if (k == 1) {
            period[k] = 0;
            continue;
        }
        int len = 1;
        int rem = 10 % k;
        while (rem != 1) {
            rem = (rem * 10) % k;
            len++;
        }
        period[k] = len;
    }

    long long total_digits_sum = 0;

    // Iterar sobre todos os pares de valores únicos de moedas existentes
    for (int vi : unique_A) {
        long long c_i = count[vi];
        for (int vj : unique_A) {
            long long c_j = count[vj];
            
            int g = std::gcd(vi, vj);
            int p = vi / g;
            int q = vj / g;

            // Contar fatores 2 e 5 de q
            int a = 0, b = 0;
            int k = q;
            while (k % 2 == 0) { a++; k /= 2; }
            while (k % 5 == 0) { b++; k /= 5; }

            int decimal_digits = std::max(a, b);
            if (k > 1) {
                decimal_digits += period[k];
            }

            int integer_digits = numDigits(vi / vj);
            int total_pair_digits = integer_digits + decimal_digits;

            // Multiplicar pela quantidade de ocorrências desse par (mod MOD)
            long long combinations = (c_i * c_j) % MOD;
            long long current_sum = (combinations * total_pair_digits) % MOD;
            total_digits_sum = (total_digits_sum + current_sum) % MOD;
        }
    }

    long long Q = ((long long)N * N) % MOD;
    long long ans = (total_digits_sum * modInverse(Q)) % MOD;

    cout << ans << "\n";

    return 0;
}
