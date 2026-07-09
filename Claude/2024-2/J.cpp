#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int theta, N;
    cin >> theta >> N;

    double tan_theta = tan(theta * M_PI / 180.0);

    vector<pair<double,double>> segs;
    for(int i = 0; i < N; i++){
        double X, H;
        cin >> X >> H;
        double shadow_len = H / tan_theta;
        segs.push_back({X, X + shadow_len});
    }

    // Ordenar por início
    sort(segs.begin(), segs.end());

    double total = 0.0;
    double cur_start = -1e18, cur_end = -1e18;

    for(auto [a, b] : segs){
        if(a > cur_end){
            if(cur_end > cur_start) total += cur_end - cur_start;
            cur_start = a;
            cur_end = b;
        } else {
            cur_end = max(cur_end, b);
        }
    }
    if(cur_end > cur_start) total += cur_end - cur_start;

    cout << fixed << setprecision(5) << total << "\n";
    return 0;
}
