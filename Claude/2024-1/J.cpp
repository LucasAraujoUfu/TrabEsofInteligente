#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    // aresta: (u, v, cor, id) — 1-indexed
    struct Edge { int u, v, c, id; };
    vector<Edge> edges(M+1);

    // adj[v] = lista de índices de arestas incidentes em v
    vector<vector<int>> adj(N+1);

    for(int i = 1; i <= M; i++){
        int u, v, c; cin >> u >> v >> c;
        edges[i] = {u, v, c, i};
        adj[u].push_back(i);
        adj[v].push_back(i);
    }

    // Condição 1: todo vértice com arestas deve ter grau par
    for(int v = 1; v <= N; v++){
        if(adj[v].size() % 2 != 0){
            cout << -1 << "\n";
            return 0;
        }
    }

    // Condição 2: grafo deve ser conexo (ignorando vértices isolados)
    {
        vector<bool> vis(N+1, false);
        int start = -1;
        for(int v = 1; v <= N; v++)
            if(!adj[v].empty()){ start = v; break; }
        if(start == -1){ cout << -1 << "\n"; return 0; }
        queue<int> bfsq;
        bfsq.push(start); vis[start] = true;
        while(!bfsq.empty()){
            int u = bfsq.front(); bfsq.pop();
            for(int eid : adj[u]){
                int w = (edges[eid].u == u) ? edges[eid].v : edges[eid].u;
                if(!vis[w]){ vis[w] = true; bfsq.push(w); }
            }
        }
        for(int v = 1; v <= N; v++)
            if(!adj[v].empty() && !vis[v]){
                cout << -1 << "\n";
                return 0;
            }
    }

    // Hierholzer com restrição de cor
    // Estado: (vértice, cor_última_aresta)
    // Ao estar em vértice v com última cor c, só podemos usar arestas de cor != c

    vector<bool> used(M+1, false);
    // Para cada vértice, ponteiro de iteração por cor
    // adj_by_color[v][c] = lista de arestas de cor c em v
    // ptr[v][c] = ponteiro atual

    // Indexar cores por vértice
    // adj_color[v] = map<cor, vector<eid>>
    vector<map<int,vector<int>>> adj_color(N+1);
    for(int i = 1; i <= M; i++){
        adj_color[edges[i].u][edges[i].c].push_back(i);
        adj_color[edges[i].v][edges[i].c].push_back(i);
    }

    // Ponteiros
    vector<map<int,int>> ptr(N+1);
    for(int v = 1; v <= N; v++)
        for(auto& [c, ev] : adj_color[v])
            ptr[v][c] = 0;

    // Hierholzer modificado
    // Stack: (vértice, cor_chegada, edge_id_usado_para_chegar)
    // cor_chegada = 0 significa início (sem restrição)

    int startV = -1;
    for(int v = 1; v <= N; v++)
        if(!adj[v].empty()){ startV = v; break; }

    vector<int> circuit; // ids de arestas em ordem
    // stack: (vértice, última_cor)
    stack<pair<int,int>> stk;
    stk.push({startV, 0});

    // Para cada elemento da stack, guardar também a aresta usada para chegar
    // Reformular: stack armazena (vértice, ultima_cor, aresta_que_gerou_este_estado)
    // aresta=0 significa estado inicial

    stack<tuple<int,int,int>> stk2; // (v, last_color, edge_id)
    stk2.push({startV, 0, 0});

    vector<int> result;
    bool failed = false;

    while(!stk2.empty()){
        auto& [v, lc, eid] = stk2.top();

        // Tentar encontrar próxima aresta de cor != lc em v
        bool found = false;
        for(auto& [c, ev] : adj_color[v]){
            if(c == lc) continue;
            while(ptr[v][c] < (int)ev.size() && used[ev[ptr[v][c]]])
                ptr[v][c]++;
            if(ptr[v][c] < (int)ev.size()){
                int neid = ev[ptr[v][c]++];
                used[neid] = true;
                int nv = (edges[neid].u == v) ? edges[neid].v : edges[neid].u;
                stk2.push({nv, c, neid});
                found = true;
                break;
            }
        }

        if(!found){
            // Sem mais arestas disponíveis — adicionar ao circuito
            if(eid != 0) result.push_back(eid);
            stk2.pop();
        }
    }

    // Verificar se todas as arestas foram usadas
    if((int)result.size() != M){
        cout << -1 << "\n";
        return 0;
    }

    // result está em ordem reversa
    reverse(result.begin(), result.end());

    // Verificar restrição de cor (incluindo wrap-around)
    // e encontrar vértice inicial
    {
        // Verificar cores consecutivas
        for(int i = 0; i < M-1; i++)
            if(edges[result[i]].c == edges[result[i+1]].c){
                cout << -1 << "\n";
                return 0;
            }
        // Primeira e última
        if(edges[result[0]].c == edges[result[M-1]].c){
            cout << -1 << "\n";
            return 0;
        }
    }

    // Determinar vértice inicial
    // result[0] é a primeira aresta; vértice inicial é um dos extremos
    // Precisamos saber de qual lado saímos
    // Reconstruir vértices: começamos em startV
    // A sequência de Hierholzer começa em startV
    // Mas após reverse, a primeira aresta pode não incidir em startV diretamente
    // Vamos recalcular o vértice inicial percorrendo o circuito

    // Determinar vértice de partida percorrendo a sequência
    // Tentar os dois extremos da primeira aresta
    auto tryStart = [&](int sv) -> bool {
        int cur = sv;
        for(int i = 0; i < M; i++){
            int e = result[i];
            if(edges[e].u == cur) cur = edges[e].v;
            else if(edges[e].v == cur) cur = edges[e].u;
            else return false;
        }
        return cur == sv;
    };

    int sv = -1;
    if(tryStart(edges[result[0]].u)) sv = edges[result[0]].u;
    else if(tryStart(edges[result[0]].v)) sv = edges[result[0]].v;

    if(sv == -1){
        cout << -1 << "\n";
        return 0;
    }

    cout << sv << "\n";
    for(int i = 0; i < M; i++){
        if(i) cout << " ";
        cout << result[i];
    }
    cout << "\n";

    return 0;
}
