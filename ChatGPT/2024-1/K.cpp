#include <bits/stdc++.h>
using namespace std;

pair<long long,long long> simulate(const vector<int>& v) {
    long long A = 0, B = 0;

    for (int x : v) {
        if (A <= B) A += x;
        else B += x;
    }

    return {A, B};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> a(N);
    for (int &x : a) cin >> x;

    vector<vector<int>> tries;

    auto asc = a;
    sort(asc.begin(), asc.end());
    tries.push_back(asc);

    auto desc = a;
    sort(desc.rbegin(), desc.rend());
    tries.push_back(desc);

    // greedy alternating
    auto dq = a;
    sort(dq.begin(), dq.end());
    vector<int> alt;
    int l = 0, r = N - 1;
    while (l <= r) {
        if (l == r) alt.push_back(dq[l++]);
        else {
            alt.push_back(dq[r--]);
            alt.push_back(dq[l++]);
        }
    }
    tries.push_back(alt);

    for (auto &v : tries) {
        auto [A, B] = simulate(v);
        if (A == B) {
            for (int i = 0; i < N; i++) {
                cout << v[i] << (i + 1 == N ? '\n' : ' ');
            }
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
