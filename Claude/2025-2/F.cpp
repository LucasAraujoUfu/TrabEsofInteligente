#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef __int128 u128;
typedef long long ll;

u64 mulmod(u64 a, u64 b, u64 mod){
    return (u64)((u128)a * b % mod);
}

u64 powmod(u64 a, u64 e, u64 mod){
    u64 r = 1 % mod;
    a %= mod;
    while(e){
        if(e&1) r = mulmod(r,a,mod);
        a = mulmod(a,a,mod);
        e >>= 1;
    }
    return r;
}

bool millerRabin(u64 n){
    if(n < 2) return false;
    for(u64 p : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL}){
        if(n % p == 0) return n == p;
    }
    u64 d = n-1;
    int r = 0;
    while(d % 2 == 0){ d/=2; r++; }
    for(u64 a : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL}){
        if(a >= n) continue;
        u64 x = powmod(a, d, n);
        if(x == 1 || x == n-1) continue;
        bool composite = true;
        for(int i=0;i<r-1;i++){
            x = mulmod(x,x,n);
            if(x == n-1){ composite = false; break; }
        }
        if(composite) return false;
    }
    return true;
}

u64 pollardRho(u64 n){
    if(n % 2 == 0) return 2;
    if(n % 3 == 0) return 3;
    u64 x = rand() % n, y = x, c = rand() % n + 1, d = 1;
    while(d == 1){
        x = (mulmod(x,x,n) + c) % n;
        y = (mulmod(y,y,n) + c) % n;
        y = (mulmod(y,y,n) + c) % n;
        u64 diff = x > y ? x - y : y - x;
        if(diff == 0){ d = n; break; }
        d = std::__gcd(diff, n);
    }
    if(d != n) return d;
    return n; // failed, caller should retry with different params
}

void factorize(u64 n, map<u64, ll>& factors){
    if(n == 1) return;
    if(millerRabin(n)){
        factors[n]++;
        return;
    }
    u64 d = n;
    while(d == n){
        d = pollardRho(n);
    }
    factorize(d, factors);
    factorize(n/d, factors);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string X;
    cin >> X;
    int L = X.size();

    map<u64, ll> factors;

    if(L <= 18){
        // exact factorization, X fits in u64 (max ~1.8e19, 18 digits max ~1e18-1)
        u64 val = 0;
        for(char c : X) val = val*10 + (c - '0');
        factorize(val, factors);
    } else {
        // Take top 12 significant digits, round based on 13th digit
        int k = 12;
        string topDigits = X.substr(0, k);
        u64 M = 0;
        for(char c : topDigits) M = M*10 + (c-'0');
        char nextDigit = X[k]; // the (k+1)-th digit, used for rounding
        if(nextDigit >= '5'){
            M += 1;
            // M might now have k+1 digits (carry), e.g. 999999999999 + 1 = 1000000000000
            // That's fine, we just track M as-is; n (number of trailing zero-equivalent digits) stays L-k
        }
        ll n = L - k; // number of digits removed from the tail

        // factor M (M <= ~1.1 * 10^12, trial division up to sqrt(M) ~ 1.05e6 is fast)
        u64 Mval = M;
        // trial division
        for(u64 p = 2; p*p <= Mval; p++){
            while(Mval % p == 0){
                factors[p]++;
                Mval /= p;
            }
        }
        if(Mval > 1){
            factors[Mval]++;
        }

        // add n copies of prime 2 and prime 5 (from 10^n = 2^n * 5^n)
        if(n > 0){
            factors[2] += n;
            factors[5] += n;
        }
    }

    cout << factors.size() << "\n";
    for(auto& [p, e] : factors){
        cout << p << " " << e << "\n";
    }

    return 0;
}
