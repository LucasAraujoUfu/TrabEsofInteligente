#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    int LIM = 1 << K;

    vector<int> cnt(LIM, 0);

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        int mask = 0;
        for (char c : s)
            mask = (mask << 1) | (c - '0');
        cnt[mask]++;
    }

    vector<int> sub = cnt;

    for (int b = 0; b < K; b++)
        for (int mask = 0; mask < LIM; mask++)
            if (mask & (1 << b))
                sub[mask] += sub[mask ^ (1 << b)];

    vector<int64> C3(LIM);

    auto choose3 = [](int64 n) -> int64 {
        if (n < 3) return 0;
        return n * (n - 1) * (n - 2) / 6;
    };

    for (int i = 0; i < LIM; i++)
        C3[i] = choose3(sub[i]);

    int M;
    cin >> M;

    while (M--) {
        string s;
        cin >> s;

        int E = 0;
        for (char c : s)
            E = (E << 1) | (c - '0');

        int64 ans = 0;

        int submask = E;
        while (true) {
            int bits = __builtin_popcount(E ^ submask);

            if (bits & 1)
                ans -= C3[submask];
            else
                ans += C3[submask];

            if (submask == 0) break;
            submask = (submask - 1) & E;
        }

        cout << ans << '\n';
    }

    return 0;
}
