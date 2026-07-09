#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool has[5] = {};

    for (int i = 0; i < 10; i++) {
        int x;
        cin >> x;
        has[x] = true;
    }

    int cnt = 0;
    for (int i = 1; i <= 4; i++)
        cnt += has[i];

    cout << 4 - cnt << '\n';

    return 0;
}
