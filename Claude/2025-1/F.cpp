#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static const ll MOD = 1000000007LL;

ll power(ll a, ll e, ll mod) {
    a %= mod; if (a < 0) a += mod;
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    vector<int> X(Q + 1);
    for (int i = 1; i <= Q; i++) scanf("%d", &X[i]);

    ll inv2 = power(2, MOD - 2, MOD);

    vector<ll> R(Q + 1, 0);
    for (int m = Q - 1; m >= 0; m--) {
        ll xnext = X[m + 1];
        R[m] = (xnext + R[m + 1]) % MOD * inv2 % MOD;
    }

    vector<ll> ans(N + 1, 0);
    for (int m = 1; m <= Q; m++) {
        int j = X[m];
        ans[j] = (ans[j] + R[m] * inv2) % MOD;
    }
    ans[1] = (ans[1] + R[0]) % MOD;

    for (int j = 1; j <= N; j++) {
        printf("%lld\n", ans[j] % MOD);
    }

    return 0;
}
