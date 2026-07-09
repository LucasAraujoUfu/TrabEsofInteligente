#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int64> a(N);

    int64 mn = LLONG_MAX;
    int64 mx = 0;

    for (int i = 0; i < N; i++) {
        cin >> a[i];
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
    }

    auto ok = [&](int64 H) {
        int L = 0;
        int R = N - 1;

        for (int i = 0; i < N; i++) {
            int64 need = max<int64>(0, H - a[i]);

            if (need > K) return false;

            if (need == 0) continue;

            int left = i;
            int right = min(N - 1, i + K - (int)need);

            L = max(L, left);
            R = min(R, right);

            if (L > R) return false;
        }

        return true;
    };

    int64 lo = mn;
    int64 hi = mx + K;

    while (lo < hi) {
        int64 mid = (lo + hi + 1) / 2;
        if (ok(mid))
            lo = mid;
        else
            hi = mid - 1;
    }

    cout << lo << "\n";
    return 0;
}
