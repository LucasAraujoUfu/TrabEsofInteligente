// Versão otimizada com bitset
#include <bits/stdc++.h>
using namespace std;

int par_tc[1001], par_bc[1001];

int find_tc(int x){ return par_tc[x]==x?x:par_tc[x]=find_tc(par_tc[x]); }
int find_bc(int x){ return par_bc[x]==x?x:par_bc[x]=find_bc(par_bc[x]); }
void unite_tc(int x,int y){ x=find_tc(x);y=find_tc(y);if(x!=y)par_tc[x]=y; }
void unite_bc(int x,int y){ x=find_bc(x);y=find_bc(y);if(x!=y)par_bc[x]=y; }

int match_r[1001];
vector<int> gadj[1001];

bool dfs_m(int u, vector<bool>& vis, int bc_cnt){
    for(int v : gadj[u]){
        if(vis[v]) continue;
        vis[v]=true;
        if(match_r[v]==-1 || dfs_m(match_r[v],vis,bc_cnt)){
            match_r[v]=u; return true;
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<string> A(N);
    for(int i=0;i<N;i++) cin>>A[i];

    for(int i=0;i<N;i++) par_tc[i]=i, par_bc[i]=i;

    for(int i=0;i<N;i++){
        // BFS 2-coloração dos vizinhos de i
        vector<int> nbrs;
        for(int j=0;j<N;j++) if(j!=i && A[i][j]=='1') nbrs.push_back(j);
        if(nbrs.empty()) continue;

        vector<int> col(N,-1);
        col[nbrs[0]]=0;
        queue<int> q; q.push(nbrs[0]);

        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v:nbrs){
                if(A[u][v]=='0' && col[v]==-1){
                    col[v]=1-col[u];
                    q.push(v);
                }
            }
        }
        for(int j:nbrs) if(col[j]==-1) col[j]=0;

        // Unir grupo 0 em tc com i, grupo 1 em bc com i
        int rep0=i, rep1=-1;
        for(int j:nbrs){
            if(col[j]==0) unite_tc(rep0,j);
            else {
                if(rep1==-1) rep1=j;
                else unite_bc(rep1,j);
            }
        }
        if(rep1!=-1) unite_bc(i,rep1);
    }

    // Mapear classes
    map<int,int> tm, bm;
    int tc=0,bc=0;
    for(int i=0;i<N;i++){
        int t=find_tc(i),b=find_bc(i);
        if(!tm.count(t)) tm[t]=tc++;
        if(!bm.count(b)) bm[b]=bc++;
    }

    // Construir grafo bipartido
    set<pair<int,int>> es;
    for(int i=0;i<N;i++) es.insert({tm[find_tc(i)],bm[find_bc(i)]});
    for(auto [u,v]:es) gadj[u].push_back(v);

    // Matching
    fill(match_r,match_r+bc,-1);
    int ans=0;
    for(int u=0;u<tc;u++){
        vector<bool> vis(bc,false);
        if(dfs_m(u,vis,bc)) ans++;
    }
    cout<<ans<<"\n";
    return 0;
}
