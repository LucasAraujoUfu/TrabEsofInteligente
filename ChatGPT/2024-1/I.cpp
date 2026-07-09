#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> V(N);

    int MAXV = 1e6;
    vector<int> spf(MAXV + 1);

    for (int i = 2; i <= MAXV; i++) {
        if (!spf[i]) {
            for (int j = i; j <= MAXV; j += i)
                if (!spf[j]) spf[j] = i;
        }
    }

    vector<vector<int>> comp(N);

    unordered_map<int,int> freq;

    for (int i = 0; i < N; i++) {
        cin >> V[i];

        int x = V[i];
        while (x > 1) {
            int p = spf[x];
            comp[i].push_back(p);
            while (x % p == 0) x /= p;
        }
    }

    int Q;
    cin >> Q;

    vector<int> bad(MAXV + 1, 0);

    long long total = 1;
    for (int i = 0; i < N; i++)
        total = (total * 2) % MOD;

    while (Q--) {
        int X;
        cin >> X;

        vector<int> primes;

        int x = X;
        while (x > 1) {
            int p = spf[x];
            primes.push_back(p);
            while (x % p == 0) x /= p;
        }

        vector<char> blocked(N, 0);

        for (int p : primes) {
            bad[p] = 1;
        }

        long long invalid = 0;

        for (int i = 0; i < N; i++) {
            bool ok = true;
            for (int p : comp[i]) {
                if (bad[p]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) invalid++;
        }

        for (int p : primes)
            bad[p] = 0;

        long long ans = 1;
        long long base = 1;

        for (int i = 0; i < N; i++)
            base = (base * 2) % MOD;

        // subset of valid foods
        long long valid = N - invalid;

        long long res = 1;
        for (int i = 0; i < valid; i++)
            res = (res * 2) % MOD;

        cout << res << '\n';
    }

    return 0;
}
