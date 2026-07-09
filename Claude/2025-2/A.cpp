#include <bits/stdc++.h>
using namespace std;

int N;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> N;
    long long P; cin >> P;
    vector<int> L(P);
    for(auto &x: L) cin >> x;
    long long Q; cin >> Q;
    vector<int> R(Q);
    for(auto &x: R) cin >> x;

    auto printNo = [](){ cout << "N\n"; exit(0); };

    if(N % 2 == 0){
        if(N != 2) printNo();
        long long T = 2;
        for(int cand=0; cand<2; cand++){
            vector<int> full(2);
            if(cand==0){ full[0]=1; full[1]=2; }
            else { full[0]=2; full[1]=1; }
            if(P > T) continue;
            if(Q > T) continue;
            if(P + Q > T){
                bool ok = true;
                for(int i=0;i<(int)P;i++){
                    if(i<(int)T && full[i]!=L[i]) { ok=false; break; }
                }
                if(ok){
                    for(int i=0;i<(int)Q;i++){
                        int pos = (int)T - (int)Q + i;
                        if(pos<0 || pos>=(int)T) { ok=false; break; }
                        if(full[pos]!=R[i]) { ok=false; break; }
                    }
                }
                if(ok){ cout << "Y\n"; return 0; }
            } else {
                bool ok=true;
                for(int i=0;i<(int)P;i++) if(full[i]!=L[i]) { ok=false; break; }
                if(ok){
                    for(int i=0;i<(int)Q;i++){
                        int pos = (int)T-(int)Q+i;
                        if(full[pos]!=R[i]) { ok=false; break; }
                    }
                }
                if(ok){ cout << "Y\n"; return 0; }
            }
        }
        printNo();
    }

    long long T = (long long)N*(N-1)/2 + 1;

    auto checkTrail = [&](vector<int>& seq)->bool{
        for(size_t i=0;i+1<seq.size();i++){
            int a=seq[i], b=seq[i+1];
            if(a==b) return false;
            if(a<1||a>N||b<1||b>N) return false;
        }
        return true;
    };
    if(!checkTrail(L)) printNo();
    if(!checkTrail(R)) printNo();

    if(P + Q > T){
        long long overlap = P+Q-T;
        if(overlap > P || overlap > Q) printNo();
        for(long long i=0;i<overlap;i++){
            if(L[P-overlap+i] != R[i]) printNo();
        }
        vector<int> W(T);
        for(long long i=0;i<P;i++) W[i]=L[i];
        for(long long i=0;i<Q-overlap;i++) W[P+i]=R[overlap+i];
        vector<vector<bool>> used(N+1, vector<bool>(N+1,false));
        bool ok=true;
        for(long long i=0;i+1<T && ok;i++){
            int a=W[i], b=W[i+1];
            if(a==b){ ok=false; break;}
            if(a<1||a>N||b<1||b>N){ ok=false; break; }
            if(used[a][b]) { ok=false; break; }
            used[a][b]=used[b][a]=true;
        }
        if(!ok) printNo();
        if(N>1){
            if(W[0] != W[T-1]) printNo();
        }
        cout << "Y\n";
        return 0;
    }

    static vector<vector<bool>> used;
    used.assign(N+1, vector<bool>(N+1,false));
    for(size_t i=0;i+1<L.size();i++){
        int a=L[i], b=L[i+1];
        if(used[a][b]) printNo();
        used[a][b]=used[b][a]=true;
    }
    for(size_t i=0;i+1<R.size();i++){
        int a=R[i], b=R[i+1];
        if(used[a][b]) printNo();
        used[a][b]=used[b][a]=true;
    }

    vector<int> degUsed(N+1,0);
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++) if(i!=j && used[i][j]) degUsed[i]++;
    }
    vector<int> degPrime(N+1,0);
    for(int i=1;i<=N;i++) degPrime[i] = (N-1) - degUsed[i];

    int startV = (P>0)? L[P-1] : -1;
    int endV = (Q>0)? R[0] : -1;

    vector<int> oddVerts;
    for(int i=1;i<=N;i++) if(degPrime[i]%2==1) oddVerts.push_back(i);

    bool degOk = false;
    if(P>0 && Q>0){
        if(startV == endV){
            degOk = (oddVerts.empty());
        } else {
            degOk = (oddVerts.size()==2 && ((oddVerts[0]==startV && oddVerts[1]==endV) || (oddVerts[0]==endV && oddVerts[1]==startV)));
        }
    } else if(P>0 && Q==0){
        if(oddVerts.empty()){
            degOk = true;
        } else if(oddVerts.size()==2){
            degOk = (oddVerts[0]==startV || oddVerts[1]==startV);
        } else degOk = false;
    } else if(P==0 && Q>0){
        if(oddVerts.empty()){
            degOk = true;
        } else if(oddVerts.size()==2){
            degOk = (oddVerts[0]==endV || oddVerts[1]==endV);
        } else degOk = false;
    } else {
        degOk = oddVerts.empty();
    }

    if(!degOk) printNo();

    long long totalEdgesHprime = 0;
    for(int i=1;i<=N;i++) totalEdgesHprime += degPrime[i];
    totalEdgesHprime /= 2;

    if(totalEdgesHprime == 0){
        cout << "Y\n";
        return 0;
    }

    set<int> unvisited;
    for(int i=1;i<=N;i++) if(degPrime[i] > 0) unvisited.insert(i);

    if(unvisited.empty()){
        cout << "Y\n";
        return 0;
    }

    int src = *unvisited.begin();
    unvisited.erase(unvisited.begin());
    queue<int> q;
    q.push(src);
    int visitedCount = 1;

    while(!q.empty()){
        int u = q.front(); q.pop();
        vector<int> toRemove;
        for(int v : unvisited){
            if(!used[u][v]){
                toRemove.push_back(v);
            }
        }
        for(int v: toRemove){
            unvisited.erase(v);
            q.push(v);
            visitedCount++;
        }
    }

    int totalActive = 0;
    for(int i=1;i<=N;i++) if(degPrime[i]>0) totalActive++;

    if(visitedCount != totalActive) printNo();

    cout << "Y\n";
    return 0;
}
