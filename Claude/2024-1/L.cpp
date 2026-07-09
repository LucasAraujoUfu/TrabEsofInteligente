#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<long long> a(N);
    for(int i = 0; i < N; i++) cin >> a[i];

    // Para cada bit k (0..29), contar quantos 1s existem
    vector<int> ones(30, 0);
    for(int i = 0; i < N; i++)
        for(int k = 0; k < 30; k++)
            if((a[i] >> k) & 1) ones[k]++;

    // Para maximizar lexicograficamente:
    // Para cada bit k, os 'ones[k]' uns vão para os primeiros ones[k] elementos
    vector<long long> result(N, 0);
    for(int k = 0; k < 30; k++)
        for(int i = 0; i < ones[k]; i++)
            result[i] |= (1LL << k);

    for(int i = 0; i < N; i++){
        if(i) cout << " ";
        cout << result[i];
    }
    cout << "\n";

    return 0;
}
