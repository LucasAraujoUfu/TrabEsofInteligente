#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;

    long long a = 1, b = 1;

    for (int i = 1; i <= N; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }

    cout << a << '\n';
}
