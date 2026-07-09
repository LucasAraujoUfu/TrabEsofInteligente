#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = s.size();

    vector<int> sufMask(n + 1, 0);
    vector<int> freq(26, 0);

    for (int i = n - 1; i >= 0; i--) {
        freq[s[i] - 'A']++;
        sufMask[i] = sufMask[i + 1] | (1 << (s[i] - 'A'));
    }

    vector<int> prefFreq(26, 0);
    int prefMask = 0;

    for (int k = 1; k < n; k++) {
        prefFreq[s[k - 1] - 'A']++;
        prefMask |= (1 << (s[k - 1] - 'A'));

        int len = n - k;
        int suf = sufMask[k];

        // sufixo deve ter exatamente letras distintas
        int cnt = __builtin_popcount(suf);

        if (len != cnt) continue;

        if (suf == prefMask) {
            cout << k << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}
