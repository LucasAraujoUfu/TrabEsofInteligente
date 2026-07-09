#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;

    // volume[i] e nome[i] para nós 1..2N-1
    vector<ll> vol(2*N);
    vector<int> nome(2*N);

    for(int i = 1; i <= N; i++){
        cin >> vol[i];
        nome[i] = i;
    }

    // filhos de cada nó interno
    vector<int> left(2*N, 0), right(2*N, 0);

    // nós internos: N+1 .. 2N-1, criados em ordem
    for(int i = 1; i <= N-1; i++){
        int a, b; cin >> a >> b;
        int node = N + i;
        left[node] = a;
        right[node] = b;
    }

    // Processa todos os nós internos em ordem (já é topológica)
    auto recompute = [&](){
        for(int node = N+1; node <= 2*N-1; node++){
            int a = left[node], b = right[node];
            vol[node] = vol[a] + vol[b];
            if(vol[a] > vol[b])       nome[node] = nome[a];
            else if(vol[b] > vol[a])  nome[node] = nome[b];
            else                       nome[node] = min(nome[a], nome[b]);
        }
    };

    recompute();

    // Raiz é o nó 2N-1
    int raiz = 2*N - 1;
    if(N == 1) raiz = 1;

    cout << nome[raiz] << "\n";

    int Q; cin >> Q;
    while(Q--){
        int ni; ll qi;
        cin >> ni >> qi;
        vol[ni] += qi;
        recompute();
        cout << nome[raiz] << "\n";
    }

    return 0;
}
