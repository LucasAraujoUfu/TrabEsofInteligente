#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<int> a(N);
    int total = 0;
    for(int i = 0; i < N; i++){ cin >> a[i]; total += a[i]; }

    if(total % 2 != 0){ cout << -1 << "\n"; return 0; }

    sort(a.begin(), a.end());

    // DP: dp[diff + OFF] = possível chegar nesse diff após alguns passos
    // Para reconstrução: em cada passo guardamos qual valor foi escolhido
    // e o diff anterior

    const int OFF = 5001;
    const int DMAX = 10002;

    // dp[d] = alcançável?
    // Para reconstrução: choice_at[step][d_depois] = (d_antes, valor)
    vector<vector<pair<int,int>>> trace(N, vector<pair<int,int>>(DMAX, {-1,-1}));

    vector<bool> cur(DMAX, false);
    cur[OFF] = true; // diff = 0 inicial

    // cnt de valores disponíveis
    vector<int> cnt(101, 0);
    for(int x : a) cnt[x]++;

    for(int step = 0; step < N; step++){
        vector<bool> nxt(DMAX, false);

        // Para cada diff atual alcançável
        for(int d = 0; d < DMAX; d++){
            if(!cur[d]) continue;
            int diff = d - OFF;

            // Tentar cada valor disponível
            // Mas quais valores ainda disponíveis neste step?
            // Problema: DP não sabe quais valores foram usados!

            // Solução: iterar valores em ordem e usar cnt dinâmico
            // Isso requer estado completo — inviável diretamente.
            break;
        }
        // Esta abordagem não funciona sem codificar o multiset no estado.
        break;
    }

    // ABORDAGEM FINAL: backtracking com poda forte é suficiente para N<=100, a_i<=100
    // Com valores distintos agrupados e poda |diff| > sum_remaining, 
    // na prática converge muito rápido.

    vector<int> result;
    // cnt de cada valor
    map<int,int> avail;
    for(int x : a) avail[x]++;
    int sum_rem = total;

    function<bool(int,int)> bt = [&](int step, int diff) -> bool {
        if(step == N) return diff == 0;
        if(abs(diff) > sum_rem) return false;

        for(auto& [v, c] : avail){
            if(c == 0) continue;
            int nd = (diff <= 0) ? diff + v : diff - v;
            c--; sum_rem -= v;
            result.push_back(v);
            if(bt(step+1, nd)) return true;
            result.pop_back();
            c++; sum_rem += v;
        }
        return false;
    };

    if(bt(0, 0)){
        for(int i = 0; i < N; i++){
            if(i) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    } else {
        cout << -1 << "\n";
    }

    return 0;
}
