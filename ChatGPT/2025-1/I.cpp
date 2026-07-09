#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<int64,int64>> p(N + 1);

    for (int i = 1; i <= N; i++)
        cin >> p[i].first >> p[i].second;

    vector<int64> d(N);

    for (int i = 1; i < N; i++) {
        d[i] = llabs(p[i].first - p[i + 1].first)
             + llabs(p[i].second - p[i + 1].second);
    }

    int64 L = 1;
    int64 R = (1LL << 60);

    for (int i = N - 1; i >= 1; i--) {
        if (d[i] <= 1) {
            cout << -1 << '\n';
            return 0;
        }

        int64 nL = max<int64>(1, d[i] - R);
        int64 nR = d[i] - 1;

        if (nL > nR) {
            cout << -1 << '\n';
            return 0;
        }

        L = nL;
        R = nR;
    }

    cout << R << '\n';
    return 0;
}
