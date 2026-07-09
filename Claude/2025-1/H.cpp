#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int FULL = 1 << K;
    vector<int> cnt(FULL, 0);

    static char buf[25];
    for (int i = 0; i < N; i++) {
        scanf("%s", buf);
        int mask = 0;
        for (int j = 0; j < K; j++)
            if (buf[j] == '1') mask |= (1 << (K - 1 - j));
        cnt[mask]++;
    }

    vector<ll> f(cnt.begin(), cnt.end());
    for (int bit = 0; bit < K; bit++) {
        int b = 1 << bit;
        for (int S = 0; S < FULL; S++)
            if (S & b) f[S] += f[S ^ b];
    }

    vector<ll> g(FULL);
    for (int S = 0; S < FULL; S++) {
        ll n = f[S];
        g[S] = (n >= 3) ? (n * (n - 1) / 2 * (n - 2) / 3) : 0;
    }

    vector<ll> h = g;
    for (int bit = 0; bit < K; bit++) {
        int b = 1 << bit;
        for (int S = 0; S < FULL; S++)
            if (S & b) h[S] -= h[S ^ b];
    }

    int M;
    scanf("%d", &M);
    for (int q = 0; q < M; q++) {
        scanf("%s", buf);
        int mask = 0;
        for (int j = 0; j < K; j++)
            if (buf[j] == '1') mask |= (1 << (K - 1 - j));
        printf("%lld\n", h[mask]);
    }
    return 0;
}
