#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    string S;
    cin >> K >> S;

    int n = S.size();
    int ops = 0;

    // Greedy: percorrer da esquerda para direita
    // manter quantos consecutivos iguais temos até agora
    int consec = 1;
    for(int i = 1; i < n; i++){
        if(S[i] == S[i-1]){
            consec++;
            if(consec == K){
                // Flipar S[i]
                S[i] = (S[i] == '0') ? '1' : '0';
                ops++;
                consec = 1;
            }
        } else {
            consec = 1;
        }
    }

    cout << ops << " " << S << "\n";
    return 0;
}
