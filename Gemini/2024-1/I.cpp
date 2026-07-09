#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXV = 1000000;

int f_comidas[MAXV + 1];
int primos_divisores[MAXV + 1];
vector<int> fatores[MAXV + 1];
long long pot2[100005];

void crivo() {
    for (int i = 2; i <= MAXV; i++) {
        if (fatores[i].empty()) {
            for (int j = i; j <= MAXV; j += i) {
                fatores[j].push_back(i);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    crivo();

    pot2[0] = 1;
    for (int i = 1; i <= 100000; i++) pot2[i] = (pot2[i - 1] * 2) % MOD;

    int n;
    if (!(cin >> n)) return 0;

    // Contar a ocorrência de múltiplos para cada número
    vector<int> count_val(MAXV + 1, 0);
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        count_val[v]++;
    }

    // multiplos[i] armazena quantas comidas são múltiplas de i
    vector<int> multiplos(MAXV + 1, 0);
    for (int i = 1; i <= MAXV; i++) {
        for (int j = i; j <= MAXV; j += i) {
            multiplos[i] += count_val[j];
        }
    }

    int q;
    if (cin >> q) {
        while (q--) {
            int x;
            cin >> x;

            // Inclusão-Exclusão sobre os fatores primos de X
            int n_fat = fatores[x].size();
            int comidas_proibidas = 0;

            for (int mask = 1; mask < (1 << n_fat); mask++) {
                int prod = 1;
                int bits = 0;
                for (int i = 0; i < n_fat; i++) {
                    if ((mask >> i) & 1) {
                        prod *= fatores[x][i];
                        bits++;
                    }
                }
                if (bits & 1) {
                    comidas_proibidas += multiplos[prod];
                } else {
                    comidas_proibidas -= multiplos[prod];
                }
            }

            int validas = n - comidas_proibidas;
            cout << pot2[validas] << "\n";
        }
    }

    return 0;
}
