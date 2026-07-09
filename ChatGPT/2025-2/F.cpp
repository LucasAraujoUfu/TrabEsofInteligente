#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<int> primes;

void sieve() {
    const int LIM = 100000;
    vector<bool> mark(LIM + 1, true);
    mark[0] = mark[1] = false;

    for (int i = 2; i <= LIM; i++) {
        if (mark[i]) {
            primes.push_back(i);
            if ((ll)i * i <= LIM) {
                for (int j = i * i; j <= LIM; j += i)
                    mark[j] = false;
            }
        }
    }
}

map<ll, long long> factorize(ll x) {
    map<ll, long long> ans;

    for (int p : primes) {
        if ((ll)p * p > x)
            break;

        while (x % p == 0) {
            ans[p]++;
            x /= p;
        }
    }

    if (x > 1)
        ans[x]++;

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string X;
    cin >> X;

    sieve();

    int n = X.size();

    ll A;
    long long zeros;

    if (n <= 10) {
        A = stoll(X);
        zeros = 0;
    } else {
        string first = X.substr(0, 10);
        A = stoll(first);

        int next = X[10] - '0';

        if (next >= 5)
            A++;

        zeros = n - 10;

        // caso 9999999999 arredonde para 10000000000
        if (A == 10000000000LL) {
            // 10^10 * 10^zeros = 10^(zeros+10)
            A = 1;
            zeros += 10;
        }
    }

    map<ll, long long> ans = factorize(A);

    // multiplicar por 10^zeros = 2^zeros * 5^zeros
    if (zeros > 0) {
        ans[2] += zeros;
        ans[5] += zeros;
    }

    cout << ans.size() << '\n';

    for (auto [p, e] : ans) {
        cout << p << ' ' << e << '\n';
    }

    return 0;
}
