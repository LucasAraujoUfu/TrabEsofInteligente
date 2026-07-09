#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string Ms, Ns;
    cin >> Ms >> Ns;

    // Coletar todos os *'s (posição e se é de M ou N)
    vector<pair<int,int>> stars; // (0=M/1=N, índice)
    for(int i = 0; i < (int)Ns.size(); i++)
        if(Ns[i] == '*') stars.push_back({1, i});
    for(int i = 0; i < (int)Ms.size(); i++)
        if(Ms[i] == '*') stars.push_back({0, i});

    int S = stars.size();

    // Enumerar 2^S substituições
    for(int mask = 0; mask < (1 << S); mask++){
        string M = Ms, N = Ns;
        for(int i = 0; i < S; i++){
            char c = ((mask >> i) & 1) ? '1' : '0';
            if(stars[i].first == 1) N[stars[i].second] = c;
            else                    M[stars[i].second] = c;
        }

        // Calcular N como número (até 16 bits)
        ll Nval = 0;
        for(char c : N) Nval = Nval*2 + (c-'0');
        if(Nval == 0) continue;

        // Calcular M mod Nval (M pode ser 500 bits, processar bit a bit)
        ll rem = 0;
        for(char c : M) rem = (rem*2 + (c-'0')) % Nval;

        if(rem == 0){
            cout << M << "\n";
            return 0;
        }
    }

    return 0;
}
