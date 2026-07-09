#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    int ans = 0;
    int n = S.size();

    for (int i = 0; i < n; i++) {
        if (i + 1 < n && S.substr(i, 2) == "ha")
            ans++;

        if (i + 5 <= n && S.substr(i, 5) == "boooo")
            ans--;

        if (i + 5 <= n && S.substr(i, 5) == "bravo")
            ans += 3;
    }

    cout << ans << '\n';

    return 0;
}
