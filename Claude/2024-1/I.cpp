#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;
const int MAXV = 1e6 + 1;

ll pw2[100005];
int f[MAXV]; // f[d] = # comidas divisíveis por d

ll power(ll base, ll exp, ll mod){
    ll res = 1; base %= mod;
    while(exp > 0){
        if(exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Pré-computar potências de 2
    pw2[0] = 1;
    for(int i = 1; i <= 100000; i++)
        pw2[i] = pw2[i-1] * 2 % MOD;

    int N; cin >> N;
    vector<int> V(N);
    for(int i = 0; i < N; i++) cin >> V[i];

    // cnt[v] = quantas comidas têm valor v
    vector<int> cnt(MAXV, 0);
    for(int v : V) cnt[v]++;

    // f[d] = soma de cnt[d], cnt[2d], cnt[3d], ...
    for(int d = 1; d < MAXV; d++)
        for(int mult = d; mult < MAXV; mult += d)
            f[d] += cnt[mult];

    int Q; cin >> Q;
    while(Q--){
        int X; cin >> X;

        // Fatorar X
        vector<int> primes;
        int tmp = X;
        for(int p = 2; p * p <= tmp; p++){
            if(tmp % p == 0){
                primes.push_back(p);
                while(tmp % p == 0) tmp /= p;
            }
        }
        if(tmp > 1) primes.push_back(tmp);

        int k = primes.size();

        // PIE: contar comidas com gcd(v, X) == 1
        ll count = 0;
        for(int mask = 0; mask < (1 << k); mask++){
            ll prod = 1;
            int bits = __builtin_popcount(mask);
            for(int i = 0; i < k; i++)
                if(mask >> i & 1) prod *= primes[i];
            if(prod >= MAXV){
                // f[prod] = 0 pois nenhuma comida <= 10^6 é divisível
                continue;
            }
            if(bits % 2 == 0) count += f[prod];
            else              count -= f[prod];
        }

        cout << pw2[count] << "\n";
    }

    return 0;
}
