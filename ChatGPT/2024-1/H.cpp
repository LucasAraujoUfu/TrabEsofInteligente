#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string Ms, Ns;
    cin >> Ms >> Ns;

    int m = Ms.size();

    vector<int> candN;

    int q = Ns.size();
    vector<int> pos;

    for (int i = 0; i < q; i++)
        if (Ns[i] == '*')
            pos.push_back(i);

    int k = pos.size();

    for (int mask = 0; mask < (1 << k); mask++) {
        string t = Ns;
        for (int i = 0; i < k; i++) {
            t[pos[i]] = ((mask >> i) & 1) + '0';
        }

        int val = 0;
        for (char c : t)
            val = val * 2 + (c - '0');

        if (val > 0) candN.push_back(val);
    }

    sort(candN.begin(), candN.end());
    candN.erase(unique(candN.begin(), candN.end()), candN.end());

    for (int N : candN) {
        vector<vector<int>> prev(m + 1, vector<int>(N, -1));
        vector<vector<char>> take(m + 1, vector<char>(N, -1));

        prev[0][0] = 0;

        for (int i = 0; i < m; i++) {
            for (int r = 0; r < N; r++) {
                if (prev[i][r] == -1) continue;

                for (int bit = 0; bit <= 1; bit++) {
                    if (Ms[i] != '*' && Ms[i] - '0' != bit)
                        continue;

                    int nr = (r * 2 + bit) % N;

                    if (prev[i + 1][nr] == -1) {
                        prev[i + 1][nr] = r;
                        take[i + 1][nr] = bit;
                    }
                }
            }
        }

        if (prev[m][0] == -1) continue;

        string res(m, '0');

        int r = 0;
        for (int i = m; i >= 1; i--) {
            int pr = prev[i][r];
            int bit = take[i][r];
            res[i - 1] = char('0' + bit);
            r = pr;
        }

        cout << res << '\n';
        return 0;
    }

    return 0;
}
