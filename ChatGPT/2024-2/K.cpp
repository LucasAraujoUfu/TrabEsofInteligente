#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    string s;
    cin >> K >> s;

    int n = (int)s.size();

    string t = s;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (i > 0 && t[i] == t[i-1]) {
            int j = i;
            while (j < n && t[j] == t[i]) j++;

            int len = j - i + 1;

            if (len >= K) {
                // flip current position
                t[i] = (t[i] == '0' ? '1' : '0');
                ans++;
            }
        }
    }

    // fix again to guarantee validity
    for (int i = 1, run = 1; i < n; i++) {
        if (t[i] == t[i-1]) run++;
        else run = 1;

        if (run >= K) {
            t[i] = (t[i] == '0' ? '1' : '0');
            ans++;
            run = 1;
        }
    }

    cout << ans << " " << t << "\n";

    return 0;
}
