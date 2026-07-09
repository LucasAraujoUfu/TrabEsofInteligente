#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Extremes {
    ll val1, val2;
    int id1, id2;

    Extremes() {
        val1 = LLONG_MAX;
        val2 = LLONG_MAX;
        id1 = id2 = -1;
    }

    void add(ll x, int id) {
        if (x < val1) {
            val2 = val1;
            id2 = id1;
            val1 = x;
            id1 = id;
        } else if (x < val2) {
            val2 = x;
            id2 = id;
        }
    }
};

struct MaxExtremes {
    ll val1, val2;
    int id1, id2;

    MaxExtremes() {
        val1 = LLONG_MIN;
        val2 = LLONG_MIN;
        id1 = id2 = -1;
    }

    void add(ll x, int id) {
        if (x > val1) {
            val2 = val1;
            id2 = id1;
            val1 = x;
            id1 = id;
        } else if (x > val2) {
            val2 = x;
            id2 = id;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll K;

    cin >> N >> K;

    vector<ll> r(N), c(N);

    Extremes minR, minC;
    MaxExtremes maxR, maxC;

    for (int i = 0; i < N; i++) {
        cin >> r[i] >> c[i];

        minR.add(r[i], i);
        minC.add(c[i], i);

        maxR.add(r[i], i);
        maxC.add(c[i], i);
    }

    auto getMin = [](const Extremes& e, int id) {
        return (e.id1 == id ? e.val2 : e.val1);
    };

    auto getMax = [](const MaxExtremes& e, int id) {
        return (e.id1 == id ? e.val2 : e.val1);
    };

    ll ans = 0;

    for (int i = 0; i < N; i++) {
        ll mnR = getMin(minR, i);
        ll mxR = getMax(maxR, i);
        ll mnC = getMin(minC, i);
        ll mxC = getMax(maxC, i);

        if (N == 1) {
            mnR = mxR = r[i];
            mnC = mxC = c[i];
        }

        ll nr[2] = {r[i] - K, r[i] + K};
        ll nc[2] = {c[i] - K, c[i] + K};

        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                ll loR = min(mnR, nr[a]);
                ll hiR = max(mxR, nr[a]);

                ll loC = min(mnC, nc[b]);
                ll hiC = max(mxC, nc[b]);

                ll area = (hiR - loR + 1) * (hiC - loC + 1);
                ans = max(ans, area);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
