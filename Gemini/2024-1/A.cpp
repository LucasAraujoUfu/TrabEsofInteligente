#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n, k;
    if (cin >> n >> k) {
        long long tempo_disponivel = k - (n - 1);
        long long resposta = tempo_disponivel / n;
        cout << resposta << "\n";
    }
    return 0;
}
