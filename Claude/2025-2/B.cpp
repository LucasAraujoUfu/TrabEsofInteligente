#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long N, K;
    cin >> N >> K;

    long long upTo = min(N, K - 1);
    if (upTo < 1) upTo = 1; // K==1 case: K-1=0, but we still need at least step i=1 initialized

    // dp[m] for m in [1..K]: number of sequences of length 'i' with m_i = m
    vector<long long> dp(K + 2, 0);
    // i = 1: m_1 = c1 in [1..K]
    for (long long c1 = 1; c1 <= K; c1++) dp[c1] = (dp[c1] + 1) % MOD;

    for (long long i = 2; i <= upTo; i++) {
        vector<long long> ndp(K + 2, 0);
        for (long long m_prev = 1; m_prev <= K; m_prev++) {
            if (dp[m_prev] == 0) continue;
            long long cnt = dp[m_prev];
            long long r = m_prev % i;
            long long c = (r >= 1) ? r : i;
            for (; c <= K; c += i) {
                long long m = ((i - 1) * m_prev + c) / i;
                if (m <= K + 1) {
                    ndp[m] = (ndp[m] + cnt) % MOD;
                }
            }
        }
        dp = ndp;
    }

    long long ans = 0;
    for (long long m = 0; m <= K + 1; m++) ans = (ans + dp[m]) % MOD;

    cout << ans << "\n";
    return 0;
}
