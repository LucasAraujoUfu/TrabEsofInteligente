#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

// Tamanho máximo baseado nas restrições típicas de matrizes da regional (ajustável para N)
const int MAXN = 2005; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    if (!(cin >> r >> c)) return 0;

    vector<bitset<MAXN>> matriz(r);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int val;
            cin >> val;
            if (val) matriz[i].set(j);
        }
    }

    // Análise de equivalência de linhas para redução do espaço de estados
    long long pares_validos = 0;
    for (int i = 0; i < r; i++) {
        for (int j = i + 1; j < r; j++) {
            // Se duas linhas são iguais ou completamente complementares, elas preservam a propriedade
            if (matriz[i] == matriz[j] || matriz[i] == (~matriz[j])) {
                pares_validos++;
            }
        }
    }

    cout << pares_validos << "\n";
    return 0;
}
