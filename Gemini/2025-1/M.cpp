#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool possivel(long long H, const vector<long long>& x, int n, long long K) {
    long long j_maximo = n - 1; 
    long long i_maximo_necessitado = -1;

    for (int i = 0; i < n; ++i) {
        if (x[i] < H) {
            long long precisa = H - x[i];
            if (precisa > K) return false;

            i_maximo_necessitado = max(i_maximo_necessitado, (long long)i);
            long long limite1 = K + i - precisa;
            long long limite2 = i + K - 1;

            j_maximo = min({j_maximo, limite1, limite2});
        }
    }
    if (i_maximo_necessitado == -1) return true;
    return j_maximo >= i_maximo_necessitado;
}

int main() {
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

    long long low = min_inicial;
    long long high = min_inicial + K;
    long long ans = min_inicial;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (possivel(mid, x, n, K)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << ans << "\n";
    return 0;
}
