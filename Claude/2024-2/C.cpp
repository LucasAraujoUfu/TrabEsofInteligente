#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll R, B;
    cin >> R >> B;
    string S; cin >> S;
    int n = S.size();

    vector<int> prefR(n+1,0), prefB(n+1,0);
    for(int i = 0; i < n; i++){
        prefR[i+1] = prefR[i] + (S[i]=='R');
        prefB[i+1] = prefB[i] + (S[i]=='B');
    }

    int W; cin >> W;
    while(W--){
        int L, U; cin >> L >> U;
        int lo = L-1;
        ll len = U - L + 1;

        auto eval = [&](ll i) -> ll {
            if(i < 0 || i > len) return (ll)4e18;
            ll rRi = prefR[lo+(int)i] - prefR[lo];
            ll bBi = prefB[U] - prefB[lo+(int)i];
            return max(i,R) - min(rRi,R) + max(len-i,B) - min(bBi,B);
        };

        // Ponto de saturação de rR: menor i com rR(i)>=R
        int j_rsat;
        {
            int tgt = prefR[lo] + (int)min(R,(ll)2e9);
            j_rsat = (int)(lower_bound(prefR.begin()+lo,
                           prefR.begin()+lo+(int)len+1, tgt) - prefR.begin()) - lo;
        }
        // Ponto de saturação de bB: maior i com bB(i)>=B
        int j_bsat;
        {
            int tgt = prefB[U] - (int)min(B,(ll)2e9);
            j_bsat = (int)(upper_bound(prefB.begin()+lo,
                           prefB.begin()+lo+(int)len+1, tgt) - prefB.begin()) - lo - 1;
        }

        ll ans = (ll)4e18;
        for(ll i : {0LL, len, R, len-B, R-1, len-B+1,
                    (ll)j_rsat-1,(ll)j_rsat,(ll)j_bsat,(ll)j_bsat+1}){
            ans = min(ans, eval(i));
        }
        cout << ans << "\n";
    }
    return 0;
}
