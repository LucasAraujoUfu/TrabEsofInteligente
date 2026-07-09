#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> v(N);
    for (int i = 0; i < N; i++) cin >> v[i];

    // Suffix Array (O(N log N))
    vector<int> sa(N), rnk(N), tmp(N);

    for (int i = 0; i < N; i++) {
        sa[i] = i;
        rnk[i] = v[i];
    }

    for (int k = 1;; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];

            int ra = (a + k < N ? rnk[a + k] : -1);
            int rb = (b + k < N ? rnk[b + k] : -1);

            return ra < rb;
        };

        sort(sa.begin(), sa.end(), cmp);

        tmp[sa[0]] = 0;

        for (int i = 1; i < N; i++) {
            tmp[sa[i]] =
                tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }

        rnk = tmp;

        if (rnk[sa[N - 1]] == N - 1) break;
    }

    // Kasai LCP
    vector<int> pos(N);
    for (int i = 0; i < N; i++) pos[sa[i]] = i;

    vector<long long> lcp(max(0, N - 1));

    int k = 0;
    for (int i = 0; i < N; i++) {
        int r = pos[i];

        if (r == N - 1) {
            k = 0;
            continue;
        }

        int j = sa[r + 1];

        while (i + k < N && j + k < N && v[i + k] == v[j + k])
            k++;

        lcp[r] = k;

        if (k) k--;
    }

    // Soma dos mínimos de todos os subarrays do LCP
    long long T = 0;

    int M = N - 1;

    vector<int> left(M), right(M);
    stack<int> st;

    for (int i = 0; i < M; i++) {
        while (!st.empty() && lcp[st.top()] > lcp[i])
            st.pop();

        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    for (int i = M - 1; i >= 0; i--) {
        while (!st.empty() && lcp[st.top()] >= lcp[i])
            st.pop();

        right[i] = st.empty() ? M : st.top();
        st.push(i);
    }

    for (int i = 0; i < M; i++) {
        long long cnt =
            1LL * (i - left[i]) * (right[i] - i);

        T += lcp[i] * cnt;
    }

    long long self = 1LL * N * (N + 1) / 2;

    long long P = 2 * T + self;
    long long Q = 1LL * N * N;

    long long g = gcd(P, Q);

    cout << (P / g) << '/' << (Q / g) << '\n';

    return 0;
}
