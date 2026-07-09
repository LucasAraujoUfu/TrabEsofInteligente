#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

// Suffix Array - O(N log N)
vector<int> buildSA(const vector<int>& s) {
    int n = s.size();
    vector<int> sa(n), rank_(n), tmp(n);
    iota(sa.begin(), sa.end(), 0);
    rank_ = s;

    for (int gap = 1; gap < n; gap <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rank_[a] != rank_[b]) return rank_[a] < rank_[b];
            int ra = a + gap < n ? rank_[a + gap] : -1;
            int rb = b + gap < n ? rank_[b + gap] : -1;
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i-1]] + (cmp(sa[i-1], sa[i]) ? 1 : 0);
        rank_ = tmp;
    }
    return sa;
}

// Kasai LCP Array - O(N)
vector<int> buildLCP(const vector<int>& s, const vector<int>& sa) {
    int n = s.size();
    vector<int> rank_(n), lcp(n, 0);
    for (int i = 0; i < n; i++) rank_[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (rank_[i] > 0) {
            int j = sa[rank_[i] - 1];
            while (i + h < n && j + h < n && s[i+h] == s[j+h]) h++;
            lcp[rank_[i]] = h;
            if (h > 0) h--;
        }
    }
    return lcp;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> V(N);
    for (int i = 0; i < N; i++) cin >> V[i];

    // Caso N == 1: lcp(1,1) = 1, E = 1/1
    if (N == 1) {
        cout << "1/1\n";
        return 0;
    }

    vector<int> sa = buildSA(V);
    vector<int> lcp = buildLCP(V, sa);

    // Soma de lcp(i,j) para todos os pares (i,j) incluindo i==j
    // lcp(i,i) = N - sa[i] (comprimento do sufixo)
    // Para pares distintos no SA, usamos pilha monotônica:
    // soma_lcp_pares = sum over all pairs (i<j) of min(lcp[i+1..j])
    // Total = 2 * soma_pares + soma_diagonais

    // Soma das diagonais (i == j): cada par (i,i) contribui com (N - i)
    // Na verdade lcp(i,i) = comprimento do sufixo começando em i = N - i
    ll diag = 0;
    for (int i = 0; i < N; i++) diag += (N - i);

    // Soma de min(lcp[l+1..r]) para todos 0<=l<r<=N-1 no SA
    // Usando pilha monotônica: contribuição de lcp[k] como mínimo
    // para pares (l, r) onde k é o índice do mínimo
    // = lcp[k] * (left_count) * (right_count)
    // onde left_count = distância até próximo elemento menor à esquerda
    // e right_count = distância até próximo elemento menor ou igual à direita

    // lcp tem índice 0..N-1, lcp[0]=0 sempre
    // Trabalhar com lcp[1..N-1] para pares de sufixos adjacentes no SA

    vector<int>& h = lcp; // h[i] = lcp entre sa[i-1] e sa[i]

    // Pilha monotônica para calcular sum of range minimums
    // Para cada posição k (1..N-1), conta quantos pares (l,r) com l<r
    // têm h[k] como o mínimo estrito
    // left[k] = número de posições à esquerda de k até o último valor < h[k]
    // right[k] = número de posições à direita de k até o próximo valor <= h[k]

    lll sum_pairs = 0;
    // stack stores (value, count)
    stack<pair<ll,ll>> stk;

    for (int k = 1; k < N; k++) {
        ll cnt = 1;
        while (!stk.empty() && stk.top().first >= h[k]) {
            auto [val, c] = stk.top(); stk.pop();
            // val >= h[k], esses pares agora têm h[k] como mínimo
            // contribuição já foi contada quando val foi inserido
            // Na verdade vamos usar abordagem diferente
            cnt += c;
        }
        // Para cada par (l, r) que cruza k como mínimo:
        // left_span * right_span * h[k]
        // Usamos a abordagem: ao inserir k, acumular contribuição
        stk.push({h[k], cnt});
    }

    // Recalcular com abordagem correta de soma de range min
    while (!stk.empty()) stk.pop();

    // Abordagem: soma de todos min(h[l+1..r]) para 0<=l<r<=N-1
    // Equivale a: para cada k, h[k] * (# pares onde h[k] é o mínimo)
    // Usando pilha com (valor, span_esquerdo)
    sum_pairs = 0;
    // stack: (h_val, left_span)
    vector<pair<ll,ll>> st;
    vector<ll> contrib(N, 0); // não usado diretamente

    // Método direto: dp com pilha
    // f[r] = soma de min(h[l+1..r]) para l = 0..r-1
    // f[r] = f[prev] + h[r] * left_span
    // onde prev é o índice do último elemento < h[r]

    vector<ll> f(N, 0);
    // stk2: (value, left_count) — elementos na pilha
    stack<pair<ll,ll>> stk2;

    ll running = 0;
    for (int r = 1; r < N; r++) {
        ll cnt2 = 1;
        ll add = 0;
        while (!stk2.empty() && stk2.top().first >= h[r]) {
            auto [v, c] = stk2.top(); stk2.pop();
            cnt2 += c;
            // remove contribuição de v, vai ser substituída por h[r]
            add -= v * c;
        }
        add += (ll)h[r] * cnt2;
        running += add;
        f[r] = running;
        stk2.push({h[r], cnt2});
        sum_pairs += running;
    }

    // sum_pairs = soma de min(h[l+1..r]) para todos 0<=l<r<=N-1
    // Cada par ordenado de sufixos distintos (sa[l], sa[r]) com l<r
    // contribui com min(h[l+1..r])
    // Para pares não ordenados, multiplicamos por 2
    lll total = (lll)2 * sum_pairs + (lll)diag;

    // E = total / N^2
    ll denom = (ll)N * N;
    ll numer = (ll)total; // total cabe em ll? max: N=1e5, lcp<=N, sum~N^3/6 ~ 1.6e14 ok com ll

    // Checar se total cabe em ll
    // max sum_pairs ~ N^2 * N / 2 = 5e14, diag ~ N^2/2 = 5e9 → ok com ll
    ll num2 = (ll)total;
    ll g = gcd(abs(num2), denom);
    cout << num2/g << "/" << denom/g << "\n";

    return 0;
}
