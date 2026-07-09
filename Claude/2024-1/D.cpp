#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

int M;
// magias agrupadas por b: magias[b] = {a1, a2, ...}
// para cada b, guarda lista de a_i's
vector<pair<int,int>> magias; // (a, b)

map<ll, ll> memo;

// v2(x): maior potência de 2 que divide x
int v2(ll x) {
    if (x == 0) return 64;
    int r = 0;
    while ((x & 1) == 0) { x >>= 1; r++; }
    return r;
}

ll dp(ll x) {
    if (x == 0) return 1;
    if (x < 0) return 0;
    auto it = memo.find(x);
    if (it != memo.end()) return it->second;

    int vx = v2(x);
    ll res = 0;

    for (auto& [a, b] : magias) {
        if (b <= vx && a <= x) {
            res = (res + dp(x - a)) % MOD;
        }
    }

    memo[x] = res;
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N >> M;

    magias.resize(M);
    for (int i = 0; i < M; i++)
        cin >> magias[i].first >> magias[i].second;

    // Remover magias duplicadas não é necessário, mas
    // podemos otimizar: agrupar por b e contar multiplicidades
    // Para cada estado x, soma sobre todas magias válidas dp(x - a_i)
    // Como M pode ser 1e5, cada estado visita M magias — pode ser lento
    // Otimização: para cada b, guardar multiset de a's
    // e para cada x, iterar apenas b <= v2(x)

    // Reagrupar
    map<int, vector<int>> por_b; // b -> lista de a's
    for (auto& [a, b] : magias)
        por_b[b].push_back(a);

    memo.clear();

    // Reescrever dp com nova estrutura
    // Limpar e usar função lambda com referência
    function<ll(ll)> solve = [&](ll x) -> ll {
        if (x == 0) return 1;
        if (x < 0) return 0;
        auto it = memo.find(x);
        if (it != memo.end()) return it->second;

        int vx = v2(x);
        ll res = 0;

        for (auto& [b, av] : por_b) {
            if (b > vx) continue;
            for (int a : av) {
                if ((ll)a <= x) {
                    res = (res + solve(x - a)) % MOD;
                }
            }
        }

        return memo[x] = res;
    };

    cout << solve(N) << "\n";
    return 0;
}
