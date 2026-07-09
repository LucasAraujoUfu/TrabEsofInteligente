#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXV = 1000000;

vector<int> prime_factors[MAXV + 1];
int freq[MAXV + 1];
int mult_count[MAXV + 1];
long long pow2[100005];

void sieve() {
    for (int i = 2; i <= MAXV; i++) {
        if (prime_factors[i].empty()) {
            for (int j = i; j <= MAXV; j += i) {
                prime_factors[j].push_back(i);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();

    pow2[0] = 1;
    for (int i = 1; i <= 100000; i++) pow2[i] = (pow2[i - 1] * 2) % MOD;

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        freq[v]++;
    }

    for (int i = 1; i <= MAXV; i++) {
        for (int j = i; j <= MAXV; j += i) {
            mult_count[i] += freq[j];
        }
    }

    int q;
    if (cin >> q) {
        while (q--) {
            int x;
            cin >> x;

            int n_factors = prime_factors[x].size();
            int forbidden_dishes = 0;

            for (int mask = 1; mask < (1 << n_factors); mask++) {
                int prod = 1;
                int bits = 0;
                for (int i = 0; i < n_factors; i++) {
                    if ((mask >> i) & 1) {
                        prod *= prime_factors[x][i];
                        bits++;
                    }
                }
                if (bits & 1) forbidden_dishes += mult_count[prod];
                else forbidden_dishes -= mult_count[prod];
            }

            int allowed = n - forbidden_dishes;
            cout << pow2[allowed] << "\n";
        }
    }
    return 0;
}
