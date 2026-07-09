#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
const int MAXM = 3e5 + 5;

int N, M;
struct Edge { int u, v, id; };
vector<Edge> edges(MAXM);
vector<pair<int,int>> adj[MAXN]; // {vizinho, id_aresta}

// Tarjan para pontes
int disc[MAXN], low[MAXN], timer_ = 0;
bool is_bridge[MAXM];

void dfs_bridge(int u, int par_edge){
    disc[u] = low[u] = ++timer_;
    for(auto [v, eid] : adj[u]){
        if(eid == par_edge) continue;
        if(disc[v]){
            low[u] = min(low[u], disc[v]);
        } else {
            dfs_bridge(v, eid);
            low[u] = min(low[u], low[v]);
            if(low[v] > disc[u])
                is_bridge[eid] = true;
        }
    }
}

// Componentes 2-aresta-conexos
int comp[MAXN];
int ncomp = 0;

void dfs_comp(int u, int c){
    comp[u] = c;
    for(auto [v, eid] : adj[u]){
        if(comp[v] == -1 && !is_bridge[eid])
            dfs_comp(v, c);
    }
}

// Encontrar ciclo com >= 3 vértices distintos dentro de componente
// DFS com rastreamento de caminho
vector<int> cycle_edges;
bool found_cycle = false;

int par_node[MAXN], par_edge_id[MAXN];
bool in_stack[MAXN];
int visited[MAXN]; // 0=unvisited, 1=in stack, 2=done

void dfs_cycle(int u, int target_comp){
    visited[u] = 1;
    in_stack[u] = true;

    for(auto [v, eid] : adj[u]){
        if(found_cycle) return;
        if(is_bridge[eid]) continue;
        if(comp[v] != target_comp) continue;

        if(visited[v] == 1){
            // Fechou ciclo: reconstruir de v até u
            // O ciclo vai de v → ... → u → v (via eid)
            // Verificar se tem >= 3 vértices distintos
            vector<int> cyc_e;
            cyc_e.push_back(eid);
            int cur = u;
            while(cur != v){
                cyc_e.push_back(par_edge_id[cur]);
                cur = par_node[cur];
            }
            // Contar vértices distintos no ciclo
            // O ciclo tem cyc_e.size() arestas e cyc_e.size() vértices
            // (v, ..., u, v) — ciclo de comprimento cyc_e.size()
            if((int)cyc_e.size() >= 3){
                cycle_edges = cyc_e;
                found_cycle = true;
            }
            return;
        }

        if(visited[v] == 0){
            par_node[v] = u;
            par_edge_id[v] = eid;
            dfs_cycle(v, target_comp);
            if(found_cycle) return;
        }
    }

    visited[u] = 2;
    in_stack[u] = false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i = 1; i <= M; i++){
        int u, v; cin >> u >> v;
        edges[i] = {u, v, i};
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    // Encontrar pontes (iterativo para evitar stack overflow)
    // Usando versão iterativa de Tarjan
    fill(disc+1, disc+N+1, 0);
    fill(low+1, low+N+1, 0);
    fill(is_bridge+1, is_bridge+M+1, false);

    // Iterative bridge finding
    vector<int> stk;
    vector<int> iter(N+1, 0);
    vector<int> par_e(N+1, -1);
    
    for(int start = 1; start <= N; start++){
        if(disc[start]) continue;
        stk.push_back(start);
        disc[start] = low[start] = ++timer_;
        
        while(!stk.empty()){
            int u = stk.back();
            bool pushed = false;
            
            while(iter[u] < (int)adj[u].size()){
                auto [v, eid] = adj[u][iter[u]++];
                if(eid == par_e[u]) continue;
                if(disc[v]){
                    low[u] = min(low[u], disc[v]);
                } else {
                    disc[v] = low[v] = ++timer_;
                    par_e[v] = eid;
                    stk.push_back(v);
                    pushed = true;
                    break;
                }
            }
            
            if(!pushed){
                stk.pop_back();
                if(!stk.empty()){
                    int p = stk.back();
                    low[p] = min(low[p], low[u]);
                    if(low[u] > disc[p])
                        is_bridge[par_e[u]] = true;
                }
            }
        }
    }

    // Componentes 2-aresta-conexos
    memset(comp, -1, sizeof(comp));
    for(int u = 1; u <= N; u++)
        if(comp[u] == -1)
            dfs_comp(u, ncomp++);

    // Encontrar ciclo com >= 3 vértices em algum componente
    memset(visited, 0, sizeof(visited));
    memset(par_node, -1, sizeof(par_node));
    memset(par_edge_id, -1, sizeof(par_edge_id));

    for(int u = 1; u <= N && !found_cycle; u++){
        if(visited[u] == 0)
            dfs_cycle(u, comp[u]);
    }

    if(!found_cycle){
        cout << "*\n";
        return 0;
    }

    cout << cycle_edges.size() << "\n";
    for(int i = 0; i < (int)cycle_edges.size(); i++){
        if(i) cout << " ";
        cout << cycle_edges[i];
    }
    cout << "\n";

    return 0;
}
