#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

static const ll LIMIT = 1000000000LL;
static const ll CAP = 2000000000LL;

static void kmpFailure(const ll* s, int n, int* pi) {
    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
}

ll gcdll(ll a, ll b) { while (b) { a %= b; swap(a, b); } return a; }

ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int N;
vector<ll> A, B;
vector<int> P;
vector<char> visited;

int main() {
    if (scanf("%d", &N) != 1) return 0;
    A.resize(N); B.resize(N); P.resize(N);
    for (int i = 0; i < N; i++) scanf("%lld", &A[i]);
    for (int i = 0; i < N; i++) scanf("%lld", &B[i]);
    for (int i = 0; i < N; i++) { scanf("%d", &P[i]); P[i]--; }

    visited.assign(N, false);

    bool fixedMode = false;
    ll curR = 0, curM = 1;
    bool possible = true;

    vector<int> pos;
    pos.reserve(N);
    vector<ll> a, b, combined;
    a.reserve(N); b.reserve(N); combined.reserve(2 * N + 1);
    vector<int> pi;
    pi.reserve(2 * N + 1);

    for (int start = 0; start < N && possible; start++) {
        if (visited[start]) continue;
        pos.clear();
        int cur = start;
        while (!visited[cur]) {
            visited[cur] = true;
            pos.push_back(cur);
            cur = P[cur];
        }
        int L = (int)pos.size();

        a.resize(L); b.resize(L);
        for (int t = 0; t < L; t++) { a[t] = A[pos[t]]; b[t] = B[pos[t]]; }

        combined.clear();
        for (int t = 0; t < L; t++) combined.push_back(a[t]);
        combined.push_back(-1);
        for (int t = 0; t < L; t++) combined.push_back(b[t]);
        for (int t = 0; t < L; t++) combined.push_back(b[t]);

        int total = (int)combined.size();
        pi.resize(total);
        kmpFailure(combined.data(), total, pi.data());

        int k0 = -1;
        for (int i = L + 1; i < total; i++) {
            if (pi[i] == L) {
                int startInText = i - 2 * L;
                if (startInText >= 0 && startInText < L) { k0 = startInText; break; }
            }
        }

        if (k0 == -1) { possible = false; break; }

        int failLen = pi[L - 1];
        int p = L - failLen;
        if (L % p != 0) p = L;

        int r0 = k0 % p;

        if (!fixedMode) {
            ll g = gcdll(curM, (ll)p);
            if (((ll)r0 - curR) % g != 0) { possible = false; break; }
            ll lcm = curM / g * (ll)p;
            ll x, y;
            extgcd(curM / g, p / g, x, y);
            ll mod2 = p / g;
            lll t = ( (lll)( ((ll)r0 - curR) / g % mod2 ) * (lll)(x % mod2) ) % mod2;
            ll tll = (ll)((t % mod2 + mod2) % mod2);
            ll newR = ( (lll)curM * (lll)tll + curR ) % lcm;
            if (newR < 0) newR += lcm;
            curR = newR;
            curM = lcm;
            if (curM > CAP) fixedMode = true;
        } else {
            if (curR % p != r0) { possible = false; break; }
        }
    }

    if (!possible) { printf("IMPOSSIVEL\n"); return 0; }
    if (curR > LIMIT) printf("DEMAIS\n");
    else printf("%lld\n", curR);

    return 0;
}
