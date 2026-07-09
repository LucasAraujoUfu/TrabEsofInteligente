#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long K, N;
    cin >> K >> N;

    long long mn = (N+2)/3;
    long long mx = (N+1)/2;

    if(K < mn || K > mx){ cout<<"*\n"; return 0; }

    string res(N, '-');

    if(N == 2*K-1){
        // X-X-X-...-X
        for(int i=0;i<N;i+=2) res[i]='X';
    } else {
        long long a = N-2*K; // grupos de 3
        long long b = 3*K-N; // grupos de 2

        int pos = 0;
        long long total = a+b;

        for(long long i=0;i<total;i++){
            bool last = (i == total-1);
            long long sz = (i < b) ? 2 : 3;

            if(!last){
                // Pessoa no início do grupo
                res[pos] = 'X';
            } else {
                // Último grupo: pessoa no final - 1
                // sz=2: posições [pos, pos+1] → pessoa em pos+0 (X-)
                //   pos+1 viz(X,end) → bloqueado ✓
                // sz=3: posições [pos,pos+1,pos+2] → pessoa em pos+1 (-X-)
                //   pos viz('-',X) ✓; pos+2 viz(X,end) ✓
                if(sz == 2) res[pos] = 'X';
                else        res[pos+1] = 'X';
            }
            pos += sz;
        }
    }

    // Verificação
    bool valid = true;
    int xcnt=0;
    for(int i=0;i<N;i++) if(res[i]=='X') xcnt++;
    if(xcnt!=K) valid=false;

    for(int i=0;i<N&&valid;i++){
        if(res[i]=='-'){
            bool bl=(i>0&&res[i-1]=='X')||(i<N-1&&res[i+1]=='X');
            if(!bl) valid=false;
        } else {
            if((i>0&&res[i-1]=='X')||(i<N-1&&res[i+1]=='X')) valid=false;
        }
    }

    if(!valid){cout<<"*\n";return 0;}
    cout<<res<<"\n";
    return 0;
}
