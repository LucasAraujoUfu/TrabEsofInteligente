#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    uint32_t mask = 0;

    for (int i = N; i >= 0; i--) {
        int b;
        cin >> b;
        if (b) mask |= (1u << i);
    }

    const uint32_t LIM = (1u << 22) - 1;

    long long ans = 0;

    while (mask != 1) {
        if (mask & 1) {
            mask = (mask ^ (mask << 1)) & LIM;
            mask ^= 1;
        } else {
            mask >>= 1;
        }
        ans++;
    }

    cout << ans << '\n';

    return 0;
}
