#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K;
    cin >> N >> K;
    
    // N falas de duração T + (N-1) intervalos de 1 min <= K
    // T = floor((K - (N-1)) / N)
    cout << (K - (N - 1)) / N << "\n";
    
    return 0;
}
