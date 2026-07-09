#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long R, B;
    cin >> R >> B;

    string s;
    cin >> s;

    int n = s.size();

    vector<long long> prefR(n + 1, 0), prefB(n + 1, 0), prefG(n + 1, 0);
    vector<long long> f(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        prefR[i] = prefR[i - 1];
        prefB[i] = prefB[i - 1];
        prefG[i] = prefG[i - 1];

        if (s[i - 1] == 'R') prefR[i]++;
        else if (s[i - 1] == 'B') prefB[i]++;
        else prefG[i]++;

        f[i] = prefR[i] - prefB[i];
    }

    int W;
    cin >> W;

    while (W--) {
        int L, U;
        cin >> L >> U;

        long long len = U - L + 1;

        long long Rcnt = prefR[U] - prefR[L - 1];
        long long Bcnt = prefB[U] - prefB[L - 1];
        long long Gcnt = prefG[U] - prefG[L - 1];

        long long best = LLONG_MIN;
        long long minF = LLONG_MAX;

        for (int i = L - 1; i <= U; i++) {
            minF = min(minF, f[i]);
            best = max(best, f[i]);
        }

        long long ans = len - (best - minF) + Gcnt;

        cout << ans << "\n";
    }

    return 0;
}
