#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    if (!(cin >> n >> t)) return 0;

    vector<int> row_perm(n), col_perm(n);
    iota(row_perm.begin(), row_perm.end(), 0);
    iota(col_perm.begin(), col_perm.end(), 0);

    for (int i = 0; i < t; i++) {
        char type;
        int u, v;
        cin >> type >> u >> v;
        u--; v--; // Ajuste para indexação 0-based
        if (type == 'R') {
            swap(row_perm[u], row_perm[v]);
        } else if (type == 'C') {
            swap(col_perm[u], col_perm[v]);
        }
    }

    // Construímos um quadrado latino candidato válido
    vector<vector<int>> matriz(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = ((i + j) % n) + 1;
        }
    }

    // Verificamos se a matriz candidata satisfaz a invariância sob a transformação acumulada
    bool valido = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] != matriz[row_perm[i]][col_perm[j]]) {
                valido = false;
                break;
            }
        }
        if (!valido) break;
    }

    if (valido) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << matriz[i][j] << (j + 1 == n ? "" : " ");
            }
            cout << "\n";
        }
    } else {
        cout << "*\n";
    }

    return 0;
}
