#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<long long> mx(M, 0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            long long x;
            cin >> x;
            mx[j] = max(mx[j], x);
        }
    }

    long long ans = 0;
    for (long long x : mx) ans += x;

    cout << ans << '\n';

    return 0;
}
