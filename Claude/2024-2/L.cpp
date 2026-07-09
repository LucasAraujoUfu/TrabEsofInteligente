#include <bits/stdc++.h>
using namespace std;

// Matching bipartido
struct Matching {
    int n, m;
    vector<vector<int>> adj;
    vector<int> matchL, matchR;
    vector<bool> vis;

    Matching(int n, int m): n(n), m(m), adj(n), matchL(n,-1), matchR(m,-1), vis(n) {}

    void addEdge(int u, int v){ adj[u].push_back(v); }

    bool dfs(int u){
        for(int v: adj[u]){
            if(!vis[v]){
                vis[v]=true;
                if(matchR[v]==-1||dfs(matchR[v])){
                    matchL[u]=v; matchR[v]=u;
                    return true;
                }
            }
        }
        return false;
    }

    int solve(){
        int res=0;
        for(int u=0;u<n;u++){
            fill(vis.begin(),vis.end(),false);
            if(dfs(u)) res++;
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, T;
    cin >> N >> T;

    vector<int> rp(N), cp(N);
    iota(rp.begin(),rp.end(),0);
    iota(cp.begin(),cp.end(),0);

    for(int t=0;t<T;t++){
        char X; int I, J;
        cin>>X>>I>>J; I--;J--;
        if(X=='R') swap(rp[I],rp[J]);
        else       swap(cp[I],cp[J]);
    }

    vector<int> r(N),c(N);
    for(int i=0;i<N;i++) r[rp[i]]=i;
    for(int i=0;i<N;i++) c[cp[i]]=i;

    // Union-Find
    vector<int> par(N*N);
    iota(par.begin(),par.end(),0);
    function<int(int)> find=[&](int x)->int{
        return par[x]==x?x:par[x]=find(par[x]);
    };
    auto unite=[&](int x,int y){
        x=find(x);y=find(y);
        if(x!=y)par[x]=y;
    };

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            unite(i*N+j,r[i]*N+c[j]);

    // Verificar conflitos por classe
    vector<int> cls_row_seen(N*N,-1), cls_col_seen(N*N,-1);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++){
            int cls=find(i*N+j);
            if(cls_row_seen[cls]==i&&cls_col_seen[cls]==j) continue; // mesma célula
            if(cls_row_seen[cls]!=-1&&cls_row_seen[cls]!=i){
                // dois i distintos na mesma classe
            }
            // Verificar única ocorrência por linha
            // Usar mapa
        }

    // Simplificação: verificar usando sets
    map<int,set<int>> cls_rows, cls_cols;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++){
            int cls=find(i*N+j);
            cls_rows[cls].insert(i);
            cls_cols[cls].insert(j);
        }

    for(auto&[cls,rows]:cls_rows)
        if((int)rows.size()!=(int)cls_cols[cls].size()){
            cout<<"*\n";return 0;
        }

    // Verificar: para cada linha, classes distintas
    for(int i=0;i<N;i++){
        set<int> seen;
        for(int j=0;j<N;j++){
            int cls=find(i*N+j);
            if(seen.count(cls)){cout<<"*\n";return 0;}
            seen.insert(cls);
        }
    }

    // Atribuir valores às classes via Latin Square construction
    // Usar o seguinte approach:
    // Construir a permutação de colunas para cada linha usando matching.
    
    // col_val[j] = valor na posição de coluna j da linha 0 = j+1
    // Para linha i, a permutação de valores é determinada pelas classes.
    
    // val[cls] = valor da classe
    vector<int> val(N*N, 0);

    // Linha 0: atribuir 1..N em ordem
    for(int j=0;j<N;j++) val[find(0*N+j)]=j+1;

    // Para cada linha i>=1: verificar consistency e atribuir
    // Rastrear valores usados por coluna
    // col_used[j] = conjunto de valores já usados na coluna j
    vector<set<int>> col_used(N);
    for(int j=0;j<N;j++) col_used[j].insert(val[find(0*N+j)]);

    for(int i=1;i<N;i++){
        // Classes nessa linha com valores já atribuídos e não atribuídos
        vector<int> row_cls(N);
        for(int j=0;j<N;j++) row_cls[j]=find(i*N+j);

        // Verificar conflitos nos já atribuídos
        set<int> used_in_row;
        for(int j=0;j<N;j++){
            if(val[row_cls[j]]){
                if(used_in_row.count(val[row_cls[j]])){
                    cout<<"*\n";return 0;
                }
                used_in_row.insert(val[row_cls[j]]);
            }
        }

        // Coletar classes não atribuídas e posições de coluna disponíveis
        vector<int> unassigned_cls;
        set<int> unassigned_cls_set;
        vector<int> free_cols; // colunas onde a classe não está atribuída
        for(int j=0;j<N;j++){
            if(!val[row_cls[j]] && !unassigned_cls_set.count(row_cls[j])){
                unassigned_cls.push_back(row_cls[j]);
                unassigned_cls_set.insert(row_cls[j]);
            }
        }

        // Valores disponíveis (não usados na linha)
        vector<int> avail_vals;
        for(int v=1;v<=N;v++)
            if(!used_in_row.count(v)) avail_vals.push_back(v);

        // Usar matching: classes não atribuídas × valores disponíveis
        // Restrição: classe cls pode receber valor v se
        //   para cada coluna j onde cls aparece: v não está em col_used[j]
        int nc = unassigned_cls.size();
        int nv = avail_vals.size();

        if(nc != nv){ cout<<"*\n"; return 0; }
        if(nc == 0) continue;

        // Mapear classe → índice local
        map<int,int> cls_idx;
        for(int k=0;k<nc;k++) cls_idx[unassigned_cls[k]]=k;

        // Para cada classe, quais colunas ela ocupa nessa linha
        map<int,vector<int>> cls_cols_in_row;
        for(int j=0;j<N;j++)
            if(!val[row_cls[j]])
                cls_cols_in_row[row_cls[j]].push_back(j);

        // Matching bipartido: cls → val
        Matching match(nc, nv);
        for(int k=0;k<nc;k++){
            int cls=unassigned_cls[k];
            for(int vi=0;vi<nv;vi++){
                int v=avail_vals[vi];
                // Verificar se v é válido para cls nas suas colunas
                bool ok=true;
                for(int col:cls_cols_in_row[cls]){
                    if(col_used[col].count(v)){ok=false;break;}
                }
                if(ok) match.addEdge(k,vi);
            }
        }

        int matched=match.solve();
        if(matched!=nc){cout<<"*\n";return 0;}

        // Atribuir valores
        for(int k=0;k<nc;k++){
            int cls=unassigned_cls[k];
            int v=avail_vals[match.matchL[k]];
            val[cls]=v;
            // Atualizar col_used
            for(int col:cls_cols_in_row[cls])
                col_used[col].insert(v);
        }

        // Também atualizar col_used para classes já atribuídas nessa linha
        for(int j=0;j<N;j++){
            if(val[row_cls[j]] && cls_cols_in_row.find(row_cls[j])==cls_cols_in_row.end()){
                // Classe já atribuída — verificar col_used
                if(col_used[j].count(val[row_cls[j]])){
                    cout<<"*\n";return 0;
                }
                col_used[j].insert(val[row_cls[j]]);
            }
        }
    }

    // Construir e verificar
    vector<vector<int>> M(N,vector<int>(N));
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            M[i][j]=val[find(i*N+j)];

    for(int i=0;i<N;i++){
        set<int> s(M[i].begin(),M[i].end());
        if((int)s.size()!=N){cout<<"*\n";return 0;}
    }
    for(int j=0;j<N;j++){
        set<int> s;
        for(int i=0;i<N;i++) s.insert(M[i][j]);
        if((int)s.size()!=N){cout<<"*\n";return 0;}
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){if(j)cout<<" ";cout<<M[i][j];}
        cout<<"\n";
    }
    return 0;
}
