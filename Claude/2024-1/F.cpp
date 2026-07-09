#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;

    long long a = 1, b = 1;
    for (int i = 2; i <= N; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }

    // numerador de p_N = fib(N+1)
    cout << b << "\n";

    return 0;
}
