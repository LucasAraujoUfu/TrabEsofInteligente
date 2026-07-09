#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;

struct SegTree {
    int n;
    vector<long long> mn;   // min value in range (only counts "active" leaves; inactive = INF)
    vector<long long> lazy; // pending add

    void init(int n_){
        n = n_;
        mn.assign(4*n, INF);
        lazy.assign(4*n, 0);
    }

    void push(int node){
        if(lazy[node]!=0){
            for(int c: {2*node, 2*node+1}){
                if(mn[c] < INF) mn[c] += lazy[node];
                lazy[c] += lazy[node];
            }
            lazy[node]=0;
        }
    }

    void rangeAdd(int node, int l, int r, int ql, int qr, long long val){
        if(qr<l || r<ql || ql>qr) return;
        if(ql<=l && r<=qr){
            if(mn[node] < INF) mn[node]+=val;
            lazy[node]+=val;
            return;
        }
        push(node);
        int mid=(l+r)/2;
        rangeAdd(2*node,l,mid,ql,qr,val);
        rangeAdd(2*node+1,mid+1,r,ql,qr,val);
        mn[node] = min(mn[2*node], mn[2*node+1]);
    }

    void pointSet(int node, int l, int r, int pos, long long val){
        if(l==r){
            mn[node]=val;
            lazy[node]=0;
            return;
        }
        push(node);
        int mid=(l+r)/2;
        if(pos<=mid) pointSet(2*node,l,mid,pos,val);
        else pointSet(2*node+1,mid+1,r,pos,val);
        mn[node]=min(mn[2*node], mn[2*node+1]);
    }

    void pointDeactivate(int node, int l, int r, int pos){
        if(l==r){
            mn[node]=INF;
            lazy[node]=0;
            return;
        }
        push(node);
        int mid=(l+r)/2;
        if(pos<=mid) pointDeactivate(2*node,l,mid,pos);
        else pointDeactivate(2*node+1,mid+1,r,pos);
        mn[node]=min(mn[2*node], mn[2*node+1]);
    }

    long long globalMin(){
        return mn[1];
    }
};

struct Fenwick {
    int n;
    vector<int> bit;
    void init(int n_){ n=n_; bit.assign(n+1,0); }
    void update(int i, int delta){
        for(; i<=n; i+=i&(-i)) bit[i]+=delta;
    }
    int query(int i){
        int s=0;
        for(; i>0; i-=i&(-i)) s+=bit[i];
        return s;
    }
};

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int Q; cin >> Q;
    vector<long long> X(Q);
    for(auto &x: X) cin >> x;

    vector<long long> vals;
    vals.reserve(Q);
    for(auto x: X) vals.push_back(llabs(x));
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int n = vals.size();

    auto getIdx = [&](long long v)->int{
        return lower_bound(vals.begin(), vals.end(), v) - vals.begin() + 1;
    };

    SegTree seg;
    seg.init(n);
    Fenwick fen;
    fen.init(n);

    vector<int> presentCount(n+1, 0);

    long long totalCount = 0;

    string out;
    out.reserve(Q*7);

    for(int qi=0; qi<Q; qi++){
        long long x = X[qi];
        if(x>0){
            int idx = getIdx(x);
            long long v = x;
            if(presentCount[idx]==0){
                if(idx-1>=1){
                    seg.rangeAdd(1,1,n,1,idx-1,1);
                }
                long long g = v + (totalCount - fen.query(idx));
                seg.pointSet(1,1,n,idx, g);
                fen.update(idx, 1);
            } else {
                if(idx-1>=1) seg.rangeAdd(1,1,n,1,idx-1,1);
                fen.update(idx,1);
            }
            presentCount[idx]++;
            totalCount++;
        } else {
            long long v = -x;
            int idx = getIdx(v);
            presentCount[idx]--;
            totalCount--;
            fen.update(idx, -1);
            if(presentCount[idx]==0){
                if(idx-1>=1) seg.rangeAdd(1,1,n,1,idx-1,-1);
                seg.pointDeactivate(1,1,n,idx);
            } else {
                if(idx-1>=1) seg.rangeAdd(1,1,n,1,idx-1,-1);
            }
        }

        long long best = seg.globalMin();
        long long candidateZero = totalCount;
        best = min(best, candidateZero);

        out += to_string(best);
        if(qi+1<Q) out += ' ';
    }
    out += '\n';
    cout << out;

    return 0;
}
