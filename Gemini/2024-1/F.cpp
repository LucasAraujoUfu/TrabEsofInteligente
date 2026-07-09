#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (cin >> n) {
        vector<long long> fib(n + 2);
        fib[1] = 1;
        fib[2] = 1;
        for (int i = 3; i <= n + 1; i++) {
            fib[i] = fib[i-1] + fib[i-2];
        }
        cout << fib[n+1] << "\n";
    }
    return 0;
}
