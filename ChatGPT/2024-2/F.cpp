#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, N;
    cin >> K >> N;

    vector<char> ans(N, '-');

    // máximo de escolhas possíveis sem adjacência de escolha segura
    int maxK = (N + 1) / 2;

    if (K > maxK || K < (N + 1) / 3) {
        cout << "*\n";
        return 0;
    }

    int used = 0;

    // estratégia: tentar ocupar posições espaçadas
    for (int i = 0; i < N && used < K; i++) {
        if ((i == 0 || ans[i - 1] == '-') &&
            (i == N - 1 || ans[i + 1] == '-')) {

            ans[i] = 'X';
            used++;
        }
    }

    // se não atingiu K, tenta forçar em posições restantes válidas
    for (int i = 0; i < N && used < K; i++) {
        if (ans[i] == '-') {
            if ((i == 0 || ans[i - 1] == '-') &&
                (i == N - 1 || ans[i + 1] == '-')) {

                ans[i] = 'X';
                used++;
            }
        }
    }

    if (used != K) {
        cout << "*\n";
        return 0;
    }

    // valida condição final: não pode existir posição válida
    for (int i = 0; i < N; i++) {
        if (ans[i] == '-') {
            bool ok =
                (i == 0 || ans[i - 1] == '-') &&
                (i == N - 1 || ans[i + 1] == '-');
            if (ok) {
                cout << "*\n";
                return 0;
            }
        }
    }

    for (char c : ans) cout << c;
    cout << "\n";

    return 0;
}
