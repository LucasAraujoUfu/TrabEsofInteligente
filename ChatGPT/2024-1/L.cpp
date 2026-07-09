#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> a(N);
    for (auto &x : a) cin >> x;

    const int B = 31;
    vector<int> cnt(B, 0);

    for (int i = 0; i < N; i++) {
        for (int b = 0; b < B; b++) {
            if (a[i] & (1LL << b))
                cnt[b]++;
        }
    }

    vector<long long> res(N, 0);

    for (int i = 0; i < N; i++) {
        long long val = 0;

        for (int b = B - 1; b >= 0; b--) {
            if (cnt[b] > 0) {
                cnt[b]--;
                val |= (1LL << b);
            }
        }

        res[i] = val;
    }

    for (int i = 0; i < N; i++) {
        cout << res[i] << (i + 1 == N ? '\n' : ' ');
    }

    return 0;
}
