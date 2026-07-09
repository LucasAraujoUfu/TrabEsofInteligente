#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> a(N);
    vector<int> used(N + 1, 0);

    for (int i = 0; i < N; i++) {
        cin >> a[i];
        if (a[i] != 0) {
            if (used[a[i]]) {
                cout << "*\n";
                return 0;
            }
            used[a[i]] = 1;
        }
    }

    vector<int> missing;
    for (int i = 1; i <= N; i++) {
        if (!used[i]) missing.push_back(i);
    }

    // tentar montar bitônico simples
    vector<int> res(N, 0);

    int m = missing.size();
    int mid = N - m; // tentativa de split

    // estratégia: pico em algum lugar, tentamos todos
    for (int peak = 0; peak < N; peak++) {

        vector<int> cur = a;
        vector<int> small = missing, large = missing;

        sort(small.begin(), small.end());
        sort(large.rbegin(), large.rend());

        int iS = 0, iL = 0;
        bool ok = true;

        // esquerda (crescente)
        int last = 0;
        for (int i = 0; i <= peak; i++) {
            if (cur[i] == 0) {
                while (iS < (int)small.size() && small[iS] <= last) iS++;
                if (iS == (int)small.size()) { ok = false; break; }
                cur[i] = small[iS++];
            }
            if (cur[i] <= last) { ok = false; break; }
            last = cur[i];
        }

        // direita (decrescente)
        last = N + 1;
        for (int i = peak + 1; i < N && ok; i++) {
            if (cur[i] == 0) {
                while (iL < (int)large.size() && large[iL] >= last) iL++;
                if (iL == (int)large.size()) { ok = false; break; }
                cur[i] = large[iL++];
            }
            if (cur[i] >= last) { ok = false; break; }
            last = cur[i];
        }

        if (ok) {
            for (int i = 0; i < N; i++) {
                cout << cur[i] << (i + 1 == N ? '\n' : ' ');
            }
            return 0;
        }
    }

    cout << "*\n";
    return 0;
}
