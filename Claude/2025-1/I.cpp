#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int N;
    scanf("%d", &N);
    vector<ll> X(N), Y(N);
    for (int i = 0; i < N; i++) scanf("%lld %lld", &X[i], &Y[i]);

    vector<ll> D(N - 1);
    for (int i = 0; i < N - 1; i++) {
        ll dx = llabs(X[i] - X[i + 1]);
        ll dy = llabs(Y[i] - Y[i + 1]);
        D[i] = dx + dy;
    }

    int sign = 1;
    ll C = 0;
    ll lower = 1;
    bool hasUpper = false;
    ll upper = 0;

    for (int i = 0; i < N - 1; i++) {
        ll newC = D[i] - C;
        sign = -sign;
        C = newC;

        if (sign == 1) {
            ll b = 1 - C;
            if (b > lower) lower = b;
        } else {
            ll b = C - 1;
            if (!hasUpper || b < upper) { upper = b; hasUpper = true; }
        }
    }

    if (!hasUpper) { printf("%lld\n", lower); return 0; }

    if (upper >= lower) printf("%lld\n", upper);
    else printf("-1\n");

    return 0;
}
