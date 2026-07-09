#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    int soma_total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        soma_total += a[i];
    }

    if (soma_total % 2 != 0) {
        cout << "-1\n";
        return 0;
    }

    int alvo = soma_total / 2;
    vector<vector<bool>> dp(n + 1, vector<bool>(alvo + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; i++) {
        int val = a[i - 1];
        for (int j = 0; j <= alvo; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= val && dp[i - 1][j - val]) {
                dp[i][j] = true;
            }
        }
    }

    if (!dp[n][alvo]) {
        cout << "-1\n";
        return 0;
    }

    // Reconstrói as escolhas
    vector<int> alice_items, bob_items;
    int curr_j = alvo;
    for (int i = n; i > 0; i--) {
        int val = a[i - 1];
        if (curr_j >= val && dp[i - 1][curr_j - val]) {
            alice_items.push_back(val);
            curr_j -= val;
        } else {
            bob_items.push_back(val);
        }
    }

    sort(alice_items.rbegin(), alice_items.rend());
    sort(bob_items.rbegin(), bob_items.rend());

    // Intercala simulando a regra do jogo
    vector<int> resultado;
    int al = 0, bob = 0;
    size_t i_a = 0, i_b = 0;

    while (i_a < alice_items.size() || i_b < bob_items.size()) {
        if (al <= bob && i_a < alice_items.size()) {
            resultado.push_back(alice_items[i_a]);
            al += alice_items[i_a];
            i_a++;
        } else if (i_b < bob_items.size()) {
            resultado.push_back(bob_items[i_b]);
            bob += bob_items[i_b];
            i_b++;
        } else {
            resultado.push_back(alice_items[i_a]);
            al += alice_items[i_a];
            i_a++;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << resultado[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
