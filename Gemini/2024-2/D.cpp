#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX_C = 2005;

struct Magia {
    int a, b;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N;
    int M;
    if (!(cin >> N >> M)) return 0;

    vector<Magia> magias(M);
    for (int i = 0; i < M; i++) {
        cin >> magias[i].a >> magias[i].b;
    }

    vector<long long> dp(MAX_C, 0);
    dp[0] = 1;

    for (int bit = 0; bit <= 60; bit++) {
        int bit_N = (N >> bit) & 1;
        vector<long long> transicao = dp;

        for (const auto& m : magias) {
            if (m.b <= bit) {
                for (int c = m.a; c < MAX_C; c++) {
                    transicao[c] = (transicao[c] + transicao[c - m.a]) % MOD;
                }
            }
        }

        vector<long long> next_dp(MAX_C, 0);
        for (int c = 0; c < MAX_C; c++) {
            if (transicao[c] == 0) continue;
            if ((c & 1) == bit_N) {
                int nxt_c = c >> 1;
                next_dp[nxt_c] = (next_dp[nxt_c] + transicao[c]) % MOD;
            }
        }
        dp = move(next_dp);
    }

    cout << dp[0] << "\n";
    return 0;
}
