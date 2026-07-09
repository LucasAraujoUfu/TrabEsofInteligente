#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

const int MOD = 1000000007;

int64 modpow(int64 a, int64 e) {
    int64 r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int64> lazy(N + 1, 0);
    vector<int64> ans(N + 1, 0);

    const int64 inv2 = (MOD + 1) / 2;

    int64 g = 1;
    int64 invg = 1;

    lazy[1] = 1;

    for (int k = 0; k < Q; k++) {
        int X;
        cin >> X;

        int64 coef = (int64)X * inv2 % MOD;
        int64 realFactor = g;

        for (int i = 1; i <= N; i++) {
            if (lazy[i])
                ans[i] = (ans[i] + coef * realFactor % MOD * lazy[i]) % MOD;
        }

        g = g * inv2 % MOD;
        invg = invg * 2 % MOD;

        lazy[X] = (lazy[X] + inv2 * invg) % MOD;
    }

    for (int i = 1; i <= N; i++)
        cout << ans[i] % MOD << "\n";

    return 0;
}
