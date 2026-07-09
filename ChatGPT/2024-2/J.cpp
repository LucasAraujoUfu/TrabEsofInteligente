#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int theta, N;
    cin >> theta >> N;

    const double PI = acos(-1.0);
    double rad = theta * PI / 180.0;

    double cot = 1.0 / tan(rad);

    vector<pair<double,double>> segs;
    segs.reserve(N);

    for (int i = 0; i < N; i++) {
        double x, h;
        cin >> x >> h;

        double len = h * cot;
        segs.push_back({x, x + len});
    }

    sort(segs.begin(), segs.end());

    double ans = 0;
    double L = segs[0].first;
    double R = segs[0].second;

    for (int i = 1; i < N; i++) {
        auto [l, r] = segs[i];

        if (l > R) {
            ans += R - L;
            L = l;
            R = r;
        } else {
            R = max(R, r);
        }
    }

    ans += R - L;

    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}
