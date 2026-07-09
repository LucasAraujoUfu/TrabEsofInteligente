#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // filme_atores[f] = lista de atores do filme f (1-indexed)
    vector<vector<int>> filme_atores(N + 1);
    // ator_filmes[a] = lista de filmes do ator a
    vector<vector<int>> ator_filmes(M + 1);

    for(int f = 1; f <= N; f++){
        int ni; cin >> ni;
        for(int j = 0; j < ni; j++){
            int a; cin >> a;
            filme_atores[f].push_back(a);
            ator_filmes[a].push_back(f);
        }
    }

    int Q; cin >> Q;

    while(Q--){
        int src, dst;
        cin >> src >> dst;

        // BFS: estado = ator
        // prev_ator[a] = ator que veio antes
        // prev_filme[a] = filme usado para chegar em a
        vector<int> prev_ator(M + 1, -1);
        vector<int> prev_filme(M + 1, -1);
        vector<bool> visited_ator(M + 1, false);
        vector<bool> visited_filme(N + 1, false);

        queue<int> q;
        q.push(src);
        visited_ator[src] = true;
        prev_ator[src] = 0; // marcador de inicio

        bool found = false;

        while(!q.empty() && !found){
            int u = q.front(); q.pop();

            for(int f : ator_filmes[u]){
                if(visited_filme[f]) continue;
                visited_filme[f] = true;

                for(int v : filme_atores[f]){
                    if(visited_ator[v]) continue;
                    visited_ator[v] = true;
                    prev_ator[v] = u;
                    prev_filme[v] = f;

                    if(v == dst){
                        found = true;
                        break;
                    }
                    q.push(v);
                }
                if(found) break;
            }
        }

        if(!found){
            cout << -1 << "\n";
            continue;
        }

        // Reconstruir caminho
        vector<int> atores;
        vector<int> filmes;

        int cur = dst;
        while(cur != src){
            atores.push_back(cur);
            filmes.push_back(prev_filme[cur]);
            cur = prev_ator[cur];
        }
        atores.push_back(src);

        reverse(atores.begin(), atores.end());
        reverse(filmes.begin(), filmes.end());

        // ki = número de atores na sequência
        int ki = (int)atores.size();
        cout << ki << "\n";

        // Saída alternada: a1 f1 a2 f2 ... f(k-1) ak
        for(int i = 0; i < ki; i++){
            if(i > 0) cout << " ";
            cout << atores[i];
            if(i < ki - 1) cout << " " << filmes[i];
        }
        cout << "\n";
    }

    return 0;
}
