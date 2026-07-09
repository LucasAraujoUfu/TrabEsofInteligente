#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n): n(n), bit(n+1,0) {}

    void add(int i, int v) {
        for (; i <= n; i += i & -i) bit[i] += v;
    }

    int sum(int i) {
        int s = 0;
        for (; i > 0; i -= i & -i) s += bit[i];
        return s;
    }

    // find smallest idx such that prefix sum >= k
    int find_kth(int k) {
        int idx = 0;
        int bitmask = 1 << 20;

        while (bitmask) {
            int nxt = idx + bitmask;
            if (nxt <= n && bit[nxt] < k) {
                k -= bit[nxt];
                idx = nxt;
            }
            bitmask >>= 1;
        }
        return idx + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    unsigned long long K;
    cin >> N >> K;

    vector<unsigned long long> fact(N+1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = min((unsigned long long)4e18, fact[i-1] * i);
    }

    K--; // 0-index

    Fenwick fw(N);
    for (int i = 1; i <= N; i++) fw.add(i, 1);

    vector<int> ans;

    for (int i = N; i >= 1; i--) {
        unsigned long long f = (i-1 >= 0 ? fact[i-1] : 1);
        unsigned long long pos = (f ? K / f : 0);
        K %= (f ? f : 1);

        int val = fw.find_kth(pos + 1);
        ans.push_back(val);
        fw.add(val, -1);
    }

    for (int i = 0; i < N; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}
