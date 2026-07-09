#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

const int64 LIM = 1000000000LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int64> A(N), B(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];

    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
        --P[i];
    }

    vector<int> vis(N, 0);

    auto buildPi = [&](const vector<int64>& pat) {
        int m = pat.size();
        vector<int> pi(m);
        for (int i = 1; i < m; i++) {
            int j = pi[i - 1];
            while (j && pat[i] != pat[j]) j = pi[j - 1];
            if (pat[i] == pat[j]) j++;
            pi[i] = j;
        }
        return pi;
    };

    auto rotations = [&](vector<int64>& a, vector<int64>& b) {
        int L = a.size();

        vector<int64> text = b;
        text.insert(text.end(), b.begin(), b.end());

        auto pi = buildPi(a);

        vector<int> ans;
        int j = 0;
        for (int i = 0; i < (int)text.size() - 1; i++) {
            while (j && text[i] != a[j]) j = pi[j - 1];
            if (text[i] == a[j]) j++;
            if (j == L) {
                int start = i - L + 1;
                if (start < L)
                    ans.push_back((L - start) % L);
                j = pi[j - 1];
            }
        }
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    };

    auto egcd = [&](auto self, int64 a, int64 b) -> array<int64,3> {
        if (b == 0) return {a,1,0};
        auto t = self(self,b,a%b);
        return {t[0],t[2],t[1]-a/b*t[2]};
    };

    int64 cur = 0;
    int64 mod = 1;

    for (int i = 0; i < N; i++) {
        if (vis[i]) continue;

        vector<int> pos;
        int u = i;
        while (!vis[u]) {
            vis[u] = 1;
            pos.push_back(u);
            u = P[u];
        }

        int L = pos.size();

        vector<int64> ca(L), cb(L);
        for (int j = 0; j < L; j++) {
            ca[j] = A[pos[j]];
            cb[j] = B[pos[j]];
        }

        auto rs = rotations(ca, cb);

        bool ok = false;
        int64 bestCur = -1;
        int64 newMod = mod / gcd(mod, (int64)L) * (int64)L;

        for (int r : rs) {
            auto e = egcd(egcd, mod, (int64)L);
            int64 g = e[0];
            if ((r - cur) % g != 0) continue;

            int64 m2 = L / g;

            i128 mult = (i128)(r - cur) / g;
            mult *= e[1];
            int64 t = (int64)((mult % m2 + m2) % m2);

            i128 candidate = (i128)cur + (i128)t * mod;
            candidate %= newMod;
            if (candidate < 0) candidate += newMod;

            if (!ok || candidate < bestCur) {
                ok = true;
                bestCur = (int64)candidate;
            }
        }

        if (!ok) {
            cout << "IMPOSSIVEL\n";
            return 0;
        }

        cur = bestCur;
        mod = newMod;
    }

    if (cur > LIM)
        cout << "DEMAIS\n";
    else
        cout << cur << '\n';

    return 0;
}
