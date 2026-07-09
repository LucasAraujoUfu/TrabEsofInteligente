#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> A;

vector<int> solve(int p){
    vector<int> res = A;
    if(res[p] != 0 && res[p] != N) return {};
    res[p] = N;

    // Verificar fixados
    {
        int prev = 0;
        for(int i = 0; i <= p; i++){
            if(res[i]==0) continue;
            if(res[i]<=prev) return {};
            prev=res[i];
        }
    }
    {
        int prev=N+1;
        for(int i=p;i<N;i++){
            if(res[i]==0) continue;
            if(res[i]>=prev) return {};
            prev=res[i];
        }
    }

    // Valores faltantes
    vector<bool> used(N+1,false);
    for(int i=0;i<N;i++) if(A[i]!=0) used[A[i]]=true;
    used[N]=true;
    multiset<int> miss;
    for(int v=1;v<N;v++) if(!used[v]) miss.insert(v);

    // Preencher slots zerados da esquerda [0..p-1]:
    // Para cada slot zerado em posição i, o valor deve estar em (prev_fixed, next_fixed)
    // Usar greedy: para cada slot zerado em ordem, pegar o menor disponível
    // que é maior que o valor anterior e menor que o próximo fixado à direita

    // Calcular próximo fixado à direita de cada posição na esquerda
    // Preencher esquerda: esquerda para direita
    {
        int prev=0;
        // próximo fixado à direita (excluindo posição p)
        // Pré-calcular next_fixed_left[i] = menor j>i com res[j]!=0 e j<=p
        vector<int> nf(p+1, N+1); // N+1 = sentinela (sem fixado)
        nf[p]=N; // pico
        for(int i=p-1;i>=0;i--){
            if(res[i]!=0) nf[i]=res[i];
            else nf[i]=nf[i+1];
        }

        for(int i=0;i<p;i++){
            if(res[i]!=0){
                prev=res[i];
                continue;
            }
            // Escolher menor disponível em (prev, nf[i+1])
            // nf[i+1] = próximo fixado após i
            int hi_val = (i+1<=p) ? nf[i+1] : N+1;
            auto it = miss.upper_bound(prev);
            if(it==miss.end() || *it>=hi_val) return {};
            res[i]=*it;
            prev=*it;
            miss.erase(it);
        }
    }

    // Preencher direita [p+1..N-1]: direita para esquerda (para respeitar decrescente)
    // Equivalente a preencher em ordem normal mas querendo decrescente
    {
        int prev=N+1;
        // próximo fixado à esquerda (para direita, lendo da esquerda)
        // prev_fixed_right[i] = maior j<i com res[j]!=0 e j>p
        // Pré-calcular próximo fixado à ESQUERDA de cada posição na direita
        vector<int> pf(N, 0);
        pf[p]=N;
        for(int i=p+1;i<N;i++){
            if(res[i]!=0) pf[i]=res[i];
            else pf[i]=pf[i-1];
        }

        for(int i=p+1;i<N;i++){
            if(res[i]!=0){
                prev=res[i];
                continue;
            }
            // Escolher maior disponível em (next_fixed_right, prev)
            // onde next_fixed_right = próximo fixado à direita de i
            // Calcular next fixado à direita
            int lo_val=0;
            for(int j=i+1;j<N;j++){
                if(A[j]!=0){ lo_val=A[j]; break; }
            }
            // Queremos: lo_val < res[i] < prev
            auto it = miss.lower_bound(prev);
            if(it==miss.begin()) return {};
            --it;
            if(*it<=lo_val) return {};
            res[i]=*it;
            prev=*it;
            miss.erase(it);
        }
    }

    if(!miss.empty()) return {};

    // Verificação final
    for(int i=0;i<p-1;i++) if(res[i]>=res[i+1]) return {};
    for(int i=p;i<N-1;i++) if(res[i]<=res[i+1]) return {};

    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>N;
    A.resize(N);
    for(int i=0;i<N;i++) cin>>A[i];

    int peak_pos=-1;
    for(int i=0;i<N;i++) if(A[i]==N){peak_pos=i;break;}

    auto print=[&](vector<int>& r){
        for(int i=0;i<N;i++){if(i)cout<<" ";cout<<r[i];}
        cout<<"\n";
    };

    if(peak_pos!=-1){
        auto res=solve(peak_pos);
        if(res.empty()) cout<<"*\n";
        else print(res);
        return 0;
    }

    // Determinar range válido para pico
    int lo=0,hi=N-1;
    {
        int prev=0;
        for(int i=0;i<N;i++){
            if(A[i]==0) continue;
            if(A[i]<prev) hi=min(hi,i-1);
            else prev=A[i];
        }
    }
    {
        int prev=0;
        for(int i=N-1;i>=0;i--){
            if(A[i]==0) continue;
            if(A[i]<prev) lo=max(lo,i+1);
            else prev=A[i];
        }
    }

    for(int p=lo;p<=hi;p++){
        if(A[p]!=0) continue;
        auto res=solve(p);
        if(!res.empty()){print(res);return 0;}
    }
    cout<<"*\n";
    return 0;
}
