#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

ll gcdll(ll a, ll b){ while(b){ a%=b; swap(a,b);} return a; }

struct SegTree {
    int n;
    vector<ll> sumCap;      // sum of cap_j (streets capacity) for active cleaners in range
    vector<ll> sumWeighted; // sum of cap_j * H_j for active cleaners in range
    vector<ll> Hval;        // H value associated with leaf index (sorted distinct H)

    void init(int n_, vector<ll>& Hsorted){
        n = n_;
        sumCap.assign(4*n, 0);
        sumWeighted.assign(4*n, 0);
        Hval = Hsorted;
    }

    void update(int node, int l, int r, int pos, ll capDelta, ll weightedDelta){
        if(l==r){
            sumCap[node]+=capDelta;
            sumWeighted[node]+=weightedDelta;
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(2*node,l,mid,pos,capDelta,weightedDelta);
        else update(2*node+1,mid+1,r,pos,capDelta,weightedDelta);
        sumCap[node]=sumCap[2*node]+sumCap[2*node+1];
        sumWeighted[node]=sumWeighted[2*node]+sumWeighted[2*node+1];
    }

    // Greedy walk: take smallest H first, accumulate cap until we reach S streets.
    // Returns (totalWeightedSum) for exactly S streets taken from leftmost-H-first ordering,
    // or -1 (via reachedS flag) if insufficient total capacity.
    // We implement via recursive walk down the tree, always going left first.
    ll remainingS;
    ll accumWeighted;
    bool possible;

    void walk(int node, int l, int r){
        if(remainingS<=0) return;
        if(sumCap[node] <= remainingS){
            // take entire subtree
            accumWeighted += sumWeighted[node];
            remainingS -= sumCap[node];
            return;
        }
        if(l==r){
            // partial take at leaf: take remainingS streets from this leaf, each costing Hval[l] time unit contributes... 
            // careful: sumWeighted[node] = cap_j*H_j aggregated; but capacity available here could come from multiple cleaners aggregated. 
            // Since we only need aggregated sums (cost is v * sum(s_i*H_i)), and all active cleaners at same H contribute the same H_j = Hval[l],
            // a partial take of 'remainingS' units still costs remainingS * Hval[l] (since all have same H at this leaf).
            ll take = remainingS;
            accumWeighted += take * Hval[l];
            remainingS -= take;
            return;
        }
        int mid=(l+r)/2;
        walk(2*node,l,mid);
        if(remainingS>0) walk(2*node+1,mid+1,r);
    }

    // returns weighted sum needed to cover S streets, or -1 if impossible (total capacity < S)
    ll greedyFill(ll S){
        remainingS = S;
        accumWeighted = 0;
        walk(1,0,n-1);
        if(remainingS>0) return -1;
        return accumWeighted;
    }
};

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll N,S,K;
    cin >> N >> S >> K;
    vector<ll> H(N), L(N), U(N);
    for(ll i=0;i<N;i++){
        cin >> H[i] >> L[i] >> U[i];
    }

    // capacity per cleaner
    vector<ll> cap(N);
    for(ll i=0;i<N;i++) cap[i] = K / H[i];

    // coordinate compress H values (only those with cap>0 matter, but let's include all for simplicity of indexing)
    vector<ll> Hsorted = H;
    sort(Hsorted.begin(), Hsorted.end());
    Hsorted.erase(unique(Hsorted.begin(), Hsorted.end()), Hsorted.end());
    int n = Hsorted.size();
    auto getIdx = [&](ll h)->int{
        return lower_bound(Hsorted.begin(), Hsorted.end(), h) - Hsorted.begin();
    };

    SegTree seg;
    seg.init(n, Hsorted);

    // events: at v = L_i/H_i -> add cleaner i; at v = U_i/H_i -> after processing this breakpoint, schedule removal (remove happens for all v' > U_i/H_i)
    // We'll process breakpoints in sorted order of v (as fraction a/H_i using __int128 cross multiplication for comparisons).

    // candidate breakpoints: (numerator a, denom H, type: is it an L-type or U-type, cleaner index)
    struct Event {
        ll num, den; // value = num/den
        int type; // 0 = add (this is L_i), 1 = removeAfter (this is U_i, meaning remove should apply for v > this value)
        int idx;
    };
    vector<Event> events;
    events.reserve(2*N);
    for(ll i=0;i<N;i++){
        if(cap[i] <= 0) continue; // cleaner can never be hired if K < H_i (cap=0)
        events.push_back({L[i], H[i], 0, (int)i});
        events.push_back({U[i], H[i], 1, (int)i});
    }

    // candidates for v to test: both L_i/H_i and U_i/H_i (only for cleaners with cap>0)
    struct Cand { ll num, den; };
    vector<Cand> candidates;
    for(ll i=0;i<N;i++){
        if(cap[i]<=0) continue;
        candidates.push_back({L[i], H[i]});
        candidates.push_back({U[i], H[i]});
    }

    if(candidates.empty()){
        cout << "*\n";
        return 0;
    }

    // Sort candidates by value ascending; compare using __int128 cross multiply
    auto cmpFrac = [](const Cand&a, const Cand&b)->bool{
        return (lll)a.num*b.den < (lll)b.num*a.den;
    };
    sort(candidates.begin(), candidates.end(), cmpFrac);
    candidates.erase(unique(candidates.begin(), candidates.end(), [](const Cand&a, const Cand&b){
        return a.num==b.num && a.den==b.den;
    }), candidates.end());

    // We need to process events in order of their v-value, interleaved with candidates.
    // Separate add-events and remove-events, each sorted by their value.
    vector<Event> addEvents, removeEvents;
    for(auto&e: events){
        if(e.type==0) addEvents.push_back(e);
        else removeEvents.push_back(e);
    }
    auto cmpEvent = [](const Event&a, const Event&b)->bool{
        return (lll)a.num*b.den < (lll)b.num*a.den;
    };
    sort(addEvents.begin(), addEvents.end(), cmpEvent);
    sort(removeEvents.begin(), removeEvents.end(), cmpEvent);

    size_t addPtr = 0, remPtr = 0;
    ll bestNum = -1, bestDen = 1; // best cost as fraction bestNum/bestDen; -1 means none found yet
    bool found = false;

    auto fracLE = [](ll anum, ll aden, ll bnum, ll bden)->bool{
        // a <= b  <=> anum*bden <= bnum*aden (assuming positive denominators)
        return (lll)anum*bden <= (lll)bnum*aden;
    };
    auto fracLT = [](ll anum, ll aden, ll bnum, ll bden)->bool{
        return (lll)anum*bden < (lll)bnum*aden;
    };

    for(auto& c : candidates){
        ll vnum = c.num, vden = c.den;
        // apply all add events with value <= v
        while(addPtr < addEvents.size() && fracLE(addEvents[addPtr].num, addEvents[addPtr].den, vnum, vden)){
            int idx = addEvents[addPtr].idx;
            int hi = getIdx(H[idx]);
            seg.update(1,0,n-1, hi, cap[idx], cap[idx]*H[idx]);
            addPtr++;
        }
        // apply all remove events with value < v (strictly less, since at v==U_i/H_i cleaner is still eligible)
        while(remPtr < removeEvents.size() && fracLT(removeEvents[remPtr].num, removeEvents[remPtr].den, vnum, vden)){
            int idx = removeEvents[remPtr].idx;
            int hi = getIdx(H[idx]);
            seg.update(1,0,n-1, hi, -cap[idx], -cap[idx]*H[idx]);
            remPtr++;
        }

        ll weightedSum = seg.greedyFill(S);
        if(weightedSum < 0) continue; // not enough capacity at this v

        // cost = v * weightedSum = (vnum/vden) * weightedSum = (vnum*weightedSum) / vden
        // Compare fractions: costNum/costDen vs bestNum/bestDen
        lll costNum = (lll)vnum * weightedSum;
        ll costDen = vden;

        if(!found){
            found = true;
            // reduce and store; but keep as __int128 temporarily, reduce with gcd later using ll where possible
            // reduce fraction
            ll g = gcdll((ll)(costNum % costDen == 0 ? costNum/costDen : 0), 0); // placeholder, do proper reduce below
            // proper reduce:
            ll cn;
            // costNum might not fit in ll in extreme cases? Let's bound: vnum<=100, weightedSum <= S*max(H)<=1e5*1e5=1e10, so costNum <= 100*1e10=1e12, fits in ll (ll is 64-bit, fine)
            cn = (ll)costNum;
            ll cd = costDen;
            ll gg = std::__gcd(cn, cd);
            bestNum = cn/gg; bestDen = cd/gg;
        } else {
            // compare costNum/costDen < bestNum/bestDen  <=> costNum*bestDen < bestNum*costDen
            if( (lll)costNum * bestDen < (lll)bestNum * costDen ){
                ll cn = (ll)costNum;
                ll cd = costDen;
                ll gg = std::__gcd(cn, cd);
                bestNum = cn/gg; bestDen = cd/gg;
            }
        }
    }

    if(!found){
        cout << "*\n";
    } else {
        cout << bestNum << " " << bestDen << "\n";
    }

    return 0;
}

