#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int main() {
    int N;
    scanf("%d", &N);

    ull B = 0;
    // lê a_N, a_{N-1}, ..., a_0
    for (int i = N; i >= 0; i--) {
        int a;
        scanf("%d", &a);
        if (a) B |= (1ULL << i);
    }

    long long steps = 0;
    while (B != 1ULL) {
        if (B & 1ULL) {
            B = (B << 1) ^ B ^ 1ULL;
        } else {
            B = B >> 1;
        }
        steps++;
    }

    printf("%lld\n", steps);
    return 0;
}
